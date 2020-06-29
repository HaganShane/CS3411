/*
Step 5
Shane Hagan
Programming Assignment 2
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


/* global variables */
char output[128];
const char directory[] = "SORTED";
int i, childVal;
pid_t cpid;
char buffer[128];
const char path[] = "/usr/bin/sort";
char *envp[] = {NULL};

int main(int argc, char **argv){
    /* make sure sufficient amount of arguments are passed */
    if (argc < 2){
        sprintf(output, "Error: Not enough arguments were given!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* 'man 3 opendir' for open directory manual page, need to include more libraries above
    also use 'man 3 errno', include library: ENOENT: no such file or directory */
    DIR* direct = opendir(directory);
    
    /* if the directory exists, print statement saying it already exists*/
    if (direct){
        sprintf(output, "Directory 'SORTED' already exists!\n");
        write(2, output, strlen(output));
    }

    /* if the error raised is ENOENT (no such file or directory), print the statement, then create 'SORTED' directory with 
    0777 permission (which will give everyone read, write, and execute permissions) */
    else if (errno == ENOENT){
        sprintf(output, "Error: 'SORTED' Directory doesn't exist! Creating the directory now!\n");
        write(2, output, strlen(output));
        mkdir(directory, 0777);
    }

    /* loop through our arguments with the child pid's */
    /* only working with one argument -- UPDATE: needed to add child pid's, seems to go through all arguments now -- */
    for (i = 1; i < argc; i++){
        /* copy the string to buffer, then append buffer to our argument of i */
        strcpy(buffer, "SORTED/");
        strcat(buffer, argv[i]);

        /* variable for our execve() */
        char *arg[] = {"sort", "-o", buffer, argv[i], NULL};

        /* if statement for forking, ensuring it is = 0. Will execve to our sorted program, perror otherwise */
        cpid = fork();
        if (cpid == 0){
            getpid();
            execve(path, arg, envp);
            perror("error with execve");
        }

        /* parent will run, wait for child, then print out our successes and failures */
        else if (cpid > 0){
            wait(&childVal);
            sleep(2);
            /* successes */
            if (childVal == 0){
                sprintf(output, "%s: success! (%d)\n", argv[i], childVal);
                write(2, output, strlen(output));
            }

            /* failures (also set finish value for "all done") */
            else{
                sprintf(output, "%s: failure! (2)\n", argv[i]);
                write(2, output, strlen(output));
            }
        }
        
    }

    return 0;
}