/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE *fp = fopen(filename,'r');
	if(fp == NULL){
		printf("error,no such file %s",filename);
		return NULL;
	}

	//创建image
	Image* image = (Image*) malloc(sizeof(Image));

	//读取文件头，判断是否符合格式
	char format[3];
	int maxsize;
	fscanf(fp,"%c%c",&format[0],&format[1]);
	fscanf(fp,"%u %u",&image->cols,&image->rows);
	fscanf(fp,"%d",&maxsize);
	if(format[0] != 'P' || format[1] != '3'){printf("wrong format");return NULL;}
	if(image->cols<=0 ||image->rows <=0){printf("wrong size");return NULL;}
	if(maxsize != 255){printf("wrong size");return NULL;}

	//为图像分配内存
	int pixels = image->cols * image->rows;
	image->image = (Color** )malloc(sizeof(Color*) * pixels);
	if(image->image == NULL){
		pritnf("no more memory");
		return NULL;
	}
	for(int i =0;i<pixels;i++){
		*(image->image + i) = (Color*)malloc(sizeof(Color));
		if(*(image->image + i) == NULL){
			pritnf("no more memory");
		return NULL;
		}
		fscanf(fp,"%hhu %hhu %hhu",&(*(image->image + i))->R,&(*(image->image + i))->G,&(*(image->image + i))->B);
	}
	//关闭文件
	fclose(fp);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n");
	printf("%u %u\n255",image->cols,image->rows);
	Color **img = image->image;
	for(int i=0;i<image->cols*image->rows;i++){
		Color* color = *(img+i);
		printf("%3hhd%3hhd%3hhd",color->R,color->G,color->B);
	}
}

//Frees an image
void freeImage(Image *image)
{
	int totpixels = image->rows * image->cols;
	for(int i=0;i<totpixels;i++){
		free(*(image->image+i));
	}
	free(image->image);
	free(image);
}