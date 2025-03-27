

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

Image *readData(char *filename) 
{
	FILE *fp = fopen(filename,"r");
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
		printf("no more memory");
		return NULL;
	}
	for(int i =0;i<pixels;i++){
		*(image->image + i) = (Color*)malloc(sizeof(Color));
		if(*(image->image + i) == NULL){
			printf("no more memory");
		return NULL;
		}
		fscanf(fp,"%hhu %hhu %hhu",&(*(image->image + i))->R,&(*(image->image + i))->G,&(*(image->image + i))->B);
	}
	//关闭文件
	fclose(fp);
	return image;
}


void writeData(Image *image)
{
	printf("P3\n%d %d\n255\n", image->cols, image->rows);
	Color** p = image->image;
	for (int i = 0; i < image->rows; i++) {
		for (int j = 0; j < image->cols - 1; j++) {
			printf("%3hhu %3hhu %3hhu   ", (*p)->R, (*p)->G, (*p)->B);
			p++;
		}
		printf("%3hhu %3hhu %3hhu\n", (*p)->R, (*p)->G, (*p)->B);
		p++;
	}
}


void freeImage(Image *image)
{
	int totpixels = image->rows * image->cols;
	for(int i=0;i<totpixels;i++){
		free(*(image->image + i));
	}
	free(image->image);
	free(image);
}
