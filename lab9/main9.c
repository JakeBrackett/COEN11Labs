// Main program file MAIN9.C
// Written by:
// Daniel W. Lewis (dlewis@scu.edu)
// Computer Engineering Department
// Santa Clara University
// Revised Jan 2, 2015
//
// Purpose: Create and manipulate a linked list of audio segments

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "wav.h"

typedef struct LIST_TAG
	{
	struct LIST_TAG	*nextnode ;
	AUDIO			*segment ;
	} LIST ;

LIST *	CreateList(AUDIO *segment1, AUDIO *segment2, AUDIO *segment3) ;
AUDIO *	CombineSegments(LIST *list) ;

void DisplayAudio(char *filespec) ;

int main(int argc, char **argv)
	{
	AUDIO *src, *dst, *part1, *part2, *part3 ;
	char *src_filespec, *dst_filespec ;
	unsigned one_third ;
	LIST *list ;

	if (argc != 3)
		{
		fprintf(stderr, "Usage: %s src-file dst-file\n", argv[0]) ;
		exit(255) ;
		}

	src_filespec = argv[1] ;
	dst_filespec = argv[2] ;

	src = ReadWAV16(src_filespec) ;
	one_third = src->num_samples / 3 ;

	part1 = CopySegment(src, 0, one_third) ;
	part2 = CopySegment(src, one_third + 1, 2*one_third) ;
	part3 = CopySegment(src, 2*one_third, src->num_samples - 1) ;

	list  = CreateList(part1, part2, part3) ;
	dst   = CombineSegments(list) ;

	WriteWAV16(dst_filespec, dst) ;
	DisplayAudio(dst_filespec) ;

	return 0 ;
	}

LIST *CreateList(AUDIO *segment1, AUDIO *segment2, AUDIO *segment3){
    AUDIO *segarray[] = {segment1, segment2, segment3};
    LIST *head, *node1, *node2, *node3;

    if((node1 = (LIST *)malloc(sizeof(LIST))) == NULL) exit(255);
    if((node2 = (LIST *)malloc(sizeof(LIST))) == NULL) exit(255);
    if((node3 = (LIST *)malloc(sizeof(LIST))) == NULL) exit(255);
    head = node1;
    
    node1->segment = segarray[0];
    node1->nextnode = node2;
    
    node2->segment = segarray[1];
    node2->nextnode = node3;
    
    node3->segment = segarray[2];
    node3->nextnode = NULL;
    
    return head;
}

AUDIO *CombineSegments(LIST *list){
    LIST *pnode = list, *next_node;
    AUDIO *combined = pnode->segment;
    pnode = pnode->nextnode;
    while(pnode != NULL){
        combined = InsertSegment(combined, pnode->segment, combined->num_samples-1);
        pnode = pnode->nextnode;
    }
    //delete list
    pnode = list;
    next_node = NULL;
    while(pnode != NULL){
        next_node = pnode->nextnode;
        free(pnode);
        pnode = next_node;
        
    }
    list = NULL;
    return combined;
}

void DisplayAudio(char *filespec)
	{
	char progspec[200], command[1000], *program_files ;
	struct stat filestat ;

#if defined(_WIN32)
	program_files = getenv("ProgramFiles(x86)") ;
	if (program_files == NULL) program_files = getenv("C:\\Program Files") ;
	if (program_files == NULL) return ;

	sprintf(progspec, "%s\\Audacity\\audacity.exe", program_files) ;
	if (stat(progspec, &filestat) != 0) return ;
	if ((filestat.st_mode & S_IFREG) == 0) return ;

	sprintf(command, "\"%s\" %s", progspec, filespec) ;
#elif defined(__unix)
	sprintf(command, "vlc \"%s\"", filespec) ;
#elif defined(__APPLE__)
	sprintf(command, "/Applications/VLC.app/Contents/MacOS/VLC \"%s\"", filespec) ;
#endif 
	system(command) ;
	}
