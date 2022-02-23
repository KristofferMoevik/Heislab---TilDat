#pragma once
/**
* @file
* @brief A library for running the elevator at the "Heislab"
*/


/**
* @brief Reads inputs from the "Etasjepanel" and the "Heispanel". 
* 
*
* @return Array of inputs with the structure 
* [1 Stop up, 1 Go to, 2 Stop up, 2 Stop down, 2 Go to, ..., 4 Stop down, 4 Go to, Stop, Obstruksjon]
* size 12
*/
int * ReadInputs(void);


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
int SortOrders();
void ExecuteOrders();