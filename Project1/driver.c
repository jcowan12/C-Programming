/*
	Jonathan Cowan
	CPSC 1020, Section 010, PA1
	9/30/2021
	The driver of the program, includes main function
*/

#include "ppm_info.h"

int main (int argc, char *argv[]) {

	// Open both input files
	FILE* oldImage1 = fopen(argv[1], "r");
	FILE* oldImage2 = fopen(argv[2], "r");

	if (!oldImage1 || !oldImage2) {
		printf("ERROR: File(s) could not be opened.\n");
		return -1;
	}

	// read in images
	image_t* image1 = read_ppm(oldImage1);
	image_t* image2 = read_ppm(oldImage2);

	// Create filePtr_t pointers for each image
	filePtr_t* pImage1 = (filePtr_t*)malloc(sizeof(filePtr_t));
	filePtr_t* pImage2 = (filePtr_t*)malloc(sizeof(filePtr_t));


	// Initialize values for image1
	pImage1->theFile = oldImage1;
	pImage1->imageFileName = argv[1];
	pImage1->theImage = image1;
	pImage1->next = NULL;

	// Initialize values for image21
	pImage2->theFile = oldImage2;
	pImage2->imageFileName = argv[2];
	pImage2->theImage = image2;
	pImage2->next = NULL;

	// add images to list of output files
	filePtr_t* theList = NULL;

	// link nodes
	theList = pImage1;
	theList->next = pImage2;

	// print menu
	int count = 0;
	count = printMenu();
	filePtr_t* imageChoice = NULL;
	int size = 2;

	// loop to continue user manipulation
	while ((count == 1) || (count == 2) || (count == 3)) {
		//gray scale
		if (count == 1) {
			imageChoice = printList(theList);
			++size;
			gray_scale(imageChoice, &theList, size);
		}

		// mirror
		if (count == 2) {
			imageChoice = printList(theList);
			++size;
			mirror(imageChoice, &theList, size);
		}

		// green screen
		if (count == 3) {
			printf("\nThe Clemson paw image will be copied on top of which of the following Disney images:\n");
			imageChoice = printList(theList);
			++size;
			green_screen(pImage1, imageChoice, &theList, size);
		}

		count = printMenu();
	}


	return 0;
}
