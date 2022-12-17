#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef enum {
	LONGNUM,
	DATEANDTIME,
	DATE,
	DOUBLENUM,
	SIZE,
	FUNCTION_READ_COUNT
} VALUE_ORDER_E;

// 1262638800, 2010-01-04 16:00, 2010-01-04, 16.000000, 1132.990000, 2010-01-07, 1262898000, 3.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, , , 0.000000, 101 x 101, 205.990000, 208.990000, 925.000000, 0.000000, 0.060000, 0 x 420, 0.050000, -0.000770, 0.000040, 0.004390, -0.021160, -0.000490, 0.640130, 550.000000, 208.000000, 0.184000
static const VALUE_ORDER_E valueOrder[] = {
	LONGNUM,     // QUOTE_UNIXTIME      1262638800
	DATEANDTIME, // QUOTE_READTIME      2010-01-04 16:00
	DATE,        // QUOTE_DATE          2010-01-04
	DOUBLENUM,   // QUOTE_TIME_HOURS    16.000000
	DOUBLENUM,   // UNDERLYING_LAST     1132.990000
	DATE,		 // EXPIRE_DATE         2010-01-07
	LONGNUM,     // EXPIRE_UNIX         1262898000
	DOUBLENUM,   // DTE                 3.000000

	DOUBLENUM,   // C_DELTA             1.000000
	DOUBLENUM,   // C_GAMMA             0.000000
	DOUBLENUM,   // C_VEGA              0.000000
	DOUBLENUM,   // C_THETA             0.000000
	DOUBLENUM,   // C_RHO               0.000000
	DOUBLENUM,   // C_IV                0.640130
	DOUBLENUM,   // C_VOLUME            550.000000
	DOUBLENUM,   // C_LAST              0.000000
	SIZE,        // C_SIZE              101 x 101
	DOUBLENUM,   // C_BID               205.990000
	DOUBLENUM,   // C_ASK               208.990000

	DOUBLENUM,   // STRIKE              925.000000

	DOUBLENUM,   // P_BID               0.000000
	DOUBLENUM,   // P_ASK               0.060000
	SIZE,        // P_SIZE              0 x 420
	DOUBLENUM,   // P_LAST              0.050000
	DOUBLENUM,   // P_DELTA             -0.000770
	DOUBLENUM,   // P_GAMMA             0.000040
	DOUBLENUM,   // P_VEGA              0.004390
	DOUBLENUM,   // P_THETA             -0.021160
	DOUBLENUM,   // P_RHO               -0.000490
	DOUBLENUM,   // P_IV                0.640130
	DOUBLENUM,   // P_VOLUME            550.000000
	DOUBLENUM,   // STRIKE_DISTANCE     208.000000
	DOUBLENUM,   // STRIKE_DISTANCE_PCT 0.184000
};

/*
Unique Data Types:
LONGNUM     - Done
DATEANDTIME - Done
DATE        - Done
DOUBLENUM   - Done
SIZE        - 
*/

typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
} Date;

typedef struct {
	uint16_t minutes;
} Time;

typedef struct {
	Date date;
	Time time;
} DateAndTime;

typedef struct {
	uint32_t first;
	uint32_t second;
} BidAskSize;

typedef struct {
	uint64_t QUOTE_UNIXTIME;
	DateAndTime QUOTE_READTIME;
	Date QUOTE_DATE;
	double QUOTE_TIME_HOURS;
	double UNDERLYING_LAST;
	DateAndTime EXPIRE_DATE;
	uint64_t EXPIRE_UNIX;
	double DTE;

	double C_DELTA;
	double C_GAMMA;
	double C_VEGA;
	double C_THETA;
	double C_RHO;
	double C_IV;
	double C_VOLUME;
	double C_LAST;
	BidAskSize C_SIZE;
	double C_BID;
	double C_ASK;

	double STRIKE;

	double P_BID;
	double P_ASK;
	BidAskSize P_SIZE;
	double P_LAST;
	double P_DELTA;
	double P_GAMMA;
	double P_VEGA;
	double P_THETA;
	double P_RHO;
	double P_IV;
	double P_VOLUME;
	double STRIKE_DISTANCE;
	double STRIKE_DISTANCE_PCT;
} OptionData;

char * nameList[] = {
	"QUOTE_UNIXTIME",
	"QUOTE_READTIME",
	"QUOTE_DATE",
	"QUOTE_TIME_HOURS",
	"UNDERLYING_LAST",
	"EXPIRE_DATE",
	"EXPIRE_UNIX",
	"DTE",
	"C_DELTA",
	"C_GAMMA",
	"C_VEGA",
	"C_THETA",
	"C_RHO",
	"C_IV",
	"C_VOLUME",
	"C_LAST",
	"C_SIZE",
	"C_BID",
	"C_ASK",
	"STRIKE",
	"P_BID",
	"P_ASK",
	"P_SIZE",
	"P_LAST",
	"P_DELTA",
	"P_GAMMA",
	"P_VEGA",
	"P_THETA",
	"P_RHO",
	"P_IV",
	"P_VOLUME",
	"STRIKE_DISTANCE",
	"STRIKE_DISTANCE_PCT"
};

void printLongNum(void * output) {
	uint64_t * print = (uint64_t *) output;
	printf("%llu\n", *print);
}

void printDateAndTime(void * output) {
	DateAndTime * outputPtr = (DateAndTime *) output;
	Date * date = &outputPtr->date;
	Time * time = &outputPtr->time;
	printf("%d-%d-%d %d\n", date->year, date->month, date->day, time->minutes);
}

void printDate(void * output) {
	Date * date = (Date *) output;
	printf("%d-%d-%d\n", date->year, date->month, date->day);
}

void printDouble(void * output) {
	double * print = (double *) output;
	printf("%lf\n", *print);
}

void printSize(void * output) {
	BidAskSize * print = (BidAskSize *) output;
	printf("%d x %d\n", print->first, print->second);
}

void writeLongNum(FILE * out, void * data) {
	uint64_t * dataToWrite = (uint64_t *) data;
	fwrite(data, sizeof(uint64_t), 1, out);
}

void writeDateAndTime(FILE * out, void * data) {
	DateAndTime * dataToWrite = (DateAndTime *) data;
	Date * date = &dataToWrite->date;
	Time * time = &dataToWrite->time;
	fwrite(date, sizeof(Date), 1, out);
	fwrite(time, sizeof(Time), 1, out);
}

void writeDate(FILE * out, void * data) {
	Date * dataToWrite = (Date *) data;
	fwrite(dataToWrite, sizeof(Date), 1, out);
}

void writeDouble(FILE * out, void * data) {
	double * dataToWrite = (double *) data;
	fwrite(dataToWrite, sizeof(double), 1, out);
}

void writeSize(FILE * out, void * data) {
	BidAskSize * dataToWrite = (BidAskSize *) data;
	fwrite(&(dataToWrite->first), sizeof(uint32_t), 1, out);
	fwrite(&(dataToWrite->second), sizeof(uint32_t), 1, out);
}

int readLongNum(char ** iterator, void * output) {
	uint64_t * outputPtr = (uint64_t *) output;
	*outputPtr = 0;

	if(!(**iterator >= '0' && **iterator <= '9')) {return 0;}

	while(**iterator != ',') {
		*outputPtr *= 10;
		*outputPtr += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;
	(*iterator) += **iterator == ' ';

	return 1;
}

// Repeated whiles but I don't want to fix it.
int readDateAndTime(char ** iterator, void * output) {
	DateAndTime * outputPtr = (DateAndTime *) output;
	Date * date = &outputPtr->date;
	Time * time = &outputPtr->time;
	date->year = 0;

	if(!(**iterator >= '0' && **iterator <= '9')) {return 0;}
	while(**iterator != '-') {
		date->year *= 10;
		date->year += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;

	date->month = 0;
	if(!(**iterator >= '0' && **iterator <= '9')) {return -1;}
	while(**iterator != '-') {
		date->month *= 10;
		date->month += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;

	date->day = 0;
	if(!(**iterator >= '0' && **iterator <= '9')) {return -2;}
	while(**iterator != ' ') {
		date->day *= 10;
		date->day += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;

	uint16_t tempMinutes = 0;

	tempMinutes = 0;
	if(!(**iterator >= '0' && **iterator <= '9')) {return -3;}
	while(**iterator != ':') {
		tempMinutes *= 10;
		tempMinutes += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;

	tempMinutes *= 60;
	if(!(**iterator >= '0' && **iterator <= '9')) { return -4;}
	while(**iterator != ',') {
		time->minutes *= 10;
		time->minutes += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;
	(*iterator) += **iterator == ' ';

	time->minutes += tempMinutes;

	return 1;
}

int readDate(char ** iterator, void * output) {
	Date * outputPtr = (Date *) output;

	outputPtr->year = 0;
	if(!(**iterator >= '0' && **iterator <= '9')) {return 0;}
	while(**iterator != '-') {
		outputPtr->year *= 10;
		outputPtr->year += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;

	outputPtr->month = 0;

	if(!(**iterator >= '0' && **iterator <= '9')) {return -1;}
	while(**iterator != '-') {
		outputPtr->month *= 10;
		outputPtr->month += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;

	outputPtr->day = 0;
	if(!(**iterator >= '0' && **iterator <= '9')) {return -2;}
	while(**iterator != ',') {
		outputPtr->day *= 10;
		outputPtr->day += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;
	(*iterator) += **iterator == ' ';

	return 1;
}

int readDouble(char ** iterator, void * output) {
	double * outputPtr = (double *) output;
	*outputPtr = 0;

	double negative = 1;

	if(**iterator == '-') {
		negative = -1;
		(*iterator)++;
	}

	if(!(**iterator >= '0' && **iterator <= '9')) { return 0;}
	while(**iterator != '.') {
		*outputPtr *= 10;
		*outputPtr += (double) ((**iterator) - '0');
		(*iterator)++;
	}
	(*iterator)++;

	double divider = 10;
	if(!(**iterator >= '0' && **iterator <= '9')) { return -1;}
	while(**iterator >= '0' && **iterator <= '9') {
		*outputPtr += (double) ((**iterator) - '0') / divider;
		divider *= 10;
		(*iterator)++;
	}
	(*iterator)++;
	(*iterator) += **iterator == ' ';

	*outputPtr *= negative;

	return 1;
}

int readSize(char ** iterator, void * output) {
	BidAskSize * outputPtr = (BidAskSize *) output;
	outputPtr->first = 0;
	outputPtr->second = 0;

	// printf("Reading first value...\n"); fflush(stdout);
	if(!(**iterator >= '0' && **iterator <= '9')) { return 0;}
	while(**iterator != ' ') {
		outputPtr->first *= 10;
		outputPtr->first += **iterator - '0';
		(*iterator)++;
	}

	(*iterator)++;
	if(!(**iterator == 'x')) { return -1;}
	(*iterator)++;
	if(!(**iterator == ' ')) { return -2;}
	(*iterator)++;

	// printf("Reading second value...\n"); fflush(stdout);
	if(!(**iterator >= '0' && **iterator <= '9')) { return -3;}
	while(**iterator != ',') {
		outputPtr->second *= 10;
		outputPtr->second += **iterator - '0';
		(*iterator)++;
	}
	(*iterator)++;
	(*iterator) += **iterator == ' ';

	return 1;
}

typedef int (*ReadFunction)(char **, void *);

ReadFunction readFunctionList[FUNCTION_READ_COUNT] = 
	{readLongNum, readDateAndTime, readDate, readDouble, readSize};

typedef void (*PrintFunction)(void *);

PrintFunction printFunctionList[FUNCTION_READ_COUNT] = 
	{printLongNum, printDateAndTime, printDate, printDouble, printSize};

typedef void (*WriteFunction)(FILE *, void *);

WriteFunction writeFunctionList[FUNCTION_READ_COUNT] = 
	{writeLongNum, writeDateAndTime, writeDate, writeDouble, writeSize};

int main() {
	// FILE * file = fopen()

	FILE * fp;
	FILE * fp_out;
	uint64_t lSize;
	char *buffer;

	printf("Opening input file...\n"); fflush(stdout);
	fp = fopen("OptionsData.txt" , "rb");
	if(!fp) {
		printf("Error opening input file...\n");
		return 1;
	}

	printf("Opening output file...\n"); fflush(stdout);
	fp_out = fopen("OptionsData.bin" , "wb");
	if(!fp) {
		printf("Error opening output file...\n");
		return 1;
	}

	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	/* allocate memory for entire content */
	printf("Allocating memory...\n"); fflush(stdout);
	buffer = calloc(sizeof(char), lSize+1);
	if(!buffer) {
		fclose(fp);
		printf("Memory allocation failed...\n");
		return 1;
	}

	/* copy the file into the buffer */
	printf("Reading from disk to memory...\n"); fflush(stdout);
	if(1 != fread(buffer, lSize, 1, fp)) {
		fclose(fp);
		free(buffer);
		printf("File read failed...\n");
		return 1;
	}

	char * iterator = buffer;
	char * endIterator = buffer + lSize;

	uint32_t finalOptionCount = 1;

	for(char * i = iterator; i < endIterator; i++) {
		finalOptionCount += *i == '\n';
	}

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

	int optionCounter = 1;

	fwrite(&finalOptionCount, sizeof(uint32_t), 1, fp_out);

	printf("Beginning to parse memory...\n"); fflush(stdout);
	while(iterator < endIterator) {
		for(int i = 0; i < sizeof(valueOrder)/sizeof(VALUE_ORDER_E); i++) {
			int eCode = readFunctionList[valueOrder[i]](&iterator, optionPtrList[i]);
			if(eCode != 1) {
				// printf("An error occurred reading %s. Error code: %d\n", nameList[i], eCode);
				// return -1;
				while(*iterator != ',') {
					iterator++;
				}
				iterator++;
				iterator += *iterator == ' ';
			}
		}
		if(iterator > endIterator) {
			break;
		}
		for(int i = 0; i < sizeof(valueOrder)/sizeof(VALUE_ORDER_E); i++) {
			writeFunctionList[valueOrder[i]](fp_out, optionPtrList[i]);
		}

		optionCounter++;
		if(optionCounter % 1000 == 0) {
			printf("%lf/100 done... %d \n", (double) (iterator - buffer) / 
										(double) (endIterator - buffer) * 
										(double) 100, iterator > endIterator);
			fflush(stdout);
		}
	}
	printf("%d items parsed...\n", optionCounter);

	printf("Memory parsed...\n"); fflush(stdout);

	printf("Exiting...\n"); fflush(stdout);

	fclose(fp);
	free(buffer);
}

