#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include "inputs_and_orders.h"
#include "driver/elevio.h"

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


int inputs_and_orders_get_target_floor(int64_t orders[], int64_t ordered_store){
    // set witch story to go to based on first order
    int64_t time_of_order;
    int64_t earliest = 9223372036854775807;
    int64_t earliest_value = -1;
    for(int i = 0; i < 10; i++){
        time_of_order= orders[i];
        if(time_of_order< earliest && time_of_order!= 0){
            earliest = time_of_order;
            earliest_value = i;
        }
    }
    if(earliest_value > -1){
        if(earliest_value == 0 || earliest_value == 1){
            ordered_store = 10;
        }
        else if(earliest_value == 2 || earliest_value == 3 || earliest_value == 4){
            ordered_store = 20;
        }
        else if(earliest_value == 5 || earliest_value == 6 || earliest_value == 7){
            ordered_store = 30;
        }
        else if(earliest_value == 8 || earliest_value == 9){
            ordered_store = 40;
        }         
        else{
            ordered_store = 0;
        }   
        
    }
    return ordered_store;
}

void inputs_and_orders_update_inputs(int64_t *inputs, int64_t *obstruction, int64_t *stop){
    // Reads in the inputs to the inputs array
    int64_t diff_t = (int64_t)clock(); 
    if(elevio_callButton(0, 0) == 1){ *(inputs) = diff_t; elevio_buttonLamp(0, BUTTON_HALL_UP, 1);} else{inputs[0] = 0;}
    if(elevio_callButton(0, 2) == 1){ *(inputs + 1) = diff_t; elevio_buttonLamp(0, BUTTON_CAB, 1);} else{inputs[1] = 0;}
    if(elevio_callButton(1, 0) == 1){ *(inputs + 2) = diff_t; elevio_buttonLamp(1, BUTTON_HALL_UP, 1);} else{inputs[2] = 0;}
    if(elevio_callButton(1, 1) == 1){ *(inputs + 3) = diff_t; elevio_buttonLamp(1, BUTTON_HALL_DOWN, 1);} else{inputs[3] = 0;}
    if(elevio_callButton(1, 2) == 1){ *(inputs + 4) = diff_t; elevio_buttonLamp(1, BUTTON_CAB, 1);} else{inputs[4] = 0;}
    if(elevio_callButton(2, 0) == 1){ *(inputs + 5) = diff_t; elevio_buttonLamp(2, BUTTON_HALL_UP, 1);} else{inputs[5] = 0;}
    if(elevio_callButton(2, 1) == 1){ *(inputs + 6) = diff_t; elevio_buttonLamp(2, BUTTON_HALL_DOWN, 1);} else{inputs[6] = 0;}
    if(elevio_callButton(2, 2) == 1){ *(inputs + 7) = diff_t; elevio_buttonLamp(2, BUTTON_CAB, 1);} else{inputs[7] = 0;}
    if(elevio_callButton(3, 1) == 1){ *(inputs + 8) = diff_t; elevio_buttonLamp(3, BUTTON_HALL_DOWN, 1);} else{inputs[8] = 0;}
    if(elevio_callButton(3, 2) == 1){ *(inputs + 9) = diff_t; elevio_buttonLamp(3, BUTTON_CAB, 1);} else{inputs[9] = 0;}
    if(elevio_obstruction() == 1){ *(inputs + 10) = diff_t; *obstruction = 1;} else{inputs[10] = 0; *obstruction = 0;}
    if(elevio_stopButton() == 1){ *(inputs + 11) = diff_t; *stop = 1;} else{inputs[11] = 0; *stop = 0;}
    return;
}


void inputs_and_orders_update_orders(int64_t *inputs, int64_t *orders){
    // The orders array is set based on the values of the input array
    if((*(inputs) != 0) && (*(orders) == 0)){*(orders) = *(inputs);}
    if((*(inputs + 1) != 0) && (*(orders + 1) == 0)){*(orders + 1) = *(inputs + 1);}
    if((*(inputs + 2) != 0) && (*(orders + 2) == 0)){*(orders + 2) = *(inputs + 2);}
    if((*(inputs + 3) != 0) && (*(orders + 3) == 0)){*(orders + 3) = *(inputs + 3);}
    if((*(inputs + 4) != 0) && (*(orders + 4) == 0)){*(orders + 4) = *(inputs + 4);}
    if((*(inputs + 5) != 0) && (*(orders + 5) == 0)){*(orders + 5) = *(inputs + 5);}
    if((*(inputs + 6) != 0) && (*(orders + 6) == 0)){*(orders + 6) = *(inputs + 6);}
    if((*(inputs + 7) != 0) && (*(orders + 7) == 0)){*(orders + 7) = *(inputs + 7);}
    if((*(inputs + 8) != 0) && (*(orders + 8) == 0)){*(orders + 8) = *(inputs + 8);}
    if((*(inputs + 9) != 0) && (*(orders + 9) == 0)){*(orders + 9) = *(inputs + 9);}
    if((*(inputs + 10) != 0) && (*(orders + 10) == 0)){*(orders + 10) = *(inputs + 10);}
    if((*(inputs + 11) != 0) && (*(orders + 11) == 0)){*(orders + 11) = *(inputs + 11);}
    printf("orders = [%" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 "] \n", orders[0], orders[1], orders[2], orders[3], orders[4], orders[5], orders[6], orders[7], orders[8], orders[9], orders[10], orders[11]);
    return;
}

