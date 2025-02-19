#include "includes/ComplexNums.h"

complexNum* Get_SinusoidalBasis(double kt) {

    complexNum *result = malloc(sizeof(complexNum));

    //Should I add 2pi to this?: k x 2pi x t
    result->realPart = cosf(kt); 
    result->imaginaryPart = -sin(kt);

    return result;
}

complexNum* Set_Z(double angle, double magnitude_r, int n) {

    complexNum *z = Get_SinusoidalBasis(angle);

    //Simulating magnitude = magnitude ^ 0
    if (n == 0) { magnitude_r = 1; }
    
    //Simulating magnitude = magnitude ^ n
    if (n > 1) { 
        
        for (int i = 2; i <= n; i++) { magnitude_r *= magnitude_r; }
     }

    //Simulating magnitude = magnitude ^ 1
    z->realPart *= (1 / magnitude_r);
    z->imaginaryPart *= (1 / magnitude_r);

    return z;
}

complexNum* ValuetoComplexNum(double *realValues, int numOfValues) {

    complexNum *cNum = malloc(numOfValues * sizeof(complexNum));
    for (int i = 0; i < numOfValues; i++) {
        cNum[i].realPart = realValues[i];
        cNum[i].imaginaryPart = 0.0;
    }

    return cNum;
}

void recycle_complex_num(complexNum *z) {
    free(z);
}


/*
 * 			TO-DO
 * 			-----
 *  - 
 *
 *  - 
 *  
 *  - 
 *  */

