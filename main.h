#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int get_server_fd();
int handle_connections(int server_fd);
int handle_client(void *fd);
int generate_response();