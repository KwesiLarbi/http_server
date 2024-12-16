/**
 *  Title: Building an HTTP Server v1.0.0
 *  Author: Kwesi A. Larbi
 *  Description:
 *      -> Creating an HTTP server using C that:
 *          - Accepts a connection on a port and sends back a HTTP 1.0 "200 OK response"
 *            with a HTML-encoded message
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#define PORT "6969" /* port users will connect to */
#define BACKLOG 10 /* pending connections queue will hold */

void sigchld_handler(int s);

int main(void)
{
    struct addrinfo hints, *servinfo, *p;
    struct sigaction sa; /* specifying action associated with specific signal */
    int sockfd, rv, new_fd;
    int yes = 1;

    /* load up address structs with getaddrinfo(): */
    memset(&hints, 0, sizeof hints); /* fill in block of memory with addresses */
    hints.ai_family = AF_UNSPEC; /* AF_UNSPEC = 0; will accept any address family (IPv4 or IPv6) */
    hints.ai_socktype = SOCK_STREAM; /* SOCK_STREAM = 1, reliable stream socket, tcp */
    hints.ai_flags = AI_PASSIVE; /* assign address of my local host to socket structures */

    /* if getaddrinfo returns non-zero print error w/ cause */
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    /* loop through all socket results and bind first available */
    for (p = servinfo; p != NULL; p = p->ai_next) {
        /* make socket, if -1 that means an error has occurred */
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        /* setting socket to SO_REUSEADDR, allows for reuse of local address unless error */
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setcokopt");
            exit(1);
        }

        /* assign local socket, unless error then close socket */
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    /* graciously free up allocated space */
    freeaddrinfo(servinfo);

    /* if port is NULL, there was a failure to bind so error */
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; /* reap all dead processes to prevent memory leaks*/
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("\nserver: waiting for connections...\n");
    
    // TODO: Read on the connected socket
    // TODO: Figure out how to respond
    // TODO: Write back on the connected socket
    // TODO: Close the connection
    // TODO: Go back to blocking on accept

    return 0;
}

void sigchld_handler(int s)
{
    /* waitpid() might overwrite errno, so we save and restore it: */
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}