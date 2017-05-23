#include <assert.h>
#include <limits.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

float dataIn[8] = { 1, 0, 2, 0, 4, 1, 8, 3 };
float dataOut[8];

void genData(int *data, int nrow, int ncol) {
	int i, j;
	int count = 0;
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			data[count] = count;
			count++;
		}
	}
}

void print2D(const int *data, int nrow, int ncol) {
	int i, j;
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
			printf("%6d", data[i*ncol + j]);
		}
		printf("\n");
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}

int findWMax(const int *data, int ncol, int w) {
	int i, j;
	int ret = INT_MIN;
	for (i = 0; i < w; i++) {
		for (j = 0; j < w; j++) {
			ret = max(ret, data[i*ncol+j]);
		}
	}

	return ret;
}

void searchWindowMax(const int *data, int *winMax, int nrow, int ncol, int w) {
	/// window is of size w*w
	if (!(nrow % w == 0 && ncol % w == 0)) {
		printf("w must be dividable by nrow and ncol\n");
		exit(1);
	}

	int i, j;
	int winCount = 0;
	for (i = 0; i < nrow; i += w) {
		for (j = 0; j < ncol; j += w) {
			winMax[winCount] = findWMax(&data[i*ncol+j], ncol, w);
			winCount++;
		}
	}
}

int main()
{
	float coeffs[3] = {0.75, 1.5, 0.75};

	const int imageCol = 12;		/// # of column
	const int imageRow = 12;	/// # of row
	const int windowLength = 3;	/// window is square
	const int windowRow = imageRow / windowLength;
	const int windowCol = imageCol / windowLength;

	int *inputImage = malloc(imageCol * imageRow * sizeof *inputImage);
	assert(inputImage);

	int *windowMax = malloc(windowRow * windowCol * sizeof *windowMax);
	assert(windowMax);

	printf("Generate test input data\n");
	genData(inputImage, imageRow, imageCol);
	print2D(inputImage, imageRow, imageCol);

	printf("\nsearch window max\n");
	searchWindowMax(inputImage, windowMax, imageRow, imageCol, windowLength);
	print2D(windowMax, windowRow, windowCol);

	free(inputImage);
	free(windowMax);




	printf("Running DFE\n");
	MovingAverageWeighted_weighted(8, coeffs, dataIn, dataOut);

	for (int i = 1; i < 7; i++) // Ignore edge values
		printf("dataOut[%d] = %f\n", i, dataOut[i]);

	return 0;
}
