#include "sift.h"

/**********************************************
 * Difference of Gaussians (DoG)
 * Only diff neighboring scales in same octave
 * Do not diff across two octaves
 *
 * Parameters
 * dog: output, Ox(S-1) images in floating point
 * scaleSpace: input, OxS images in floating pt
 * O: number of octaves
 * S: scales per octave
 * octavesW: output, width of each octave
 * octavesH: output, height of each octave
 **********************************************/

void DoG(float dog[MAX_O*(MAX_S - 1)*MAX_OCTAVE_SIZE],
         float scaleSpace[MAX_O*MAX_S*MAX_OCTAVE_SIZE],
         int* octavesW, int* octavesH){
  
    // comon variables
    int i, j, ii, jj;
  
    for(i = 0; i < NUMBER_OF_OCTAVES; i++){
        for(j = 0; j < NUMBER_OF_SCALES-1; j++){
            for(ii = 0; ii < octavesH[i]; ii++){
                for(jj = 0; jj < octavesW[i]; jj++){
                    // dog = upper scale - lower scale
                    dog[(i*(MAX_S-1)+j)*MAX_OCTAVE_SIZE+ii*octavesW[i]+jj] 
                        =
                        scaleSpace[(i*MAX_S+(j+1))*MAX_OCTAVE_SIZE+ii*octavesW[i]+jj] 
                        -
                        scaleSpace[(i*MAX_S+j)*MAX_OCTAVE_SIZE+ii*octavesW[i]+jj];
                }
            }
        }
    }

}
