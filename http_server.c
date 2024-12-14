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

#define PORT 6969

int main()
{
    struct addrinfo hints, *res;
    int sockfd;

    // load up address structs with getaddrinfo():
    memset(&hints, 0, sizeof hints); // fill in block of memory with addresses
    hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, &hints, &res);

    // make a socket
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    bind(sockfd, res->ai_addr, res->ai_addrlen);

    // TODO: Listen on the address
    // TODO: Block on Accept until a connection is made
    // TODO: Read on the connected socket
    // TODO: Figure out how to respond
    // TODO: Write back on the connected socket
    // TODO: Close the connection
    // TODO: Go back to blocking on accept

    return 0;
}

