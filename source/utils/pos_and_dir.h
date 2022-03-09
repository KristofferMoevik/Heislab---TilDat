#pragma once
#include <inttypes.h>

// get current position, and save last known position, 
        // inputs: current pos, motor_direction, floor_sensor, last_pos, last_motor_direction 
        // outputs: last_pos, current_pos, last_motor_direction

int64_t pos_and_dir_get_current_pos(int64_t current_pos, int64_t motor_direction, int64_t floor_sensor, int64_t last_pos, int64_t last_motor_direction);

int64_t pos_and_dir_get_last_pos(int64_t current_pos, int64_t last_pos);

int64_t pos_and_dir_get_last_motor_direction(int64_t motor_direction, int64_t last_motor_direction);

int64_t pos_and_dir_get_need_for_initializing(int64_t floor_sensor, int64_t last_pos, int64_t motor_direction, int64_t last_motor_direction, int64_t STATE);
