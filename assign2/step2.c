/*
Step 2
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

/* global variables (output to output text to terminal, directory to make directory to take in a const char) */
char output[256];
const char directory[] = "SORTED";

int main(int argc, char **argv){
    int i;

    /* make sure sufficient amount of arguments are passed */
    if (argc < 2){
        sprintf(output, "Error: Not enough arguments were given!\n");
        write(2, output, strlen(output));
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
    
    /* for loop that will loop through our arguments */
    for (i = 1; i < argc; i++){
        sprintf(output, "Argument %d: %s\n", i, argv[i]);
        write(2, output, strlen(output));
    }
    
    return 0;
}