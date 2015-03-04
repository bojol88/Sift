#ifndef _SIFT_H_
#define _SIFT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/****************************************
 * Flags
 ***************************************/
// print information
#define VERBOSE 1

/****************************************
 * Global Definitions
 ***************************************/

// maximum number of octaves
#define MAX_O (6)
// maximum nuber of scales per octave
#define MAX_S (6)
// number of bins for orientation histogram
#define ORI_BINS (36)


/****************************************
 * Memory allocations customized for CIF images: 352x288
 ***************************************/

// number of total octaves (skip last two level)
#define NUMBER_OF_OCTAVES (6)
// int NUMBER_OF_OCTAVES = (int)(log2( (w < h) ? (float)w : (float)h))-2;

// number of scales per octaves (empirical number)
#define NUMBER_OF_SCALES (6)

// size of the largest octave
// to simplify, each octave is allocated the same size.
// this can be improved
#define MAX_OCTAVE_SIZE (101376)

// maximum number of SIFT points to retrieve
#define MAX_NUMBER_OF_POINTS (500)

/****************************************
 * Data Structures
 ***************************************/

// 128-element descriptor
#define NUM_OF_DESCRIPTORS (128)
typedef struct SiftKeypoint_t {
    int o; // octave number
    float x; // x coordinate
    float y; // y coordinate
    float s; // scale
    float ori; // orientation in degrees.
    float mag; // magnitude
    //float descriptors [NUM_OF_DESCRIPTORS]; // In the current code, the descriptors are not computed
} SiftKeypoint;

// a linked list for descriptors
typedef struct pointList_t{
    SiftKeypoint list[MAX_NUMBER_OF_POINTS];
    int size;
} pointList;

// Gradient buffer for orientation and descriptor calculation
extern int current_octave;
extern float* grad_buffer;

/****************************************
 * Functions
 ***************************************/

void sift(unsigned char* img,
          int w, int h, char* out_filename,
          unsigned char octaves[][MAX_OCTAVE_SIZE],
          int* octavesW, int* octavesH,
          float scaleSpace[][MAX_S][MAX_OCTAVE_SIZE],
          float dog[][MAX_S-1][MAX_OCTAVE_SIZE],
		  pointList* keyPointList, int O, int S, unsigned char* r, unsigned char* g, unsigned char* b);

void buildOB(unsigned char* img,
             unsigned char octaves[][MAX_OCTAVE_SIZE],
             int O,
             int* octavesW, int* octavesH);

void buildSS(unsigned char octaves[][MAX_OCTAVE_SIZE],
             float scaleSpace[][MAX_S][MAX_OCTAVE_SIZE],
             int O, int S,
             int* octavesW, int* octavesH,
             float sigmas[MAX_O][MAX_S]);

void DoG(float dog[][MAX_S-1][MAX_OCTAVE_SIZE],
         float scaleSpace[][MAX_S][MAX_OCTAVE_SIZE],
         int O, int S,
         int* octavesW, int* octavesH);

void extreme(pointList* keyPointList,
             float dog[][MAX_S-1][MAX_OCTAVE_SIZE],
             int O, int S,
             int* octavesW, int* octavesH);

void orientation(pointList* keyPointList,
                 float scaleSpace[][MAX_S][MAX_OCTAVE_SIZE],
                 float sigmas[MAX_O][MAX_S],
                 int* octavesW);

void write_keypoints(FILE* fp,
                     SiftKeypoint* keys,
                     int n);

void  render(unsigned char* img, char* out_filename,
             int* octavesW, int* octavesH,
             pointList* keyPointList,
			 float sigmas[MAX_O][MAX_S], unsigned char* r, unsigned char* g, unsigned char* b);


void AppelSift(unsigned char* input, int xsize, int ysize, unsigned char* r, unsigned char* g, unsigned char* b);

#endif//_SIFT_H_

