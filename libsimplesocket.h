#ifndef __SIMPLE_SOCKET_H__
#define __SIMPLE_SOCKET_H__ 1

#define SIMPLE_SOCKET_BAD_ADDRESS -1
#define SIMPLE_SOCKET_SOCKET_FAILED -2
#define SIMPLE_SOCKET_CONNECT_FAILED -3

int simple_socket_close(int);
int simple_socket_connect(const char*, int);

#endif

