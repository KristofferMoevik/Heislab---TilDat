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

int64_t main(){
    int64_t STATE = INIT_STATE;
    int64_t inputs[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int64_t current_pos = UNDEFINED;
    int64_t last_pos = UNDEFINED;
    int64_t motor_direction = STILL;
    int64_t last_motor_direction = STILL;


    while(1){
        
        // read inputs
        int64_t diff_t = clock();
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
        if(current_pos != UNDEFINED){
            last_pos = current_pos;
        }

        if(motor_direction != STILL){
            last_motor_direction = motor_direction;
        }

        int64_t floor_sensor = elevio_floorSensor() * 10;
        if(floor_sensor != UNDEFINED){
            current_pos = floor_sensor;
        } else if(floor_sensor == UNDEFINED && last_pos != UNDEFINED){
            if(motor_direction == UP){
                current_pos = last_pos + 10;
            } else if (motor_direction == DOWN){
                current_pos = last_pos + 1;
            } else if (motor_direction == STILL){
                if(last_motor_direction == STILL){
                    STATE = INIT_STATE;
                }
                else if(last_motor_direction == UP){
                    current_pos = last 
                }
            }

        }

        switch (STATE)
        {
        case  INIT_STATE:
            elevio_motorDirection(DIRN_DOWN); 
            if (elevio_floorSensor() == 1||2||3||4){
                elevio_motorDirection(DIRN_STOP);
                elevio_floorIndicator(elevio_floorSensor());
                current_pos = elevio_floorSensor();
                STATE = IDLE;
                }
            break;

        case IDLE:
            int64_t order_pos = input_pos; //Blir definert i main, så kan fjernes
            // Take order from array
            // Hent ut første element i array
            if(order_pos == current_pos){STATE = OPEN_DOOR;};
            if(order_pos < current_pos){STATE = GO_DOWN;};
            if(order_pos > current_pos){STATE = GO_UP;};
            break;

        case GO_UP:
            elevio_motorDirection(DIRN_UP);
            elevio_floorIndicator(elevio_floorSensor());
            if(order_pos == current_pos){
                elevio_motorDirection(DIRN_STOP);
                STATE = OPEN_DOOR;
                }
            break;

        case GO_DOWN:
            elevio_motorDirection(DIRN_DOWN);
            elevio_floorIndicator(elevio_floorSensor());
            if(order_pos == current_pos){
                elevio_motorDirection(DIRN_STOP);
                STATE = OPEN_DOOR;
                }
            break;

        case OPEN_DOOR:
            elevio_doorOpenLamp(1);
            STATE = WAIT;
            break;

        case WAIT:
            if(elevio_obstruction()){
                STATE = WAIT;
            }
            if(!elevio_obstruction()){
                //3 sekund timer
                STATE = CLOSE_DOOR;
            }
            break;

        case CLOSE_DOOR:
            elevio_doorOpenLamp(0);
            /* code */
            break;

        case STOP:
            /* code */
            break;
        case WAIT_STOP:
            /* code */
            break;
        case OPEN_DOORS_STOP:
            /* code */
            break;
        
        default:
            break;
        }
    }
    
}

