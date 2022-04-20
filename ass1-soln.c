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

/* Function prototypes */
int read_par_arrays(int dates[], int days[], int months[], int years[], 
    double prices[], int max_rows);
void print_dates(int days[], int months[], int years[], double prices[], int index);
void discard_header();


/* ************************************************************************** */

/* Main function scafolding */
int
main(int argc, char *argv[]) {
    int nrows;
    int dates[MAXROWS], days[MAXROWS], months[MAXROWS], years[MAXROWS];
    double asx[MAXROWS];
    
    nrows = read_par_arrays(dates, days, months, years, asx, MAXROWS);

    /* SECTION 1 */

    print_dates(days, months, years, asx, FIRSTWEEK);
    print_dates(days, months, years, asx, nrows - 1);







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
/* prints out a single row of the inputed data based on the inputted index */

void print_dates(int days[], int months[], int years[], double price[], int index) {
    printf("S1, week ending %d/%02d/%d,    prices = %.1f\n", 
        days[index], months[index], years[index], price[index]);
}


/* ************************************************************************** */