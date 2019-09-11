/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"
#include "ImageList.h"
#include "Image.h"

/*Range check for RGB/YUV Values*/
int clip(int x){
	if(x<0){
		x = 0;
	}
	else if (x > 255){
		x = 255;
	}
	return x;
}

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{	MOVIE *movie;
	movie = malloc(sizeof(MOVIE));
	if (! movie){
                perror("Out of memory! Aborting . . .");
                exit(10);
        }
	movie->Frames = NULL;
	movie->Frames = CreateImageList();
	return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	if(movie){
		DeleteImageList(movie->Frames);
	}
	free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{	assert(movie);
	unsigned int height = MovieHeight(movie), width = MovieWidth(movie);	
        int i,j;
        int Y,U,V,R,G,B,C,D,E;
        /*This should work*/
        /******************/
	IENTRY *curr = NULL, *next = NULL;
        curr = movie->Frames->First;
        while(curr != NULL){
		next = curr->Next;
                curr->RGBImage = CreateImage(width,height);
                for (i = 0;i<width;i++){
                        for(j = 0;j<height;j++){
                                Y = GetPixelY(curr->YUVImage,i,j);
                                U = GetPixelU(curr->YUVImage,i,j);
                                V = GetPixelV(curr->YUVImage,i,j);
				C = Y-16;
				D = U -128;
				E = V - 128;
                                R=clip(( 298 * C + 409 * E + 128) >> 8);
                                G=clip(( 298 * C -100 * D -208 * E + 128) >> 8) ;
                                B=clip(( 298 * C + 516 * D + 128) >> 8);
                                SetPixelR(curr->RGBImage,i,j,R);
                                SetPixelG(curr->RGBImage,i,j,G);
                                SetPixelB(curr->RGBImage,i,j,B);
                        }
                }
		DeleteYUVImage(curr->YUVImage);
		curr->YUVImage = NULL;
                curr = next;
        }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie);
	assert(movie->Frames);
	unsigned int height = MovieHeight(movie), width = MovieWidth(movie);
	int i,j;
	int Y,U,V,R,G,B;
	/*This should work*/
	/******************/
	IENTRY *curr = NULL, *next = NULL;
	curr = movie->Frames->First;
	
	while(curr != NULL){
		next = curr->Next;		
		curr->YUVImage = CreateYUVImage(width,height);
		for (i = 0;i<width;i++){
			for(j = 0;j<height;j++){
				R = GetPixelR(curr->RGBImage,i,j);
				G = GetPixelG(curr->RGBImage,i,j);
				B = GetPixelB(curr->RGBImage,i,j);
				Y=clip((( 66*R+129*G+ 25*B+128)>>8)+ 16);
				U=clip(((-38*R-74*G+112*B+128)>>8)+128);
				V=clip(((112*R-94*G-18*B+128)>>8)+128);
				SetPixelY(curr->YUVImage,i,j,Y);
				SetPixelU(curr->YUVImage,i,j,U);
				SetPixelV(curr->YUVImage,i,j,V);
			}
		}
		/*!!Setting pointers to null very important!!*/
		DeleteImage(curr->RGBImage);
	 	curr->RGBImage = NULL;	
		curr = next;
	}	 
}

int MovieLength(const MOVIE *movie)
{
	assert(movie);
	assert(movie->Frames);
	return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{	
	int Height = 0;
	assert(movie);
	assert(movie->Frames);
	if (movie->Frames->First->RGBImage){
		Height = movie->Frames->First->RGBImage->H;	
	}
	else if(movie->Frames->First->YUVImage){
		Height = movie->Frames->First->YUVImage->H;
	}
	return Height;
}

int MovieWidth(const MOVIE *movie)
{
        assert(movie);
        assert(movie->Frames);
	int Width = 0;
        if (movie->Frames->First->RGBImage){
                Width = movie->Frames->First->RGBImage->W;
        }
        else if(movie->Frames->First->YUVImage){
                Width = movie->Frames->First->YUVImage->W;
        }
        return Width;
}

/* EOF */
