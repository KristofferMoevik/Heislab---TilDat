#pragma once
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

int64_t states_INIT_STATE(int64_t current_pos, int64_t *motor_direction, int64_t STATE);

int64_t states_IDLE(int64_t ordered_store, int64_t current_pos, int64_t STATE);

int64_t states_GO_UP(int64_t ordered_store, int64_t current_pos, int64_t UP_2, int64_t CAB_2, int64_t UP_3, int64_t CAB_3, int64_t last_pos, int64_t *motor_direction, int64_t STATE);

int64_t states_GO_DOWN(int64_t ordered_store, int64_t current_pos, int64_t DOWN_2, int64_t CAB_2, int64_t DOWN_3, int64_t CAB_3, int64_t last_pos, int64_t *motor_direction, int64_t STATE);

int64_t states_OPEN_DOOR(int64_t STATE, double *timer, int64_t current_pos);

int64_t states_WAIT(int64_t obstruction, double *timer, double *clock_time, double *time_elapsed, int64_t current_pos, int64_t STATE);

int64_t states_CLOSE_DOOR(int64_t obstruction, int64_t stop, int64_t current_pos, int64_t *orders, int64_t *ordered_store, int64_t STATE);

int64_t states_STOP(int64_t stop, int64_t *motor_direction, int64_t *orders, int64_t *ordered_store, int64_t current_pos, int64_t STATE);

int64_t states_WAIT_STOP(int64_t ordered_store, int64_t current_pos, int64_t STATE);

int64_t states_OPEN_DOOR_STOP(double *timer, int64_t STATE);
