/*
step1-client.c
Shane Hagan
Programming Assignment 4
CS3411
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int csocket_FD, messageIn, conn, length;
struct sockaddr_in c_in, c_in2;
char cmessage[] = { "Hello world!" }, smessage[32] = {0}, output[128], ch;
unsigned short port;

int main(int argc, char **argv){
    port = atoi(argv[2]);

    csocket_FD = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *)&c_in, sizeof(c_in));
    c_in.sin_family = (short)AF_INET;
    c_in.sin_port = htons(port);

    length = sizeof(c_in2);
    /* send the message */
    connect(csocket_FD, (struct sockaddr *)&c_in, sizeof(c_in));
    send(csocket_FD, cmessage, strlen(cmessage), 0);
    messageIn = read(csocket_FD, smessage, 32);
    sprintf(output, "%s", smessage);
    write(2, output, strlen(output));
    sprintf(output, "\n");
    write(2, output, strlen(output));

    return 0;
}