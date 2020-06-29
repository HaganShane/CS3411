/*
Step 1
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

    /*
    else{
        testing to make sure the argument returns properly here 
        sprintf(output, "argv is: %d\n", playerCount);
        write(2, output, strlen(output));
    }*/

    /* Loop through int i (from 2 to whatever playerCount is + 1) */
    for (i = 2; i < playerCount+1; i++){
        /* fork here */
        cpid = fork();

        /* if the cpid is = 0, go through child process (just print pid for now) */
        if (cpid == 0){
            sprintf(output, "For child %d, the PID is: %d\n", i, getpid());
            write(2, output, strlen(output));
        }

        /* else if cpid > 0, go through parent process (just wait for now) */
        else if (cpid > 0){
            wait(&childValue);
            exit(0);
        }
    }

    
    /* successfully return 0 */
    return 0;
}