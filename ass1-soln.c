/* Solution to comp20005 Assignment 1, 2022 semester 1.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Tristan Thomas
   Datesd:     19/4/2022

*/

/* Preprocessor declarations */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ROWS 10000
#define FIRST_WEEK 0
#define STAGE1 1
#define STAGE2 2
#define STAGE3 3
#define MIN 0
#define MAX 1
#define MAX_MONTHS 12
#define MAX_YEARS MAX_ROWS / 52
#define OVERALL 13
#define MAX_MONTH_STR_LEN 9
#define NESTED_MONTH_COLS 4
#define NESTED_MONTH_MONTH 0
#define NESTED_MONTH_WEEKS 1
#define NESTED_MONTH_AVG 2
#define NESTED_MONTH_CONF 3
#define NESTED_YEAR_COLS 3
#define NESTED_YEAR_YEAR 0
#define NESTED_YEAR_MIN 1
#define NESTED_YEAR_MAX 2
#define POINTS_PER_CHAR 200
#define MAX_PRICE 100000
#define MAX_MARKER MAX_PRICE / POINTS_PER_CHAR
#define MARKER '*'
#define NULL_BYTE '\0'

/* Typedefs */






/* Function prototypes */
int read_par_arrays(int dates[], int days[], int months[], int years[], 
    double prices[], int max_rows);
void print_one_row(int days[], int months[], int years[], double prices[], 
    int index);
void discard_header();
void do_stage1(int days[], int months[], int years[], double prices[], 
    int nrows, int stage);
void do_stage2(int months[], double prices[], int nrows, int stage);
void do_stage3(int years[], double prices[], int nrows, int stage);
void print_stage(int stage);
double min_perc_gain(double prices[], int n, int *min_index);
double max_perc_gain(double prices[], int n, int *max_index);
double perc_gain(double prices[], int index1, int index2);
void print_gain(int days[], int months[], int years[], double gain, 
    int index, int type);
void print_tot_gain(int n, double gain);
int monthly_stats(double month_stats[][NESTED_MONTH_COLS], int months[], 
    double prices[], int n);
double avg_gain(double gains[], int num_weeks);
double sum_arr(double arr[], int n);
double conf_int(double gains[], int num_weeks, double avg);
double std_dev(double gains[], int num_weeks, double avg);
void print_month_stats(double month_stats[][NESTED_MONTH_COLS], int nmonths, 
    int stage);
int yearly_stats(double year_stats[][NESTED_YEAR_COLS], int years[], 
    double prices[], int n);
double min_price(double prices[], int start, int finish);
double max_price(double prices[], int start, int finish);
void print_year_stats(double year_stats[][NESTED_YEAR_COLS], 
    double prices[], int n, int nyears, int stage);
void form_graph(double year_stats[][NESTED_YEAR_COLS], 
    char graph_string[MAX_MARKER], int year_index);
int round_up(double num);
void ta_da();




/* ============================== Main function ============================= */

int
main(int argc, char *argv[]) {
    int nrows;
    int dates[MAX_ROWS], days[MAX_ROWS], months[MAX_ROWS], years[MAX_ROWS];
    double asx[MAX_ROWS];
    
    nrows = read_par_arrays(dates, days, months, years, asx, MAX_ROWS);

    do_stage1(days, months, years, asx, nrows, STAGE1);
    do_stage2(months, asx, nrows, STAGE2);
    do_stage3(years, asx, nrows, STAGE3);
    
    ta_da();
   
	return 0;
}

/* ========================================================================== */

/* Function that reads the 5 data columns into parallel arrays 
** give credit for this code */

int read_par_arrays(int dates[], int days[], int months[], int years[], 
        double prices[], int max_rows) {
    int nrows = 0;
    int date, day, month, year;
    double price;
    
    /* discards header line */
    discard_header();
    
    
    /* reads data into 5 arrays */
    while (scanf("%d %d %d %d %lf", &date, &day, &month, 
            &year, &price) == 5) {
        
        dates[nrows] = date;
        days[nrows] = day;
        months[nrows] = month;
        years[nrows] = year;
        prices[nrows] = price;
        nrows++;

    }

    /* returns the number of rows read */
    return nrows;
}


/* ========================================================================== */

/* discards the header of the input file */
void discard_header() {
    char ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            return;
        }
    }
}



/* ================================= Stage 1 ================================ */

/* stage one outputs the following 
    - price at week 1
    - price at the last week
    - min weekly percentage gain over period
    - max weekly percentage gain over period
    - total percentage gain over the period */

void do_stage1(int days[], int months[], int years[], double prices[], 
        int nrows, int stage) {
    double min_gain, max_gain, tot_gain;
    int max_index, min_index;

    min_gain = min_perc_gain(prices, nrows, &min_index);
    max_gain = max_perc_gain(prices, nrows, &max_index);
    tot_gain = perc_gain(prices, FIRST_WEEK, nrows - 1);
    
    /* prints first and last data points */
    print_stage(stage);
    print_one_row(days, months, years, prices, FIRST_WEEK);
    print_stage(stage);
    print_one_row(days, months, years, prices, nrows - 1);

    /* prints gains */
    print_stage(stage);
    print_gain(days, months, years, min_gain, min_index, MIN);
    print_stage(stage);
    print_gain(days, months, years, max_gain, max_index, MAX);
    print_stage(stage);
    print_tot_gain(nrows, tot_gain);
}


/* ================================= Stage 2 ================================ */

/* stage two outputs the following
    - average weekly gain for each month
    - confidence interval for each month using standard deviation */
 
 void do_stage2(int months[], double prices[], int nrows, int stage) {
    double month_stats[MAX_MONTHS + 1][NESTED_MONTH_COLS];
    int nmonths;

    /* fills array with number of weeks, average gains and 95% confidence 
     * interval for each month */
    nmonths = monthly_stats(month_stats, months, prices, nrows);
    
    print_month_stats(month_stats, nmonths, stage);
    printf("\n");

 }



/* ================================= Stage 3 ================================ */

/* stage three outputs the following
    - min and max asx values for each year
    - tabulates yearly data into multiple 200 index point groups */

void do_stage3(int years[], double prices[], int nrows, int stage) {
    double year_stats[MAX_YEARS][NESTED_YEAR_COLS];
    int nyears;

    nyears = yearly_stats(year_stats, years, prices, nrows);

    print_year_stats(year_stats, prices, nrows, nyears, STAGE3);

    printf("\n");

}



/* ========================================================================== */
/* prints 'ta daa!' (indicating finish) */

void ta_da() {

    printf("ta daa!\n");

}

/* ========================================================================== */

/* calculates gain between two values of array */
double perc_gain(double prices[], int index1, int index2) {

    return 100.0 * (prices[index2] - prices[index1]) / prices[index1];

}


/* ========================================================================== */

/* calculates the minimum percentage gain over the period */

double min_perc_gain(double prices[], int n, int *min_index) {
    double min_gain, gain;

    for (int i = 0; i < n - 1; i++) {

        gain = perc_gain(prices, i, i + 1);

        if (gain < min_gain || i == 0) {

            min_gain = gain;
            *min_index = i + 1;

        }

    }

    return min_gain;

}

/* ========================================================================== */

/* calculates the maximum percentage gain over the period */
double max_perc_gain(double prices[], int n, int *max_index) {
    double max_gain, gain;

    for (int i = 0; i < n - 1; i++) {

        gain = perc_gain(prices, i, i + 1);

        if (gain > max_gain || i == 0) {

            max_gain = gain;
            *max_index = i + 1; // incremented because gain at end of week

        }
    }

    return max_gain;

}


/* ========================================================================== */

/* finds the average gain and confidence interval for each month 
 * and puts into array */

int monthly_stats(double month_stats[][NESTED_MONTH_COLS], int months[], 
        double prices[], int n) {
    double gains[MAX_ROWS];
    int num_weeks, nmonths = 0;
    
    // iterates through the months plus an extra index for overall stats
    for (int month = 1; month <= MAX_MONTHS + 1; month++) {

        num_weeks = 0; // buddy variable to gains

        for (int i = 1; i < n; i++) {

            if (months[i] == month) {

                gains[num_weeks] = perc_gain(prices, i - 1, i);
                num_weeks++;

            } else if (month == OVERALL) {

                gains[num_weeks] = perc_gain(prices, i - 1, i);
                num_weeks++;

            }
        }
        if (num_weeks) {

            month_stats[nmonths][NESTED_MONTH_MONTH] = month;
            month_stats[nmonths][NESTED_MONTH_WEEKS] = num_weeks;
            month_stats[nmonths][NESTED_MONTH_AVG] = avg_gain(gains, 
                num_weeks);
            month_stats[nmonths][NESTED_MONTH_CONF] = conf_int(gains, 
                num_weeks, month_stats[nmonths][NESTED_MONTH_AVG]);
            
            nmonths++; // buddy variable for month_stats

        }
    }

    return nmonths;

}


/* ========================================================================== */

/* calculates the average gain given sum and number of elements */
double avg_gain(double gains[], int num_weeks) {

    return sum_arr(gains, num_weeks) / num_weeks;

}


/* ========================================================================== */

/* calculates the sum of the elements of an array */
double sum_arr(double arr[], int n) {
    double sum = 0;

    for (int i = 0; i < n; i++) {

        sum += arr[i];

    }

    return sum;

}


/* ========================================================================== */

/* calculates the confidence interval */

double conf_int(double gains[], int num_weeks, double avg) {

    return 1.96 * std_dev(gains, num_weeks, avg) / sqrt(num_weeks);

}


/* ========================================================================== */

/* calculates the standard deviation */

double std_dev(double gains[], int num_weeks, double avg) {
    double sum = 0;

    for (int i = 0; i < num_weeks; i++) {

        sum += ((gains[i] - avg) * (gains[i] - avg)) / (num_weeks - 1);

    }

    return sqrt(sum);

}



/* ========================================================================== */

/* for each year calculates the minimum and maximum prices and adds 
 * to nested array */

int yearly_stats(double year_stats[][NESTED_YEAR_COLS], int years[], 
        double prices[], int n) {
    int nyears = 0, j = 0;

    for (int i = 0; i < n; i++) {
        
        if (years[i] != years[i + 1]) {

            year_stats[nyears][NESTED_YEAR_YEAR] = years[i];
            year_stats[nyears][NESTED_YEAR_MIN] = min_price(prices, j, i);
            year_stats[nyears][NESTED_YEAR_MAX] = max_price(prices, j, i);
            nyears++;
            /* offset by one to avoid starting at the last element 
             * of the previous year */
            j = i + 1; 

        }

    }

    return nyears;

}



/* ========================================================================== */

/* calculates the minimum value of a given array between two indexes */
double min_price(double prices[], int start, int finish) {
    double min = prices[start];

    for (int i = start; i <= finish; i++) {

        if (prices[i] < min) {

            min = prices[i];

        }

    }

    return min;

}




/* ========================================================================== */

/* calculates the maximum value of a given array between two indexes */
double max_price(double prices[], int start, int finish) {
    double max = prices[start];

    for (int i = start; i <= finish; i++) {

        if (prices[i] > max) {

            max = prices[i];

        }

    }

    return max;

}




/* ============================ Helper Functions ============================ */

/* prints the section number */
void print_stage(int stage) {

    printf("S%d, ", stage);

}

/* ========================================================================== */

/* prints out a single row of the inputed data based on the inputted index */

void print_one_row(int days[], int months[], int years[], double price[], 
        int index) {

    printf("week ending %02d/%02d/%d,   asx = %5.1f\n", days[index], 
        months[index], years[index], price[index]);

}



/* ========================================================================== */

/* prints out the percentage gains for stage 1 */
void print_gain(int days[], int months[], int years[], double gain, 
        int index, int type) {

    printf("%s weekly gain on %02d/%02d/%d = %6.2f%%\n", type ? "max" : "min", 
        days[index], months[index], years[index], gain);

}


/* ========================================================================== */

/* prints out the total gain over period for stage 1 */
void print_tot_gain(int n, double gain) {

    printf("change over  %4d week period = %6.2f%%\n\n", n - 1, gain);

}


/* ========================================================================== */

/* prints out the monthly gain stats for each month covered */

void print_month_stats(double month_stats[][NESTED_MONTH_COLS], 
        int nmonths, int stage) {

    // array of months plus overall
    char month_num[MAX_MONTHS + 1][MAX_MONTH_STR_LEN + 1] = 
            {"January", "February", "March", "April", "May", "June", 
            "July", "August", "September", "October", "November", 
            "December", "Overall"};

    for (int i = 0; i < nmonths; i++) {

        print_stage(stage);
        printf("%-9s :%5.f Fridays, average gain = %5.2f%%, ci95 +- %.2f%%\n", 
            month_num[(int) month_stats[i][NESTED_MONTH_MONTH] - 1], 
            month_stats[i][NESTED_MONTH_WEEKS], 
            month_stats[i][NESTED_MONTH_AVG], 
            month_stats[i][NESTED_MONTH_CONF]);

    }

}



/* ========================================================================== */

/* prints out yearly min and max stats for each year covered */
void print_year_stats(double year_stats[][NESTED_YEAR_COLS], 
        double prices[], int n, int nyears, int stage) {
    int max_chars = round_up(max_price(prices, 0, n - 1) / 
        POINTS_PER_CHAR) + 1;
    char graph[max_chars];
    
    for (int i = 0; i < nyears; i++) {

        form_graph(year_stats, graph, i);

        print_stage(stage);
        printf("%.f | %6.1f-- %-5.1f |%s\n", year_stats[i][NESTED_YEAR_YEAR], 
            year_stats[i][NESTED_YEAR_MIN], year_stats[i][NESTED_YEAR_MAX], 
            graph);

    }
    
}


/* ========================================================================== */

/* prints out the graph corresponding to min and max values */
void form_graph(double year_stats[][NESTED_YEAR_COLS], char graph_string[], 
        int year_index) {
    int min_pos = round_up(year_stats[year_index][NESTED_YEAR_MIN] 
        / POINTS_PER_CHAR);
    int max_pos = round_up(year_stats[year_index][NESTED_YEAR_MAX] 
        / POINTS_PER_CHAR);

    // adds the requried chars to the string (-1 there due to rounding up)
    for (int i = 0; i < min_pos - 1; i++) {

        graph_string[i] = ' ';

    }

    for (int i = min_pos - 1; i < max_pos; i++) {

        graph_string[i] = MARKER;

    }
    
    graph_string[max_pos] = NULL_BYTE; 

}

               
/* ========================================================================== */

/* rounds up the positive floating point numbers and returns as int */
int round_up(double num) {
    
    return (int) num + 1;

}

/* programming is fun */
