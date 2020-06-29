/* 
 * This question is worth [20] points.
 *
 * Complete the following code so that it first forks a child and waits for it
 * to terminate.  During this time, the child process executes the binary
 * /bin/ls and passes it the argument /bin so that it correctly lists the
 * directory /bin.  All output to the standard output of the child process
 * should go to the file named ls.output.  This file should be created if it
 * does not exist with the permission 0600 and should be truncated if exists.
 * You may use any form of exec including execl. 
 *
 * ALL INCLUDE FILES YOU WILL NEED ARE INCLUDED! Do not include any other files.
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child = fork();
    struct stat stats;

    /* success, carry out child code */
    if (child == 0){
        execl("/bin/ls", "ls", "-l", (char *)0);
    }

    /* some type of error with the fork */
    else if (child < 0){
        return -1;
    }

    /* parent process will go here after the child has processed */
    else{
        int returnval;
        waitpid(child, &returnval, 0);

    }
    
    return 0;
}
