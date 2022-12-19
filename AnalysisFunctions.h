#ifndef ANALYSISFUNCTIONS_H
#define ANALYSISFUNCTIONS_H

#include "Structures.h"

void doCallDataAnalysisFunction(
	Date * dateArray,
	OptionData * optionArray,
	double * underlyingPrice,
	int optionCounter,
	int uniqueDateCount);

void doPutDataAnalysisFunction(
	Date * dateArray,
	OptionData * optionArray,
	double * underlyingPrice,
	int optionCounter,
	int uniqueDateCount);

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