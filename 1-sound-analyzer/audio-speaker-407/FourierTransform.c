#include "includes/FourierTransform.h"

#define PI 3.141592
#define _1HZ (2 * PI)

frequencyBin_data* fourier_transform(float *sample_values, int const samples_per_sec) {

    /*!!!Change this to a "samples_per_sec"-sized pointer with non-pointer elements.
    I think this would save a good bit of space*/

    frequencyBin_data *frequency_bins = malloc(sizeof(frequencyBin_data));
    frequency_bins->realPart = calloc((samples_per_sec / 2), sizeof(float));
    frequency_bins->imaginaryPart = calloc((samples_per_sec / 2), sizeof(float));
    frequency_bins->amplitude = calloc((samples_per_sec / 2), sizeof(float));
    frequency_bins->nyquist_magnitude = calloc((samples_per_sec / 2), sizeof(float));
    frequency_bins->phase = calloc((samples_per_sec / 2), sizeof(float));

    for (int k = 0; k < samples_per_sec / 2; k++) { //Keeping Number of Frequency bins calculated under the Nyquist Limit
        
        for (int n = 0; n < samples_per_sec; n++) {

            //x[n] * (cos(basis) + jsin(basis)) + ... + ...
            float sinusoidal_basis = -1.0 * ((_1HZ * k * n) / samples_per_sec);
            frequency_bins->realPart[k] += (sample_values[n] * cos(sinusoidal_basis));
            frequency_bins->imaginaryPart[k] += (sample_values[n] * sin(sinusoidal_basis));
        }
        // Get Magnitude (The Nyquist Version)
        float realPartSquared = (frequency_bins->realPart[k] * 2) * (frequency_bins->realPart[k] * 2);
        float imaginaryPartSquared = (frequency_bins->imaginaryPart[k] * 2) * (frequency_bins->imaginaryPart[k] * 2);
        frequency_bins->nyquist_magnitude[k] = (float) sqrt( realPartSquared + imaginaryPartSquared );

        //Get Amplitude
        frequency_bins->amplitude[k] = frequency_bins->nyquist_magnitude[k] / samples_per_sec;
    }

    return frequency_bins;
}

void fourier_transform_deinit(frequencyBin_data* frequency_bins) {

    free(frequency_bins->realPart);
    free(frequency_bins->imaginaryPart);
    free(frequency_bins->amplitude);
    free(frequency_bins->nyquist_magnitude);
    free(frequency_bins->phase);
    free(frequency_bins);
}

void IDFT_deinit(complexNum* sample_coefficients) {
    free(sample_coefficients);
}

complexNum* IDFT(float *frequency_values, int const num_of_bins) {

    complexNum *sample_coefficients = malloc(num_of_bins * sizeof(complexNum));
    for (int k = 0; k < num_of_bins; k++) {
        sample_coefficients[k].realPart = 0.0;
        sample_coefficients[k].imaginaryPart = 0.0;
        
        for (int n = 0; n < num_of_bins; n++) {

            //x[n] * (cos(basis) + jsin(basis)) + ... + ...
            float sinusoidal_basis = -1.0 * ((_1HZ * k * n) / num_of_bins);
            sample_coefficients[k].realPart += (frequency_values[n] * cos(sinusoidal_basis));
            sample_coefficients[k].imaginaryPart += (frequency_values[n] * sin(sinusoidal_basis));
        }

        sample_coefficients[k].realPart /= num_of_bins;
        sample_coefficients[k].imaginaryPart /= num_of_bins;
    }
    return sample_coefficients;
}



/*
 * 			TO-DO
 * 			-----
 *  - Add Window Functions
 *
 *  - Change this to a "samples_per_sec"-sized pointer with non-pointer elements. (line 12)
 *  
 *  - Test Code
 *  */