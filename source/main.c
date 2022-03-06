#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "driver/elevio.h"
#include <inttypes.h>

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

int64_t get_floor_to_indicate(int64_t last_floor){
    return (last_floor / 10) - 1;
}

int main(){
    elevio_init();
    int64_t STATE = INIT_STATE;
    int64_t inputs[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int64_t orders[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int64_t ordered_store = 0;
    int64_t current_pos = UNDEFINED;
    int64_t last_pos = UNDEFINED;
    int64_t motor_direction = STILL;
    int64_t last_motor_direction = STILL;
    int64_t timer = 0;
    int64_t time_elapsed;
    int64_t stop = 0;
    int64_t obstruction = 0;


    while(1){
        printf("\n");
        // read inputs
        // shape of input array: [1 up, 1 cab, 2 up, 2 down, 2 cab, 3 up, 3 down, 3 cab, 4 down, 4 cab, Stop, Obstruksjon]
        int64_t diff_t = (int64_t)clock();
        //printf("time = %" PRId64, diff_t); 
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
        // printf("inputs = [%" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 "] \n", inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6], inputs[7], inputs[8], inputs[9], inputs[10], inputs[11]);
        
        // add orders, the lowest number is the next order
        // shape of orders array: [1 up, 1 cab, 2 up, 2 down, 2 cab, 3 up, 3 down, 3 cab, 4 down, 4 cab]
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
        printf("orders = [%" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 ", %" PRId64 "] \n", orders[0], orders[1], orders[2], orders[3], orders[4], orders[5], orders[6], orders[7], orders[8], orders[9], orders[10], orders[11]);

        // set witch story to go to based on first order
        int64_t time;
        int64_t earliest = 9223372036854775807;
        int64_t earliest_value = -1;
        for(int i = 0; i < 10; i++){
            time = orders[i];
            if(time < earliest && time != 0){
                earliest = time;
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
        printf("  earliest value = %" PRId64 " ordered_store = %" PRId64"\n", earliest, ordered_store);
        // get current position, and save last known position
        if(current_pos != UNDEFINED && (current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40)){
            last_pos = current_pos;
        }

        if(motor_direction != STILL){
            last_motor_direction = motor_direction;
        }

        int64_t floor_sensor = (elevio_floorSensor() + 1) * 10;
        if(floor_sensor != UNDEFINED){
            current_pos = floor_sensor;
        } 
        else if(floor_sensor == UNDEFINED && last_pos != UNDEFINED && last_motor_direction != UNDEFINED){
            if(motor_direction == UP){
                current_pos = last_pos + 5;
            } 
            else if (motor_direction == DOWN){
                current_pos = last_pos - 5;
            } 
            else if (motor_direction == STILL){
                if(last_motor_direction == STILL){
                    STATE = INIT_STATE;
                }
                else if(last_motor_direction == UP){

                    current_pos = last_pos + 5;
                }
                else if(last_motor_direction == DOWN){
                    current_pos = last_pos - 5;

                }
            }

        }
        else{
            STATE = INIT_STATE;
        }

        if(STATE == OPEN_DOOR || STATE == WAIT){
            elevio_buttonLamp(get_floor_to_indicate(ordered_store), 0, 0);// Turn off up_button lamp
            elevio_buttonLamp(get_floor_to_indicate(ordered_store), 1, 0);// Turn off down_button lamp
            elevio_buttonLamp(get_floor_to_indicate(ordered_store), 2, 0);// Turn off cab_button lamp
        }

        if(stop == 1){
            STATE = STOP;
        }


        
        switch (STATE)
        {
        case  INIT_STATE:
            printf("State = INIT_STATE, current_pos: %" PRId64 " \n", current_pos);
            if (current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40){
                elevio_motorDirection(DIRN_STOP);
                elevio_floorIndicator(get_floor_to_indicate(current_pos));
                STATE = IDLE;
            }
            else{
                elevio_motorDirection(DIRN_DOWN);
            }

            break;

        case IDLE:
            printf("State = IDLE \n");
            if(ordered_store == 0){
                STATE = IDLE;
            }
            if(ordered_store != 0){
                if(ordered_store == current_pos){STATE = OPEN_DOOR;};
                if(ordered_store < current_pos){STATE = GO_DOWN;};
                if(ordered_store > current_pos){STATE = GO_UP;};
            }

            break;

        case GO_UP:
            printf("State = GO_UP \n");
            elevio_floorIndicator(get_floor_to_indicate(last_pos));
            if(ordered_store == current_pos){
                elevio_motorDirection(DIRN_STOP);
                elevio_floorIndicator(get_floor_to_indicate(current_pos));
                STATE = OPEN_DOOR;
            }
            else{
                elevio_motorDirection(DIRN_UP);
            }
            
            break;

        case GO_DOWN:
            printf("State = GO_DOWN \n");
            elevio_floorIndicator(get_floor_to_indicate(last_pos));
            if(ordered_store == current_pos){
                elevio_motorDirection(DIRN_STOP);
                elevio_floorIndicator(get_floor_to_indicate(current_pos));
                STATE = OPEN_DOOR;
            }
            else{
                elevio_motorDirection(DIRN_DOWN);
            }
            
            
            break;

        case OPEN_DOOR:
            printf("State = OPEN_DOOR \n");
            if(elevio_floorSensor() != -1){
                elevio_doorOpenLamp(1);
                timer = clock();
                STATE = WAIT; 
            }
            
            break;

        case WAIT:
            printf("State = WAIT, time_ elapsed = %" PRId64 " obstruction = %" PRId64 " \n", time_elapsed, obstruction);
            time_elapsed = ((int64_t)clock()/(int64_t)CLOCKS_PER_SEC) - ((int64_t)timer/(int64_t)CLOCKS_PER_SEC);
            if(time_elapsed >= 0.5){
                STATE = CLOSE_DOOR;
            }
            break;

        case CLOSE_DOOR:
            printf("State = Closed_DOOR, obstruction = %" PRId64 " stop = %" PRId64 " \n", obstruction, stop);
            if(obstruction == 0){
                elevio_doorOpenLamp(0);
                //[1 up, 1 cab, 2 up, 2 down, 2 cab, 3 up, 3 down, 3 cab, 4 down, 4 cab]
                if(ordered_store == 10){
                    orders[0] = 0;
                    orders[1] = 0;
                } 
                if(ordered_store == 20){
                    orders[2] = 0;
                    orders[3] = 0;
                    orders[4] = 0;
                } 
                if(ordered_store == 30){
                    orders[5] = 0;
                    orders[6] = 0;
                    orders[7] = 0;
                } 
                if(ordered_store == 40){
                    orders[8] = 0;
                    orders[9] = 0;
                } 
                ordered_store = 0;
                STATE = IDLE;
            }
            if(obstruction != 0){
                STATE = WAIT;
                timer = clock();
            }
            break;

        case STOP:
            printf("State = STOP \n");
            if(stop == 1){
                elevio_stopLamp(1); //Turn on stop_lamp
                elevio_motorDirection(DIRN_STOP); //Stop elevator
                
                orders[0] = 0; orders[1] = 0; orders[2] = 0; orders[3] = 0; orders[4] = 0; orders[5] = 0; orders[6] = 0; orders[7] = 0;orders[8] = 0; orders[9] = 0; orders[10] = 0; orders[11] = 0;
                ordered_store = 0;

                elevio_buttonLamp(0, 0, 0); elevio_buttonLamp(0, 2, 0);
                elevio_buttonLamp(1, 0, 0); elevio_buttonLamp(1, 1, 0); elevio_buttonLamp(1, 2, 0);
                elevio_buttonLamp(2, 0, 0); elevio_buttonLamp(2, 1, 0); elevio_buttonLamp(2, 2, 0);
                elevio_buttonLamp(3, 1, 0); elevio_buttonLamp(3, 2, 0);
                

                elevio_stopLamp(0);
            }

            if(current_pos == 10 || current_pos == 20 || current_pos == 30 || current_pos == 40){
                    ordered_store = current_pos;
                    STATE = OPEN_DOORS_STOP;
                }
            else{
                    STATE = WAIT_STOP;
                }

            break;

        case WAIT_STOP:
            printf("State = WAIT_STOP \n");

            if(ordered_store == 0){
                STATE = WAIT_STOP;
            }
            if(ordered_store != 0){
                if(ordered_store < current_pos){STATE = GO_DOWN;};
                if(ordered_store > current_pos){STATE = GO_UP;};
            }
            
            break;

        case OPEN_DOORS_STOP:
            printf("State = OPEN_DOOR_STOP \n");

            STATE = WAIT;
            
            break;
        
        default:
            break;
        }
    }
    
}

