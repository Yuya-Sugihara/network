#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    cerr << "socket failure..." << endl;
    exit(1);
  }

  //ディスクリプタとポートをつなぐ
  const int port = 12345;
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    cerr << "can't bind" << endl;
    exit(1);
  }

  //クライアントからの接続をまつ
  listen(sock, 5);

  //確立したコネクションからディスクリプタと生成
  struct sockaddr_in client;
  unsigned int length = sizeof(client);
  int clientSock = accept(sock, (struct sockaddr *)&client, &length);

  write(clientSock, "HELLO", 5);
  close(clientSock);

  close(sock);

  return 0;
}
