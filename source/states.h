#pragma once
#include <inttypes.h>

/**
* @file
* @brief A library for the finite state machine in main.c
*/

/**
* @brief Starts the elevator
*
* @return void
*/
void states_start_elevator();

/**
* @brief Drives the elevator to the floor underneat when the elevator starts
*
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in, out] motor_direction value of the motor_direction. Has values [-1, 0, 1]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value INIT_STATE or IDLE
*/
int64_t states_INIT_STATE(int64_t current_pos, int64_t *motor_direction, int64_t STATE);

/**
* @brief If there is no orders the elevator waits. If there are orders the state returned is either OPEN_DOOR, GO_UP or GO_DOWN
*
* @param[in] ordered_store value of the ordered store.
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value OPEN_DOOR, GO_UP, GO_DOWN or IDLE
*/
int64_t states_IDLE(int64_t ordered_store, int64_t current_pos, int64_t STATE);

/**
* @brief Drives the elevator up and stops on the way if there are orders between current store and ordered store
*
* @param[in] ordered_store value of the ordered store.
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in] orders array of orders. The elements represent the buttons in the stores and the cab. The value of the elements are a time stamp.
* @param[in] last_pos value of the last known position based on the sensors. Has values [10, 20, 30, 40]
* @param[in, out] motor_direction value of the motor_direction. Has values [-1, 0, 1]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value OPEN_DOOR or GO_UP
*/
int64_t states_GO_UP(int64_t ordered_store, int64_t current_pos, int64_t *orders, int64_t last_pos, int64_t *motor_direction, int64_t STATE);

/**
* @brief Drives the elevator down and stops on the way if there are orders between current store and ordered store
*
* @param[in] ordered_store value of the ordered store.
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in] orders array of orders. The elements represent the buttons in the stores and the cab. The value of the elements are a time stamp.
* @param[in] last_pos value of the last known position based on the sensors. Has values [10, 20, 30, 40]
* @param[in, out] motor_direction value of the motor_direction. Has values [-1, 0, 1]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value OPEN_DOOR or GO_DOWN
*/
int64_t states_GO_DOWN(int64_t ordered_store, int64_t current_pos, int64_t *orders, int64_t last_pos, int64_t *motor_direction, int64_t STATE);

/**
* @brief Opens the door of the elevator and turn the ligths of the current store off
*
* @param[in] timer time when @p STATE was set to WAIT
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value OPEN_DOOR or WAIT
*/
int64_t states_OPEN_DOOR(int64_t STATE, double *timer, int64_t current_pos);

/**
* @brief Waits for 3 seconds and then sets STATE to CLOSE_DOOR. If there is a obstruction the function waits 3 seconds after the obstruction is gone before it sets STATE to CLOSE_DOOR
*
* @param[in] obstruction tells if there are a obstruction hindering the doors from closing
* @param[in] timer time when @p STATE was set to WAIT
* @param[in] clock_time the clock time rigth now
* @param[in] time_elapsed the time since th WAIT state was called
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value CLOSE_DOOR or WAIT
*/
int64_t states_WAIT(int64_t obstruction, double *timer, double *clock_time, double *time_elapsed, int64_t current_pos, int64_t STATE);

/**
* @brief Closes door if there is no obstruction. And empties orders in the store.
*
* @param[in] obstruction tells if there are a obstruction hindering the doors from closing
* @param[in] stop tells if the stop button is pushed. If pushed stop = 1, else stop = 0.
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in] orders array of orders. The elements represent the buttons in the stores and the cab. The value of the elements are a time stamp.
* @param[in] ordered_store value of the ordered store.
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value CLOSE_DOOR or WAIT
*/
int64_t states_CLOSE_DOOR(int64_t obstruction, int64_t stop, int64_t current_pos, int64_t *orders, int64_t *ordered_store, int64_t STATE);

/**
* @brief Stops the elevator and clears order list.
*
* @param[in] stop tells if the stop button is pushed. If pushed stop = 1, else stop = 0.
* @param[in, out] motor_direction value of the motor_direction. Has values [-1, 0, 1]
* @param[in] orders array of orders. The elements represent the buttons in the stores and the cab. The value of the elements are a time stamp.
* @param[in] ordered_store value of the ordered store.
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value WAIT_STOP or OPEN_DOOR_STOP
*/
int64_t states_STOP(int64_t stop, int64_t *motor_direction, int64_t *orders, int64_t *ordered_store, int64_t current_pos, int64_t STATE);

/**
* @brief Waits for new order
*
* @param[in] ordered_store value of the ordered store.
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value GO_UP or GO_DOWN
*/
int64_t states_WAIT_STOP(int64_t ordered_store, int64_t current_pos, int64_t STATE);

/**
* @brief Waits for new order
*
* @param[in] timer time when @p STATE was set to OPEN_DOOR_STOP
* @param[in, out] STATE state of the finite state machine. Has value 0, 1, 2, 3, 4, 5, 6, 7, 8 or 9 of type STATE
*
* @return @p STATE state of the finite state machine. Has value WAIT
*/
int64_t states_OPEN_DOOR_STOP(double *timer, int64_t STATE);
