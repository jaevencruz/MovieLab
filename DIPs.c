/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* DIPs.c: source file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include <math.h>
#include <stdio.h>


void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
    // Memory for result
    float result[3] = {0, 0, 0};

    // Perform multiplication
    result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
    result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
    result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

    // Copy result into other stack's memory
    vector[0] = result[0];
    vector[1] = result[1];
    vector[2] = result[2];
}

#ifdef HUEROTATE_UNITTEST
static void pvec(float vec[3])
{
    printf("%f, %f, %f\n\n", vec[0], vec[1], vec[2]);
}
#endif

IMAGE *HueRotate(IMAGE *image, float angle)
{
	// Matrix to transform normalized
    // RGB color vector from the RGB
    // color space to the YIQ color space
    static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
                                               {0.596, -0.274, -0.321},
                                               {0.211, -0.523,  0.311}};

    // Matrix to transform normalized
    // YIQ color vector from the YIQ
    // color space to the RGB color space
    static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
                                               {1.000, -0.272, -0.647},
                                               {1.000, -1.107,  1.705}};

    const float cs = cos(angle), ss = sin(angle);

    // Matrix to perform a hue
    // rotation on a normalized
    // YIQ color vector
    const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
                                                   {0.000, cs, -ss},
                                                   {0.000, ss, cs}};

    // Image variables
    const unsigned int WIDTH = ImageWidth(image);
    const unsigned int HEIGHT = ImageHeight(image);
    float temp[3];

	for(unsigned int i = 0; i < WIDTH; i++)
    {
        for(unsigned int j = 0; j < HEIGHT; j++)
        {
            // Create a normalized RGB color
            // vector fro the current pixel
            // in the image
            temp[0] = (float)GetPixelR(image, i, j)/255;
            temp[1] = (float)GetPixelG(image, i, j)/255;
            temp[2] = (float)GetPixelB(image, i, j)/255;

            // Transform the RGB vector
            // to a YIQ vector
            matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

            // Perform the DIP
            matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

            // Transform back to RGB
            matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

            // Denormalize and store back into the image
            temp[0] = temp[0] * 255;
            temp[0] = temp[0] < 0 ? 0 : temp[0];
            temp[0] = temp[0] > 255 ? 255 : temp[0];
            temp[1] = temp[1] * 255;
            temp[1] = temp[1] < 0 ? 0 : temp[1];
            temp[1] = temp[1] > 255 ? 255 : temp[1];
            temp[2] = temp[2] * 255;
            temp[2] = temp[2] < 0 ? 0 : temp[2];
            temp[2] = temp[2] > 255 ? 255 : temp[2];
            SetPixelR(image, i, j, (unsigned char)(temp[0]));
            SetPixelG(image, i, j, (unsigned char)(temp[1]));
            SetPixelB(image, i, j, (unsigned char)(temp[2]));
        }// rof
    }// rof

    return image;
}

IMAGE *Saturate(IMAGE *image, float percent){
	assert(image);
        assert(image->R);
        assert(image->G);
        assert(image->B);
	percent = percent*10;
        float Rt, Gt, Bt;
        int x,y;
        for(x = 0; x < ImageWidth(image); x++){
                for(y=0;y<ImageHeight(image); y++){
                        Rt = (image->R[x+y*(ImageWidth(image))]+image->G[x+y*(ImageWidth(image))]+image->B[x+y*(ImageWidth(image))])/3;
                        Gt = Rt;
                        Bt = Rt;
                        /*Difference of Original and Temporary R value*/
                        Rt = image->R[x+y*(ImageWidth(image))]-Rt;
                        Gt = image->G[x+y*(ImageWidth(image))]-Gt;
                        Bt = image->B[x+y*(ImageWidth(image))]-Bt;

                        /*Add the difference multiplied by percentage with conditional checks to keep pixel values in range of 0-255*/
                        Rt = image->R[x+y*(ImageWidth(image))] + (Rt * percent)/100.00;
                        if(Rt<0){
                                Rt = 0;
                        }
                        else if(Rt>255){
                                Rt = 255;
                        }
                        Gt  = image->G[x+y*(ImageWidth(image))] + (Gt * percent)/100.00;
                        if(Gt<0){
                                Gt = 0;
                        }
                        else if(Gt>255){
                                Gt = 255;
                        }
                        Bt = image->B[x+y*(ImageWidth(image))] + (Bt * percent)/100.0;
                        if(Bt<0){
                                Bt = 0;
                        }
                        else if(Bt>255){
                                Bt = 255;
                        }
                        /*Pixel values cast back into unsigned char*/
                        image->R[x+y*ImageWidth(image)] = (unsigned char)Rt;
                        image->G[x+y*ImageWidth(image)] = (unsigned char)Gt;
                        image->B[x+y*ImageWidth(image)] = (unsigned char)Bt;

                }
        }
        return image;
	
}

/*Same is used if user loads an image, does no operation, and saves it to an output file*/
IMAGE *same(IMAGE *image,float percent){
	return image;
}
/* EOF */
