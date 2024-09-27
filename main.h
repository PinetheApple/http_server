#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>

int get_sock_fd();
int handle_client();
int build_response();