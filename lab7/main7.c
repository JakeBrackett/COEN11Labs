// Main program file MAIN7.C
// Written by Daniel W. Lewis
// Revised Feb 13, 2015
//
// Purpose: Create horizontally and vertically mirrored versions of an image using multi-threading.

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include "bmp3.h"
#include <pthread.h>

void *ThreadMirrorCols(void *arg);
IMAGE *MirrorLeftRight(IMAGE *image);

void *ThreadMirrorRows(void *arg);
IMAGE *MirrorUpDown(IMAGE *image);

IMAGE * image;
typedef struct
	{
	char	*format ;
	IMAGE	*(*function)() ;
	double	param ;
	} OPTION ;

#define NUM_THREADS 8 

OPTION	*GetOption(int argc, char **argv, OPTION options[]) ;
void	DisplayImage(char *filespec, char *format, ...) ;

int main(int argc, char **argv)
	{
	char *src_filespec, *dst_filespec ;
	static OPTION options[] =
		{
		{"Mirror Left-Right",	MirrorLeftRight,	   0},
		{"Mirror Up-Down",		MirrorUpDown,		   0},
		{NULL,					NULL,				   0}
		} ;
	OPTION *option ;

	if (argc != 3 && argc != 4)
		{
		fprintf(stderr, "Usage: %s src-file dst-file {option#}\n", argv[0]) ;
		exit(255) ;
		}

	src_filespec = argv[1] ;
	dst_filespec = argv[2] ;

	image = ReadBMP24(src_filespec) ;

	if ((option = GetOption(argc, argv, options))== NULL)
		{
		fprintf(stderr, "Usage: %s src-file dst-file {option#}\n", argv[0]) ;
		exit(255) ;
		}

	image = (option->function)(image, option->param) ;

	WriteBMP24(dst_filespec, image) ;
	FreeImage(image) ;
	DisplayImage(dst_filespec, option->format, option->param) ;

	return 0 ;
	}


void *ThreadMirrorCols(void *arg)
	{
    PIXEL temp;
    if(max > min)
        {
        temp=image->pxlrow[row][min];
        image->pxlrow[row][min] = image->pxlrow[row][max];
        image->pxlrow[row][max] = temp;
        MirrorCols(image, row, min+1, max-1);
        }
    }

IMAGE *MirrorLeftRight(IMAGE *image)
	{
	   	// To be completed by student ...	
	}

void *ThreadMirrorRows(void *arg)
	{
    int col;
    PIXEL temp;
    row = *((int*) arg);
    if(max > min)
        {
        for(col = 0; col < image->cols; col++)
            {
            temp = image->pxlrow[min][col];
            image->pxlrow[min][col] = image->pxlrow[max][col];
            image->pxlrow[max][col] = temp;
            }
        MirrorRows(image, min+1, max-1);
        }
    }

IMAGE *MirrorUpDown(IMAGE *image){
    int thread, *p_row;
    *p_row = 0;
    pthread_t id[NUM_THREADS];
    for(thread = 0; thread < NUM_THREADS; thread++){
        pthread_create(id[thread], NULL, ThreadMirrorRows, (void*)p_row);
        *p_row += image->rows/NUM_THREADS
    }
}


OPTION *GetOption(int argc, char **argv, OPTION options[])
	{
	unsigned number, index = 0 ;

	// count number of options
	for (number = 0; options[number].function != NULL; number++) ;

	if (argc == 4)
		{
		sscanf(argv[3], "%u", &index) ;
		}
	else
		{
		printf("\nOptions:\n\n") ;
		for (index = 0; index < number; index++)
			{
			char title[100] ;
			sprintf(title, options[index].format, options[index].param) ;
			printf("%2d: %s\n", index + 1, title) ;
			}

		printf("\nOption? ") ;
		scanf("%u", &index) ;
		}

	return (1 <= index && index <= number) ? &options[index - 1] : NULL ;
	}

void DisplayImage(char *filespec, char *format, ...)
	{
	char progspec[200], command[1000], *program_files, title[100] ;
	struct stat filestat ;
	va_list args ;
	
	va_start(args, format) ;
	vsprintf(title, format, args) ;
	va_end(args) ;

#if defined(_WIN32)
	program_files = getenv("ProgramFiles(x86)") ;
	if (program_files == NULL) program_files = getenv("C:\\Program Files") ;
	if (program_files == NULL) program_files = "" ;

	sprintf(progspec, "%s\\IrfanView\\i_view32.exe", program_files) ;
	if (stat(progspec, &filestat) == 0 && (filestat.st_mode & S_IFREG) != 0)
		{
		sprintf(command, "\"%s\" %s /hide=7 /title=%s", progspec, filespec, title) ;
		}
	else sprintf(command, "mspaint \"%s\"\n", filespec) ;
#elif defined(__unix)
	sprintf(command, "qiv \"%s\"", filespec) ;
#elif defined(__APPLE__)
	sprintf(command, "open \"%s\"", filespec) ;
#endif 
	system(command) ;
	}

