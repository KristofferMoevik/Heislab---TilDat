#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include "order_sorting.h"
#include "../driver/elevio.h"


int64_t states_get_floor_to_indicate(int64_t last_floor){
    return (last_floor / 10) - 1;
}


int64_t states_INIT_STATE(int64_t current_pos, int64_t *motor_direction, int64_t STATE){
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
    if (current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40){
        elevio_motorDirection(DIRN_STOP);
        *motor_direction = DIRN_STOP;
        elevio_floorIndicator(states_get_floor_to_indicate(current_pos));
        STATE = IDLE;
    }
    else{
        elevio_motorDirection(DIRN_DOWN);
        *motor_direction = DIRN_DOWN;
    }
    return STATE;
}


int64_t states_IDLE(int64_t ordered_store, int64_t current_pos, int64_t STATE){
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
    if(ordered_store == 0){
        STATE = IDLE;
    }
    if(ordered_store != 0){
        if(ordered_store == current_pos){STATE = OPEN_DOOR;};
        if(ordered_store < current_pos){STATE = GO_DOWN;};
        if(ordered_store > current_pos){STATE = GO_UP;};
    }
    return STATE;
}


int64_t states_GO_UP(int64_t ordered_store, int64_t current_pos, int64_t UP_2, int64_t CAB_2, int64_t UP_3, int64_t CAB_3, int64_t last_pos, int64_t *motor_direction, int64_t STATE){
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
    elevio_floorIndicator(states_get_floor_to_indicate(last_pos));
    if(ordered_store == current_pos){
        elevio_motorDirection(DIRN_STOP);
        *motor_direction = DIRN_STOP;
        elevio_floorIndicator(states_get_floor_to_indicate(current_pos));
        STATE = 4;
    }
    else if((current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40)){
        if(current_pos == 20 && (UP_2 != 0 || CAB_2 != 0)){
            elevio_motorDirection(DIRN_STOP);
            *motor_direction = DIRN_STOP;
            elevio_floorIndicator(states_get_floor_to_indicate(current_pos));
            STATE = 4;
        }
        else if(current_pos == 30 && (UP_3 != 0 || CAB_3 != 0)){
            elevio_motorDirection(DIRN_STOP);
            *motor_direction = DIRN_STOP;
            elevio_floorIndicator(states_get_floor_to_indicate(current_pos));
            STATE = OPEN_DOOR;
        }
        else{
            elevio_motorDirection(DIRN_UP);
            *motor_direction = DIRN_UP;
        }
    }
    else{
        elevio_motorDirection(DIRN_UP);
        *motor_direction = DIRN_UP;
    }
    return STATE;
}


int64_t states_GO_DOWN(int64_t ordered_store, int64_t current_pos, int64_t DOWN_2, int64_t CAB_2, int64_t DOWN_3, int64_t CAB_3, int64_t last_pos, int64_t *motor_direction, int64_t STATE){
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
    elevio_floorIndicator(states_get_floor_to_indicate(last_pos));
    if(ordered_store == current_pos){
        elevio_motorDirection(DIRN_STOP);
        *motor_direction = DIRN_STOP;
        elevio_floorIndicator(states_get_floor_to_indicate(current_pos));
        STATE = OPEN_DOOR;
    }
    else if((current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40)){
        if(current_pos == 20 && (DOWN_2 != 0 || CAB_2 != 0)){
            elevio_motorDirection(DIRN_STOP);
            *motor_direction = DIRN_STOP;
            elevio_floorIndicator(states_get_floor_to_indicate(current_pos));
            STATE = OPEN_DOOR;
        }
        else if(current_pos == 30 && (DOWN_3 != 0 || CAB_3 != 0)){
            elevio_motorDirection(DIRN_STOP);
            *motor_direction = DIRN_STOP;
            elevio_floorIndicator(states_get_floor_to_indicate(current_pos));
            STATE = OPEN_DOOR;
        }
        else{
            elevio_motorDirection(DIRN_DOWN);
            *motor_direction = DIRN_DOWN;
        }
    }
    else{
        elevio_motorDirection(DIRN_DOWN);
        *motor_direction = DIRN_DOWN;
    }
    return STATE;
}


