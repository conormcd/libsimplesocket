#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "libsimplesocket.h"

int main() {
    int sock;

    const char* ipv4_addr = "127.0.0.1";
    const char* ipv6_addr = "::1";
    int good_port = 22;
    int bad_port = 12345;

    // Try a successful connection
    sock = simple_socket_connect(ipv4_addr, good_port);
    assert(sock >= 0);
    assert(simple_socket_close(sock) == 0);

    // Try connecting to a port that isn't open.
    sock = simple_socket_connect(ipv4_addr, bad_port);
    assert(sock == SIMPLE_SOCKET_CONNECT_FAILED);
    assert(errno == ECONNREFUSED);
    assert(close(sock) == -1);
    assert(errno == EBADF);

    // IPv6 tests
    if (getenv("SKIP_IPV6_TESTS") == NULL) {
        // Try a successful connection over IPv6
        sock = simple_socket_connect(ipv6_addr, good_port);
        assert(sock >= 0);
        assert(simple_socket_close(sock) == 0);

        // Try connecting over IPv6 to a port that isn't open.
        sock = simple_socket_connect(ipv6_addr, bad_port);
        assert(sock == SIMPLE_SOCKET_CONNECT_FAILED);
        assert(errno == ECONNREFUSED);
        assert(close(sock) == -1);
        assert(errno == EBADF);
    }
}
