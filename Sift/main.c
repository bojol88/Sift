#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define _CRT_SECURE_NO_DEPRECATE

#include "img_io.h"
#include "sift.h"
#include "yuvRead.h"


int
main(int argc, char* argv[]) {

	int xsize=352, ysize=288;
	int i=1;
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

		Sift(y, xsize, ysize,r,g,b);
		
		write_ppm(r, g, b, xsize, ysize);

		printf("%d ", i); i++; // To see that's running !
	}

    return 0;
}// main()

