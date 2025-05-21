#include "select_tcp_server.hpp"

int main(int argc, char const *argv[]) {
  SelectTcpServer select_tcp_server;
  select_tcp_server.StartServer();
  return 0;
}
