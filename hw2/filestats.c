#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    char output[512];
    // added retvalue
    int fd, retval;
    // add the struc declaration
    struct stat fdstat;

    if (argc < 2) {
        sprintf(output, "Not enough arguments.\nUsage: filestat filename\n");
        write(2, output, strlen(output));
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        sprintf(output, "Error opening file %s\n", argv[1]);
        write(2, output, strlen(output));
        return 1;
    }

    /*
    set the file descriptor with our file descriptor buffer to be used below:
    fdstat.st_uid --> get the user ID of our buffer
    fdstat.st_gid --> get the group ID of our buffer
    fdstat.st_size --> get the file size of our buffer
    */
    fstat(fd, &fdstat);

    /*
    from manual for lseek: 
    'Upon  successful  completion, lseek() returns the resulting offset location as
    measured in bytes from the  beginning  of  the  file.   On  error,  the  value
    (off_t) -1 is returned and errno is set to indicate the error.'
    --> meaning, if it returns -1, it will mean we've read a non-regular file, otherwise it will return the file size in bytes
    */

    // calculate return value from seek, using SEEK_END for end of file with 0 offset
    retval = lseek(fd, 0, SEEK_END);


    // if it's = -1, its non-regular, print out the user ID and group ID using stat function
    if (retval == -1){
        sprintf(output, "Different type of file. User ID: %d Group ID: %d\n", fdstat.st_uid, fdstat.st_uid);
        write(2, output, strlen(output));
    }

    // else is regular, print out file size in bytes using stat function
    else{
        sprintf(output, "This file is regular, the file size is %ld bytes\n", fdstat.st_size);
        write(2, output, strlen(output));
    }
    
    return 0;
}
