#pragma once
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

constexpr auto SERVER_PORT = 8099;
constexpr auto MAX_EVENTS = 64; // epoll_wait 最大返回事件数
constexpr auto BUFFER_SIZE = 1024;

/**
 * ​epoll接口说明​
 * ​1. 核心函数
 *  epoll_create1()：创建epoll实例
 *  epoll_ctl()：增/删/改监控的fd
 *  epoll_wait()：等待事件就绪
 * ​2. 关键结构体​
​ *  struct epoll_event {
​ *      uint32_t events;  // 事件类型（如EPOLLIN、EPOLLET）
​ *      epoll_data_t data; // 用户数据（通常存fd）
​ *  };
​ * 3. 事件类型宏​
​ *  EPOLLIN：可读
​ *  EPOLLOUT：可写
​ *  EPOLLET：边缘触发
​ *  EPOLLERR/EPOLLHUP：错误/挂起
​ *
​ * ​4. 典型流程​
​ *  epoll_create1 创建实例
​ *  epoll_ctl(EPOLL_CTL_ADD) 注册fd
​ *  epoll_wait 循环处理事件
 */

/* int epoll_create1(int flags);
 * 创建epoll实例
 * @param flags : 0 或 EPOLL_CLOEXEC（exec时关闭）
 * @return      : 成功返回epoll_fd，失败返回-1
 */

/* int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
 * 控制epoll监控列表
 * @param epfd  : epoll实例描述符
 * @param op    : EPOLL_CTL_ADD / EPOLL_CTL_MOD / EPOLL_CTL_DEL
 * @param fd    : 要操作的目标文件描述符
 * @param event : 事件配置（ADD/MOD时必需，DEL时可NULL）
 * @return      : 成功返回0，失败返回-1
 */

class EpollTcpServer {
private:
  int server_fd_ = -1;                // 服务端监听套接字
  int epoll_fd_ = -1;                 // epoll实例描述符
  struct sockaddr_in server_addr_ {}; // 服务器地址信息
  char buffer_[BUFFER_SIZE]{};        // 数据缓冲区

public:
  EpollTcpServer() {
    printf("Epoll tcp server\n");
    // 1. 创建TCP套接字
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1) {
      perror("socket");
      exit(EXIT_FAILURE);
    }

    // 设置地址重用SO_REUSEADDR选项（避免TIME_WAIT状态导致绑定失败）
    int opt = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) <
        0) {
      perror("setsockopt");
      exit(EXIT_FAILURE);
    }

    // 配置服务器地址
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = INADDR_ANY;
    server_addr_.sin_port = htons(SERVER_PORT);

    // 绑定套接字到指定端口
    if (bind(server_fd_, (struct sockaddr *)&server_addr_,
             sizeof(server_addr_)) < 0) {
      perror("bind");
      exit(EXIT_FAILURE);
    }
  }

  void StartServer() {
    /* 启动监听 */
    if (listen(server_fd_, SOMAXCONN) == -1) {
      perror("listen");
      close(server_fd_);
      exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", SERVER_PORT);

    /** 创建epoll实例，进行epoll组件的初始化
     *
     * 资源分配：
     * 创建一个 struct eventpoll 内核对象
     * 初始化红黑树（rbr）用于存储监控的 fd
     * 初始化就绪队列（rdllist）用于存放活跃事件
     *
     * 返回用户态：
     * 将epoll实例与新的fd绑定，用户可以通过fd操控实例
     */
    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
      perror("epoll_create1");
      close(server_fd_);
      exit(EXIT_FAILURE);
    }

    /* 将监听套接字server_fd_添加到epoll实例​进行监控 */
    struct epoll_event ev;
    ev.events = EPOLLIN;     // 监控可读事件（新连接）
    ev.data.fd = server_fd_; // 事件触发时返回的标识符

    /* 成功返回0，失败返回-1 */
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, server_fd_, &ev) == -1) {
      perror("epoll_ctl: listen_fd");
      close(server_fd_);
      close(epoll_fd_);
      exit(EXIT_FAILURE);
    }

    // 4. 事件循环
    struct epoll_event events[MAX_EVENTS];
    while (true) {

      /* 阻塞等待epoll_fd_实例所有就绪事件,
       * -1为最大等待时间，-1意味无限阻塞等待*/
      int nfds = epoll_wait(epoll_fd_, events, MAX_EVENTS, -1);
      if (nfds == -1) {
        perror("epoll_wait");
        break;
      }

      /* 处理就绪事件
      server_fd_是通过socket()listen()创建的监听套接字，
      唯一职责为接受accept()新连接，不参与数据通信，但起到事件通知作用

      EPOLLIN 事件是内核 ​专门设计​
      的新连接通知信号，与数据套接字完全隔离。
      */
      for (int i = 0; i < nfds; ++i) {

        /* 当事件的fd等于监听fd时，必定是新连接到来，
        epoll内核协议栈的强制规定(区分select) */
        if (events[i].data.fd == server_fd_) {
          HandleNewConnection(); // 处理新连接
        } else {
          HandleClientData(events[i].data.fd); // 处理客户端数据
        }
      }
    }
  }

private:
  void HandleNewConnection() {
    // 1. 接受新连接
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // 从已完成连接队列中取出一个连接，返回新的fd
    int client_fd =
        accept(server_fd_, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd == -1) {
      perror("accept");
      return;
    }

    /* 设置客户端套接字为非阻塞模式,边缘触发必须设置非阻塞 */
    int flags = fcntl(client_fd, F_GETFL, 0);
    fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);

    /* 将新客户端组成epoll_event，加入epoll进行监控 */
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET; // 边缘触发 + 可读事件
    ev.data.fd = client_fd;
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
      perror("epoll_ctl: client_fd");
      close(client_fd);
      return;
    }

    printf("New client connected: %s:%d (fd=%d)\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
           client_fd);
  }

  void HandleClientData(int client_fd) {
    /*  边缘触发模式（EPOLLET）下必须一次性读完连接fd的所有数据 */
    while (true) {

      /* 必须持续调用read()直到返回EAGAIN或EWOULDBLOCK，表示内核缓冲区已空。 */
      ssize_t bytes_read = read(client_fd, buffer_, BUFFER_SIZE - 1);

      /* ​非阻塞模式下，当前已经无数据可读 */
      if (bytes_read == -1) {
        /* 读取完毕*/
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
          break; // 数据已读完
        }

        /* error */
        perror("read");
        close(client_fd);
        break;

      }
      /* 读取字节为0，表示对端已关闭连接收到FIN包*/
      else if (bytes_read == 0) {
        printf("Client fd=%d disconnected\n", client_fd);
        close(client_fd);
        break;
      }
      /* 处理已经读取到用户缓冲区的数据 */
      else {
        buffer_[bytes_read] = '\0';
        printf("Received from fd=%d: %s", client_fd, buffer_);
        write(client_fd, buffer_, bytes_read); // Echo back
      }
    }
  }

public:
  ~EpollTcpServer() {
    if (server_fd_ != -1)
      close(server_fd_);
    if (epoll_fd_ != -1)
      close(epoll_fd_);
    printf("Server shutdown\n");
  }
};