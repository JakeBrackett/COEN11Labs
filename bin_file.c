//
//  bin_file.c
//  
//
//  Created by Jacob Brackett on 3/1/15.
//
//

#include <stdio.h>

int main() {
    char x[] = "THIS IS SO STUPID";
    FILE *fh = fopen ("input.bin", "wb");
    if (fh != NULL) {
        fwrite (&x, sizeof (x), 1, fh);
        fclose (fh);
    }
}