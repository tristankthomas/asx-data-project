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

/* ========================================================================== */

/* -- Library inclusions -- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* -- Defining constants -- */
#define MAX_ROWS 10000
#define FIRST_WEEK 0
#define MIN 0
#define MAX 1

#define STAGE1 1
#define STAGE2 2
#define STAGE3 3

#define MAX_MONTHS 12
#define OVERALL 13
#define MAX_MONTH_STR_LEN 9

#define POINTS_PER_CHAR 200
#define MARKER '*'

/* --- Type definitions --- */
typedef int weeks_t[MAX_ROWS];
typedef double prices_t[MAX_ROWS];

typedef char month_t[MAX_MONTH_STR_LEN + 1];
typedef month_t month_arr_t[MAX_MONTHS + 1];


/* -- Function prototypes - */
int read_par_arrays(int dates[], int days[], int months[], int years[], 
    double prices[], int max_rows);
void do_stage1(int days[], int months[], int years[], double prices[], 
    int nrows, int stage);
void do_stage2(int months[], double prices[], int nrows, int stage);
void do_stage3(int years[], double prices[], int nrows, int stage);
void ta_da(void);
double min_perc_gain(double prices[], int nrows, int *min_index);
double max_perc_gain(double prices[], int nrows, int *max_index);
double perc_gain(double prices[], int week1, int week2);
void print_stage(int stage);
void print_one_week(int days[], int months[], int years[], double prices[], 
    int index);
void print_gain(int days[], int months[], int years[], double gain, 
    int index, int type);
double avg_gain(double gains[], int num_weeks);
double sum_arr(double arr[], int n);
double conf_int(double gains[], int num_weeks, double avg);
double std_dev(double gains[], int num_weeks, double avg);
double min_price(double prices[], int start, int finish);
double max_price(double prices[], int start, int finish);
void form_graph(int min_pos, int max_pos, char graph_string[]);
int round_up(double num);
void error_and_exit(char *err, int line);




/* ============================== Main function ============================= */

int main(int argc, char *argv[]) {
    int nrows;
    weeks_t dates = {0}, days = {0}, months = {0}, years = {0};
    prices_t asx = {0};
    
    nrows = read_par_arrays(dates, days, months, years, asx, MAX_ROWS);

    do_stage1(days, months, years, asx, nrows, STAGE1);
    do_stage2(months, asx, nrows, STAGE2);
    do_stage3(years, asx, nrows, STAGE3);
    
    ta_da();
   
	return 0;
}


/* ========================= Reading input function ========================= */

/* This function was adapted from two functions provided as Figure 4.1.3
    on page 58 and Figure 7.2 on page 102 of the subject textbook,
    written by Alistair Moffat, and accessed via
    https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/
    Altered to sort parallel arrays and detect a line of chars */

/* Reads the 5 data columns into parallel arrays */

    

int read_par_arrays(int dates[], int days[], int months[], int years[], 
        double prices[], int max_rows) {
    int nrows = 0;
    int date, day, month, year;
    double price;
    
    /* discards header line */
    char ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }
    }
    
    /* reads data into 5 parallel arrays */
    while (scanf("%d %d %d %d %lf", &date, &day, &month, 
            &year, &price) == 5) {
        
        if (nrows == MAX_ROWS) {

            error_and_exit("Too much input data", __LINE__);

        }
        
        dates[nrows] = date;
        days[nrows] = day;
        months[nrows] = month;
        years[nrows] = year;
        prices[nrows] = price;
        nrows++;

    }

    /* returns the number of rows read (buddy variable to arrays) */
    return nrows;
}


/* ================================= Stage 1 ================================ */

/* The names of the next three functions were taken from the sample solution, 
    written by Alistair Moffat, and accessed via the LMS */

/* Stage one outputs the following 
    - price at week 1
    - price at the last week
    - min weekly percentage gain over period
    - max weekly percentage gain over period
    - total percentage gain over the period */

void do_stage1(int days[], int months[], int years[], double prices[], 
        int nrows, int stage) {
    double min_gain, max_gain, tot_gain;
    int max_index = 0, min_index = 0;

    /* calculates the percentage gains */
    min_gain = min_perc_gain(prices, nrows, &min_index);
    max_gain = max_perc_gain(prices, nrows, &max_index);
    tot_gain = perc_gain(prices, FIRST_WEEK, nrows - 1);
    
    /* prints first and last data points */
    print_stage(stage);
    print_one_week(days, months, years, prices, FIRST_WEEK);
    print_stage(stage);
    print_one_week(days, months, years, prices, nrows - 1);

    /* prints percentage gains */
    print_stage(stage);
    print_gain(days, months, years, min_gain, min_index, MIN);
    print_stage(stage);
    print_gain(days, months, years, max_gain, max_index, MAX);
    print_stage(stage);
    printf("change over  %4d week period = %6.2f%%\n", nrows - 1, tot_gain);

    printf("\n");

}



/* ================================= Stage 2 ================================ */

/* Stage two outputs the following
    - average weekly gain for each month
    - confidence interval for each month using standard deviation */
 
 void do_stage2(int months[], double prices[], int nrows, int stage) {
     /* array sizes are months plus 1 to accomodate the overall stats */
    double gains[MAX_ROWS];
    int num_weeks;
    month_arr_t month_arr = {"January", "February", "March", "April", "May", 
            "June", "July", "August", "September", "October", "November", 
            "December", "Overall"};
    
    /* iterates through the months plus an extra index for overall stats */
    for (int month = 1; month <= MAX_MONTHS + 1; month++) {

        num_weeks = 0; // buddy variable to gains

        /* iterates through the input month array to fill the gains array for a 
           particular month */
        for (int i = 1; i < nrows; i++) {

            if (months[i] == month || month == OVERALL) {

                gains[num_weeks] = perc_gain(prices, i - 1, i);
                num_weeks++;

            }

        }

        /* if the month is present in input (indicated by num_weeks) then 
           the monthly stats for that month are printed using gains */
        if (num_weeks) {
 
            print_stage(stage);
            printf("%-9s :%5d Fridays, average gain = %5.2f%%, ci95 +- "
                "%.2f%%\n", month_arr[month - 1], num_weeks, 
                avg_gain(gains, num_weeks), conf_int(gains, num_weeks, 
                avg_gain(gains, num_weeks)));

        }
    }

    printf("\n");

 }



/* ================================= Stage 3 ================================ */

/* Stage three outputs the following
    - min and max asx values for each year
    - tabulates yearly data into multiple 200 index point groups */

void do_stage3(int years[], double prices[], int nrows, int stage) {
    int prev_i = 0;
    /* calculates maximum characters the graph should have */
    int max_chars = round_up(max_price(prices, 0, nrows - 1) / 
        POINTS_PER_CHAR) + 1;
    char graph[max_chars];
    double min = 0, max = 0;
    
    for (int i = 0; i < nrows; i++) {
        /* once year changes the min and max price up to that point for the
           preceding year are found */
        if (years[i] != years[i + 1]) {
            min = min_price(prices, prev_i, i);
            max = max_price(prices, prev_i, i);

            /* forms the appropriate graph for each year */
            form_graph(round_up(min / POINTS_PER_CHAR), 
                round_up(max /POINTS_PER_CHAR), graph);

            /* prints data in appropriate format */
            print_stage(stage);
            printf("%d | %6.1f--%6.1f |%s\n", years[i], min, max, graph);

            /* offset by one to avoid starting at the last element of the 
               previous year */
            prev_i = i + 1;

        }

    }
    
    printf("\n");

}


/* ========================================================================== */

/* Prints 'ta daa!' (indicating finish) */

void ta_da(void) {

    printf("ta daa!\n");

}


/* ========================================================================== */
/* ============================ Helper functions ============================ */
/* ========================================================================== */



/* ====================== Calculation helper functions ====================== */

/* Calculates gain between two values of array */
double perc_gain(double prices[], int week1, int week2) {

    return 100.0 * (prices[week2] - prices[week1]) / prices[week1];

}


/* ========================================================================== */

/* calculates the minimum percentage gain over the period */

double min_perc_gain(double prices[], int nrows, int *min_index) {
    double min_gain = 0, gain;

    for (int i = 0; i < nrows - 1; i++) {

        gain = perc_gain(prices, i, i + 1);

        if (gain < min_gain || i == 0) {

            min_gain = gain;
            /* incremented because gain at end of week */
            *min_index = i + 1;

        }

    }

    return min_gain;

}

/* ========================================================================== */

/* Calculates the maximum percentage gain over the period */
double max_perc_gain(double prices[], int nrows, int *max_index) {
    double max_gain = 0, gain;

    for (int i = 0; i < nrows - 1; i++) {

        gain = perc_gain(prices, i, i + 1);

        if (gain > max_gain || i == 0) {

            max_gain = gain;
            /* incremented because gain at end of week */
            *max_index = i + 1; 

        }
    }

    return max_gain;

}


/* ========================================================================== */

/* Calculates the average gain given sum and number of elements */
double avg_gain(double gains[], int num_weeks) {

    return sum_arr(gains, num_weeks) / num_weeks;

}


/* ========================================================================== */

/* Calculates the sum of the elements of an array */
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

/* Calculates the standard deviation */
double std_dev(double gains[], int num_weeks, double avg) {
    double sum = 0;

    for (int i = 0; i < num_weeks; i++) {

        sum += ((gains[i] - avg) * (gains[i] - avg)) / (num_weeks - 1);

    }

    return sqrt(sum);

}



/* ========================================================================== */

/* Calculates the minimum value of a given array between two indexes */
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

/* Calculates the maximum value of a given array between two indexes */
double max_price(double prices[], int start, int finish) {
    double max = prices[start];

    for (int i = start; i <= finish; i++) {

        if (prices[i] > max) {

            max = prices[i];

        }

    }

    return max;

}


/* ========================================================================== */

/* Rounds up the positive floating point numbers and returns as int */
int round_up(double num) {

    return (int) num + 1;

}



/* ======================= Formatting helper functions ====================== */

/* This function was taken from the sample solution, written by Alistair 
    Moffat, and accessed via the LMS */

/* Prints the error message and exits the program */
void error_and_exit(char *err, int line) {

	printf("Problem at line %3d: %s\n", line, err);
	exit(EXIT_FAILURE);

}

/* ========================================================================== */

/* This function was taken from the sample solution, written by Alistair 
    Moffat, and accessed via the LMS */

/* Prints the stage number */
void print_stage(int stage) {

    printf("S%d, ", stage);

}

/* ========================================================================== */

/* prints out a single row of the inputed data based on the inputted index */

void print_one_week(int days[], int months[], int years[], double price[], 
        int index) {

    printf("week ending %02d/%02d/%d,   asx = %5.1f\n", days[index], 
        months[index], years[index], price[index]);

}



/* ========================================================================== */

/* Prints out the percentage gains for stage 1 */
void print_gain(int days[], int months[], int years[], double gain, 
        int index, int type) {

    printf("%s weekly gain on %02d/%02d/%d = %6.2f%%\n", type ? "max" : "min", 
        days[index], months[index], years[index], gain);

}


/* ========================================================================== */

/* Prints out the graph corresponding to min and max values */
void form_graph(int min_pos, int max_pos, char graph_string[]) {
    // adds the requried chars to the string (-1 there due to rounding up)
    for (int i = 0; i < min_pos - 1; i++) {

        graph_string[i] = ' ';

    }

    for (int i = min_pos - 1; i < max_pos; i++) {

        graph_string[i] = MARKER;

    }
    
    graph_string[max_pos] = '\0'; 

}

/* ========================================================================== */

/* programming is fun */
