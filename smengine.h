/*
 * smengine.h
 *
 *  Created on: Feb 24, 2016
 *      Author: mmetwally
 */

#ifndef STATEMACHINE_ENGINE_H_
#define STATEMACHINE_ENGINE_H_
#include "stdio.h"
#include "stddef.h"
#include "stdint.h"
#include "inttypes.h"
#include "stdbool.h"

struct state_handlers_S
{
    uint16_t state_id;
    void (*On_Entery)(void);
    void (*handler)(void);
    void (*On_Exit)(void);
};

typedef struct transition_S
{
    uint16_t current_state_id;
    bool (*EventHandler)(void);
    uint16_t next_state_id;
} transition_T;

struct sm_conf_S
{
    const struct transition_S *transition_table;
    uint8_t transition_table_length;
    const struct state_handlers_S *states_list;
    uint8_t states_number;
    uint16_t start_state;
};

typedef struct
{
    uint16_t current_state;
    struct sm_conf_S sm_conf;
    bool init_ok;
} sm_engine;

uint8_t sm_init(sm_engine* const this_sm, const struct sm_conf_S* sm_conf);
uint8_t sm_loop(sm_engine* const this_sm);
void sm_Set_Events(sm_engine* const this_sm, uint16_t event);

#endif /* STATEMACHINE_ENGINE_H_ */
