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
void AddOrders(int inputs[12]);
void SortOrders();
void ExecuteOrders();