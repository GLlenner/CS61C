/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{	
	Color ** p = image->image;
	Color * secret = (Color*) malloc(sizeof(Color));
	p += (col + row * (image->cols));
	int LSB = ((*p)->B) & 1;
	secret->B = secret->G = secret->R = LSB * 255;
	return secret;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image* new = (Image*)malloc(sizeof(Image));
	new->cols = image->cols;
	new->rows = image->rows;
	new->image = (Color**)malloc(sizeof(Color*) * (image->rows) * (image->cols));
	Color** p = new->image; 
	for(int row = 0;row<image->rows;row++){
		for(int col = 0;col<image->cols;col++){
			*p = evaluateOnePixel(image,row,col);
			p++;
		}
	}
	return new;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	if(argc != 2){
		return -1;
	}

	Image* image = readData(argv[1]);
	Image* newimg = steganography(image);
	writeData(newimg);
	freeImage(image);
	freeImage(newimg);
	return 0;
}
