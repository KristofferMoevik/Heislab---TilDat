/**
 * @file
 * @brief A structure to represent a system and desired PID tuning method.
 */
#ifndef CALCULATIONS_H
#define CALCUATIONS_H
#include "system.h" // Trenger man file øverst mtp at system.h er inkludert?

/**
 * @brief The P-parameter calculated according to either the classical
 * Ziegler Nichols rule, or the Pessens Integral Rule
 * 
 * @param current_system        The current system to have its parameters calculated
 * @return                      Returning the calculated P-parameter as a double value
 */
double calculate_P_parameter(System * current_system);

/**
 * @brief The I-parameter calculated according to either the classical
 * Ziegler Nichols rule, or the Pessens Integral Rule
 * 
 * @param current_system        The current system to have its parameters calculated
 * @return                      Returning the calculated I-parameter as a double value
 */
double calculate_I_parameter(System * current_system);

/**
 * @brief The P-parameter calculated according to either the classical
 * Ziegler Nichols rule, or the Pessens Integral Rule
 * 
 * @param current_system        The current system to have its parameters calculated
 * @return                      Returning the calculated D-parameter as a double value
 */
double calculate_D_parameter(System * current_system);

#endif
