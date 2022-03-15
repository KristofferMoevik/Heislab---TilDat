#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include "driver/elevio.h"
#include "order_sorting.h"
#include "pos_and_dir.h"
#include "states.h"

enum Motor_direction {
    DOWN = -1,
    STILL = 0,
    UP = 1,
};

int64_t get_floor_to_indicate(int64_t last_floor){
    return (last_floor / 10) - 1;
}

int main(){
    elevio_init();
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


    while(1){
        
        // Reads in the inputs to the inputs array
        int64_t diff_t = (int64_t)clock(); 
        if(elevio_callButton(0, 0) == 1){ inputs[0] = diff_t; elevio_buttonLamp(0, BUTTON_HALL_UP, 1);} else{inputs[0] = 0;}
        if(elevio_callButton(0, 2) == 1){ inputs[1] = diff_t; elevio_buttonLamp(0, BUTTON_CAB, 1);} else{inputs[1] = 0;}
        if(elevio_callButton(1, 0) == 1){ inputs[2] = diff_t; elevio_buttonLamp(1, BUTTON_HALL_UP, 1);} else{inputs[2] = 0;}
        if(elevio_callButton(1, 1) == 1){ inputs[3] = diff_t; elevio_buttonLamp(1, BUTTON_HALL_DOWN, 1);} else{inputs[3] = 0;}
        if(elevio_callButton(1, 2) == 1){ inputs[4] = diff_t; elevio_buttonLamp(1, BUTTON_CAB, 1);} else{inputs[4] = 0;}
        if(elevio_callButton(2, 0) == 1){ inputs[5] = diff_t; elevio_buttonLamp(2, BUTTON_HALL_UP, 1);} else{inputs[5] = 0;}
        if(elevio_callButton(2, 1) == 1){ inputs[6] = diff_t; elevio_buttonLamp(2, BUTTON_HALL_DOWN, 1);} else{inputs[6] = 0;}
        if(elevio_callButton(2, 2) == 1){ inputs[7] = diff_t; elevio_buttonLamp(2, BUTTON_CAB, 1);} else{inputs[7] = 0;}
        if(elevio_callButton(3, 1) == 1){ inputs[8] = diff_t; elevio_buttonLamp(3, BUTTON_HALL_DOWN, 1);} else{inputs[8] = 0;}
        if(elevio_callButton(3, 2) == 1){ inputs[9] = diff_t; elevio_buttonLamp(3, BUTTON_CAB, 1);} else{inputs[9] = 0;}
        if(elevio_obstruction() == 1){ inputs[10] = diff_t; obstruction = 1;} else{inputs[10] = 0; obstruction = 0;}
        if(elevio_stopButton() == 1){ inputs[11] = diff_t; stop = 1;} else{inputs[11] = 0; stop = 0;}
        
        // The orders array is set based on the values of the input array
        if((inputs[0] != 0) && (orders[0] == 0)){orders[0] = inputs[0];}
        if((inputs[1] != 0) && (orders[1] == 0)){orders[1] = inputs[1];}
        if((inputs[2] != 0) && (orders[2] == 0)){orders[2] = inputs[2];}
        if((inputs[3] != 0) && (orders[3] == 0)){orders[3] = inputs[3];}
        if((inputs[4] != 0) && (orders[4] == 0)){orders[4] = inputs[4];}
        if((inputs[5] != 0) && (orders[5] == 0)){orders[5] = inputs[5];}
        if((inputs[6] != 0) && (orders[6] == 0)){orders[6] = inputs[6];}
        if((inputs[7] != 0) && (orders[7] == 0)){orders[7] = inputs[7];}
        if((inputs[8] != 0) && (orders[8] == 0)){orders[8] = inputs[8];}
        if((inputs[9] != 0) && (orders[9] == 0)){orders[9] = inputs[9];}
        if((inputs[11] != 0) && (orders[11] == 0)){orders[11] = inputs[11];}

        // Prints out the order list to terminal
        printf("orders = [%" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 "] \n", orders[0], orders[1], orders[2], orders[3], orders[4], orders[5], orders[6], orders[7], orders[8], orders[9], orders[10], orders[11]);
        
        // Prioritizes what orders which should be handeled first based on time
        ordered_store = order_sorting_get_target_floor(orders, ordered_store);
        
        // Finds the position of the elevator, the last known position of the elevator, and the last known motor direction
        floor_sensor = (elevio_floorSensor() + 1) * 10;
        current_pos = pos_and_dir_get_current_pos(current_pos, motor_direction, floor_sensor, last_pos, last_motor_direction);
        last_pos = pos_and_dir_get_last_pos(current_pos, last_pos);
        last_motor_direction = pos_and_dir_get_last_motor_direction(motor_direction, last_motor_direction);

        // If the stop button is pressed the STATE of the elevator is set to STOP
        if(stop == 1){
            STATE = STOP;
        }        

        // Finite state machine for the elevator
        switch (STATE)
        {
        case  INIT_STATE:
            // The INIT_STATE drives the elevator to the floor underneat
            STATE = states_INIT_STATE(current_pos, &motor_direction, STATE);
            break;

        case IDLE:
            // The IDLE state waits for a order. Based on the order it either goes up, down or opens the door.
            STATE = states_IDLE(ordered_store, current_pos, STATE);
            break;

        case GO_UP:
            // The GO_UP state goes up until it reaches ordered floor or another order in the same direction.
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

