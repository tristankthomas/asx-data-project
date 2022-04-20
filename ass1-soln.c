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
#define MAXROWS 10000
#define FIRSTWEEK 0
#define STAGE1 1
#define STAGE2 2
#define STAGE3 3
#define MIN 0
#define MAX 1

/* Function prototypes */
int read_par_arrays(int dates[], int days[], int months[], int years[], 
    double prices[], int max_rows);
void print_one_row(int days[], int months[], int years[], double prices[], int index);
void discard_header();
void do_stage1(int days[], int months[], int years[], double prices[], int nrows, int stage);
void print_stage(int stage);
double min_per_gain(double prices[], int n, int *min_index);
double max_per_gain(double prices[], int n, int *max_index);
double tot_per_gain(double prices[], int n);
void print_gain(int days[], int months[], int years[], double gain, int index, int type);
void print_tot_gain(int n, double gain);


/* ************************************************************************** */

/* Main function scafolding */
int
main(int argc, char *argv[]) {
    int nrows;
    int dates[MAXROWS], days[MAXROWS], months[MAXROWS], years[MAXROWS];
    double asx[MAXROWS];
    
    nrows = read_par_arrays(dates, days, months, years, asx, MAXROWS);

    /* SECTION 1 */
    do_stage1(days, months, years, asx, nrows, STAGE1);

    /*
    // prints arrays for test
    for (int i = 0; i < nnumbs; i++) {
        printf("%d %d %d %d %.1f\n", dates[i], days[i], months[i], years[i], prices[i]);
    }
    */
	return 0;
}

/******************************************************************************/

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
    while (scanf("%d %d %d %d %lf", &date, &day, &month, &year, &price) == 5) {
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


/* ************************************************************************** */

/* discards the header of the input file */
void discard_header() {
    char ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            return;
        }
    }
}



/* ************************************************************************** */

/* stage one outputs the following 
    - price at week 1
    - price at the last week
    - min weekly percentage gain over period
    - max weekly percentage gain over period
    - total percentage gain over the period */

void do_stage1(int days[], int months[], int years[], double prices[], int nrows, int stage) {
    double min_gain, max_gain, tot_gain;
    int max_index, min_index;
    min_gain = min_per_gain(prices, nrows, &min_index);
    max_gain = max_per_gain(prices, nrows, &max_index);
    tot_gain = tot_per_gain(prices, nrows);
    
    /* prints first and last data points */
    print_stage(stage);
    print_one_row(days, months, years, prices, FIRSTWEEK);
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


/* ************************************************************************** */

/* calculates the minimum percentage gain over the period */

double min_per_gain(double prices[], int n, int *min_index) {
    double min_gain, gain;
    for (int i = 0; i < n - 1; i++) {
        gain = 100 * (prices[i + 1] - prices[i]) / prices[i];
        if (gain < min_gain || i == 0) {
            min_gain = gain;
            *min_index = i;
        }
    }
    return min_gain;
}

/* ************************************************************************** */

/* calculates the maximum percentage gain over the period */
double max_per_gain(double prices[], int n, int *max_index) {
    double max_gain, gain;
    for (int i = 0; i < n - 1; i++) {
        gain = 100 * (prices[i + 1] - prices[i]) / prices[i];
        if (gain > max_gain || i == 0) {
            max_gain = gain;
            *max_index = i;
        }
    }
    return max_gain;
}

/* ************************************************************************** */

/* calculates the total percentage gain over the period */
double tot_per_gain(double prices[], int n) {
    return 100 * (prices[n - 1] - prices[0]) / prices[0];
}

/* ****************************** Helper Functons ************************** */

/* prints the section number */
void print_stage(int stage) {
    printf("S%d, ", stage);
}

/* ************************************************************************** */

/* prints out a single row of the inputed data based on the inputted index */

void print_one_row(int days[], int months[], int years[], double price[], int index) {
    printf("week ending %02d/%02d/%d,   asx = %5.1f\n", 
        days[index], months[index], years[index], price[index]);
}



/* ************************************************************************** */

/* prints out the percentage gains for stage 1 */
void print_gain(int days[], int months[], int years[], double gain, int index, int type) {
    printf("%s weekly gain on %02d/%02d/%d = %5.2f%%\n", type ? "max" : "min", 
        days[index], months[index], years[index], gain);
}


/* ************************************************************************** */

/* prints out the total gain over period for stage 1 */
void print_tot_gain(int n, double gain) {
    printf("change over     %d week period = %5.2f%%\n", n - 1, gain);
}
