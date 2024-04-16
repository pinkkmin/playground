#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#define SERVER_PORT 12443
#define REQUEST "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n"

int main() {
    // 初始化SSL库
    SSL_library_init();
    SSL_CTX* ctx = SSL_CTX_new(TLS_method());

    // 创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation error");
        return 1;
    }

    // 连接服务器
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection error1");
        return 1;
    }

    // 将socket包装为SSL套接字
    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);

    // 建立SSL连接
    if (SSL_connect(ssl) != 1) {
        perror("SSL_connect error");
        return 1;
    }

    // 发送请求
    SSL_write(ssl, REQUEST, strlen(REQUEST));

    // 接收服务器响应
    char buffer[4096];
    int bytes_received;
    while ((bytes_received = SSL_read(ssl, buffer, sizeof(buffer))) > 0) {
        printf("%s", buffer);
    } 

    printf("\n");

    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    close(sockfd);

    return 0;
}
