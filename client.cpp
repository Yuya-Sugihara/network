#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    cerr << "socket failure..." << endl;
    exit(1);
  }

  //サーバに接続する
  const int port = 12345;
  const char *ipAddr = "127.0.0.1";

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(ipAddr);

  connect(sock, (struct sockaddr *)&server, sizeof(server));

  char *buf;
  int n = read(sock, buf, 10);

  cout << buf << endl;
  close(sock);

  return 0;
}
