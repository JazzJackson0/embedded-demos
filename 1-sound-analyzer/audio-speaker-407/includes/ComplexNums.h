#ifndef COMPLEX_NUMS_H
#define COMPLEX_NUMS_H
#include <math.h>
#include <stdlib.h>

typedef struct c complexNum;

//DECLARATIONS
/**
 * @brief Ouput a Sinusoidal Basis for a given value.
 * 
 * @param kt Amplitude/Magnitude value
 * @return ** complexNum* Sinusiodal Basis
 */
complexNum* Get_SinusoidalBasis(double kt);
/**
 * @brief Output z-value (Used in Z-Transforms) for a given angle and Magnitude
 * 
 * @param angle Desired angle
 * @param magnitude_r Desired Magnitude/Amplitude value
 * @param n Sample number
 * @return ** complexNum* z-value
 */
complexNum* Set_Z(double angle, double magnitude_r, int n);

/**
 * @brief Convert a set of real values to a set of complex values
 * 
 * @param realValues Set of values to convert
 * @param numOfValues Number of values present in the set.
 * @return ** complexNum* 
 */
complexNum* ValuetoComplexNum(double *realValues, int numOfValues);

/**
 * @brief Deallocate memory allocated to complexNum object
 * 
 * @param z 
 */
void recycle_complex_num(complexNum *z) ;

// Structs
struct c {
    double realPart;
    double imaginaryPart;
};

#endif

