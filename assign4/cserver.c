/*
cserver.c
Shane Hagan
Programming Assignment 4
CS3411
*/

/* 
man 2 select:
int select(int nfds, fd_set *readfds, fd_set *writefds,
    fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int newsocket, messageIn;
char output[128];
char smessage[] = { "Hello from the server!" };
char cmessage[128];


/* code below is directly from our lecture 25: sockets part 5*/
int main(){
    int ssocket_FD, conn, length, readVal;
    char ch[32] = {0};
    struct sockaddr_in s1, s2;

    ssocket_FD = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&s1, sizeof(s1));
    s1.sin_family = (short)AF_INET;
    s1.sin_addr.s_addr = htonl(INADDR_ANY);
    s1.sin_port = htons(0);
    bind(ssocket_FD, (struct sockaddr *)&s1, sizeof(s1));
    length = sizeof(s1);
    getsockname(ssocket_FD, (struct sockaddr *)&s1, &length);
    sprintf(output, "Server attempting to listen on port: %d\n", ntohs(s1.sin_port));
    write(2, output, strlen(output));

    listen(ssocket_FD, 1);
    length = sizeof(s2);
    
    while (1==1){
        conn = accept(ssocket_FD, (struct sockaddr *)&s2, &length);
        readVal = read(conn, ch, 32);
        sprintf(output, "%s", ch);
        write(2, output, strlen(output));
        sprintf(output, "\n");
        write(2, output, strlen(output));
        send(conn, smessage, strlen(smessage), 0);
    }
    
    close(conn);



    return 0;
}