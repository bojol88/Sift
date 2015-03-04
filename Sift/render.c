#include "sift.h"
#include "img_io.h"

void  render(unsigned char* img, char* out_filename,
             int* octavesW, int* octavesH,
             pointList* keyPointList,
			 float sigmas[MAX_O][MAX_S], 
			 unsigned char* r, unsigned char* g, unsigned char* b){
  
    // common variables
    int i, j;
    // pointer for list traversal
    SiftKeypoint keyPtr;
    // color imag ein PPM format
    PPM_IMG imgPPM;
    // image width and height of octave base
    int w, h;
    // x, y position of keypoint scaled to octave base
    int x, y;

    /*******************************
     * cR:
     * radius of the circle
     * cR = sigma * 4 * (2^O)
     *******************************/
    int cR;

    int keyN = keyPointList->size;

    // assign width and height
    w = octavesW[0];
    h = octavesH[0];
  
    // initialize the imgPPM
    imgPPM.w =  w;
    imgPPM.h =  h;
    imgPPM.img_r = 
        (unsigned char*)
        malloc( w * h * sizeof(unsigned char) );
    imgPPM.img_g = 
        (unsigned char*)
        malloc( w * h * sizeof(unsigned char) );
    imgPPM.img_b = 
        (unsigned char*)
        malloc( w * h * sizeof(unsigned char) );

    // copy gray PGM img to color PPM img
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
            imgPPM.img_r[i*w+j] = img[i*w+j];
            imgPPM.img_g[i*w+j] = img[i*w+j];
            imgPPM.img_b[i*w+j] = img[i*w+j];
        }
    }

    for(i = 0; i < keyN; i++){
        keyPtr = keyPointList->list[i];
        // derive circle radius cR
        cR = 
            (int)
            ( sigmas
              [keyPtr.o]
              [(int)keyPtr.s] *
              pow(2,keyPtr.o) );
        if(cR <= 1){ // avoid zero radius
            cR = 1;
        }
        x = (int)(keyPtr.x) *
            (w/octavesW[keyPtr.o]);
        y = (int)(keyPtr.y) *
            (h/octavesH[keyPtr.o]);
        draw_red_circle(&imgPPM, (int)x, (int)y, cR);
        draw_red_orientation(&imgPPM, (int)x, (int)y, keyPtr.ori, cR);
    }
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			r[i*w + j] = imgPPM.img_r[i*w + j];
			g[i*w + j] = imgPPM.img_g[i*w + j];
			b[i*w + j] = imgPPM.img_b[i*w + j];
		}
	}

    // write rendered image to output
    // write_ppm(imgPPM.img_r, imgPPM.img_g, imgPPM.img_b, w, h, out_filename);

    // free allocated memory
    free(imgPPM.img_r);
    free(imgPPM.img_g);
    free(imgPPM.img_b);
}// render()
