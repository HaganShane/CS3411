/*
Step 1
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

char output[256];

int main(int argc, char **argv){
    int i;

    /* make sure sufficient amount of arguments are passed */
    if (argc < 2){
        sprintf(output, "Error: Not enough arguments were given!\n");
        write(2, output, strlen(output));
    }
    /* for loop that will loop through our arguments */
    for (i = 1; i < argc; i++){
        sprintf(output, "Argument %d: %s\n", i, argv[i]);
        write(2, output, strlen(output));
    }
    
    return 0;
}