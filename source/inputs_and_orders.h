#pragma once
#include <inttypes.h>
/**
* @file
* @brief A simple library for prioritizing which floor to go first.
*/



/**
* @brief Get all the orders and return the floor to go to based on when the order was placed
*
* @param[in] orders Array of orders with values of when the ordr was placed. Is a array of size 12
* @param[in, out] ordered_store value of the ordered store.
*
* @return @p ordered_store, is one of the values 0, 10, 20, 30, 40
*/
int inputs_and_orders_get_target_floor(int64_t orders[], int64_t ordered_store);

/**
* @brief Get all the inputs from the elevator
*
* @param[in, out] inputs Array of the inputs from the elevator. Is a array of size 12
* @param[out] obstruction tells if there are a obstruction hindering the doors from closing. If there is an obstruction obstruction = 1, else obstruction = 0
* @param[in] stop tells if the stop button is pushed. If pushed stop = 1, else stop = 0.
*
* @return void
*/
void inputs_and_orders_update_inputs(int64_t *inputs, int64_t *obstruction, int64_t *stop);

/**
* @brief Get all the orders from the elevator
*
* @param[in] inputs Array of the inputs from the elevator. Is a array of size 12
* @param[in, out] orders array of orders. The elements represent the buttons in the stores and the cab. The value of the elements are a time stamp.
*
* @return void
*/
void inputs_and_orders_update_orders(int64_t *inputs, int64_t *orders);