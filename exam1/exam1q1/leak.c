/* 
 * This question is worth [10] points.
 *
 * The following program has at least one memory leak. Correct the code so that
 * the program no longer contains any memory leaks.
 *
 * Do not change the functionality of the program. YOU MAY ONLY ADD/REMOVE
 * CALLS TO free() to fix the memory leaks! You can find out what the program
 * does by running it and examining the code (it will produce the correct
 * output despite the memory leak).
 *
 * Requirements:
 * 1. The program functionality is not changed.
 * 2. All allocated memory is freed.
 * 3. No code is changed other than added/removed calls to free().
 * 4. The program completes without any memory errors
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SEGMENT 5

int main(){

  char *buf,*temp,ch;
  int  i,done,nsegments,len;

  buf=malloc(SEGMENT+1);
  if (buf==NULL) exit(1);
  done=0;nsegments=1;len=0;
  read(0,&ch,1);
  while (!done) {
    i=0;
    while ((i < SEGMENT) && (ch != '\n')){
      buf[len]=ch;read(0,&ch,1);i++;len++;
    }
    if ((i==SEGMENT)&&(ch!='\n')){
      nsegments++;
      temp=buf;
      buf=malloc(nsegments*SEGMENT + 1);
      if (buf==NULL) exit(1);
      strncpy(buf,temp,(nsegments-1)*SEGMENT);
    } else {done=1;}
  }
  buf[len]='\0';
  printf("Read buf <%s>\n",buf);
  free(buf);
  /*free(temp);*/

  return 0;
}
