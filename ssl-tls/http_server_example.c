/* SPDX-License-Identifier: GPL-2.0
   Copyright (c) 2024 ohh

Description: Echo HTTP Server.

1.set server socket attribute:
   family:AF_INET
   port: DEF_PORT
   addr: XX
2. bind socket to ip:port
3. waiting for client connect use by `accept`
4. read message by `recv`
   write message by 'send'
5. close  client socket 

* Compile
* 
* gcc http_server_example.c -o http_server
*
* Run
* 
* ./http_server -p 10443
* Server listening on port 10443...
* New connection accepted from 127.0.0.1:39118
* New connection accepted from 127.0.0.1:39124
*
* Request by curl client.
* 
* curl http://localhost:10441/echo
* Echo!
* curl http://localhost:10443
* Hello World!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <signal.h>

#define BACKLOG 10
int server_socket, client_socket, port = 0;

void handle_request(int client_socket, const char *request) {
    if (strncmp(request, "GET /echo", 9) == 0) {
        char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nEcho!";
        send(client_socket, response, strlen(response), 0);
    } else {
        char response[] = "HTTP/1.1 404 Not Found\r\nContent-Length: 12\r\n\r\nHello World!";
        send(client_socket, response, strlen(response), 0);
    }
}

void signal_handle(int signum) {
    printf("releasing port...\n");
    close(server_socket);
    exit(signum);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int opt;

    // 设置信号处理函数
    signal(SIGINT, signal_handle);
    signal(SIGTERM, signal_handle);

    // 解析命令行参数
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
                return -1;
        }
    }

    if(port <= 0) {
        fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
        return -1;
    }

    // 创建套接字
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // 设置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // 将套接字绑定到指定的IP地址和端口号上
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        return -1;
    }

    // 监听连接
    if (listen(server_socket, BACKLOG) == -1) {
        perror("Listening failed");
        return -1;
    }

    printf("Server listening on port %d...\n", port);

    // 接受客户端连接并处理请求
    while (1) {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
            perror("Accepting connection failed");
            return -1;
        }

        printf("New connection accepted from %s:%d\n", 
            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // 读取客户端请求
        char request[1024];
        recv(client_socket, request, sizeof(request), 0);

        handle_request(client_socket, request);

        // 关闭与客户端的连接
        close(client_socket);
    }

    return 0;
}

