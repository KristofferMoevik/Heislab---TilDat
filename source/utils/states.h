#pragma once
#include <inttypes.h>

int64_t states_INIT_STATE(int64_t current_pos, int64_t *motor_direction, int64_t STATE);

int64_t states_IDLE(int64_t ordered_store, int64_t current_pos, int64_t STATE);

int64_t states_GO_UP(int64_t ordered_store, int64_t current_pos, int64_t UP_2, int64_t CAB_2, int64_t UP_3, int64_t CAB_3, int64_t last_pos, int64_t *motor_direction, int64_t STATE);

int64_t states_GO_DOWN(int64_t ordered_store, int64_t current_pos, int64_t DOWN_2, int64_t CAB_2, int64_t DOWN_3, int64_t CAB_3, int64_t last_pos, int64_t *motor_direction, int64_t STATE);
