/*
Step 1
Shane Hagan
Programming Assignment 1
CS3411
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* global variable output */
char output[512];

/* taken directly from "program details" */
typedef struct 
{
    int file_size; /* file size in bytes */
    char deleted; /* if 1, the following file has been deleted, 0 otherwise */
    char file_name[256]; /* name of the file */
} hdr;

/* function to append the given files to the archive */
void appendFiles(int argc, char **argv) {
    sprintf(output, "Ran with -a flag!\n");
    write(2, output, strlen(output));
}

/* function to delete the given files from the archive */
void deleteFiles(int argc, char **argv) {
    sprintf(output, "Ran with -d flag!\n");
    write(2, output, strlen(output));
}

/* function to extract files from the archive */
void extractFiles(int argc, char **argv) {
    sprintf(output, "Ran with -e flag!\n");
    write(2, output, strlen(output));
}


/* main part of program, will see which flag is input using the string compare function
once it figures out which is passed in, will run the respective function (append / delete / extract)
take in the given arguments when ran */
int main(int argc, char **argv)
{
    char flag;


    if (argc < 3){
        sprintf(output, "Error: Not enough valid inputs for -a or -d flag\n");
        write(2, output, strlen(output));
        return -1;
    }

    /* check input to see if the first argument is -a, if so set flag to a */
    if (!strcmp(argv[1], "-a")){
        flag = 'a';
    }
    
    /* check input to see if the first argument is -d, if so set flag to d */
    else if (!strcmp(argv[1], "-d")){
        flag = 'd';
    }

    /* check input to see if the first argument is -e, if so set flag to e */
    else if (!strcmp(argv[1], "-e")){
        flag = 'e';
    }

    else{
        sprintf(output, "Error: Not a valid flag input\n");
        write(2, output, strlen(output));
    }
    
    /* if the flag is a, run the append function */
    if (flag == 'a'){
        appendFiles(argc, argv);
    }

    /* if the flag is d, run the delete function */
    if (flag == 'd'){
        deleteFiles(argc, argv);
    }

    /* if the flag is e, run the extract function */
    if (flag == 'e'){
        extractFiles(argc, argv);
    }

    return 0;
}

