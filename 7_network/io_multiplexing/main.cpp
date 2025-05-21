// #include "01_select_tcp_server.hpp"

// int main(int argc, char const *argv[]) {
//   SelectTcpServer select_tcp_server;
//   select_tcp_server.StartServer();
//   return 0;
// }

#include "02_epoll_tcp_server.hpp"

int main(int argc, char const *argv[]) {
  EpollTcpServer epoll_tcp_server;
  epoll_tcp_server.StartServer();
  return 0;
}