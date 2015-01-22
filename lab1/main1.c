// Main program file MAIN1.C
// Written by Daniel W. Lewis
// Revised Jan 2, 2015
//
// Purpose: Create a posterized and a negative version of an image.

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "bmp1.h"

unsigned	Brightness(unsigned red, unsigned grn, unsigned blu) ;
IMAGE		*InvertColors(IMAGE *image) ;
IMAGE		*PosterizeImage(IMAGE *image, double percent) ;

typedef struct
	{
	char	*format ;
	IMAGE	*(*function)() ;
	double	param ;
	} OPTION ;

OPTION	*GetOption(int argc, char **argv, OPTION options[]) ;
void	DisplayImage(char *filespec, char *format, ...) ;

int main(int argc, char **argv)
	{
	char *src_filespec, *dst_filespec ;
	static OPTION options[] =
		{
		{"Invert Colors",		InvertColors,		  0},
		{"Posterize (%.1f)",	PosterizeImage,		  50},
		{NULL,					NULL,				  0}
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

unsigned Brightness(unsigned red, unsigned grn, unsigned blu)
	{
        double brightness, brightness_dec;
        unsigned bright_thresh;
        brightness = (0.2126 * red) + (0.7152 * grn) + (0.0722* blu);
        brightness_dec = (brightness - (int) brightness)*10;
        if(brightness_dec >= 5.0)
            brightness++;
        bright_thresh = (unsigned) brightness;
        return bright_thresh;
    }

IMAGE *PosterizeImage(IMAGE *image, double percent)
	{
        int row,col;
        unsigned max_bright, rows, cols, red, blu, grn, brightness;
        rows = GetRows(image);
        cols = GetCols(image);
        max_bright = (percent/100)*255;
        for(int row = 0; row < rows;row++){
            for(int col = 0; col < cols; col++){
                red = GetRed(image, row, col);
                grn = GetGrn(image, row, col);
                blu = GetBlu(image, row, col);
                brightness = Brightness(red, grn, blu);
                if(brightness>max_bright)
                    red = grn = blu = 255;
                else
                    red = grn = blu = 0;
                PutRed(image, row, col, red);
                PutGrn(image, row, col, grn);
                PutBlu(image, row, col, blu);
            }
        }
        return image;
    }

IMAGE *InvertColors(IMAGE *image)
	{
        int row, col;
        unsigned rows, cols, red, blu, grn;
        rows = GetRows(image);
        cols = GetCols(image);
        for(int row = 0; row < rows; row++){
            for(int col = 0; col < cols;col++){
                red = GetRed(image, row, col);
                grn = GetGrn(image, row, col);
                blu = GetBlu(image, row, col);
                red = 255-red;
                grn = 255-grn;
                blu= 255-blu;
                PutRed(image, row, col, red);
                PutGrn(image, row, col, grn);
                PutBlu(image, row, col, blu);
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

