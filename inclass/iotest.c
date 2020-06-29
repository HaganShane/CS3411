#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	int fd, fd2, retval;
	char c;
	char strbuf[1024];

	fd = open("testfile", O_RDWR|O_CREAT, 0644);
	fd2 = open("myfile", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if (fd == -1){
		//printf("open() failed!\n");
		return -1;
	}
	//printf("open() successful!\n");

	//lseek(fd, 2, SEEK_CUR);

	retval = read(fd, &c, 1);
	// read() correctly read a byte from a file
	while (retval > 0){
		sprintf(strbuf, "%d bytes read. Read character %c\n", retval, c);
		/*
		0 -> stdin
		1 -> stdout
		2 -> stderr
		*/
		write(fd2, strbuf, strlen(strbuf));

		if (c == 'c'){
			lseek(fd, -1, SEEK_CUR);
			c = 'g';
			write(fd, &c, 1);
		}
		retval = read(fd, &c, 1);
	}

	return 0;
}
