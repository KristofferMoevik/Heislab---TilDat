#include <stdio.h>
#include "HeisUtils.h"
#include "../driver/elevio.h"

int * ReadInputs(){

    static int  r[12];
    
    r[0] = elevio_callButton(0, 0); elevio_buttonLamp(0, 0, r[0]);
    r[1] = elevio_callButton(0, 2); elevio_buttonLamp(0, 2, r[1]);
    r[2] = elevio_callButton(1, 0); elevio_buttonLamp(1, 1, r[2]);
    r[3] = elevio_callButton(1, 1); elevio_buttonLamp(1, 1, r[3]);
    r[4] = elevio_callButton(1, 2); elevio_buttonLamp(1, 2, r[4]);
    r[5] = elevio_callButton(2, 0); elevio_buttonLamp(2, 0, r[5]);
    r[6] = elevio_callButton(2, 1); elevio_buttonLamp(2, 1, r[6]);
    r[7] = elevio_callButton(2, 2); elevio_buttonLamp(2, 2, r[7]);
    r[8] = elevio_callButton(3, 1); elevio_buttonLamp(3, 1, r[8]);
    r[9] = elevio_callButton(3, 2); elevio_buttonLamp(3, 2, r[9]);
    r[10] = elevio_obstruction();
    r[11] = elevio_stopButton();
    

    return r;
}

// [1 up, 1 cab, 2 up, 2 down, 2 cab, 3 up, 3 down, 3 cab, 4 down, 4 cab]
int * AddOrders(int inputs[12], int * orders[12]){
    int i;
    for(i=0; i < 12; i++){
        if(inputs[i] == 1){
            orders[i] = 1;
        }
    }

    return orders;
}
