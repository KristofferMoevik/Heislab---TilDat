#pragma once  

/**
* @file
* @brief A library for getting position, direction and need for initializing
*/


#define N_FLOORS 4

typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


/**
* @brief Start the elevator
*
* @return void
*/
void elevio_init(void);

/**
* @brief Set the motor direction of the elevator
*
* @param[in] dirn specifies if the elevator should go up, down or stay still. down = -1, still = 0, up = 1.
*
* @return void
*/
void elevio_motorDirection(MotorDirection dirn);
void elevio_buttonLamp(int floor, ButtonType button, int value);
void elevio_floorIndicator(int floor);
void elevio_doorOpenLamp(int value);
void elevio_stopLamp(int value);

int elevio_callButton(int floor, ButtonType button);
int elevio_floorSensor(void);
int elevio_stopButton(void);
int elevio_obstruction(void);

