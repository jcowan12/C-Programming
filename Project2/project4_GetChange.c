/*
@project4_GetChange.c
@Jonathan Cowan
@4/19/2021

This program will prompt the user to input a number of buckets, each with a certain amount of change. The program will then tally up the change and display the bucket with the most coins.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getchange.h"

// Main Function
int main (void) {
    int bucketCount = 0;
    char currentchar = 'c';
    change* changePtr = NULL;

    
    // Loop to run until user enters something other than c
    while (currentchar == 'c') {
    
        // Prompt user for num of buckets
        printf("How many buckets: \n");
        scanf(" %d", &bucketCount);
    
    
        // Validates input
        if (bucketCount < 1) {
            printf("Invalid number of buckets. Program aborted. \n");
            break;
        }
    
        else {
            // Creates change array with correct number of buckets
            changePtr = (change*) malloc(bucketCount * sizeof(change));
            
            // Runs getchnage function 
            GetChange(changePtr, bucketCount);
        
            int maxVal = changePtr[0].numCoins;
            int maxCor = 0;
        
            // For loop that finds largest bucket
            for (int i = 0; i < bucketCount; ++i) {
                if (changePtr[i].numCoins >= maxVal) {
                    maxVal = changePtr[i].numCoins;
                    maxCor = i;
                }
            }
        
            // Final output
            printf("Most coins found in bucket %d.\n", maxCor + 1);
            PrintChange(changePtr[maxCor]);
            
            // Reprompt
            printf("Enter 'c' to run program again, or any other character to exit: \n");
            scanf(" %c", &currentchar);
            
        }
    
    }
    
    free(changePtr);
    
    return 0;
}
