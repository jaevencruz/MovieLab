/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include "IterativeFilter.h"
#include "Image.h"
#include "ImageList.h"
#include "Movie.h"
#include <assert.h>

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{	assert(image);
	MOVIE *movie = CreateMovie();
	float i;
	IMAGE *p = NULL;
	if(start > end){
		for(i = start; i >= end; i -= change){
			p = CopyImage(image);
			p = filter(p,i);
			AppendRGBImage(movie->Frames,p);
		}
	}
	else if(start < end){
                for(i = start; i <= end; i += change){
                        p = CopyImage(image);
                        p = filter(p,i);
                        AppendRGBImage(movie->Frames,p);
                }
        }
	RGB2YUVMovie(movie);
	return movie;
}

/*Apply Filter to a movie*/
/*MOVIE *doIterativeFilterMovie(MOVIE *movie, iterableFilter filter, float start, float end, float change)
{       assert(movie);
        MOVIE *new_movie = CreateMovie();
        float i;
        IMAGE *p = NULL;

	YUV2RGBMovie(movie);
	curr = movie->Frames->First;

        while(curr != NULL){

                next = curr->Next;
		if(start > end){
                	for(i = start; i >= end; i -= change){
                        	p = CopyImage(image);
                        	p = filter(p,i);
                        	AppendRGBImage(new_movie->Frames,p);
                	}
       		}
        	else if(start < end){
                	for(i = start; i <= end; i += change){
                        	p = CopyImage(image);
                       	 	p = filter(p,i);
                        	AppendRGBImage(new_movie->Frames,p);
                	}
        	}	
                curr = next;
        }

        RGB2YUVMovie(movie);
        return movie;
}*/

