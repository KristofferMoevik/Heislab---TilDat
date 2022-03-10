#pragma once
#include <inttypes.h>
/**
* @file
* @brief A simple library for prioritizing which floor to go first.
*/

/**
* @brief Get all the orders and return the floor to go to based on when the order was placed
*
* @param[in] orders Array of orders with values of when the ordr was placed.
* @param[in, out] ordered_store value of the ordered store.
*
* @return @p ordered_store, is one of the values 0, 10, 20, 30, 40
*/
int order_sorting_get_target_floor(int64_t orders[], int64_t ordered_store);
