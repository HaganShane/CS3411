/*
Step 6
Shane Hagan
Programming Assignment 3
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
#include <time.h>

#define READ 0
#define WRITE 1

char output[128];
int playerCount, i, childValue, x, swap, j, k, m;
int top = 0;
int deck[52] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13};

/* New addition for step 5: the shuffle function (use link to wikipedia page from assignment descrption to implement) */
void shuffleCards(){
    /* needed to add to make sure deck with shuffle everytime after time (new sequence) (manual page: 'man 3 rand') */
    srand(time(0));
    for (k = 0; k < 52; k++){
        j = k+(rand()%(52-k));
        swap = deck[k];
        deck[k] = deck[j];
        deck[j] = swap;
    }
}

/* Step 6 addition: new function below */
/* sendCards() will assign (and return) cards with an index relative to the deck after shuffling */
int sendCards(){
    int card;
    card = deck[top];
    top += 1;
    if (top >= 52){
        sprintf(output, "Deck is empty, reshuffling and distributing more cards\n");
        write(2, output, strlen(output));
        shuffleCards();
        sprintf(output, "Deck after shuffle: \n");
        write(2, output, strlen(output));
        for (m = 0; m < 52; m++){
            sprintf(output, "%d ", deck[m]);
            write(2, output, strlen(output));
        
        } 
        sprintf(output, "\n\n\n");
        write(2, output, strlen(output));
        top = 0;
    }
    return card;
}


int main(int argc, char** argv){
    /* if our argument count isn't exactly 2, give an error and return 1 */
    if (argc != 2){
        sprintf(output, "Error: Only give the player count!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* use "atoi" (man 3 atoi) to convert our argv string to a proper integer */
    /* declare the pipes and pid arrays here to satisfy the player count */
    playerCount = atoi(argv[1]);
    int c2p[playerCount][2];
    int p2c[playerCount][2];
    int cpid[playerCount];


    /* if player count is less than 2, give error message and return 1 */
    if (playerCount < 2){
        sprintf(output, "Error: Number of players must be AT LEAST 2!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* if player count is greater than 16, give error message and return 1*/
    else if(playerCount > 16){
        sprintf(output, "Error: Number of players CAN NOT exceed 16!\n");
        write(2, output, strlen(output));
        return 1;
    }

    /* Use to test to ensure the deck has shuffled (and to satisfy step 5) */
    shuffleCards();
    sprintf(output, "Deck after shuffle: \n");
    write(2, output, strlen(output));
    for (m = 0; m < 52; m++){
        sprintf(output, "%d ", deck[m]);
        write(2, output, strlen(output));
        
    } 
    sprintf(output, "\n\n\n");
    write(2, output, strlen(output));


    /* Loop through int i (from 2 to whatever playerCount is + 1) */
    for (i = 2; i < playerCount+1; i++){
        /* pipe first, then fork here.. also declare our x to be used for piping */

        pipe(c2p[i]);
        pipe(p2c[i]);
        cpid[i] = fork();
        
        /* if the cpid is = 0, go through child process (add itself to the parent process ID) */
        if (cpid[i] == 0){
            int hand[4];
            close(p2c[i][WRITE]);
            dup2(p2c[i][READ], 0);
            read(0, hand, sizeof(int)*4);
            x = hand[0] + hand[1] + hand[2] + hand[3];
            close(p2c[i][READ]);
            close(c2p[i][READ]);
            dup2(c2p[i][WRITE], 1);
            write(1, &x, sizeof(x));
            close(c2p[i][WRITE]); 
            exit(0);
        }
    }
    
    /* Parent process here (parent sends its PID to child, then recieves total back*/
    /* Step 6 update: process the cards, print out cards being sent, send to child, child will add, send back and give total message */
    /* also, project description says to change to 'ONE sizeof(int) BYTES INT' */
    for (i = 2; i < playerCount+1; i++){
        int hand[4];
        hand[0] = sendCards();
        hand[1] = sendCards();
        hand[2] = sendCards();
        hand[3] = sendCards();
        close(p2c[i][READ]);
        sprintf(output, "Dealer has dealt cards: [%d %d %d %d] to Player %d\n\n", hand[0], hand[1], hand[2], hand[3], i);
        write(2, output, strlen(output));
        write(p2c[i][WRITE], hand, sizeof(int)*4);
        close(p2c[i][WRITE]);
        close(c2p[i][WRITE]);
        read(c2p[i][READ], &x, sizeof(x));
        sprintf(output, "Player %d has a total of %d\n\n", i, x);
        write(2, output, strlen(output));
        wait(&childValue);
        close(c2p[i][READ]);


    }
    
    /* successfully return 0 */
    return 0;
}