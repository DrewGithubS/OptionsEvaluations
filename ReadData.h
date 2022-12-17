#ifndef READDATA_H
#define READDATA_H

#include "Structures.h"

void readDataIn(FILE * fp, OptionData * optionArray, int * optionCounter, int * uniqueDateCount);
void readData(OptionData ** optionArray, int * optionCounter, int * uniqueDateCount);

#endif