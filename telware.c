#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER "Put IP here"
#define PORT 23
#define INTERVAL 120  // secondes

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char* message = "R\n";

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error WSAStartup\n");
        return 1;
    }

    while (1) {
        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s == INVALID_SOCKET) {
            printf("Error socket\n");
            break;
        }

        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr.s_addr = inet_addr(SERVER);

        if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
            printf("Cannot connect\n");
        }
        else {
            printf("Connected.\n");
            send(s, message, (int)strlen(message), 0);
            printf("Command send.\n");
            closesocket(s);
            printf("Disconnected.\n");
        }

        Sleep(INTERVAL * 1000);
    }

    WSACleanup();
    return 0;
}
