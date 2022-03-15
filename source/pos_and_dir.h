#pragma once
#include <inttypes.h>

/**
* @file
* @brief A library for getting position, direction and need for initializing
*/



/**
* @brief Get the current floor of the elevator.
*
* @param[in, out] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in] motor_direction value of the motor_direction. Has values [-1, 0, 1]
* @param[in] floor_sensor value of the sensor reading from the elevator. Has values [0, 10, 20, 30, 40]
* @param[in] last_pos value of the last known position based on the sensors. Has values [10, 20, 30, 40]
* @param[in] last_motor_direction value of the ordered store. Has values [-1, 1]
*
* @return @p current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
*/
int64_t pos_and_dir_get_current_pos(int64_t current_pos, int64_t motor_direction, int64_t floor_sensor, int64_t last_pos, int64_t last_motor_direction);




/**
* @brief Get the last known position of the elevator
*
* @param[in] current_pos value of the position of the elevator. Has values [10, 15, 20, 25, 30, 35, 40]
* @param[in, out] last_pos value of the last known position based on the sensors. Has values [10, 20, 30, 40]
*
* @return @p last_pos value of the last known position based on the sensors. Has values [10, 20, 30, 40]
*/
int64_t pos_and_dir_get_last_pos(int64_t current_pos, int64_t last_pos);




/**
* @brief Get the last motor direction
*
* @param[in] motor_direction value of the motor_direction. Has values [-1, 0, 1]
* @param[in, out] last_motor_direction value of the ordered store. Has values [-1, 1]
*
* @return @p last_motor_direction value of the ordered store. Has values [-1, 1]
*/
int64_t pos_and_dir_get_last_motor_direction(int64_t motor_direction, int64_t last_motor_direction);



/**
* @brief Get the current floor of the elevator.
*
* @param[in] floor_sensor value of the sensor reading from the elevator. Has values [0, 10, 20, 30, 40]
* @param[in] last_pos value of the last known position based on the sensors. Has values [10, 20, 30, 40]
* @param[in] motor_direction value of the motor_direction. Has values [-1, 0, 1]
* @param[in] last_motor_direction value of the ordered store. Has values [-1, 1]
* @param[in, out] STATE the state of the finite state machine of the elevator.
*
* @return @p STATE the state of the finite state machine of the elevator.
*/
int64_t pos_and_dir_get_need_for_initializing(int64_t floor_sensor, int64_t last_pos, int64_t motor_direction, int64_t last_motor_direction, int64_t STATE);
