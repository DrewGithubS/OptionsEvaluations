typedef VALUE_ORDER_E enum {
	LONGNUM,
	DATEANDTIME,
	DATE,
	DOUBLENUM,
	PRICE,
	SIZE,
}
// 1262638800, 2010-01-04 16:00, 2010-01-04, 16.000000, 1132.990000, 2010-01-07, 1262898000, 3.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, , , 0.000000, 101 x 101, 205.990000, 208.990000, 925.000000, 0.000000, 0.060000, 0 x 420, 0.050000, -0.000770, 0.000040, 0.004390, -0.021160, -0.000490, 0.640130, 550.000000, 208.000000, 0.184000
static const VALUE_ORDER_E valueOrder[] = {
	LONGNUM,     // QUOTE_UNIXTIME      1262638800
	DATEANDTIME, // QUOTE_READTIME      2010-01-04 16:00
	DATE,        // QUOTE_DATE          2010-01-04
	DOUBLENUM,   // QUOTE_TIME_HOURS    16.000000
	PRICE,       // UNDERLYING_LAST     1132.990000
	DATE,		 // EXPIRE_DATE         2010-01-07
	LONGNUM,     // EXPIRE_UNIX         1262898000
	LONGNUM,     // DTE                 3.000000

	DOUBLENUM,   // C_DELTA             1.000000
	DOUBLENUM,   // C_GAMMA             0.000000
	DOUBLENUM,   // C_VEGA              0.000000
	DOUBLENUM,   // C_THETA             0.000000
	DOUBLENUM,   // C_RHO               0.000000
	DOUBLENUM,   // C_IV                0.640130
	LONGNUM,     // C_VOLUME            550.000000
	PRICE,       // C_LAST              0.000000
	SIZE,        // C_SIZE              101 x 101
	PRICE,       // C_BID               205.990000
	PRICE,       // C_ASK               208.990000

	PRICE,       // STRIKE              925.000000

	PRICE        // P_BID               0.000000
	PRICE,       // P_ASK               0.060000
	SIZE,        // P_SIZE              0 x 420
	PRICE,       // P_LAST              0.050000
	DOUBLENUM,   // P_DELTA             -0.000770
	DOUBLENUM,   // P_GAMMA             0.000040
	DOUBLENUM,   // P_VEGA              0.004390
	DOUBLENUM,   // P_THETA             -0.021160
	DOUBLENUM,   // P_RHO               -0.000490
	DOUBLENUM,   // P_IV                0.640130
	LONGNUM,     // P_VOLUME            550.000000
	LONGNUM,     // STRIKE_DISTANCE     208.000000
	DOUBLENUM,   // STRIKE_DISTANCE_PCT 0.184000
}

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

void readLongNum(char ** interator, void * output) {
	uint64_t * outputPtr = (uint64_t *) output;
	*outputPtr = 0;
	while(**interator != ',') {
		*outputPtr *= 10;
		*outputPtr += **interator - '0';
		(*interator)++;
	}
	(*interator)++;
}

// Repeated whiles but I don't want to fix it.
void readDateAndTime(char ** interator, void * output) {
	DateAndTime * outputPtr = (DateAndTime *) output;
	Date * date = &outputPtr->date;
	Time * time = &outputPtr->time;
	*date.year = 0;
	while(**interator != '-') {
		*date.year *= 10;
		*date.year += **interator - '0';
		(*interator)++;
	}
	(*interator)++;

	*date.month = 0;
	while(**interator != '-') {
		*date.month *= 10;
		*date.month += **interator - '0';
		(*interator)++;
	}
	(*interator)++;

	*date.day = 0;
	while(**interator != ' ') {
		*date.day *= 10;
		*date.day += **interator - '0';
		(*interator)++;
	}
	(*interator)++;

	uint16_t tempMinutes = 0;

	tempMinutes = 0;
	while(**interator != ':') {
		tempMinutes *= 10;
		tempMinutes += **interator - '0';
		(*interator)++;
	}
	(*interator)++;

	tempMinutes *= 60;
	while(**interator != ',') {
		*time.minutes = 0; *= 10;
		*time.minutes += **interator - '0';
		(*interator)++;
	}
	(*interator)++;

	*time.minutes += tempMinutes;
}

void readDate(char ** interator, void * output) {
	Date * outputPtr = (Date *) output;
	*date.year = 0;
	while(**interator != '-') {
		*date.year *= 10;
		*date.year += **interator - '0';
		(*interator)++;
	}
	(*interator)++;

	*date.month = 0;
	while(**interator != '-') {
		*date.month *= 10;
		*date.month += **interator - '0';
		(*interator)++;
	}
	(*interator)++;

	*date.day = 0;
	while(**interator != ' ') {
		*date.day *= 10;
		*date.day += **interator - '0';
		(*interator)++;
	}
	(*interator)++;
}

void readDouble(char ** interator, void * output) {
	Date * outputPtr = (Date *) output;

}



