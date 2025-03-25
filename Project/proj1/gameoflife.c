/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

int dx[] = {0,1,1,1,0,-1,-1,-1};
int dy[] = {1,1,0,-1,-1,-1,0,1};

int ring(int cur,int total){
	return (cur+total)%total;
}
//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	Color* new = (Color*)malloc(sizeof(Color));
	int isAliveR = (*(image->image + row * image->cols + col))->R == 255;
	int isAliveG = (*(image->image + row * image->cols + col))->G == 255;
	int isAliveB = (*(image->image + row * image->cols + col))->B == 255;
	int neborR = 0;
	int neborG = 0;
	int neborB = 0;
	for(int i =0;i<8;i++){
		int newrow = ring(row+dx[i],image->rows);
		int newcol = ring(col+dy[i],image->cols);
		if((*(image->image+newrow*image->cols+newcol))->R == 255){
			neborR++;
		}
		if((*(image->image+newrow*image->cols+newcol))->G == 255){
			neborG++;
		}
		if((*(image->image+newrow*image->cols+newcol))->B == 255){
			neborB++;
		}
	}
	int indexR = 9*isAliveR + neborR;
	int indexG = 9*isAliveG + neborG;
	int indexB = 9*isAliveB + neborB;

	if(rule & (1<<indexR)){
		new->R = 255;
	}
	else{
		new->R = 0;
	}
	
	if(rule & (1<<indexG)){
		new->G = 255;
	}
	else{
		new->G = 0;
	}

	if(rule & (1<<indexB)){
		new->B = 255;
	}
	else{
		new->B = 0;
	}

	return new;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image* new = (Image*)malloc(sizeof(Image));
	new->cols = image->cols;
	new->rows = image->rows;
	new->image = (Color**)malloc(sizeof(Color*) * (image->rows) * (image->cols));
	Color** p = new->image; 
	for(int row = 1;row<=image->rows;row++){
		for(int col = 1;col<=image->cols;col++){
			*p = evaluateOneCell(image,row,col,rule);
			p++;
		}
	}
	return image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	if(argc!=3){
		printf("usage: ./gameOfLife filename rule\nfilename is an ASCII PPM file (type P3) with\
maximum value 255.\nrule is a hex number beginning with 0x; Life is 0x1808.");
		return -1;
	}
	char* filename = argv[1];
	char* strrule = argv[2];
    uint32_t rule = strtol(strrule,NULL, 16);
	if(rule < 0x00000 || rule > 0x3FFFF){
		printf("wrong rule");	
		return -1;
	}

	Image* image = readData(filename);
	Image* newimg = life(image,rule);
	writeData(newimg);
	freeImage(image);
	freeImage(newimg);
	return 0;
}
