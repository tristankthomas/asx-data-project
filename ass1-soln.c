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
   Dated:     19/4/2022

*/

/* Preprocessor declarations */
#include <stdio.h>
#define MAXVALS 10000

/* Function prototypes */
int read_par_arrays(int D1[], int D2[], int D3[], int D4[], double F[], int maxvals);


/* Main function scafolding */
int
main(int argc, char *argv[]) {
    int nnumbs;
    int date[MAXVALS], day[MAXVALS], month[MAXVALS], year[MAXVALS];
    double asx[MAXVALS];

	nnumbs = read_par_arrays(date, day, month, year, asx, MAXVALS);

    // prints arrays for test
    for (int i = 0; i < nnumbs; i++) {
        printf("%d %d %d %d %.1f\n", date[i], day[i], month[i], year[i], asx[i]);
    }

	return 0;
}

/****************************************************************************/
/* Function that reads the 5 data columns into parallel arrays 
** give credit for this code */

int read_par_arrays(int D1[], int D2[], int D3[], int D4[], double F[], int maxvals) {
    int n = 0, excess = 0, ch;
    int num1, num2, num3, num4;
    double num5;
    
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }
    }

    while (scanf("%d %d %d %d %lf", &num1, &num2, &num3, &num4, &num5) == 5) {
        if (n == maxvals) {
            excess += 1;
        } else {
            D1[n] = num1;
            D2[n] = num2;
            D3[n] = num3;
            D4[n] = num4;
            F[n] = num5;
            n++;
        }

    }
    return n;
}

