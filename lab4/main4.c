// Main program file MAIN4.C
// Written by Daniel W. Lewis
// Revised Jan 2, 2015
//
// Purpose: Change the brightness and contrast of an image.

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "bmp2.h"

IMAGE		*AdjustBrightness(IMAGE *image, double percent) ;
IMAGE		*AdjustContrast(IMAGE *image, double percent) ;

typedef struct
	{
	char	*format ;
	IMAGE	*(*function)() ;
	double	param ;
	} OPTION ;

OPTION		*GetOption(int argc, char **argv, OPTION options[]) ;
void		DisplayImage(char *filespec, char *format, ...) ;

int main(int argc, char **argv)
	{
	char *src_filespec, *dst_filespec ;
	static OPTION options[] =
		{
		{"Brightness (%.1f)",	AdjustBrightness,	  120},
		{"Contrast (%.1f)",		AdjustContrast,		  150},
		{NULL,					NULL,				    0}
		} ;
	OPTION *option ;
	IMAGE *image ;

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

IMAGE *AdjustBrightness(IMAGE *image, double percent)
{
    int row, col, brightness;
    unsigned rows, cols, red, blu, grn;
    rows = GetRows(image);
    cols = GetCols(image);
    brightness = (int)(255*(percent-100)/100);
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols;col++){
            GetRGB(image, row, col, &red, &grn, &blu);
            red += brightness;
            if(red>255) red = 255;
            blu += brightness;
            if(blu > 255) blu = 255;
            grn += brightness;
            if(grn > 255) grn = 255;
            PutRGB(image, row, col, red, grn, blu);
        }
    }
    return image;
}

IMAGE *AdjustContrast(IMAGE *image, double percent)
{
    int row, col, dist_red, dist_blu, dist_grn;
    unsigned rows, cols, red, blu, grn;
    rows = GetRows(image);
    cols = GetCols(image);
    percent /= 100;
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols;col++){
            GetRGB(image, row, col, &red, &grn, &blu);
            dist_red = ((int)red - 128)*percent;
            // check if the distance from 128 is greater than 128
            if(dist_red< -128) dist_red = -128;
            if(dist_red > 127) dist_red = 127;
            dist_grn = ((int)grn - 128)*percent;
            // check again for grn
            if(dist_grn < -128) dist_grn = -128;
            if(dist_grn > 127) dist_grn = 127;
            dist_blu = ((int)blu - 128)*percent;
            // check again for blu
            if(dist_blu < -128) dist_blu = -128;
            if(dist_blu > 127) dist_blu = 127;
            red = (128 + dist_red);
            grn = (128 + dist_grn);
            blu = (128 + dist_blu);
            PutRGB(image, row, col, red, grn, blu);
        }
    }
    return image;
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

