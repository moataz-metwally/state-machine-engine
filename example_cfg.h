/*
 * example_cfg.h
 *
 *  Created on: Mar 15, 2016
 *      Author: Moataz Metwally
 */

#ifndef EXAMPLE_CFG_H_
#define EXAMPLE_CFG_H_
#include "smengine.h"

#define TRANSITIONS_COUNT 2

/* Door states */

typedef enum
{
    DOOR_CLOSED = 0,
    DOOR_OPENED,
    STATES_COUNT
} enu_door_state_T;

/*+++++++++++++++++++++++++++++++++Training State Machine  Configuration ++++++++++++++++++++++++++++++++++++++++++++++*/
static void DoorSm_Closed_OnEntry(void); /* On Entry handler of Closed state */


static void DoorSm__Closed_OnExit(void); /* On Exit handler of Closed state */


static void DoorSm__Closed_Do(void); /* Do handler of Closed state */


static void DoorSm_Opened_OnEntry(void);  /* On Entry handler of Closed state */


static void DoorSm__Opened_OnExit(void);   /* On Entry handler of Closed state */


static void DoorSm__Opened_Do(void);   /* On Entry handler of Closed state */

static bool CloseButtonPressed_event(void);
static bool OpenButtonPressed_event(void);



 static struct state_handlers_S door_state_handlers[] =
{

{
DOOR_CLOSED,  /* state  */
DoorSm_Closed_OnEntry,            /* On Entry */
DoorSm__Closed_Do,            /* Handler/Do */
DoorSm__Closed_Do             /* On Exit */
}
,


{
DOOR_CLOSED,     /* state  */
DoorSm_Opened_OnEntry,            /* On Entry */
DoorSm__Opened_Do,      /* Handler/Do */
DoorSm__Opened_OnExit                    /* On Exit */
}

};
 static struct transition_S door_transitions[TRANSITIONS_COUNT] =
{

    /*  In case of Closed state, If open button is pressed go to opened state*/
{
DOOR_CLOSED,   /* State */
OpenButtonPressed_event,  /* event */
DOOR_OPENED  /*next state */
},

/*  In case of Opened state,  If close button is pressed go to closed state*/
{
DOOR_OPENED,   /* State */
CloseButtonPressed_event,  /* event */
DOOR_CLOSED  /*next state */
}

};


static struct sm_conf_S door_sm_conf =
{
    &door_transitions[0],
    (uint8_t) TRANSITIONS_COUNT,
    door_state_handlers,
    (uint8_t) STATES_COUNT,
    DOOR_CLOSED
};

#endif