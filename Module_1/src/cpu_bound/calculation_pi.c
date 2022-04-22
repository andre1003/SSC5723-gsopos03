#include "calculation_pi.h"

// Imports
#include <stdlib.h>
#include <stdio.h>

// Function to calculate Pi (Monte Carlo)
double calculation_pi(unsigned long n_points) {
    // Variables for the calculation
    double x, y;
    unsigned long i, hit;

    hit = 0;

    for(i = 0; i < n_points ; i++) {
        // Generate coordinates x, y
        x = ((double) rand() / (RAND_MAX));
        y = ((double) rand() / (RAND_MAX));
       
        // Point inside the circle
        if(((x * x) + (y * y)) <= 1)
            hit++;
    }

    // Pi calculation
    return (4.0 * ((double) hit) / ((double) n_points));
}
