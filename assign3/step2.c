/*
Step 2
Shane Hagan
Programming Assignment 3
CS3411
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

char output[128];
int playerCount, i, childValue;
pid_t cpid;

int main(int argc, char** argv){
    int fd[2];
    /* if our argument count isn't exactly 2, give an error and return 1 */
    if (argc != 2){
        sprintf(output, "Error: Only give the player count!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* use "atoi" (man 3 atoi) to convert our argv string to a proper integer */
    playerCount = atoi(argv[1]);

    /* if player count is less than 2, give error message and return 1 */
    if (playerCount < 2){
        sprintf(output, "Error: Number of players must be AT LEAST 2!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* if player count is greater than 16, give error message and return 1*/
    else if(playerCount > 16){
        sprintf(output, "Error: Number of players CAN NOT exceed 16!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* Loop through int i (from 2 to whatever playerCount is + 1) */
    for (i = 2; i < playerCount+1; i++){
        /* pipe first, then fork here.. also declare our x to be used for piping */
        pipe(fd);
        cpid = fork();
        int x;
        
        
        /* if the cpid is = 0, go through child process (just print pid for now) */
        if (cpid == 0){
            /* get the pid using our x declaration, close the reading and only write to fd[1], then close writing*/
            x = getpid();
            close(fd[0]);
            write(fd[1], &x, sizeof(x));
            close(fd[1]); 
        }
        

        /* else if cpid > 0, go through parent process (just wait for now) */
        else if (cpid > 0){
            /* close the writing end of pipe, only read from reading end, then print out the child / PID, close the reading end*/
            close(fd[1]);
            read(fd[0], &x, sizeof(x));
            sprintf(output, "For child %d, recieving PID : %d\n", i, x);
            write(2, output, strlen(output));
            close(fd[0]);
            wait(&childValue);
            exit(0);
        }
    }

    
    /* successfully return 0 */
    return 0;
}