#include "server.h"

#include <iostream>

EchoServer::EchoServer() : server_fd_(0) {}

void EchoServer::start() {
  server_fd_ = socket(AF_INET, SOCK_STREAM, 0);

  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_address_.sin_port = htons(9090);

  int ret;

  ret = bind(server_fd_, reinterpret_cast<sockaddr*>(&server_address_),
             sizeof(server_address_));
  if (ret != 0) {
    std::cerr << "bind failed: " << ret << std::endl;
    return;
  }

  ret = listen(server_fd_, 5);
  if (ret != 0) {
    std::cerr << "listen failed: " << ret << std::endl;
    return;
  }

  for (;;) {
    int client_fd_;
    sockaddr_in client_address_;
    socklen_t client_len = sizeof(client_address_);

    client_fd_ = accept(
        server_fd_, reinterpret_cast<sockaddr*>(&client_address_), &client_len);
    if (client_fd_ == -1) {
      std::cerr << "accept failed: " << std::endl;
      return;
    }

    std::cout << "connected " << std::endl;

    ssize_t size;
    char buffer[80];
    size = read(client_fd_, buffer, sizeof(buffer));
    std::cout << "[Recv] " << size << " bytes: " << buffer << std::endl;

    const char message[] = "Hello Client!";
    size_t n = sizeof(message);
    std::cout << n << std::endl;
    size_t i = 0;
    while (i < n) {
      size = write(client_fd_, &message[i], n);
      if (size == -1) {
        std::cerr << "[Send] Failed" << std::endl;
        break;
      }
      i += size;
      std::cout << "[Send] " << i << "/" << n << " bytes: " << message
                << std::endl;
    }

    close(client_fd_);
  }
}

int main() {
  std::cout << "Server starting..." << std::endl;

  EchoServer server;
  server.start();

  std::cout << "Server stopped." << std::endl;

  return 0;
}