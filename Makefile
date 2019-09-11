# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -Wall

OBJS = ImageList.o FileIO.o Image.o MovieIO.o MovieLab.o Movie.o IterativeFilter.o 
DEBUG_OBJS = PhotoLab_DEBUG.o FileIO_DEBUG.o Image_DEBUG.o Test_DEBUG.o
DEPS = Image.h FileIO.h DIPs.h Movie.h IterativeFilter.h Constants.h

DESIGN = MovieLab
all: $(DESIGN)

#Compilation

MovieLab: $(OBJS) libFilter.a MovieLab.o
	$(CC) $(LFLAGS) $(OBJS) $(DEBUG) -lm -L. -lFilter -o MovieLab

libFilter.a: DIPs.o
	ar rc libFilter.a DIPs.o
	ranlib libFilter.a
IterativeFilter.o: IterativeFilter.c IterativeFilter.h Image.h ImageList.h Movie.h
	$(CC) $(CFLAGS) IterativeFilter.c -o IterativeFilter.o
MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o 
MovieIO.o: MovieIO.c MovieIO.h Movie.h Constants.h ImageList.h 
	$(CC) $(CFLAGS) MovieIO.c -o MovieIO.o
Movie.o: Movie.c Movie.h ImageList.h Image.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o
ImageList.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o

FileIO_DEBUG.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) FileIO.c -o FileIO_DEBUG.o
DIPs_DEBUG.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) DIPs.c -o DIPs_DEBUG.o
Image_DEBUG.o: Image.c Image.h
	$(CC) $(CFLAGS) $(DEBUG) Image.c -o Image_DEBUG.o

clean:
	rm -f *.o *.a $(DESIGN) `find . -name '*.ppm' ! -name 'HSSOE.ppm'`
	rm -f `find . -name '*.yuv' ! -name 'hue.yuv' ! -name 'mouse.yuv' ! -name 'reverse.yuv'`
