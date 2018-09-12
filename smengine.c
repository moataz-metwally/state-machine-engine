/*
 * smengine.c
 *
 *  Created on: Feb 24, 2016
 *      Author: mmetwally
 */

#include "smengine.h"

static uint8_t exit_transition = false;

static void Events_Handler(sm_engine* const this_sm);

uint8_t sm_init(sm_engine* const this_sm, const struct sm_conf_S* sm_conf)
{
    this_sm->init_ok = true;

    if (sm_conf == NULL)
    {
        this_sm->init_ok = false;
    }

    if (this_sm->init_ok == true)
    {

        if ((sm_conf->states_list != NULL) && (sm_conf->states_number != 0))
        {
            this_sm->sm_conf.states_list = sm_conf->states_list;
            this_sm->sm_conf.states_number = sm_conf->states_number;

        }
        else
        {
            this_sm->init_ok = false;
        }

        if ((this_sm->sm_conf.states_number) > (sm_conf->start_state))
        {
            this_sm->current_state = sm_conf->start_state;
        }
        else
        {
            this_sm->init_ok = false;
        }
        if ((sm_conf->transition_table != NULL) && (sm_conf->transition_table_length != 0))
        {
            this_sm->sm_conf.transition_table = sm_conf->transition_table;
            this_sm->sm_conf.transition_table_length = sm_conf->transition_table_length;
        }
        else
        {
            this_sm->init_ok = false;
        }


    }

    return this_sm->init_ok;
}

uint8_t sm_loop(sm_engine* const this_sm)
{
  //  if (this_sm->init_ok == E_NOT_OK)
    {
        /*handle current events*/
        Events_Handler(this_sm);
    }

    /*Check If there an exit transition is happened*/
    if(exit_transition == false)
    {
       /*If No exit transition so execute the current state handler if exist */
        /*Call current state handler function*/
        if ((this_sm->current_state < this_sm->sm_conf.states_number)
            && (this_sm->sm_conf.states_list[this_sm->current_state].handler != NULL))
        {
            this_sm->sm_conf.states_list[this_sm->current_state].handler();
        }

    }
    else
    {
        /*Don't execute the current state handler and differ it to the next cycle */
        /*clear the exit transition flag to execute the handler in the next cycle*/
        exit_transition = false;

    }

    return this_sm->init_ok;
}

static void Events_Handler(sm_engine* const this_sm)
{
    uint8_t table_index = 0;
    static bool first_call = true;

    for (table_index = 0;table_index < this_sm->sm_conf.transition_table_length;table_index++)
    {
        /*Check if an event happen that will move SVSM to next state*/
        if ((this_sm->sm_conf.transition_table[table_index].current_state_id == this_sm->current_state) &&
            this_sm->sm_conf.transition_table[table_index].EventHandler != NULL )
        {
            if((this_sm->sm_conf.transition_table[table_index].EventHandler() == true))
            {
                /*Call on exit for current state*/
                if (this_sm->sm_conf.states_list[this_sm->current_state].On_Exit != NULL)
                {
                    this_sm->sm_conf.states_list[this_sm->current_state].On_Exit();
                }

                /*Set the exit transition Flag to not execute the handler of the next state in the same execution
                 * cycle and differ it to next execution cycle*/

                exit_transition = true;

                /*move to next state*/
                this_sm->current_state = this_sm->sm_conf.transition_table[table_index].next_state_id;

                /*Call on entry for current state*/
                if (this_sm->sm_conf.states_list[this_sm->current_state].On_Entery != NULL)
                {
                    this_sm->sm_conf.states_list[this_sm->current_state].On_Entery();
                }


                break;
            }


        }
    }

}

