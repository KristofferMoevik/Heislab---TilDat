#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "driver/elevio.h"
#include "modules/HeisUtils.h"


int example(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);


    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                printf("%d",btnPressed);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}

int * test_get_compact_binary_orders(int * orders){
    int compact_binary_orders[4];
    for(int i  = 0; i < 4; i++){
        compact_binary_orders[i] = 0;
    }
    if(orders[0] != 0 || orders[1] != 0){
        compact_binary_orders[0] = 1;
    }
    if(orders[2] != 0 || orders[3] != 0 || orders[4] != 0){
        compact_binary_orders[1] = 1;
    }
    if(orders[5] != 0 || orders[6] != 0 || orders[7] != 0){
        compact_binary_orders[2] = 1;
    }
    if(orders[8] != 0 || orders[9] != 0){
        compact_binary_orders[3] = 1;
    }

    return &compact_binary_orders;
}

int test_get_stop_on_the_way(int * floor, int * ordered_floor, int *orders){
    int stop_on_the_way = 0;
    int * compact_binary_orders;
    compact_binary_orders = get_compact_binary_orders(orders);
    if(*ordered_floor < *floor){
        printf("1");
        for(int i = *ordered_floor + 1; i < *floor; ++i){
            if(compact_binary_orders[i] == 1){
                stop_on_the_way = i;
                break;
            }
        }
    }
    else if(*ordered_floor > *floor){
        printf("2");
        for(int i = *floor + 1; i < *ordered_floor; ++i){
            printf("compact_orders = [%d]", *(compact_binary_orders + i));
            if(*(compact_binary_orders + 1) == 1){
                stop_on_the_way = i;
                break;
            }
        }
    }
    else{
        stop_on_the_way = 0;
    }

    printf("floor %d, ordered floor %d, stop on the way %d", *floor, *ordered_floor, stop_on_the_way);
    return stop_on_the_way;
}

int main(){
    
    time_t start_t = clock();
    int * inputs;
    int initial_orders[] = {0,0,0,0,0,0,0,0,0,0};
    int motor_direction = 0; // up is 1, down is -1, 0 is still
    int completed_order = 1;
    int ordered_floor = elevio_floorSensor();
    int stop_on_the_way = 0;

    elevio_init();
    
    inputs = ReadInputs(start_t);
    int * orders = AddOrders(inputs, initial_orders);
    
    while(1){
    
        inputs = ReadInputs(start_t);
        orders = AddOrders(inputs, orders);
        SortOrders(orders, &completed_order, &ordered_floor, &stop_on_the_way);
        // printf("floor %d, ordered floor %d, stop on the way %d", floor, ordered_floor, stop_on_the_way);
        // printf("ordered floor : %d", ordered_floor);
        int i;
        for ( i = 0; i < 8; i++ ) {
            int order_element = *(orders + i);
            printf( "%d ", order_element);
        }
        printf("\n");
    }
}

