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
* @brief Sets the motor direction of the elevator
*
* @param[in] dirn specifies if the elevator should go up, down or stay still. down = -1, still = 0, up = 1.
*
* @return void
*/
void elevio_motorDirection(MotorDirection dirn);

/**
* @brief Sets the button lamps on or off
*
* @param[in] floor the floor to set the light
* @param[in] button specifies if the button is HALL_UP, HALL_DOWN or CAB
* @param[in] value sets light on or off
*
* @return void
*/
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
* @brief Sets the floor indicator light on or off
*
* @param[in] floor the floor to set the light
*
* @return void
*/
void elevio_floorIndicator(int floor);

/**
* @brief Sets the door (lamp) open or closed
*
* @param[in] value sets the door (lamp) open or closed
*
* @return void
*/
void elevio_doorOpenLamp(int value);

/**
* @brief Sets the stop (lamp) on or off
*
* @param[in] value sets the door (lamp) on or off
*
* @return void
*/
void elevio_stopLamp(int value);

/**
* @brief Checks the state of a specifyed button
*
* @param[in] floor what floor button to check
* @param[in] button what type of button to check
*
* @return high or low value based on button pressed or not
*/
int elevio_callButton(int floor, ButtonType button);

/**
* @brief Checks what store the elevator is in.
*
* @return store of the elevator
*/
int elevio_floorSensor(void);

/**
* @brief Checks if the stop button is pressed
*
* @return state of the stop button
*/
int elevio_stopButton(void);

/**
* @brief Checks if there is a obstruction in the door
*
* @return 1 if there is a obstruction 0 if there are no obstruction
*/
int elevio_obstruction(void);

