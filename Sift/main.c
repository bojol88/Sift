#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "img_io.h"
#include "sift.h"


int
main(int argc, char* argv[]) {
    int xsize, ysize;
	unsigned char* in_img;
	//unsigned char* output = NULL;


	in_img = read_pgm(&xsize, &ysize, "akiyo1.pgm");

	if (xsize != 352 || ysize != 288) {
        fprintf(
            stderr,
            "Only CIF pictures are supported\n");
        exit(1);
    }

    assert(in_img != NULL);

	AppelSift(in_img, xsize, ysize);
    
    return 0;
}// main()

