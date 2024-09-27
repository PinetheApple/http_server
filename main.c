#include "main.h"

int main()
{
    int sock_fd = get_sock_fd();
    if (sock_fd == -1)
    {
        return -1;
    }

    return 0;
}

int get_sock_fd()
{
    int sock_fd = socket(SOCK_STREAM, AF_INET, 0);
    if (sock_fd == -1)
    {
        printf("Failed to create the socket. Error: %d\n", errno);
        return -1;
    }

    struct sockaddr_in server_addr = {
        AF_INET,
        8080,
        INADDR_ANY};

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Binding to socket to port 8080 failed!");
        return -1;
    }

    if (listen(sock_fd, 10) < 0)
    {
        perror("Failed to listen on port 8080 failed!");
        return -1;
    }

    return sock_fd;
}

int handle_client()
{

    return 0;
}

int build_response()
{

    return 0;
}