#include "getchange.h"
#include <stdio.h>

// Function Defintions

// getchange, prompts user to enter change amount for each bucket (utilizes computechange)
void GetChange (change changeArray[], int count) {
    int changePtr = 0;
    
    for (int i = 0; i < count; ++i) {
        printf("How much change: \n");
        scanf(" %d", &changePtr);
        changeArray[i] = ComputeChange(changePtr);
    }
}

// ComputeChange, takes inputted change and calculates number of each denomination
change ComputeChange (int count) {
    change newChange;
    
    newChange.numQuart = count / 25;
    newChange.numDime = (count % 25) / 10;
    newChange.numNick = (count % 25 % 10) / 5;
    newChange.numPen = count % 5;
    
    newChange.numCoins = newChange.numQuart + newChange.numDime + newChange.numNick + newChange.numPen;
    
    
    return newChange;
}

// Prints all contents of change struct
void PrintChange (change changeArray) {
    
    printf("Quarters: %d\n", changeArray.numQuart);
    printf("Dimes: %d\n", changeArray.numDime);
    printf("Nickles: %d\n", changeArray.numNick);
    printf("Pennies: %d\n", changeArray.numPen);
    printf("Total number of coins: %d\n", changeArray.numCoins);
}