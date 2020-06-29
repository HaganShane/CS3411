/*
Step 4
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


/* global variables (output to output text to terminal, directory to make directory to take in a const char) */
char output[256];
const char directory[] = "SORTED";

int main(int argc, char **argv){
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
    /* changing here for step 4, need to add a counter value, along with cpid from step 3 */
    int i;
    int childVal = 0;
    /* new for step 4: need to wait on process id with our child pid and child value counter 
    from man 2 wait, need to include sys/wait.h library! */
    for (i = 1; i < argc; i++){
        sleep(2);
        
        /* if the child value is 0, means success (from sample output) */
        if (childVal == 0){
            sprintf(output, "%s: success! (%d)\n", argv[i], childVal);
            write(2, output, strlen(output));
        }

        /* otherwise (childval is NOT 0) means failure */
        else{
            sprintf(output, "%s: failure! (%d)\n", argv[i], childVal);
            write(2, output, strlen(output));
        }
        
    }
    /* fork() not included here, we did fork in step 3, after combining it should work fully */
    
    return 0;
}