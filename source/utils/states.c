#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include "order_sorting.h"
#include "states.h"
#include "../driver/elevio.h"


int64_t states_get_floor_to_indicate(int64_t last_floor){
    return (last_floor / 10) - 1;
}


int64_t states_INIT_STATE(int64_t current_pos, int64_t *motor_direction, int64_t STATE){
    printf("State = INIT_STATE, current_pos: %" PRId64 " \n", current_pos);
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
    printf("State = IDLE \n");
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
    printf("State = GO_UP \n");
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
    printf("State = GO_DOWN \n");
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


int64_t states_OPEN_DOOR(int64_t STATE, double *timer, int64_t current_pos){
    printf("State = OPEN_DOOR \n");
    if(elevio_floorSensor() != -1){
        elevio_doorOpenLamp(1);
        elevio_buttonLamp(states_get_floor_to_indicate(current_pos), 0, 0);// Turn off up_button lamp
        elevio_buttonLamp(states_get_floor_to_indicate(current_pos), 1, 0);// Turn off down_button lamp
        elevio_buttonLamp(states_get_floor_to_indicate(current_pos), 2, 0);// Turn off cab_button lamp
        *timer = ((double)clock()/(double)CLOCKS_PER_SEC);
        STATE = WAIT; 
    }

    return STATE;
}


int64_t states_WAIT(int64_t obstruction, double *timer, double *clock_time, double *time_elapsed, int64_t current_pos, int64_t STATE){
    printf("State = OPEN_DOOR \n");
    if(obstruction == 1){
        *timer = ((double)clock()/(double)CLOCKS_PER_SEC);
    }
    *clock_time = ((double)clock()/(double)CLOCKS_PER_SEC);
    *time_elapsed = *clock_time - *timer;
    printf("State = WAIT, time_ elapsed = %f obstruction = %" PRId64 " \n", *time_elapsed, obstruction);
    elevio_buttonLamp(states_get_floor_to_indicate(current_pos), 0, 0);// Turn off up_button lamp
    elevio_buttonLamp(states_get_floor_to_indicate(current_pos), 1, 0);// Turn off down_button lamp
    elevio_buttonLamp(states_get_floor_to_indicate(current_pos), 2, 0);// Turn off cab_button lamp
    if(*time_elapsed >= 0.3){
        STATE = CLOSE_DOOR;
    }
    return STATE;
}


int64_t states_CLOSE_DOOR(int64_t obstruction, int64_t stop, int64_t current_pos, int64_t *orders, int64_t *ordered_store, int64_t STATE){
    printf("State = Closed_DOOR, obstruction = %" PRId64 " stop = %" PRId64 " \n", obstruction, stop);
    if(obstruction == 0){
        elevio_doorOpenLamp(0);
        //[1 up, 1 cab, 2 up, 2 down, 2 cab, 3 up, 3 down, 3 cab, 4 down, 4 cab]
        if(current_pos == 10){
            *(orders) = 0;
            *(orders + 1) = 0;
        } 
        if(current_pos == 20){
            *(orders + 2) = 0;
            *(orders + 3) = 0;
            *(orders + 4) = 0;
        } 
        if(current_pos == 30){
            *(orders + 5) = 0;
            *(orders + 6) = 0;
            *(orders + 7) = 0;
        } 
        if(current_pos == 40){
            *(orders + 8) = 0;
            *(orders + 9) = 0;
        } 
        *ordered_store = 0;
        STATE = IDLE;
    }
    if(obstruction != 0){
        STATE = WAIT;
    }
    return STATE;
}


int64_t states_STOP(int64_t stop, int64_t *motor_direction, int64_t *orders, int64_t *ordered_store, int64_t current_pos, int64_t STATE){
    printf("State = STOP \n");
    if(stop == 1){
        elevio_stopLamp(1); //Turn on stop_lamp
        elevio_motorDirection(DIRN_STOP); //Stop elevator
        *motor_direction = DIRN_STOP;
        
        *(orders) = 0; *(orders + 1) = 0; *(orders + 2) = 0; *(orders + 3) = 0; *(orders + 4) = 0; *(orders + 5) = 0; *(orders + 6) = 0; *(orders + 7) = 0;*(orders + 8) = 0; *(orders + 9) = 0; *(orders + 10) = 0; *(orders + 11) = 0;
        *ordered_store = 0;

        elevio_buttonLamp(0, 0, 0); elevio_buttonLamp(0, 2, 0);
        elevio_buttonLamp(1, 0, 0); elevio_buttonLamp(1, 1, 0); elevio_buttonLamp(1, 2, 0);
        elevio_buttonLamp(2, 0, 0); elevio_buttonLamp(2, 1, 0); elevio_buttonLamp(2, 2, 0);
        elevio_buttonLamp(3, 1, 0); elevio_buttonLamp(3, 2, 0);
        

        elevio_stopLamp(0);
    }

    if(current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40){
        *ordered_store = current_pos;
        STATE = OPEN_DOORS_STOP;
    }
    else{
        STATE = WAIT_STOP;
    }
    return STATE;
}


int64_t states_WAIT_STOP(int64_t ordered_store, int64_t current_pos, int64_t STATE){
    printf("State = WAIT_STOP \n");
    if(ordered_store == 0){
        STATE = WAIT_STOP;
    }
    if(ordered_store != 0){
        if(ordered_store < current_pos){
            STATE = GO_DOWN;
        }
        if(ordered_store > current_pos){
            STATE = GO_UP;
        }
    }
    return STATE;
}


int64_t states_OPEN_DOOR_STOP(double *timer, int64_t STATE){
    printf("State = OPEN_DOOR_STOP \n");
    elevio_doorOpenLamp(1);
    *timer = ((double)clock()/(double)CLOCKS_PER_SEC);
    STATE = WAIT;
    return STATE;
}


