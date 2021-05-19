#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class EchoServer {
public:
  EchoServer();
  void start();
private:
  int server_fd_;
  sockaddr_in server_address_;

  std::function<void()> callback_;
};
