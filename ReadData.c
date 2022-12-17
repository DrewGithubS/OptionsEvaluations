#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "Structures.h"

void readLongNum(FILE * in, void * data) {
	uint64_t * dataToRead = (uint64_t *) data;
	fread(data, sizeof(uint64_t), 1, in);
}

void readDateAndTime(FILE * in, void * data) {
	DateAndTime * dataToRead = (DateAndTime *) data;
	Date * date = &dataToRead->date;
	Time * time = &dataToRead->time;
	fread(date, sizeof(Date), 1, in);
	fread(time, sizeof(Time), 1, in);
}

void readDate(FILE * in, void * data) {
	Date * dataToRead = (Date *) data;
	fread(dataToRead, sizeof(Date), 1, in);
}

void readDouble(FILE * in, void * data) {
	double * dataToRead = (double *) data;
	fread(dataToRead, sizeof(double), 1, in);
}

void readSize(FILE * in, void * data) {
	BidAskSize * dataToRead = (BidAskSize *) data;
	fread(&(dataToRead->first), sizeof(uint32_t), 1, in);
	fread(&(dataToRead->second), sizeof(uint32_t), 1, in);
}

typedef void (*ReadFunction)(FILE *, void *);
ReadFunction readFunctionList[FUNCTION_READ_COUNT] = 
	{readLongNum, readDateAndTime, readDate, readDouble, readSize};

static int compareDate(Date a, Date b) {
	return a.year == b.year && a.month == b.month && a.day == b.day;
}

void readDataIn(FILE * fp, OptionData * optionArray, int * optionCounter, int * uniqueDateCount) {
	OptionData option;
	void * optionPtrList[] = {
		&(option.QUOTE_UNIXTIME),
		&(option.QUOTE_READTIME),
		&(option.QUOTE_DATE),
		&(option.QUOTE_TIME_HOURS),
		&(option.UNDERLYING_LAST),
		&(option.EXPIRE_DATE),
		&(option.EXPIRE_UNIX),
		&(option.DTE),
		&(option.C_DELTA),
		&(option.C_GAMMA),
		&(option.C_VEGA),
		&(option.C_THETA),
		&(option.C_RHO),
		&(option.C_IV),
		&(option.C_VOLUME),
		&(option.C_LAST),
		&(option.C_SIZE),
		&(option.C_BID),
		&(option.C_ASK),
		&(option.STRIKE),
		&(option.P_BID),
		&(option.P_ASK),
		&(option.P_SIZE),
		&(option.P_LAST),
		&(option.P_DELTA),
		&(option.P_GAMMA),
		&(option.P_VEGA),
		&(option.P_THETA),
		&(option.P_RHO),
		&(option.P_IV),
		&(option.P_VOLUME),
		&(option.STRIKE_DISTANCE),
		&(option.STRIKE_DISTANCE_PCT)
	};
	Date currDate = {0, 0, 0};
	printf("Beginning to parse memory...\n"); fflush(stdout);
	while(!feof(fp)) {
		for(int i = 0; i < sizeof(valueOrder)/sizeof(VALUE_ORDER_E); i++) {
			readFunctionList[valueOrder[i]](fp, optionPtrList[i]);
		}
		if(feof(fp)) {
			break;
		}
		optionArray[*optionCounter] = option;
		(*optionCounter)++;

		(*uniqueDateCount) += !compareDate(currDate, option.QUOTE_DATE);
		currDate = option.QUOTE_DATE;
	}
	printf("Memory parsed...\n"); fflush(stdout);
}

void readData(
	OptionData ** optionArray, 
	int * optionCounter, 
	int * uniqueDateCount) {

	FILE * fp;
	uint64_t lSize;
	char *buffer;

	printf("Opening input file...\n"); fflush(stdout);
	fp = fopen("Parsing/OptionsData.bin" , "rb");
	if(!fp) {
		printf("Error opening input file...\n");
		return;
	}

	uint32_t optionCount;
	fread(&optionCount, sizeof(uint32_t), 1, fp);

	*optionArray = (OptionData *) malloc(optionCount * sizeof(OptionData));
	// printf("optionArray: %p %llu\n", optionArray, optionCount * sizeof(OptionData)); fflush(stdout);

	readDataIn(fp, *optionArray, optionCounter, uniqueDateCount);
}