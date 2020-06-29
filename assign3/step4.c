/*
Step 4
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

#define READ 0
#define WRITE 1

char output[128];
int playerCount, i, childValue, x;



int main(int argc, char** argv){
    /* if our argument count isn't exactly 2, give an error and return 1 */
    if (argc != 2){
        sprintf(output, "Error: Only give the player count!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* use "atoi" (man 3 atoi) to convert our argv string to a proper integer */
    /* step 3 addition: declare the pipes and pid arrays here to satisfy the player count */
    playerCount = atoi(argv[1]);
    int c2p[playerCount][2];
    int p2c[playerCount][2];
    int cpid[playerCount];


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

        pipe(c2p[i]);
        pipe(p2c[i]);
        cpid[i] = fork();
        
        /* if the cpid is = 0, go through child process (step 3 will add itself to the parent process ID) */
        if (cpid[i] == 0){
            close(p2c[i][WRITE]);
            dup2(p2c[i][READ], 0);
            read(0, &x, sizeof(x));
            x += getpid();
            close(p2c[i][READ]);
            close(c2p[i][READ]);
            dup2(c2p[i][WRITE], 1);
            write(1, &x, sizeof(x));
            close(c2p[i][WRITE]); 
            exit(0);
        }
    }
    
    /* Parent process here (step 3 updated so parent sends its PID to child, then recieves total back*/
    for (i = 2; i < playerCount+1; i++){
        close(p2c[i][READ]);
        x = getpid();
        write(p2c[i][WRITE], &x, sizeof(x));
        close(p2c[i][WRITE]);
        close(c2p[i][WRITE]);
        read(c2p[i][READ], &x, sizeof(x));
        sprintf(output, "For child %d and parent, total PID is : %d\n\n", i, x);
        write(2, output, strlen(output));
        wait(&childValue);
        close(c2p[i][READ]);


    }
    
    /* successfully return 0 */
    return 0;
}