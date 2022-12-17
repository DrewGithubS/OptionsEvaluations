#ifndef ANALYSISFUNCTIONS_H
#define ANALYSISFUNCTIONS_H

#include "Structures.h"

void doCallAnalysisFunction(Date * dateArray,
	OptionData * optionArray,
	double * underlyingPrice,
	int optionCounter,
	int uniqueDateCount);

void doPutAnalysisFunction(Date * dateArray,
	OptionData * optionArray,
	double * underlyingPrice,
	int optionCounter,
	int uniqueDateCount);

#endif