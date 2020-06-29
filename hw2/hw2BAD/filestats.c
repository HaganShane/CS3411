#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    char output[512];
    // added retvalue, userID and groupID here
    int fd, retval, userID, groupID;

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
    from man 2 lseek: 
    'Upon  successful  completion, lseek() returns the resulting offset location as
    measured in bytes from the  beginning  of  the  file.   On  error,  the  value
    (off_t) -1 is returned and errno is set to indicate the error.'
    --> meaning, if it returns -1, it will mean we've read a non-regular file, otherwise it will return the file size in bytes
    */
    // calculate return value from seek, using SEEK_END for end of file with 0 offset
    retval = lseek(fd, 0, SEEK_END);

    // get the user ID and group ID of the irregular file, if needed
    userID = getuid();
    groupID = getgid();

    // if it's = -1, its non-regular
    if (retval == -1){
        sprintf(output, "Different type of file. User ID: %d Group ID: %d\n", userID, groupID);
        write(2, output, strlen(output));
    }
    // else is regular, return the return value (which will be the file size in bytes)
    else{
        sprintf(output, "This file is regular, the file size is %d bytes\n", retval);
        write(2, output, strlen(output));
    }
    
    return 0;
}
