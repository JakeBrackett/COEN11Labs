// Include file WAV.H (used in MAIN8.C, MAIN9.C and MAIN10.C)
// Written by:
// Daniel W. Lewis (dlewis@scu.edu)
// Computer Engineering Department
// Santa Clara University
// Revised Jan 2, 2015
//
// Purpose: Manipulation of 16-bit mono WAV files using 
// direct access to the internal data structures.

#include <stdint.h>

typedef int16_t	SAMPLE ;

typedef struct
	{
	unsigned		sample_rate ;
	unsigned		num_samples ;
	SAMPLE			samples[0] ;
	} AUDIO ;

AUDIO *	NewAudio(unsigned samples, unsigned rate) ;
AUDIO *	ReadWAV16(char *filespec) ;
void	WriteWAV16(char *filespec, AUDIO *audio) ;
void	FreeAudio(AUDIO *audio) ;

AUDIO *	CopySegment(AUDIO *source, unsigned frstndex, unsigned lastndex) ;
AUDIO *	InsertSegment(AUDIO *target, AUDIO *segment, unsigned at) ;
AUDIO *	DeleteSegment(AUDIO *source, unsigned frstndex, unsigned lastndex) ;

