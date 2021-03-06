/*
Step 2
Shane Hagan
Programming Assignment 1
CS3411
*/

/* !!! ONLY GOT TO PART OF STEP 2, NOT COMPLETE !!! */

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

/* add for step 2, write header function, file header and file contents (below) */
/* function to write to main header */
/* from "Ctar Details - Creating and Archive":
"The very first header in the archive should have a negative file size, 0 deleted flag and the file name must 
contain the string 'CS3411 TAR'." */
int mainHeader(int fd, char file_name[256]){
    /* run through struct parameters and set the values for size (-1 to start at file) / deleted (0 because it is not deleted) */
    hdr mainHead;
    mainHead.file_size =  -1;
    mainHead.deleted = 0;

    /* use string copy to ensure "CS3411 TAR" is there (use sizeof from project descripton) */
    strncpy(mainHead.file_name, "CS3411 TAR", sizeof(mainHead.file_name));

    /* then use string concatination to append to the file name */
    strcat(mainHead.file_name, file_name);

    /* finally, write our header to the file descriptor we took in as our parameter */
    write(fd, &mainHead, sizeof(mainHead));

    /* return 0 if successful */
    return 0;  
}  

/* function to write to file header */
/* same as mainHeader(), just change names and add extra parameter for the file size */
int fileHeader(int fd, int file_size, char file_name[256]){
    /* run through struct parameters and set the values for size (file_size) / deleted (0 because it is not deleted) */
    hdr fileHead;
    fileHead.file_size =  file_size;
    fileHead.deleted = 0;

    /* use string copy to copy the file name (use sizeof from project descripton)  */
    strncpy(fileHead.file_name, file_name, sizeof(fileHead.file_name));

    /* finally, write our header to the file descriptor we took in as our parameter */
    write(fd, &fileHead, sizeof(fileHead));

    /* return 0 if successful */
    return 0;  
} 

/* function to write the file data */
/* essentially takes the file and file descriptor, runs through loop to write the data */
int fileData(int file, int fd){
    /* declare buffer to store data and counter to keep track */
    char buffer[1024];
    int counter;

    /* set the counter equal to the read data (as an int), then loop through as it's greater than 0 */
    counter = read(fd, buffer, sizeof(buffer));
    while (0 < counter){
        /* write the buffer data to the file for as long as the counter is, then set counter again */
        write(file, buffer, counter);
        counter = read(fd, buffer, sizeof(buffer));
    }

    /* return 0 if successful */
    return 0;
}

/* function to append the given files to the archive */
void appendFiles(int argc, char **argv) {
    int fileSize, fileHead, fileContents;
    struct stat st;

    /* manual of access :
    access()  checks  whether the calling process can access the file path‐
    name. */

    // otherwise create the file using the flag, do the same writing to the file as above
    
    sprintf(output, "Archive '%s' does not exist, creating archive now with appended files!\n", argv[2]);
    write(2, output, strlen(output));
    fileHead = open(argv[2], O_WRONLY | O_CREAT, 0644);
    mainHeader(fileHead, argv[2]);
    fileContents = open(argv[3], O_RDONLY, 0644);
    stat(argv[3], &st);
    fileSize = st.st_size;
    fileHeader(fileHead, fileSize, argv[3]);
    fileData(fileHead, fileContents);
    

    sprintf(output, "Ran with -a flag!\n");
    write(2, output, strlen(output));
}

/* main part of program, will see which flag is input using the string compare function
once it figures out which is passed in, will run the respective function (append / delete / extract)
take in the given arguments when ran */
int main(int argc, char **argv)
{
    char flag;

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
        if (argc < 4){
            sprintf(output, "Error: -a flag should only take in the flag (-a), the archive file name, and the file(s) to be appended!\n");
            write(2, output, strlen(output));
            return -1;
        }
        appendFiles(argc, argv);
    }

    /* if the flag is d, run the delete function */
    if (flag == 'd'){
        if (argc != 4){
            sprintf(output, "Error: -d flag should only take in the flag (-d), archive file name, and the file to be deleted!\n");
            write(2, output, strlen(output));
            return -1;
        }
        deleteFiles(argc, argv);
    }

    /* if the flag is e, run the extract function */
    if (flag == 'e'){
        if (argc != 3){
            sprintf(output, "Error: -e flag should only take in the flag (-e) and the archive file name!\n");
            write(2, output, strlen(output));
            return -1;
        }
        extractFiles(argc, argv);
    }

    return 0;
}

