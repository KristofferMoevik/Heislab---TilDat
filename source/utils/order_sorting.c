#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>
#include "order_sorting.h"


int order_soting_get_target_floor(int64_t orders[], int64_t ordered_store){
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
