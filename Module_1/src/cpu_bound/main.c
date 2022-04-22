// Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp() function
#include <time.h>
#include <math.h> // Pow

#include "calculation_pi.h"

int main(int argc, char **argv) {
    int err;                // Auxiliar variable for validation
    int exp_number;         // Exponential number
    int n;                  // Loop iteration
    unsigned long n_points; // Number of points
    double result;          // Result

    if(argc < 2) {
        fprintf(stderr, "Error: No exponential number given!\n");
        return EXIT_FAILURE;
    }

    err = sscanf(argv[1], "%d", &exp_number);

    // Exponential number is an integer number?
    if(err == 0) {
        printf("Error: '%s' is not an integer number!\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    // Exponential number validation
    if(!((exp_number >= 3) && (exp_number <= 10))) {
        printf("Error: exponential number must be between 3 and 10!\n");
        return EXIT_FAILURE;
    }

    // Number of points
    n_points = pow(10, exp_number);

    srand(time(NULL));                 // Seed to generate random values
    result = calculation_pi(n_points); // Pi calculation

    printf(">> Result = %lf\n", result); // Final result (Pi value)

    return 0;
}
