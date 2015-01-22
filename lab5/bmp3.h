// Include file BMP3.H (used in MAIN5.C and MAIN6.C)
// Written by Daniel W. Lewis
// Revised Jan 2, 2015
//
// Purpose: Manipulation of 24-bit RGB BMP files using 
// direct access to the internal data structures.

#include <stdint.h>

typedef struct
	{
	uint8_t		blu ;	// 0 to 255
	uint8_t		grn ;	// 0 to 255
	uint8_t		red ;	// 0 to 255
	} PIXEL ;

typedef struct
	{
	unsigned 	rows ;
	unsigned 	cols ;
	unsigned 	dpi ;
	PIXEL		*pxlrow[0] ;
	} IMAGE ;

IMAGE		*NewImage(unsigned rows, unsigned cols) ;
IMAGE		*ReadBMP24(char *filespec) ;
void		WriteBMP24(char *filespec, IMAGE *image) ;
void		FreeImage(IMAGE *image) ;

void		GetHSV(PIXEL *pixel, double *hue, double *sat, double *val) ;
void		PutHSV(PIXEL *pixel, double hue, double sat, double val) ;
