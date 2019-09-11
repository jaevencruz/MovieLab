/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"
#include "Image.h"
/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{	IENTRY *entry;
	entry = malloc(sizeof(IENTRY));
	if (! entry){
		perror("Out of memory! Aborting . . .");
		exit(10);
	}
	entry->List = NULL;
	entry->Next = NULL;
	entry->Prev = NULL;
	entry->RGBImage = NULL;
	entry->YUVImage = NULL;
	return entry;	
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
	assert(entry);
	if(entry->RGBImage){
		DeleteImage(entry->RGBImage);
	}
	if (entry->YUVImage){
		DeleteYUVImage(entry->YUVImage);
	}
	/*Relink entries - not done in this function*/
	/*Save code for later if needed*/
	/*if(entry->Next == NULL){
		entry->List->Last = entry->Prev;
	}
	else if(entry->Prev ==  NULL){
		entry->List->First = entry->Next;
	}
	else{
		entry->Prev->Next = entry->Next;
		entry->Next->Prev = entry->Prev;
	}*/
	free(entry);
	entry = NULL;
}

/* Create a new image list */
ILIST *CreateImageList(void)
{	ILIST *list;
	list = malloc(sizeof(ILIST));
	if(! list)
	{
		perror("Out of memory! Aborting . . .");	
		exit(10);
	}
	list->length = 0;
	list->First = NULL;
	list->Last = NULL;
	return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{	
	IENTRY *entry, *n;

	assert(list);
	entry = list->First;
	while(entry != NULL){
		n = entry->Next;
		DeleteImageEntry(entry);
		entry = n;	
	}
	free(list);
	list = NULL;	
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBImage)
{	IENTRY *entry = NULL;
	assert(list);
	assert(RGBImage);
	entry = CreateImageEntry();
	entry->RGBImage = RGBImage;
	/*If there are exiting entries*/
	if (list->Last)
	{	entry->List = list;
		entry->Next = NULL;
		entry->Prev = list->Last;
		list->Last->Next = entry;
		list->Last= entry;		
	}
	/*If there are no  existing entries*/
	else
	{	entry->List = list;
                entry->Next = NULL;
                entry->Prev = NULL;
                list->First = entry;
                list->Last= entry;
	}
	list->length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVImage)
{
	IENTRY *entry = NULL;
        assert(list);
        assert(YUVImage);
        entry = CreateImageEntry();
	entry->YUVImage = YUVImage;
        if (list->Last)
        {       entry->List = list;
                entry->Next = NULL;
                entry->Prev = list->Last;
                list->Last->Next = entry;
                list->Last= entry;
        }
        else
        {       entry->List = list;
                entry->Next = NULL;
                entry->Prev = NULL;
                list->First = entry;
                list->Last= entry;
        }
        list->length++;
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
		}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->length = newFrameNum;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{	assert(list); 
	IENTRY *prev = NULL,*next = NULL, *curr = NULL;
	int currentFrame = 1;
	/*Initialize pointers*/
	curr = list->First;
	while(curr != NULL){
		next = curr->Next;
		curr->Next = prev;
		/*Sets the first pointer to the last one in the list*/
		if(currentFrame == 1){
			list->Last = curr;	
		}
		prev = curr;
		curr = next;
		currentFrame++;	
	}
	list->First = prev;

}























/* EOF */
