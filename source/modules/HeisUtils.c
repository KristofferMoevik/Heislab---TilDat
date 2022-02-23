#include <stdio.h>
#include "HeisUtils.h"
#include "../driver/elevio.h"

int * ReadInputs(time_t start_t){

    static int  r[12];
    time_t input_t;
    time(&input_t);
    double diff_t = difftime(input_t, start_t);
    
    if(elevio_callButton(0, 0) == 1){ r[0] = diff_t; elevio_buttonLamp(0, 0, r[0]);}
    if(elevio_callButton(0, 2) == 1){ r[1] = diff_t; elevio_buttonLamp(0, 2, r[0]);}
    if(elevio_callButton(1, 0) == 1){ r[2] = diff_t; elevio_buttonLamp(1, 0, r[0]);}
    if(elevio_callButton(1, 1) == 1){ r[3] = diff_t; elevio_buttonLamp(1, 0, r[0]);}
    if(elevio_callButton(1, 2) == 1){ r[4] = diff_t; elevio_buttonLamp(1, 0, r[0]);}
    if(elevio_callButton(2, 0) == 1){ r[5] = diff_t; elevio_buttonLamp(2, 0, r[0]);}
    if(elevio_callButton(2, 1) == 1){ r[6] = diff_t; elevio_buttonLamp(2, 0, r[0]);}
    if(elevio_callButton(2, 2) == 1){ r[7] = diff_t; elevio_buttonLamp(2, 0, r[0]);}
    if(elevio_callButton(3, 1) == 1){ r[8] = diff_t; elevio_buttonLamp(3, 0, r[0]);}
    if(elevio_callButton(3, 2) == 1){ r[9] = diff_t; elevio_buttonLamp(3, 0, r[0]);}
    if(elevio_obstruction() == 1){ r[10] = diff_t;}
    if(elevio_stopButton() == 1){ r[11] = diff_t;}

    return r;
}


int * AddOrders(int * inputs, int * orders){
    int i;
    for(i=0; i < 12; i++){
        if(*(inputs + i) != 0){
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
int get_cab_order(int floor, int * orders, int * direction){
    int cab_order_array[] = {*(orders+1), *(orders+4), *(orders+7), *(orders+9)};
    int time;
    int earliest;
    int earliest_value;
    for(int i = 0; i <= sizeof(cab_order_array); i++){
        time = cab_order_array[i];
        if(time < earliest){
            earliest = time;
            earliest_value = i;
        }
    }

    if(earliest_value > floor){
        *direction = 1;
    } else if(earliest_value < floor){
        *direction = -1;
    }

    return earliest_value;
}


int get_floor_order(int floor, int * orders, int * direction){
    int floor_order_array[] = {*(orders+1), *(orders+4), *(orders+7), *(orders+9)};
    int time;
    int earliest;
    int earliest_value;
    for(int i = 0; i <= sizeof(floor_order_array); i++){
        time = cab_order_array[i];
        if(time < earliest){
            earliest = time;
            earliest_value = i;
        }
    }
    return earliest_value;
}

int SortOrders(int * orders, int * completed_order, int * ordered_floor, int * stop_on_the_way){
    int * direction; // up is 1, down is -1
    int floor = elevio_floorSensor();
    int cab_order = get_cab_order(floor, orders); //returns 0 if no order or number of story to go to
    int floor_order = get_floor_order(floor, orders); // returns 0 if no order or number of floor to go to
    int floor_between = get_floor_between(floor, cab_order); //returns 0 if none return number of floor between if not
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
        *completed_order = 0;
    }

    if(floor_between != 0){
        *stop_on_the_way = floor_between;
    }

    return 0;
}



