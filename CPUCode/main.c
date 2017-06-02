#include <assert.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

const int MAX_CIRCLE_RADIUS       = FindWindowMaxAndRadius_MAX_CIRCLE_RADIUS;
const int NUM_PIXEL_IN_WINDOW_COL = FindWindowMaxAndRadius_NUM_PIXEL_IN_WINDOW_COL;
const int NUM_WINDOW_IN_IMAGE_ROW = FindWindowMaxAndRadius_NUM_WINDOW_IN_IMAGE_ROW;
const int NUM_WINDOW_IN_IMAGE_COL = FindWindowMaxAndRadius_NUM_WINDOW_IN_IMAGE_COL;
const int NUM_PIXEL_IN_IMAGE_ROW  = FindWindowMaxAndRadius_NUM_PIXEL_IN_IMAGE_ROW;
const int NUM_PIXEL_IN_IMAGE_COL  = FindWindowMaxAndRadius_NUM_PIXEL_IN_IMAGE_COL;
const int NUM_PIXEL_IN_WINDOW_ROW = FindWindowMaxAndRadius_NUM_PIXEL_IN_WINDOW_ROW;
const int BURST_SIZE = 384;

typedef uint8_t pixelType;

typedef struct {
	pixelType *data;
	int imageSize;
	int imageSizeAligned;
} Image;


void releaseImage(Image *image) {
	free(image->data);
}

int burstAlign(int size, int oldElemSize, int newElemSize) {
	int bytes =ceil(1.0 * size * oldElemSize / BURST_SIZE) * BURST_SIZE;
	assert(bytes % newElemSize == 0);
	int alignedSize = bytes / newElemSize;

	printf("aligned size: %d, bytes: %d\n", alignedSize, bytes);

	return alignedSize;
}

Image readImage(const char *fn, int imageSize) {
	FILE *fp = fopen(fn, "r");
	if (fp == NULL) {
		printf("cannot open file: %s\n", fn);
		exit(1);
	}

	int *inputImage = malloc(imageSize * sizeof *inputImage);
	assert(inputImage);
	for (int i = 0; i < imageSize; i++) {
		assert(fscanf(fp, "%d", &inputImage[i]) == 1);
	}
	fclose(fp);

	Image image;
	image.imageSize = imageSize;
	image.imageSizeAligned = burstAlign(imageSize, sizeof *inputImage, sizeof(pixelType));
	image.data = malloc(image.imageSizeAligned * sizeof(pixelType));
	assert(image.data);
	memset(image.data, 0, image.imageSizeAligned);

	/// convert it to the right format
	for (int i = 0; i < imageSize; i++) {
		image.data[i] = inputImage[i];
	}

	free(inputImage);

	return image;
}

int test_palm_s5() {
	const int imageCol = NUM_PIXEL_IN_IMAGE_ROW;		/// # of column, fast dimension
	const int imageRow = NUM_PIXEL_IN_IMAGE_COL;			/// # of row, slow dimension
	const int imageSize = imageRow * imageCol;

	if (NUM_PIXEL_IN_WINDOW_COL != NUM_PIXEL_IN_WINDOW_ROW) {
		printf("NUM_PIXEL_IN_WINDOW_COL != NUM_PIXEL_IN_WINDOW_ROW\n");
		exit(1);
	}

	const char *imageFileName = "/home/rice/Desktop/palm_s5test.txt";
	Image image = readImage(imageFileName, imageSize);

	printf("Upload image to LMEM\n");
	FindWindowMaxAndRadius_WriteLMem(image.imageSizeAligned, image.data);

	pixelType *d_windowMax = malloc(imageRow * imageCol * sizeof *d_windowMax);
	assert(d_windowMax);
	memset(d_windowMax, 0, imageRow * imageCol * sizeof *d_windowMax);

	printf("Running DFE\n");
	FindWindowMaxAndRadius(image.imageSizeAligned, image.imageSize, d_windowMax);

	free(d_windowMax);
	releaseImage(&image);
	return 0;
}

int main()
{
	return test_palm_s5();
}
