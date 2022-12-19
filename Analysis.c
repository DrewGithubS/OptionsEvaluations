#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "AnalysisFunctions.h"
#include "ReadData.h"
#include "Structures.h"

static int compareDate(Date a, Date b) {
	return a.year == b.year && a.month == b.month && a.day == b.day;
}

static int daysToExpire(Date a, Date b) {
	return (b.year - a.year) * 252 + (b.month - a.month) * 30 + (b.day - a.day);
}

int main() {
	int optionCounter = 0;
	int uniqueDateCount = 0;
	OptionData * optionArray;

	readData(&optionArray, 
		&optionCounter, 
		&uniqueDateCount);

	Date * dateArray = (Date *) malloc(uniqueDateCount * sizeof(Date));
	double * underlyingPrice = (double *) malloc(uniqueDateCount * sizeof(double));

	Date currDate = optionArray[0].QUOTE_DATE;
	dateArray[0] = currDate;
	underlyingPrice[0] = optionArray[0].UNDERLYING_LAST;
	int dateIndex = 0;

	printf("Beginning Analysis...\n"); fflush(stdout);
	printf("Collecting prices...\n"); fflush(stdout);
	for(int i = 0; i < optionCounter; i++) {
		if(!compareDate(currDate, optionArray[i].QUOTE_DATE)) {
			dateIndex++;
			currDate = optionArray[i].QUOTE_DATE;
			dateArray[dateIndex] = currDate;
			underlyingPrice[dateIndex] = optionArray[i].UNDERLYING_LAST;
		}
	}

	doCallDataAnalysisFunction(dateArray, optionArray, underlyingPrice, optionCounter, uniqueDateCount);
}