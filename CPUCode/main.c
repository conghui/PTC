#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

float dataIn[8] = { 1, 0, 2, 0, 4, 1, 8, 3 };
float dataOut[8];

void genData(int *data, int nrow, int ncol) {
	int i, j;
	int count = 0;
	for (i = 0; i < nrow; i++) {
		for (j = 0; j < ncol; j++) {
//			data[count] = count;
			data[count] = rand() % 1024;
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

int findWMax(const int *data, int row, int col, int ncol, int w) {
	int i, j;
	int ret = INT_MIN;
	int rr = 0;
	int cc = 0;
	for (i = 0; i < w; i++) {
		for (j = 0; j < w; j++) {
			int r = i + row;
			int c = j + col;
			if (data[(r)*ncol+c] > ret) {
				ret = data[(r)*ncol+c];
				rr = r;
				cc = c;
			}
		}
	}

	printf("windowMax: %d, row: %d, col: %d\n", ret, rr, cc);
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
			winMax[winCount] = findWMax(data, i, j, ncol, w);
			winCount++;
		}
	}
}

void calMeanRadius(const int *data, int nrow, int ncol, int radius) {
	int c, r;

	for (r = radius; r < nrow - radius; r++) {
		for (c = radius; c < ncol - radius; c++) {
			int d;
			int diffEastMax = 0;
			int diffWestMax = 0;
			int maxEastDiffRadius = 0;
			int maxWestDiffRadius = 0;
			int south[2] = {0};
			int north[2] = {0};
			float NE[2] = {0}; // northeast
			float NW[2] = {0}; // northwest
			float SE[2] = {0}; // southeast
			float SW[2] = {0}; // southwest
			for (d = 0; d < radius; d++) {
				/// east
				int diff = abs(data[r*ncol+(c+d+1)] - data[r*ncol+(c+d)]);
				if (diffEastMax < diff) {
					diffEastMax = diff;
					maxEastDiffRadius = d + 1;
				}

				// west
				diff = abs(data[r*ncol+(c-d-1)] - data[r*ncol+(c-d)]);
				if (diffWestMax < diff) {
					diffWestMax = diff;
					maxWestDiffRadius = d + 1;
				}

				// south
				diff = abs(data[(r+d+1)*ncol+c] - data[(r+d)*ncol +c]);
				if (south[0] < diff) {
					south[0] = diff;
					south[1] = d + 1;
				}

				// north
				diff = abs(data[(r-d-1)*ncol+c] - data[(r-d)*ncol +c]);
				if (north[0] < diff) {
					north[0] = diff;
					north[1] = d + 1;
				}

				// northeast
				diff = abs(data[(r-d-1)*ncol+(c+d+1)] - data[(r-d)*ncol+(c+d)]);
				if (NE[0] < diff) {
					NE[0] = diff;
					NE[1] = (d+1)*1.41;
				}

				// northwest
				diff = abs(data[(r-d-1)*ncol+(c-d-1)] - data[(r-d)*ncol+(c-d)]);
				if (NW[0] < diff) {
					NW[0] = diff;
					NW[1] = (d+1)*1.41;
				}

				// southeast
				diff = abs(data[(r+d+1)*ncol+(c+d+1)] - data[(r+d)*ncol+(c+d)]);
				if (SE[0] < diff) {
					SE[0] = diff;
					SE[1] = (d+1)*1.41;
				}

				// southwest
				diff = abs(data[(r+d+1)*ncol+(c-d-1)] - data[(r+d)*ncol+(c-d)]);
				if (SW[0] < diff) {
					SW[0] = diff;
					SW[1] = (d+1)*1.41;
				}
			}
			float meanRadius = (maxEastDiffRadius + maxWestDiffRadius + south[1] + north[1] + NE[1] + NW[1] + SE[1] + SW[1]) / 8;
//			printf("pixel: %d, eastDiff: %d, maxDiffRadius: %d, row: %d, col: %d\n", data[r*ncol+(c)], diffEastMax, maxEastDiffRadius, r, c);
			printf("CPU pixel: %d, East(%d, %d), West(%d, %d), South(%d, %d), North(%d, %d), NE(%.0f, %.2f), NW(%.0f, %.2f), SE(%.0f, %.2f), SW(%.0f, %.2f), meanRadius: %.2f\n", data[r*ncol+(c)],
					diffEastMax, maxEastDiffRadius,
					diffWestMax, maxWestDiffRadius,
					south[0], south[1], north[0], north[1], NE[0], NE[1], NW[0], NW[1], SE[0], SE[1], SW[0], SW[1], meanRadius
					);

		}
	}
}

int main()
{
	const int imageCol = 12;		/// # of column, fast dimension
	const int imageRow = 9;			/// # of row, slow dimension
	const int windowLength = 3;	/// window is square
	const int windowRow = imageRow / windowLength;
	const int windowCol = imageCol / windowLength;
	const int maxRadius = 3;

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

	printf("\ncalculate mean radius\n");
	calMeanRadius(inputImage, imageRow, imageCol, maxRadius);

	int *d_windowMax = malloc(imageRow * imageCol * sizeof *d_windowMax);
	assert(d_windowMax);
	memset(d_windowMax, 0, imageRow * imageCol * sizeof *d_windowMax);

	printf("Running DFE\n");
	FindWindowMaxAndRadius(imageRow * imageCol, inputImage, d_windowMax);

	printf("print d_windowMax\n");
	print2D(d_windowMax, imageRow, imageCol);

	free(inputImage);
	free(windowMax);
	return 0;
}
