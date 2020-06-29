/*
Step 3
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

/* set our global variables here */
char output[256];
char buffer[1024];
const char path[] = "/usr/bin/sort";
char *envp[] = {NULL};
pid_t cpid;

int main(int argc, char **argv){
    int i;
    /* get the value for child pid's, malloc for size of arguments --- BE SURE TO FREE AT END */

    /* make sure we have an appropriate number of arguments */
    if (argc < 1){
        sprintf(output, "Error: Not enough arguments were given!\n");
        write(2, output, strlen(output));
        return 1;
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
    }

    /*  return 0 upon success*/
    return 0;
}