#include <stdio.h>
#include <unistd.h>

int main(){
    int x,y;
    x=5;
    y = x+5;
    printf("x is %d\n", x);
    printf("y is %d\n", y);
    fork();
    printf("hello!\n");
    x = x+5;
    printf("if we add 5 to x, it is now %d\n", x);
}