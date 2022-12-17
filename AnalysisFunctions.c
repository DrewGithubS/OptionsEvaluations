#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "AnalysisFunctions.h"
#include "Structures.h"

static int compareDate(Date a, Date b) {
	return a.year == b.year && a.month == b.month && a.day == b.day;
}

static int daysToExpire(Date a, Date b) {
	return (b.year - a.year) * 252 + (b.month - a.month) * 30 + (b.day - a.day);
}

void doCallAnalysisFunction(
	Date * dateArray,
	OptionData * optionArray,
	double * underlyingPrice,
	int optionCounter,
	int uniqueDateCount) {

	Date currDate = dateArray[0];
	double currPrice;
	double tempCumulativeProfit = 0;
	double tempIntrinsicSold = 0;
	double tempExtrinsicSold = 0;
	double tempTotalSold = 0;
	double tempAssignedLoss = 0;
	double tempOptionsSold = 0;
	double tempProfitFromHolding = 0;
	double tempProfit = 0;

	double * cumulativeProfit = (double *) malloc(uniqueDateCount * sizeof(double));
	double * intrinsicValueSold = (double *) malloc(uniqueDateCount * sizeof(double));
	double * extrinsicValueSold = (double *) malloc(uniqueDateCount * sizeof(double));
	double * totalSold = (double *) malloc(uniqueDateCount * sizeof(double));
	double * assignedLoss = (double *) malloc(uniqueDateCount * sizeof(double));
	int * optionsSold = (int *) malloc(uniqueDateCount * sizeof(int));
	double * profitFromHolding = (double *) malloc(uniqueDateCount * sizeof(double));
	double * profit = (double *) malloc(uniqueDateCount * sizeof(double));
	int dateIndex = 0;
	int found;
	double mark;

	printf("Collecting profits %d...\n", uniqueDateCount); fflush(stdout);

	for(int i = 0; i < optionCounter; i++) {
		if(!compareDate(currDate, optionArray[i].QUOTE_DATE)) {
			currDate = optionArray[i].QUOTE_DATE;
			cumulativeProfit[dateIndex] = tempCumulativeProfit;
			profit[dateIndex] = tempProfit;
			intrinsicValueSold[dateIndex] = tempIntrinsicSold;
			extrinsicValueSold[dateIndex] = tempExtrinsicSold;
			totalSold[dateIndex] = tempTotalSold;
			assignedLoss[dateIndex] = tempAssignedLoss;
			optionsSold[dateIndex] = tempOptionsSold;
			profitFromHolding[dateIndex] = tempProfitFromHolding;
			tempProfitFromHolding = 0;
			tempIntrinsicSold = 0;
		 	tempExtrinsicSold = 0;
		 	tempTotalSold = 0;
			tempAssignedLoss = 0;
			tempOptionsSold = 0;
			tempProfit = 0;
			dateIndex++;
		}
		
		found = 0;
		for(int j = dateIndex; j < uniqueDateCount; j++) {
			if(compareDate(optionArray[i].EXPIRE_DATE.date, dateArray[j])) {
				currPrice = underlyingPrice[j];
				found = 1;
				break;
			}
		}

		if(found && 
		  fabs(optionArray[i].C_DELTA) > 0.0 && 
		  fabs(optionArray[i].C_DELTA) < 0.15 && 
		  daysToExpire(currDate, optionArray[i].EXPIRE_DATE.date) < 40 &&
		  daysToExpire(currDate, optionArray[i].EXPIRE_DATE.date) > 10 &&
		  optionArray[i].C_ASK > 1 &&
		  optionArray[i].STRIKE_DISTANCE_PCT < 0.20) {

			double assignedLoss = (optionArray[i].STRIKE - currPrice) * (optionArray[i].STRIKE > currPrice ? 1 : 0);
			mark = optionArray[i].C_BID;
			tempIntrinsicSold += (optionArray[i].UNDERLYING_LAST - optionArray[i].STRIKE) * 
								  (optionArray[i].UNDERLYING_LAST > optionArray[i].STRIKE ? 1 : 0);
			tempExtrinsicSold += (mark - tempIntrinsicSold);
			tempAssignedLoss += (currPrice - optionArray[i].STRIKE) * (currPrice > optionArray[i].STRIKE ? 1 : 0);
			tempTotalSold += mark;
			tempProfitFromHolding += currPrice - optionArray[i].UNDERLYING_LAST;
			tempProfit += mark - assignedLoss + tempProfitFromHolding;
			tempCumulativeProfit += mark - assignedLoss + tempProfitFromHolding;
			tempOptionsSold++;
		}

		if(i % 1000 == 0) {
			printf("%lf%% done...\n", (double) 100 * (double) i / (double) optionCounter);
		}
	}

	printf("Outputting file...\n");
	FILE * output = fopen("Profit.csv", "w");
	fprintf(output, "Date, UnderlyingPrice, ExtrinsicSold, IntrinsicSold, TotalSold, AssignedLoss, OptionsSold, ProfitFromHolding, TotalProfit, CumulativeProfit\n");
	for(int i = 0; i < uniqueDateCount; i++) {
		fprintf(output, "%d-%d-%d, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %d, %.2lf, %.2lf, %.2lf\n", 
			dateArray[i].year, dateArray[i].month, dateArray[i].day,
			underlyingPrice[i],
			extrinsicValueSold[i],
			intrinsicValueSold[i],
			totalSold[i],
			assignedLoss[i],
			optionsSold[i],
			profitFromHolding[i],
			profit[i],
			cumulativeProfit[i]);
	}
	fclose(output);

	free(extrinsicValueSold);
	free(intrinsicValueSold);
	free(totalSold);
	free(assignedLoss);
	free(optionsSold);
	free(profitFromHolding)
	free(profit);
	free(cumulativeProfit);

	printf("Done...\n");
	printf("Exiting...\n");
}

void doPutAnalysisFunction(
	Date * dateArray,
	OptionData * optionArray,
	double * underlyingPrice,
	int optionCounter,
	int uniqueDateCount) {
	
	Date currDate = dateArray[0];
	double currPrice;
	double tempCumulativeProfit = 0;
	double tempIntrinsicSold = 0;
	double tempExtrinsicSold = 0;
	double tempTotalSold = 0;
	double tempAssignedLoss = 0;
	double tempOptionsSold = 0;
	double tempProfit = 0;

	double * cumulativeProfit = (double *) malloc(uniqueDateCount * sizeof(double));
	double * intrinsicValueSold = (double *) malloc(uniqueDateCount * sizeof(double));
	double * extrinsicValueSold = (double *) malloc(uniqueDateCount * sizeof(double));
	double * totalSold = (double *) malloc(uniqueDateCount * sizeof(double));
	double * assignedLoss = (double *) malloc(uniqueDateCount * sizeof(double));
	int * optionsSold = (int *) malloc(uniqueDateCount * sizeof(int));
	double * profit = (double *) malloc(uniqueDateCount * sizeof(double));
	int dateIndex = 0;
	int found;
	double mark;

	printf("Collecting profits %d...\n", uniqueDateCount); fflush(stdout);

	for(int i = 0; i < optionCounter; i++) {
		if(!compareDate(currDate, optionArray[i].QUOTE_DATE)) {
			currDate = optionArray[i].QUOTE_DATE;
			cumulativeProfit[dateIndex] = tempCumulativeProfit;
			profit[dateIndex] = tempProfit;
			intrinsicValueSold[dateIndex] = tempIntrinsicSold;
			extrinsicValueSold[dateIndex] = tempExtrinsicSold;
			totalSold[dateIndex] = tempTotalSold;
			assignedLoss[dateIndex] = tempAssignedLoss;
			optionsSold[dateIndex] = tempOptionsSold;
			tempIntrinsicSold = 0;
		 	tempExtrinsicSold = 0;
		 	tempTotalSold = 0;
			tempAssignedLoss = 0;
			tempOptionsSold = 0;
			tempProfit = 0;
			dateIndex++;
		}
		
		found = 0;
		for(int j = dateIndex; j < uniqueDateCount; j++) {
			if(compareDate(optionArray[i].EXPIRE_DATE.date, dateArray[j])) {
				currPrice = underlyingPrice[j];
				found = 1;
				break;
			}
		}

		if(found && 
		  fabs(optionArray[i].P_DELTA) > 0.0 && 
		  fabs(optionArray[i].P_DELTA) < 0.15 && 
		  daysToExpire(currDate, optionArray[i].EXPIRE_DATE.date) < 40 &&
		  daysToExpire(currDate, optionArray[i].EXPIRE_DATE.date) > 10 &&
		  optionArray[i].P_ASK > 1 &&
		  optionArray[i].STRIKE_DISTANCE_PCT < 0.20) {

			double assignedLoss = (optionArray[i].STRIKE - currPrice) * (optionArray[i].STRIKE > currPrice ? 1 : 0);
			mark = optionArray[i].P_BID;
			tempIntrinsicSold += (optionArray[i].STRIKE - optionArray[i].UNDERLYING_LAST) * 
								  (optionArray[i].STRIKE > optionArray[i].UNDERLYING_LAST ? 1 : 0);
			tempExtrinsicSold += (mark - tempIntrinsicSold);
			tempAssignedLoss += (optionArray[i].STRIKE - currPrice) * (optionArray[i].STRIKE > currPrice ? 1 : 0);
			tempTotalSold += mark;
			tempProfit += mark - assignedLoss;
			tempCumulativeProfit += mark - assignedLoss;
			tempOptionsSold++;
		}

		if(i % 1000 == 0) {
			printf("%lf%% done...\n", (double) 100 * (double) i / (double) optionCounter);
		}
	}

	printf("Outputting file...\n");
	FILE * output = fopen("Profit.csv", "w");
	fprintf(output, "Date, UnderlyingPrice, ExtrinsicSold, IntrinsicSold, TotalSold, AssignedLoss, OptionsSold, TotalProfit, CumulativeProfit\n");
	for(int i = 0; i < uniqueDateCount; i++) {
		fprintf(output, "%d-%d-%d, %.2lf, %.2lf, %.2lf, %.2lf, %.2lf, %d, %.2lf, %.2lf\n", 
			dateArray[i].year, dateArray[i].month, dateArray[i].day,
			underlyingPrice[i],
			extrinsicValueSold[i],
			intrinsicValueSold[i],
			totalSold[i],
			assignedLoss[i],
			optionsSold[i],
			profit[i],
			cumulativeProfit[i]);
	}
	fclose(output);

	printf("Done...\n");
	printf("Exiting...\n");
}

void doIVAnalysisFunction(
	Date * dateArray,
	OptionData * optionArray,
	double * underlyingPrice,
	int optionCounter,
	int uniqueDateCount) {


}