#include <stdio.h>

void printIntToYear(int year, char * string) {
	string[0] = year / 1000 % 10 + '0';
	string[1] = year / 100  % 10 + '0';
	string[2] = year / 10   % 10 + '0';
	string[3] = year / 1    % 10 + '0';
}

void printIntToMonth(int month, char * string) {
	string[0] = month / 10   % 10 + '0';
	string[1] = month / 1    % 10 + '0';
}

int main() {
	char fileName[]       = "spx_eod_yyyymm.txt";
	char * yearStart      = fileName + 8;
	char * monthStart     = fileName + 12;
	int startingYear      = 2010; // Hardcoded because it's a tiny program.
	int endingYear        = 2022;
	int startingMonth     = 01;
	int endingMonth       = 12;
	int fileCount = (endingYear - startingYear + 1) * 
					(endingMonth - startingMonth + 1);

	char outputFileName[] = "OptionsData.txt";
	FILE * outputFile     = fopen(outputFileName, "w");

	char lineRead[10000];
	int count = 0;

	for(int i = startingYear; i <= endingYear; i++) {
		for(int j = startingMonth; j <= endingMonth; j++) {
			printIntToYear (i, yearStart);
			printIntToMonth(j, monthStart);
			printf("File name: %s. %d/%d done.\n", 
				fileName, 
				count, 
				fileCount);
			fflush(stdout);

			FILE * file = fopen(fileName, "r");
			if(file != 0) {
				// Trash the first line
				fgets(lineRead, sizeof(lineRead), file);
				while(fgets(lineRead, sizeof(lineRead), file)) {
					fprintf(outputFile, "%s", lineRead);
				}

				fclose(file);
			} else {
				fclose(outputFile);
				return 0;
			}
			count++;
		}
	}

	fclose(outputFile);
}