#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "img_io.h"
#include "sift.h"


int
main(int argc, char* argv[]) {
    int xsize, ysize;
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

    assert(in_img != NULL);
	r = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	g = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));
	b = (unsigned char*)malloc(xsize * ysize * sizeof(unsigned char));

	AppelSift(in_img, xsize, ysize,r,g,b);
	write_ppm(r, g, b, xsize, ysize, "A_main.pgm");
    return 0;
}// main()

