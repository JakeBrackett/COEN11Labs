// Include file BMP2.H (used in MAIN3.C and MAIN4.C)
// Written by Daniel W. Lewis
// Revised Jan 2, 2015
//
// Purpose: Manipulation of 24-bit RGB BMP files using 
// functions with value and reference parameters.

#ifndef	BMP
#define IMAGE void
#endif

IMAGE			*ReadBMP24(char *filespec) ;
void			WriteBMP24(char *filespec, IMAGE *image) ;
void			FreeImage(IMAGE *image) ;

unsigned		GetRows(IMAGE *image) ;
unsigned		GetCols(IMAGE *image) ;

void			GetRGB(IMAGE *image, unsigned row, unsigned col, unsigned *red, unsigned *grn, unsigned *blu) ;
void			PutRGB(IMAGE *image, unsigned row, unsigned col, unsigned red, unsigned grn, unsigned blu) ;

void			GetHSV(IMAGE *image, unsigned row, unsigned col, double *hue, double *sat, double *val) ;
void			PutHSV(IMAGE *image, unsigned row, unsigned col, double hue, double sat, double val) ;
