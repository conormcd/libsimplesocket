#include <arpa/inet.h>
#include <unistd.h>

#include "libsimplesocket.h"

/*
 * Close a socket. This is just a thin wrapper around close(2).
 *
 * Parameters:
 *
 * socket The socket to close.
 *
 * Returns:
 *
 * The return value from the close(2) system call.
 *
 */
int simple_socket_close(int socket) {
    return close(socket);
}

/*
 * Create a TCP socket and connect it to the given address and port.
 *
 * Parameters:
 *
 * address The IPv4/IPv6 address of the remote host to connect to.
 * port    The port to connect to on the remote host.
 *
 * Returns:
 *
 * On succcess, the socket is returned. On failure, one of the following values
 * will be returned:
 *
 * SIMPLE_SOCKET_BAD_ADDRESS    The address failed to parse.
 * SIMPLE_SOCKET_SOCKET_FAILED  The socket(2) call failed.
 * SIMPLE_SOCKET_CONNECT_FAILED The connect(2) call failed.
 */
int simple_socket_connect(const char* address, int port) {
    int family;
    int sock;
    struct sockaddr_in host;
    struct sockaddr_in6 host6;

    // inet_pton(3)
    if (inet_pton(AF_INET, address, &host.sin_addr.s_addr) == 1) {
        family = AF_INET;
        host.sin_family = family;
        host.sin_port = htons(port);
    } else if (inet_pton(AF_INET6, address, &host6.sin6_addr.s6_addr) == 1) {
        family = AF_INET6;
        host6.sin6_family = family;
        host6.sin6_port = htons(port);
    } else {
        return SIMPLE_SOCKET_BAD_ADDRESS;
    }

    // socket(2)
    if ((sock = socket(family, SOCK_STREAM, 0)) == -1) {
        return SIMPLE_SOCKET_SOCKET_FAILED;
    }

    // connect(2)
    int cr = -1;
    if (family == AF_INET) {
        cr = connect(sock, (struct sockaddr*)(&host), sizeof(struct sockaddr_in));
    } else if (family == AF_INET6) {
        cr = connect(sock, (struct sockaddr*)(&host6), sizeof(struct sockaddr_in6));
    }
    if (cr != 0) {
        close(sock);
        return SIMPLE_SOCKET_CONNECT_FAILED;
    }

    return sock;
}
