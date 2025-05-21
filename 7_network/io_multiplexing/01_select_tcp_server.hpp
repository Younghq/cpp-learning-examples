#pragma once
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/** select概括
 * select其实就是作为一种内核态与用户态之间的I/O事件通知中间件而存在
 * 是操作系统提供的一种系统调用，作为用户程序与内核之间的事件代理
 * 负责：
 *  ​收集​：应用程序关注的多个文件描述符（fd）的I/O状态需求（可读/可写/异常）。
 *  过滤​：内核监控这些fd，​仅返回真正发生事件的fd，避免应用程序盲目轮询。
 *  同步​：通过fd_set结构在用户态和内核态之间传递事件状态。
 * select 只有水平触发
 */

constexpr auto SERVER_PORT = 8099;
constexpr auto MAX_CLIENTS = 10;
constexpr auto BUFFER_SIZE = 1024;

/** 操作fd_set的宏
 * FD_ZERO(fd_set *set);         清空集合
 * FD_SET(int fd, fd_set *set);  添加fd到集合
 * FD_CLR(int fd, fd_set *set);  从集合移除fd
 * FD_ISSET(int fd, fd_set *set);检查fd是否在集合中
 */

class SelectTcpServer {
private:
  int server_fd_ = -1; // 服务器套接字文件描述符
  int client_fds_[MAX_CLIENTS]; // 客户端套接字数组（使用int类型避免类型问题）
  fd_set read_fds_;                   // select监控的读事件集合
  int max_fd_ = -1;                   // 当前监控的最大文件描述符
  struct sockaddr_in server_addr_ {}; // 服务器地址信息
  char server_buffer_[BUFFER_SIZE]{}; // 改用char类型便于字符串操作

public:
  SelectTcpServer() {
    printf("Select tcp server\n");
    // 初始化客户端fd数组为-1（无效值）
    for (auto &fd : client_fds_)
      fd = -1;

    // 创建TCP套接字
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ < 0) {
      perror("socket");
      exit(EXIT_FAILURE);
    }

    // 设置地址重用，避免TIME_WAIT状态导致绑定失败
    int opt = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) <
        0) {
      perror("setsockopt");
      exit(EXIT_FAILURE);
    }

    // 配置服务器地址
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = INADDR_ANY;
    server_addr_.sin_port = htons(SERVER_PORT); // host => net

    // 绑定套接字到指定端口
    if (bind(server_fd_, (struct sockaddr *)&server_addr_,
             sizeof(server_addr_)) < 0) {
      perror("bind");
      exit(EXIT_FAILURE);
    }
  }

  void StartServer() {
    /* 启动内核对server_fd_进行监听，内联tcp/ip协议栈会自动处理三次握手，
    处理完成的连接会被放入内核的已完成连接队列（backlog队列） */
    if (listen(server_fd_, 5) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
    }
    printf("Select Server listening on port %d...\n", SERVER_PORT);

    while (true) {

      /* select初始化 */
      FD_ZERO(&read_fds_);            // 清空读事件集合
      FD_SET(server_fd_, &read_fds_); // 监控服务器套接字的新连接事件
      max_fd_ = server_fd_;           // 初始化当前最大fd

      /* 将上一轮新加入的客户端连接设置进读事件集合 */
      for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (client_fds_[i] > 0) {
          FD_SET(client_fds_[i], &read_fds_); // 添加fd到集合
          if (client_fds_[i] > max_fd_) {
            max_fd_ = client_fds_[i];
            /* ※ 必须更新最大套接字
            select 的第一个参数 nfds 需要设置为​最大监控的fd+
            1。内核会遍历0到nfds-1的所有文件描述符，检查它们是否在
            read_fds/write_fds中。
            */
          }
        }
      }

      /* 阻塞等待一切事件（可读|可写|异常）,select会返回已经就绪的fd总数量，
      返回值>0为就绪fd总数,=0为超时,-1为出错 */
      int active_fds =
          select(max_fd_ + 1, &read_fds_, nullptr, nullptr, nullptr);

      if (active_fds < 0) {
        perror("select");
        continue;
      }

      /* 查询主服务套接字是否有新连接到达
      1.无新连接时：select 不会将 server_fd_ 加入 read_fds_（内核未标记其可读）
      2.有新连接时：select 将 server_fd_ 置位到
      read_fds_（内核标记其可读，表示可调用 accept）
      */
      if (FD_ISSET(server_fd_, &read_fds_)) {
        HandleNewConnection();
      }

      /* 无新连接则为数据到达，进入数据处理逻辑 */
      HandleClientData();
    }
  }

  ~SelectTcpServer() {
    // 关闭所有客户端连接
    for (auto &fd : client_fds_) {
      if (fd > 0) {
        close(fd);
        fd = -1;
      }
    }
    // 关闭服务器套接字
    if (server_fd_ > 0) {
      close(server_fd_);
      server_fd_ = -1;
    }
  }

private:
  void HandleNewConnection() {
    struct sockaddr_in client_addr {};
    socklen_t addr_len = sizeof(client_addr);

    /* accept从内核的"已完成连接队列"中取出一个连接，并返回新的fd。
    当队列为空，accept默认阻塞等待新连接，但可以通过fcntl设置非阻塞模式 */
    int client_fd =
        accept(server_fd_, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
      perror("accept");
      return;
    }

    /* 将客户端套接字插入到客户端套接字数组空闲位置中，
    目前最大支持10个客户端连接 */
    for (int i = 0; i < MAX_CLIENTS; ++i) {
      if (client_fds_[i] == -1) {
        client_fds_[i] = client_fd;
        printf("New client connected: fd=%d, IP=%s:%d\n", client_fd,
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        return;
      }
    }

    /* 超出范围的客户端套接字将被移除 */
    close(client_fd);
    printf("Reject connection: Client list full\n");
  }

  void HandleClientData() {
    for (int i = 0; i < MAX_CLIENTS; ++i) {
      const int fd = client_fds_[i];
      /* 查询当前客户端套接字是否存在于读事件集合 */
      if (fd <= 0 || !FD_ISSET(fd, &read_fds_))
        continue;

      /* 进行套接字数据读取操作
      ※ read读取的并不是fd的数据，而是内核缓冲区的数据。
      1.fd即作为内核资源（内核缓冲区）的标识而存在，同时也提供着可读事件的异步通知功能
      2.数据流向为【网卡->内核缓冲区->用户缓冲区】
      3.可读数据>BUFFER_SIZE,读满返回；<BUFFER_SIZE,读可读数据并返回
      */
      const ssize_t bytes_read = read(fd, server_buffer_, BUFFER_SIZE - 1);

      /* 根据读取结果进行关闭连接或下一步操作 */
      if (bytes_read <= 0) {
        // 连接关闭或错误
        close(fd);
        client_fds_[i] = -1;
        printf("Client fd=%d disconnected\n", fd);
      }
      /* 数据处理 */
      else {
        server_buffer_[bytes_read] = '\0';
        printf("Received from fd=%d: %s", fd, server_buffer_);
        if (write(fd, server_buffer_, bytes_read) < 0) {
          perror("write");
        }
      }
    }
  }
};

// 编译命令：g++ -std=c++11 -o select_server select_server.cpp