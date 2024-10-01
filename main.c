#include "main.h"

#define PORT 8080
#define BUFFER_SIZE 1000000

int main() {
    int server_fd = get_server_fd();
    if (server_fd == -1) {
        return -1;
    }

    while (1) {
        handle_connections(server_fd);
    }

    return 0;
}

int get_server_fd() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Failed to create the socket!");
        return -1;
    }

    struct sockaddr_in server_addr = {AF_INET, htons(PORT), INADDR_ANY};
    if (bind(server_fd, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr)) < 0) {
        perror("Binding the socket to the port failed!");
        return -1;
    }

    if (listen(server_fd, 10) == -1) {
        perror("Failed to listen on the port!");
        return -1;
    }

    printf("Listening on port %d...\n", PORT);
    return server_fd;
}

int handle_connections(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
        perror("Failed to accept the connection!");
        return -1;
    }

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, (void *)&handle_client, (void *)&client_fd) != 0) {
        perror("Failed to create a thread to handle the connection!");
        return -1;
    }
    if (pthread_detach(thread_id) != 0) {
        perror("Failed to detach the client thread!");
    }
    return 0;
}

int handle_client(void *fd) {
    int client_fd = *(int *)fd;
    char *buffer = (char *)malloc(BUFFER_SIZE);

    if (recvfrom(client_fd, buffer, BUFFER_SIZE, 0, NULL, 0) < 0) {
        perror("Failed to received data from the client!");
    }
    printf("%s", buffer);
    return 0;
}

int generate_response() {
    char response[] =
        "HTTP/1.0 200 OK\r\n"
        "Server: webserver-c\r\n"
        "Content-type: text/html\r\n\r\n"
        "<html>hello, world</html>\r\n";
    return 0;
}