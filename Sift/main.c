#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define _CRT_SECURE_NO_DEPRECATE

#include "img_io.h"
#include "sift.h"
#include "yuvRead.h"


int
main(int argc, char* argv[]) {
   /* int xsize, ysize;
	unsigned char* in_img;
	unsigned char* r = NULL;
	unsigned char* g = NULL;
	unsigned char* b = NULL;


	in_img = read_pgm(&xsize, &ysize, "akiyo1.pgm");

	if (xsize != 352 || ysize != 288) {
        fprintf(
            stderr,
            "Only CIF pictures are supported\n");
        exit(1);
    }

    assert(in_img != NULL);*/

	int xsize=352, ysize=288;
	//int i=1; 
	//char nom[256];
	unsigned char* input = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	unsigned char* tmp = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	unsigned char* r = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	unsigned char* g = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	unsigned char* b = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	unsigned char* y = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	unsigned char* u = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	unsigned char* v = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));

	initReadYUV(xsize, ysize);
	while (1)
	{
		readYUV(xsize, ysize, y, u, v);

		AppelSift(y, xsize, ysize,r,g,b);

		//sprintf(nom, "Resultats/%d.pgm", i);
		write_ppm(r, g, b, xsize, ysize);
		//i++;
	}

    return 0;
}// main()

