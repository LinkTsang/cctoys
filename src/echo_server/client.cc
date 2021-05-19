#include "client.h"
#include <iostream>

EchoClient::EchoClient() {

}


void EchoClient::run() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(9090);


  int ret = connect(sockfd, reinterpret_cast<sockaddr*>(&address), sizeof(address));
  if(ret == -1) {
    std::cerr << "connect failed!" << std::endl;
    return;
  }

  const char message[] = "Hello~!";
  write(sockfd, message, sizeof(message));

  std::cout << "[Send] " << message << std::endl;

  char buffer[80];
  ssize_t size = read(sockfd, buffer, sizeof(buffer));

  std::cout << "[Recv] " << size << " bytes: " << buffer << std::endl;

  close(sockfd);
}


int main() {
  EchoClient client;
  client.run();
}