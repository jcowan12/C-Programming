/* 
	Jonathan Cowan
	CPSC 1020, Section 010, 9/27/2021
	contains manipulation functions for PA1 assignment
*/

#include "ppm_info.h"


// make each color pixel the average of the r, g, b components
// which will gray-scale the image
// inputs:  the image pointer, list double pointer, count integer
// outputs:  none
void gray_scale(filePtr_t* image, filePtr_t** theList, int count) {
   int row = 0;
   int col = 0;
	int avg = 0;
   header_t header = image->theImage->header;

	// Create new image
	image_t* newImage = allocate_memory(header);

	// Create new file and open for writing
	char fileName[30] = "g"; // for gray scale
	strcat(fileName, image->imageFileName);

	// see if image already exists in list, if g is second, then yes
	if (fileName[1] != 'g') {
		char buf[5];
		fileName[strlen(fileName)-4] = '\0';
		int length = snprintf(buf, 5, "%d", count);
		// snprintf(buf, 5, "%d", count);
		char* imageName = (char*)malloc(length + 1);
		sprintf(imageName, "%s%02d.ppm", fileName, count);

		FILE* grayedImage = fopen(imageName, "w");
		if (!grayedImage) {
			fprintf(stderr, "grayed image file could not open\n\n");
			exit(1);
		}


		// copy header info over
		newImage->header = header;

   	for(row = 0; row < header.height; row++) {
      	for(col = 0; col < header.width; col++) {
				//Calculate the average of the r, g, b values for the pixel
				avg = ( image->theImage->pixels[row][col].r +
			        image->theImage->pixels[row][col].g +
					  image->theImage->pixels[row][col].b ) / 3;

				// assign avg
				newImage->pixels[row][col].r = avg;
				newImage->pixels[row][col].g = avg;
				newImage->pixels[row][col].b = avg;
			}
		}

		// call write_p6 with new image
		write_p6(grayedImage, newImage);
		fclose(grayedImage);

		// add to list
		addToList(*theList, grayedImage, newImage, imageName);
	}
}

// mirror the image vertically by switching pixels
// inputs: file_t pointer, file_t double pointer, count integer
// outputs: none, but new image is passed to write_p6
void mirror (filePtr_t* image, filePtr_t** theList, int count) {
   int row = 0;
   int col = 0;

   header_t header = image->theImage->header;

	// Create new image
	image_t* newImage = allocate_memory(header);

	// Create new file and open for writing
	char fileName[30] = "m"; // for gray scale
	strcat(fileName, image->imageFileName);

	// see if image already exists in list, if g is second, then yes
	if (fileName[1] != 'm') {
		char buf[5];
		fileName[strlen(fileName)-4] = '\0';
		 int length = snprintf(buf, 5, "%d", count);
		// snprintf(buf, 5, "%d", count);
		char* imageName = (char*)malloc(length + 1);
		sprintf(imageName, "%s%02d.ppm", fileName, count);

		FILE* mirrorImage = fopen(imageName, "w");
		if (!mirrorImage) {
			fprintf(stderr, "mirrored image file could not open\n\n");
			exit(1);
		}

		// copy header info over
		newImage->header = header;

		// Mirror algorithm
		for (row = 0; row < header.height; row++) {
			int farCol = header.width - 1;

			for (col = 0; col < (header.width / 2); col++) {

				// swap pixels
				newImage->pixels[row][col] = image->theImage->pixels[row][farCol];
				newImage->pixels[row][farCol] = image->theImage->pixels[row][col];

				--farCol;
			}
		}


		// call write_p6 with new image
		write_p6(mirrorImage, newImage);
		fclose(mirrorImage);

		//add to list
		addToList(*theList, mirrorImage, newImage, imageName);
	}
}
// takes image and places on another
// inputs: filePtr_t pointers, filePtr_t double pointer, count integer
// outputs: none
void green_screen (filePtr_t* image1, filePtr_t* image2, filePtr_t** theList, int count) {
	int row, col = 0;


   header_t header = image1->theImage->header;

	// Create new image
	image_t* newImage = allocate_memory(header);

	// Create new file and open for writing
	char fileName[30] = "gs"; // for green screen
	strcat(fileName, image2->imageFileName);

	// see if image already exists in list, if g is second, then yes
	if ((fileName[2] != 'g') && (fileName[3] != 's')) {
		char buf[5];
		fileName[strlen(fileName)-4] = '\0';
		int length = snprintf(buf, 5, "%d", count);
		// snprintf(buf, 5, "%d", count);
		char* imageName = (char*)malloc(length + 1);
		sprintf(imageName, "%s%02d.ppm", fileName, count);

		FILE* gsImage = fopen(imageName, "w");
		if (!gsImage) {
			fprintf(stderr, "green screen image file could not open\n\n");
			exit(1);
		}

		// copy header info over
		newImage->header = header;

		// green screen algorithm
		for (row = 0; row < header.height; row++) {
			for (col = 0; col < header.width; col++) {
				// check image2's pixel value for green
				if ((image1->theImage->pixels[row][col].g == 255) &&
					((image1->theImage->pixels[row][col].b == 0) &&
					(image1->theImage->pixels[row][col].r == 0))) {
					newImage->pixels[row][col] = image2->theImage->pixels[row][col];
				}

				// otherwise
				else {
					newImage->pixels[row][col] = image1->theImage->pixels[row][col];
				}
			}
		}
		// call write_p6 with new image
		write_p6(gsImage, newImage);
		fclose(gsImage);

		//add to list
		addToList(*theList, gsImage, newImage, imageName);
	}
}


// addToList creates list of images, adding each time an image is created
// input: filePtr_t pointer, FILE pointer, newImage pointer, name of new image
// output: none
void addToList(filePtr_t* frontOfList, FILE* newImage, image_t* theNewImage, char* nameOfImage) {
	filePtr_t *temp = frontOfList;

	// Allocate memory for new node
	filePtr_t *newNode = (filePtr_t*)malloc(sizeof(filePtr_t));

	// Initialize values
	newNode->theFile = newImage;
	newNode->theImage = theNewImage;
	newNode->imageFileName = nameOfImage;
	newNode->next = NULL;

	// Check if empty, if so, newNode is first
	if (frontOfList == NULL) {
		frontOfList = newNode;
	}

	else {
		// Traverse to last
		while (temp->next != NULL) {
			temp = temp->next;
		}

		// Now at last
		temp->next = newNode;
	}
}
