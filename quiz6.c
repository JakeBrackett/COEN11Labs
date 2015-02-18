//
//  quiz6.c
//  
//
//  Created by Jacob Brackett on 2/16/15.
//
//

#include <stdio.h>
#include <pthread.h>
#include <string.h>

char str[100];

void *capFirst(void *arg){
    int i;
    str[0] = toupper(str[0]);
    for(i = 1; i < strlen(str); i++){
        if(str[i - 1] == ' '){
            str[i] = toupper(str[i]);
        }
    }
    return NULL;
}

void *capLast(void *arg){
    int i;
    str[strlen(str)-2] = toupper(str[strlen(str)-2]);
    for(i = 0; i < strlen(str); i++){
        if(str[i + 1] == ' '){
            str[i] = toupper(str[i]);
        }
    }
    return NULL;
}

int main(){
    pthread_t id[2];
    printf("Enter a lowercase string to be capitalized: ");
    fgets(str, sizeof(str), stdin);
    
    pthread_create(&id[0], NULL, capFirst, NULL);
    pthread_create(&id[1], NULL, capLast, NULL);
    
    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
    
    printf("%s\n", str);
    return 0;
}