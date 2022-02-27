#include <stdio.h>
#include "HeisUtils.h"
#include "../driver/elevio.h"

double * ReadInputs(time_t start_t){

    int r[12];
    time_t input_t = clock();
    int diff_t = clock();
    // printf(" %f \n", diff_t);
    
    if(elevio_callButton(0, 0) == 1){ r[0] = diff_t; elevio_buttonLamp(0, 0, 1);} else{r[0] = 0;}
    if(elevio_callButton(0, 2) == 1){ r[1] = diff_t; elevio_buttonLamp(0, 2, 1);} else{r[1] = 0;}
    if(elevio_callButton(1, 0) == 1){ r[2] = diff_t; elevio_buttonLamp(1, 0, 1);} else{r[2] = 0;}
    if(elevio_callButton(1, 1) == 1){ r[3] = diff_t; elevio_buttonLamp(1, 0, 1);} else{r[3] = 0;}
    if(elevio_callButton(1, 2) == 1){ r[4] = diff_t; elevio_buttonLamp(1, 0, 1);} else{r[4] = 0;}
    if(elevio_callButton(2, 0) == 1){ r[5] = diff_t; elevio_buttonLamp(2, 0, 1);} else{r[5] = 0;}
    if(elevio_callButton(2, 1) == 1){ r[6] = diff_t; elevio_buttonLamp(2, 0, 1);} else{r[6] = 0;}
    if(elevio_callButton(2, 2) == 1){ r[7] = diff_t; elevio_buttonLamp(2, 0, 1);} else{r[7] = 0;}
    if(elevio_callButton(3, 1) == 1){ r[8] = diff_t; elevio_buttonLamp(3, 0, 1);} else{r[8] = 0;}
    if(elevio_callButton(3, 2) == 1){ r[9] = diff_t; elevio_buttonLamp(3, 0, 1);} else{r[9] = 0;}
    if(elevio_obstruction() == 1){ r[10] = diff_t;}
    if(elevio_stopButton() == 1){ r[11] = diff_t;}

    return r;
}


int * AddOrders(int * inputs, int * orders){
    int i;
    for(i=0; i < 12; i++){
        if(*(inputs + i) != 0 && *(orders + i) == 0){
            *(orders + i) = *(inputs + i);
        }
    }
    return orders;
}

// priority
// 1. cab. First one is priority 1.
// 2. floor on the way
// 3. nearest floor

//assumptions
// 1. when the elevator stops it does not move before it has a new order

// variables
// completed_order: is 0 if order not completed. Equals story completed if completed

//returns 0 if no order or number of story to go to. Based on who pushed the button first
int get_cab_order(int floor, int * orders){
    printf("%d", orders[1]);
    int cab_order_array[4];
    cab_order_array[0] = orders[1];
    cab_order_array[1] = orders[4];
    cab_order_array[2] = orders[7]; 
    cab_order_array[3] = orders[9];
    double time;
    double earliest;
    int earliest_value;
    for(int i = 0; i < 4; i++){
        time = cab_order_array[i];
        if(time < earliest){
            earliest = time;
            earliest_value = i;
        }
    }

    return earliest_value;
}

//returns 0 if no order or number of story to go to. Based on who pushed the button first
int get_floor_order(int floor, int * orders, int * direction){
    int floor_order_array[] = {*(orders+1), *(orders+4), *(orders+7), *(orders+9)};
    int time;
    int earliest;
    int earliest_value;
    for(int i = 0; i < 4; i++){
        time = floor_order_array[i];
        if(time < earliest){
            earliest = time;
            earliest_value = i;
        }
    }
    return earliest_value;
}


int * get_compact_binary_orders(int * orders){
    int * compact_binary_orders;
    for(int i  = 0; i < 4; i++){
        *(compact_binary_orders + i) = 0;
    }
    
    if(compact_binary_orders[0] != 0 || compact_binary_orders[1] != 0){
        compact_binary_orders[0] = 1;
    }
    if(compact_binary_orders[2] != 0 || compact_binary_orders[3] != 0 || compact_binary_orders[4] != 0){
        compact_binary_orders[1] = 1;
    }
    if(compact_binary_orders[5] != 0 || compact_binary_orders[6] != 0 || compact_binary_orders[7] != 0){
        compact_binary_orders[2] = 1;
    }
    if(compact_binary_orders[8] != 0 || compact_binary_orders[9] != 0){
        compact_binary_orders[3] = 1;
    }

    return compact_binary_orders;
}


int get_stop_on_the_way(int * floor, int * ordered_floor, int *orders){
    int stop_on_the_way = 0;
    int * compact_binary_orders = get_compact_binary_orders;

    if(*ordered_floor > floor){
        for(int i = *ordered_floor + 1; i < floor; ++i){
            if(compact_binary_orders[i] == 1){
                stop_on_the_way = i;
                break;
            }
        }
    }
    else{
        stop_on_the_way = 0;
    }

    return stop_on_the_way;
}


void SortOrders(int * orders, int * completed_order, int * ordered_floor, int * direction){
    int * floor = elevio_floorSensor();
    int cab_order = get_cab_order(floor, orders); //returns 0 if no order or number of story to go to
    int floor_order = get_floor_order(floor, orders, direction); // returns 0 if no order or number of floor to go to
    int stop_on_the_way = get_stop_on_the_way(floor, ordered_floor, orders); //returns 0 if none return number of floor between if not
    printf("floor = %d, cab orders = %d, floor_orders = %d, floor between = %d \n", floor, cab_order, floor_order, stop_on_the_way);
    // Find main order
    if(completed_order != 0){
        if(cab_order != 0){
            *ordered_floor = cab_order;
        } 
        else if(floor_order != 0){
            *ordered_floor = floor_order;
        }
        else{
            *ordered_floor = floor;
        }

        int stop_on_the_way = get_stop_on_the_way(floor, ordered_floor,orders);
        if(stop_on_the_way != 0){
            *ordered_floor = stop_on_the_way;
        }
        *completed_order = 0;
    }

    return;
}



