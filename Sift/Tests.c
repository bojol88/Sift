#include "sift.h"
#include "img_io.h"
#include "Tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

static int k = 1,l=1,m=1;

void Test_OB(unsigned char* octaves)
{
	char filename[256];
	sprintf(filename, "Tests/BuildOB/%d.pgm", k);
	k++;
	write_pgm(octaves, 352, 6*288, filename);
}

void Test_SS(float* scaleSpace)
{
	char filename[256];
	sprintf(filename, "Tests/BuildSS/%d.pgm", l);
	l++;
	write_float_pgm(scaleSpace, 6*352, 6*288, filename,1);
}

void Test_DoG(float* DoG)
{
	char filename[256];
	sprintf(filename, "Tests/DoG/%d.pgm", m);
	m++;
	write_float_pgm(DoG, 5 * 352, 6 * 288, filename,1);
}