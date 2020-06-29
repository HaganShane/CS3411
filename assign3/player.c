/*
Player
Shane Hagan
Programming Assignment 3
CS3411
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(argc, char** argv){
    int hand[4];
    int total;

    /* infinite loop */
    while(1){
        read(0, hand, sizeof(int)*4);
        total = hand[0] + hand[1] + hand[2] + hand[3];
        write(1, &total, sizeof(int)*4);
    }
    exit(0);
}