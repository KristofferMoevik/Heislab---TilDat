/**
 * @file
 * @brief A structure to represent a system and desired PID tuning method.
 */
#ifndef SYSTEM_H
#define SYSTEM_H

typedef enum {
    Classic_Ziegler_Nichols,
    Pessen_Integral_Rule
} Tuning;


typedef struct {
    double Ku;            /** < The gain margin for loop stability */
    double Tu;            /** < The period of the oscillations frequency at the stability limit */
    Tuning tuning_method; /** < The desired PID tuning method */
} System;


/**
 * @brief This function creates a new system object on the heap.
 * 
 * @param Ku             The gain margin for loop stability
 * @param Tu             The period of the oscillations frequency at the stability limit
 * @param tuning_method  The desired PID tuning method
 * @return System*      
 */
System * system_create(double Ku, double Tu, Tuning tuning_method);

/**
 * @brief This function relinquishes the memory of a system object
 * 
 * @param system_current  The system that gets freed
 */
void system_delete(System * system_current);

#endif
