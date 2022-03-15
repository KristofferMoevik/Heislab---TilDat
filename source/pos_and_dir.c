#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include "pos_and_dir.h"

int64_t pos_and_dir_get_current_pos(int64_t current_pos, int64_t motor_direction, int64_t floor_sensor, int64_t last_pos, int64_t last_motor_direction){
    if(floor_sensor != 0){
        current_pos = floor_sensor;
    } 
    else if(floor_sensor == 0 && last_pos != -10 && last_motor_direction != -10){
        if(motor_direction == 1){
            current_pos = last_pos + 5;
        } 
        else if (motor_direction == -1){
            current_pos = last_pos - 5;
        } 
        else if (motor_direction == 0){
            if(last_motor_direction == 1){
                current_pos = last_pos + 5;
            }
            else if(last_motor_direction == -1){
                current_pos = last_pos - 5;
            }
        }

    }
    
    return current_pos;
}

int64_t pos_and_dir_get_last_pos(int64_t current_pos, int64_t last_pos){
    if(current_pos != -10 && (current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40)){
        last_pos = current_pos;
    }
    return last_pos;
}

int64_t pos_and_dir_get_last_motor_direction(int64_t motor_direction, int64_t last_motor_direction){
    if(motor_direction != 0){
        last_motor_direction = motor_direction;
    }
    return last_motor_direction;
}

int64_t pos_and_dir_get_need_for_initializing(int64_t floor_sensor, int64_t last_pos, int64_t motor_direction, int64_t last_motor_direction, int64_t STATE){
    if(floor_sensor == 0 && last_pos != -10 && motor_direction == 0 && last_motor_direction == 0){
        STATE = 0;
    }
    
    return STATE;
}


