#ifndef FOURER_TRANSFORM_H
#define FOURIER_TRANSFORM_H
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "ComplexNums.h"

typedef struct binData frequencyBin_data;

//DECLARATIONS
/**
 * @brief Run a fourier transform on signal sample data and output 
 *        the signal's frequency information.
 * 
 * @param sample_values Signal samples 
 * @param samples_per_sec Number of samples taken per second (Sample Frequency)
 * @return ** frequencyBin_data* Frequency domain data for a given signal.
 */
frequencyBin_data* fourier_transform(float *sample_values, int const samples_per_sec);
/**
 * @brief Run an inverse fourier transform on frequency data and output 
 *        the values needed to create a signal of the given frequencies.
 * 
 * @param frequency_values Desired Frequencies
 * @param samples_per_sec Desired FIR tap-size
 * @return ** complexNum* Values to be used as FIR Coefficients
 */
complexNum* IDFT(float *frequency_values, int const samples_per_sec);

/**
 * @brief Deallocate memory allocated to frequency_bins
 * 
 * @param frequency_bins Frequency domain data for a given signal.
 */
void fourier_transform_deinit(frequencyBin_data* frequency_bins);

/**
 * @brief Deallocate memory allocated to sample_coefficients
 * 
 * @param sample_coefficients Values to be used as FIR Coefficients
 */
void IDFT_deinit(complexNum* sample_coefficients);


//Structs
struct binData {
    //Fourier Coefficients
    float* realPart;
    float* imaginaryPart;

    float* nyquist_magnitude;
    float* amplitude;
    float* phase; //Ignoring Phase for now...
};

#endif

