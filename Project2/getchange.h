#ifndef GETCHANGE_H
#define GETCHANGE_H

// struct defintion for change
typedef struct change_struct {
    int numQuart;
    int numDime;
    int numNick;
    int numPen;
    int numCoins;
} change;

// Function Prototypes
void GetChange (change changeArray[], int count);

change ComputeChange (int count);

void PrintChange (change changeArray);

#endif