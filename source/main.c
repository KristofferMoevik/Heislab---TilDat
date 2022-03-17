#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include "inputs_and_orders.h"
#include "pos_and_dir.h"
#include "states.h"

/**
* @file
* @brief A program for running the elevator at the elevator lab.
*/

enum Current_pos {
    UNDEFINED = -10,
    STORY_1 = 10, 
    BETWEEN_1_2 = 15,
    STORY_2 = 20,
    BETWEEN_2_3 = 25,
    STORY_3 = 30,
    BEETWEEN_3_4 = 35,
    STORY_4 = 40,
}; 

enum States {
    INIT_STATE = 0,
    IDLE = 1,
    GO_UP = 2,
    GO_DOWN = 3,
    OPEN_DOOR = 4,
    CLOSE_DOOR = 5,
    WAIT = 6,
    STOP = 7,
    WAIT_STOP = 8,
    OPEN_DOORS_STOP = 9,
};

enum Motor_direction {
    DOWN = -1,
    STILL = 0,
    UP = 1,
};


int main(){
    
    int64_t STATE = INIT_STATE;
    int64_t inputs[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int64_t orders[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int64_t ordered_store = 0;
    int64_t floor_sensor = -10;
    int64_t current_pos = UNDEFINED;
    int64_t last_pos = UNDEFINED;
    int64_t motor_direction = STILL;
    int64_t last_motor_direction = STILL;
    double timer = 0;
    double time_elapsed;
    double clock_time;
    int64_t stop = 0;
    int64_t obstruction = 0;
    
    states_start_elevator();

    while(1){
       
        inputs_and_orders_update_inputs(inputs, &obstruction, &stop);

        inputs_and_orders_update_orders(inputs, orders);
        
        ordered_store = inputs_and_orders_get_target_floor(orders, ordered_store);
        
        floor_sensor = pos_and_dir_get_floor_sensor(); 

        current_pos = pos_and_dir_get_current_pos(current_pos, motor_direction, floor_sensor, last_pos, last_motor_direction); 

        last_pos = pos_and_dir_get_last_pos(current_pos, last_pos); 

        last_motor_direction = pos_and_dir_get_last_motor_direction(motor_direction, last_motor_direction); 

        if(stop == 1){     
            STATE = STOP;
        }        

        switch (STATE)
        {
        case  INIT_STATE:
            STATE = states_INIT_STATE(current_pos, &motor_direction, STATE);
            break;

        case IDLE:
            STATE = states_IDLE(ordered_store, current_pos, STATE);
            break;

        case GO_UP:
            STATE = states_GO_UP(ordered_store, current_pos, orders, last_pos, &motor_direction, STATE);
            break;

        case GO_DOWN:
            STATE = states_GO_DOWN(ordered_store, current_pos, orders, last_pos, &motor_direction, STATE);
            break;

        case OPEN_DOOR:
            STATE = states_OPEN_DOOR(STATE, &timer, current_pos);
            break;

        case WAIT:
            STATE = states_WAIT(obstruction, &timer, &clock_time, &time_elapsed, current_pos, STATE);
            break;

        case CLOSE_DOOR:
            STATE = states_CLOSE_DOOR(obstruction, stop, current_pos, orders, &ordered_store, STATE);
            break;

        case STOP:
            STATE = states_STOP(stop, &motor_direction, orders, &ordered_store, current_pos, STATE);
            break;

        case WAIT_STOP:
            STATE = states_WAIT_STOP(ordered_store, current_pos, STATE);
            break;

        case OPEN_DOORS_STOP:
            STATE = states_OPEN_DOOR_STOP(&timer, STATE);
            break;
        
        default:
            break;
        }
    }
}

