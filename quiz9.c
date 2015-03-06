//
//  quiz7.c
//  
//
//  Created by Jacob Brackett on 3/1/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *finput, *foutput;
    char crlf[] = "\r\0\n\0 ", unicode_id[] = {0xFF, 0xFE}, bfr[1000];
    int bfrchar;
    if(argc != 3){
        fprintf(stderr, "Usage: progam_name binary_filename output_filename\n");
        return 1;
    }
    if((finput = fopen(argv[1], "rb")) == NULL){
        fprintf(stderr, "Could not read binary file, try again\n");
        return 2;
    }
    if((foutput = fopen(argv[2], "w")) == NULL){
        fprintf(stderr, "Could not write to output file, check permissions and space in folder\n");
        return 3;
    }
    fwrite(unicode_id, sizeof(unicode_id), 1, foutput);
    while(fscanf(finput, "%[^\r\n]%*[\r\n]", bfr) != EOF){
        for(bfrchar = 0; bfrchar < strlen(bfr); bfrchar++){
            fputc(bfr[bfrchar], foutput);
            fputc('\0', foutput);
        }
        fwrite(crlf, sizeof(crlf) - 1, 1, foutput) ;
    }
    
    fclose(finput);
    fclose(foutput);
}