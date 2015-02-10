//
//  quiz5.c
//  
//
//  Created by Jacob Brackett on 2/8/15.
//
//

#include <stdio.h>
#include <stdlib.h>
void printint(int n);

int main(){
    int n = -1234;
    printint(n);
    putchar('\n');
    return 0;
}

void printint(int n){
    char lookup[] = "0123456789";
    if(n < 0){
        putchar('-');
        n = -n;
    }x
    if(n/10 < 10){
        putchar(lookup[n/10]);
    }
    else{
        printint(n/10);
    }
    putchar(lookup[n % 10]);
}