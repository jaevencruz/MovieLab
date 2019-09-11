/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/* Modified by Mihnea Chirila for EECS 22 Fall 2018                                                            */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{
	char *InImageName = NULL, *InMovieName = NULL, *OutMovieName = NULL;
	iterableFilter filter;
	/*Check variable decide whether or not to run operation*/
	int i, filterCheck = 0,reverseCheck=0, imageCheck = 0, movieCheck = 0;
	unsigned int  numFrames = 0,width = 0, height = 0;
	float startVal = 0, endVal = 0, stepVal = 0;
	IMAGE *image = NULL;
	MOVIE *movie = NULL;	
	for(i = 1; i < argc; i++){
		/*Image Input name*/
		if(0 == strcmp(argv[i],"-i")){
			i++; 
			if (i < argc) { 
				InImageName = argv[i];
				imageCheck = 1; 
			} 
			else { 
				fputs("Missing argument for -i!\n", stderr);  
				exit(10); 
			} 
		}
		/*Check Output name*/
		else if (0 == strcmp(argv[i],"-o")){
			i++;
                        if (i < argc) {
                                OutMovieName = argv[i];

                        }
                        else {
                                fputs("Missing argument for -0!\n", stderr);
                                exit(10);
                        }

		}
		/*Movie Input*/
		else if (0 == strcmp(argv[i],"-m")){
                        i++;
                        if (i < argc) {
                                InMovieName = argv[i];
				movieCheck = 1;

                        }
                        else {
                                fputs("Missing argument for -m!\n", stderr);
                                exit(10);
                        }

                }
		/*Check number of frames*/
		else if (0 == strcmp(argv[i],"-f")){
                        i++;
                        if (i < argc) {
				sscanf(argv[i],"%d",&numFrames);
                        }
                        else {
                                fputs("Missing argument for -f!\n", stderr);
                                exit(10);
                        }

                }
		/*Image size input*/
		else if (0 == strcmp(argv[i],"-s")){
                        i++;
                        if (i < argc) {
                                sscanf(argv[i], "%dx%d", &width, &height);

                        }
                        else {
                                fputs("Missing argument for -s!\n", stderr);
                                exit(10);
                        }

                }
		/*Start value check*/
		else if (0 == strcmp(argv[i],"-start=")){
                        i++;
                        if (i < argc) {
                                sscanf(argv[i], "%f", &startVal);

                        }
                        else {
                                fputs("Missing argument for -start!\n", stderr);
                                exit(10);
                        }
                }
		/*End value check*/
		else if (0 == strcmp(argv[i],"-end=")){
                        i++;
                        if (i < argc) {
                                sscanf(argv[i], "%f", &endVal);

                        }
                        else {
                                fputs("Missing argument for -end!\n", stderr);
                                exit(10);
                        }
                }
		/*Step Value Check*/
		else if (0 == strcmp(argv[i],"-step=")){
                        i++;
                        if (i < argc) {
                                sscanf(argv[i], "%f", &stepVal);

                        }
                        else {
                                fputs("Missing argument for -step!\n", stderr);
                                exit(10);
                        }
                }
		/*Reverse Check*/
		else if (0 == strcmp(argv[i],"-reverse")){
			
			reverseCheck = 1;	
                }
		/*Hue*/
		else if (0 == strcmp(argv[i],"-hue")){
			filter = HueRotate;
			filterCheck = 1;
                }
		else if (0 == strcmp(argv[i],"-saturate")){
                        filter = Saturate;
                        filterCheck = 1;
                }
		else{
			printf("Unknown Command in index %d. Terminating Program.\n",i);
			exit(10);
		}


	}

	/*If a movie name is taken from the command line, a movie is loaded*/
	if(movieCheck==1){
		movie = LoadMovie(InMovieName,numFrames,width,height);
	}
	/*If an image name is taken from the command line, an image is loaded*/
	if(imageCheck == 1){
		image = LoadImage(InImageName);
	}
	/*If a filter is selected, a movie is made from an image with the filter*/
	if(filterCheck == 1){
		movie = doIterativeFilter(image,filter,startVal,endVal,stepVal);
	}
	/*If a reverse is in the command line, the movie is reversed*/
	if(reverseCheck == 1){
		ReverseImageList(movie->Frames);
	}
	
	/*If a movie exists or a movie was loaded, then the movie is saved and the remaining movie pointer is freed*/
	if(movie != NULL){
       		SaveMovie(OutMovieName,movie);
		DeleteMovie(movie);
	}
		//DeleteMovie(movie);
	/*If an image was loaded, it is freed*/
	if(imageCheck == 1){
		DeleteImage(image);
	}
	
}



/* EOF */
