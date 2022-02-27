#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../driver/elevio.h"
/**
* @file
* @brief A library for running the elevator at the "Heislab"
*/


typedef enum { 
    STILL = 0,
    UP    = 1,
    DOWN  = 2
} ELVEVATOR_DIR;

/**
* @brief Reads inputs from the "Etasjepanel" and the "Heispanel". 
* 
*
* @return Array of inputs with the structure 
* [1 Stop up, 1 Go to, 2 Stop up, 2 Stop down, 2 Go to, ..., 4 Stop down, 4 Go to, Stop, Obstruksjon]
* size 12
*/
double * ReadInputs(time_t start_t);


/**
* @brief Input to the function is the inputs from the elevator 
* 
*
* @return Returns a list of orders on the form 
* [1 up, 1 cab, 2 up, 2 down, 2 cab, 3 up, 3 down, 3 cab, 4 down, 4 cab]
*/
int * AddOrders(int * inputs, int * orders);


/**
* @brief Input to the function is the order array 
* 
*
* @return Returns what story to go to a number in the range {1,2,3,4}
*/
void SortOrders(int * orders, int * completed_order, int * ordered_floor, int * stop_on_the_way);
void ExecuteOrders();