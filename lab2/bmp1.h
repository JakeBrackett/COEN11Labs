// Include file BMP1.H (used in MAIN1.C and MAIN2.C)
// Written by Daniel W. Lewis
// Revised Jan 2, 2015
//
// Purpose: Manipulation of 24-bit RGB BMP files
// using functions with only value parameters.

#ifndef	BMP
#define IMAGE void
#endif

IMAGE			*ReadBMP24(char *filespec) ;
void			WriteBMP24(char *filespec, IMAGE *image) ;
void			FreeImage(IMAGE *image) ;

unsigned		GetRows(IMAGE *image) ;
unsigned		GetCols(IMAGE *image) ;

unsigned		GetRed(IMAGE *image, unsigned row, unsigned col) ;
unsigned		GetGrn(IMAGE *image, unsigned row, unsigned col) ;
unsigned		GetBlu(IMAGE *image, unsigned row, unsigned col) ;

void			PutRed(IMAGE *image, unsigned row, unsigned col, unsigned red) ;
void			PutGrn(IMAGE *image, unsigned row, unsigned col, unsigned grn) ;
void			PutBlu(IMAGE *image, unsigned row, unsigned col, unsigned blu) ;

