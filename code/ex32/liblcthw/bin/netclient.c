#undef NDEBUG
#include <stdlib.h>
#include <sys/select.h>
#include <stdio.h>
#include <lcthw/ringbuffer.h>
#include <lcthw/dbg.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

struct tagbstring NL = bsStatic("\n");
struct tagbstring CRLF = bsStatic("\r\n");

int nonblock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    check(flags >= 0, "Invalid flags on nonblock.");

    int rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    check(rc == 0, "Can't set nonblocking.");

    return 0;
error:
    return -1;
}

int client_connect(char *host, char *port)
{
    int rc = 0;
    struct addrinfo *addr = NULL;

    rc = getaddrinfo(host, port, NULL, &addr);
    check(rc == 0, "Failed to lookup %s:%s", host, port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    check(sock >= 0, "Cannot create a socket.");

    rc = connect(sock, addr->ai_addr, addr->ai_addrlen);
    check(rc == 0, "Connect failed.");

    rc = nonblock(sock);
    check(rc == 0, "Can't set nonblocking.");

    freeaddrinfo(addr);
    return sock;

error:
    freeaddrinfo(addr);
    return -1;
}

int read_some(RingBuffer *buffer, int fd, int is_socket)
{
    int rc = 0;

    if(RingBuffer_available_data(buffer) == 0) {
        buffer->start = buffer->end = 0; // reset buffer
    }

    if(is_socket) {
        rc = recv(fd, RingBuffer_starts_at(buffer), RingBuffer_available_space(buffer), 0);
    } else {
        rc = read(fd, RingBuffer_starts_at(buffer), RingBuffer_available_space(buffer));
    }

    check(rc >= 0, "Failed to read from fd: %d", fd);

    RingBuffer_commit_write(buffer, rc);

    return rc;

error:
    return -1;
}


int write_some(RingBuffer *buffer, int fd, int is_socket)
{
    int rc = 0;
    bstring data = RingBuffer_get_all(buffer);

    check(data != NULL, "Failed to get from the buffer.");
    check(bfindreplace(data, &NL, &CRLF, 0) == BSTR_OK, "Failed to replace NL.");

    if(is_socket) {
        rc = send(fd, bdata(data), blength(data), 0);
    } else {
        rc = write(fd, bdata(data), blength(data));
    }

    check(rc == blength(data), "Failed to write everything to fd: %d.", fd);
    bdestroy(data);

    return rc;

error:
    return -1;
}


// To run this:
//
//   ./bin/netclient c.learncodethehardway.org 80
//
// Then type the below two lines (with a return after)
//
//     GET /ex45.txt HTTP/1.1
//     Host: learncodethehardway.org

int main(int argc, char *argv[])
{
    fd_set allreads; // ????
    fd_set readmask; // ????

    int socket = 0;  // a file descriptor
    int rc = 0;
    RingBuffer *in_rb   = RingBuffer_create(1024 * 10);
    RingBuffer *sock_rb = RingBuffer_create(1024 * 10);

    check(argc == 3, "USAGE: netclient host port");

    socket = client_connect(argv[1], argv[2]);
    check(socket >= 0, "connect to %s:%s failed.", argv[1], argv[2]);

    FD_ZERO(&allreads);        // ??
    FD_SET(socket, &allreads); // ??
    FD_SET(0, &allreads);      // ??

    while(1) {
        printf("\nMAIN LOOP>>>>\n");

        readmask = allreads;
        rc = select(socket + 1, &readmask, NULL, NULL, NULL); // seems like this blocks. But what does it actually do?????
        check(rc >= 0, "select failed.");

        if(FD_ISSET(0, &readmask)) {
            // READ from stdin (fd=0) -> into buffer in_rb
            printf("\nread from stdin, into in_rb\n");
            rc = read_some(in_rb, 0 /* stdin */, 0);
            check_debug(rc != -1, "Failed to read from stdin.");
        }

        if(FD_ISSET(socket, &readmask)) {
            // READ from socket -> into buffer sock_rb
            printf("\nread from socket, into sock_rb\n");
            rc = read_some(sock_rb, socket, 0);
            check_debug(rc != -1, "Failed to read from socket.");
        }

        while(!RingBuffer_empty(sock_rb)) {
            // WRITE to stdout (fd=1) <- from buffer sock_rb
            printf("\nread to stdout, from sock_rb\n");
            rc = write_some(sock_rb, 1, 0);
            check_debug(rc != -1, "Failed to write to stdout.");
        }

        while(!RingBuffer_empty(in_rb)) {
            // WRITE to socket <- from buffer in_rb
            printf("\nread to socket, from in_rb\n");
            rc = write_some(in_rb, socket, 1);
            check_debug(rc != -1, "Failed to write to socket.");
        }
    }

    return 0;

error:
    return -1;
}
