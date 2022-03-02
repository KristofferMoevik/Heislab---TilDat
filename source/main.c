#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "driver/elevio.h"
#include "modules/HeisUtils.h"

enum Current_pos {
    STORY_1 = 1, 
    BETWEEN_1_2 = 15,
    STORY_2 = 2,
    BETWEEN_2_3 = 25,
    STORY_3 = 3,
    BEETWEEN_3_4 = 35,
    STORY_4 = 4,
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

int main(){
    int STATE = INIT_STATE;
    int inputs[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int current_pos = -1;
    int last_pos = -1;
    int motor_direction = 0;


    while(1){
        
        // read inputs
        int diff_t = clock();
        if(elevio_callButton(0, 0) == 1){ inputs[0] = diff_t; elevio_buttonLamp(0, 0, 1);} else{inputs[0] = 0;}
        if(elevio_callButton(0, 2) == 1){ inputs[1] = diff_t; elevio_buttonLamp(0, 2, 1);} else{inputs[1] = 0;}
        if(elevio_callButton(1, 0) == 1){ inputs[2] = diff_t; elevio_buttonLamp(1, 0, 1);} else{inputs[2] = 0;}
        if(elevio_callButton(1, 1) == 1){ inputs[3] = diff_t; elevio_buttonLamp(1, 0, 1);} else{inputs[3] = 0;}
        if(elevio_callButton(1, 2) == 1){ inputs[4] = diff_t; elevio_buttonLamp(1, 0, 1);} else{inputs[4] = 0;}
        if(elevio_callButton(2, 0) == 1){ inputs[5] = diff_t; elevio_buttonLamp(2, 0, 1);} else{inputs[5] = 0;}
        if(elevio_callButton(2, 1) == 1){ inputs[6] = diff_t; elevio_buttonLamp(2, 0, 1);} else{inputs[6] = 0;}
        if(elevio_callButton(2, 2) == 1){ inputs[7] = diff_t; elevio_buttonLamp(2, 0, 1);} else{inputs[7] = 0;}
        if(elevio_callButton(3, 1) == 1){ inputs[8] = diff_t; elevio_buttonLamp(3, 0, 1);} else{inputs[8] = 0;}
        if(elevio_callButton(3, 2) == 1){ inputs[9] = diff_t; elevio_buttonLamp(3, 0, 1);} else{inputs[9] = 0;}
        if(elevio_obstinputsuction() == 1){ inputs[10] = diff_t;}
        if(elevio_stopButton() == 1){ inputs[11] = diff_t;}

        // get current position, and save last known position
        if(current_pos != -1){
            last_pos = current_pos;
        }
        int floor_sensor = elevio_floorSensor();
        if(floor_sensor != -1)){
            current_pos = floor_sensor;
        } else if(floor_sensor == -1){
            
        }

        switch (STATE)
        {
        case  INIT_STATE:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        case /* constant-expression */:
            /* code */
            break;
        
        default:
            break;
        }
    }
    
}

