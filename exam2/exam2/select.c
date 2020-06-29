/*
 * 20 points. 
 *
 * The following program wants to print the message the user types on the
 * terminal.  However, it also wants to print an "Input delayed" message if the
 * user does not type something for 5 seconds. This is accomplished by sending
 * a signal to the process if there is no data on file descriptor 0 in 5
 * seconds.
 *
 * The function "no_message_on_descriptor(int)" is declared to provide this
 * functionality. Fill out the function. Do not modify any other part of the
 * program other than the function. The function should return 1 if nothing is
 * available to read from fd after 5 seconds, and 0 if something is available
 * to read from fd.
 *
 * Hint: You should use select()!
 *
 * Error checking is not needed, assume all your calls will succeed.
 *
 */

/* NAME: Shane Hagan */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>

int no_message_on_descriptor(int fd) {
    struct timeval timeout;
    fd_set readfd;

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;    

    FD_ZERO(&readfd);
    FD_SET(0, &readfd);

    if (select(1, &readfd, NULL, NULL, &timeout) == 0){
        return 1;
    }
    else{
        return 0;
    }
    
}

void USR1_handler() {
    printf("Input delayed, waiting...\n");
}

int main() {
    int rv;
    char buf[128];
    signal(SIGUSR1, USR1_handler);
    while (no_message_on_descriptor(0)) kill(getpid(), SIGUSR1); 
    rv = read(0, buf, 128);
    buf[rv] = 0;

    printf("User typed: %s", buf);
}
