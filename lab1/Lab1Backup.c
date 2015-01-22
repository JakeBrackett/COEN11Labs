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
int brightness = (.2126*red)+(.7152*grn)+(.0722*blu)+.5;             //that easy
return brightness;
}

IMAGE *PosterizeImage(IMAGE *image, double percent)
	{
	unsigned rows, cols, grn, blu, red, brightness;
	int k,c;
	rows = GetRows(IMAGE *image);
	cols = GetCols(IMAGE *image);
									//2nd part	
	for(k=0;k<=rows;k++){
		for(c=0;c<=cols;c++){
			red = GetRed(image, k, c);
			blu = GetGrn(image, k, c);
			grn = GetBlu(image, k, c);
			brightness=get_brightness(red,blue,grn);
			if(brightness/255 >= percent){			//replace with white
				PutRed(image, k, c, 255);
				PutGrn(image, k, c, 255);
				PutBlu(image, k, c, 255);
			}
			else {
				PutRed(image, k, c, 0);				//replace with black
				PutGrn(image, k, c, 0);
				PutBlu(image, k, c, 0);
	}

IMAGE *InvertColors(IMAGE *image)
	{
	rows = GetRows(IMAGE *image);
	cols = GetCols(IMAGE *image);

	for(k=0;k<=rows;k++){
		for(c=0;c<=cols;c++){
			red = GetRed(image, k, c);
			blu = GetGrn(image, k, c);
			grn = GetBlu(image, k, c);
			PutRed(image, k, c, 255-red);			//replace with inverse
			PutGrn(image, k, c, 255-grn);
			PutBlu(image, k, c, 255-blu);
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
