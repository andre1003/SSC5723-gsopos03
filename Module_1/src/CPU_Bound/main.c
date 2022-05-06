// CPU bound program

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Function to calculate Pi (Monte Carlo)
double calculation_pi(unsigned long nPoints) {
    // Variables for the calculation
    double x, y;
    unsigned long i, hit;

    hit = 0;

    for(i = 0; i < nPoints ; i++) { // Loop through the number of points
        // Generate coordinates x, y
        x = ((double) rand() / (RAND_MAX));
        y = ((double) rand() / (RAND_MAX));
       
        // Point inside the circle
        if(((x * x) + (y * y)) <= 1)
            hit++;
    }

    // Pi calculation
    return (4.0 * ((double) hit) / ((double) nPoints));
}

int main(int argc, char const *argv[]) {
    // Declaration of variables
    int expNumber;         
    unsigned long nPoints;
    double result;

    printf("###################################\n");
    printf("#            CPU bound            #\n");
    printf("###################################\n\n");

    expNumber = 8; // Exponential number
    // The larger it is, the greater the accuracy and computational cost

    // Number of points
    nPoints = pow(10, expNumber);

    srand(time(NULL)); // Seed to generate random values
    result = calculation_pi(nPoints); // Pi calculation

    printf(">> Pi value = %lf\n", result); // Final result

    return 0;
}