/* 
 * File:   sfsm.h
 * Author: Jakub Lisowski
 *
 * Created on 6 sierpień 2012, 18:55
 * 
 * Simple Finite State Machine implementation with hierarchical support.
 * Code uses static memory allocation and is based on the lookup table 
 * approach to state machines.
 */

#ifndef SFSM_H
#define	SFSM_H

#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif
int test(void);
    /*States and events are implemented as int */
    typedef int State; 
    typedef int Event;
    
    /*forward declaration of Machine struct*/
    struct Machine;
    /*State transition stuct
     * If transition takes place to state with submachine within, the
     * sub pointer to this machine must be specified during initialization.
     * Otherwise sub = NULL  */
    struct Transition{
        const State to; //transition occurs to State 'to'
        int (* action)(void); //during transition action is made
        struct Machine *const sub; //machine within target state
    };
    
    /*Machine struct
     * all variables must be specified during initialization.
     * if machine is nested in others machine state parentM and parentS
     * members must be specified. Otherwise parentM = NULL, parentS = -1 */
    struct Machine{
        const int nEvents; //number of events
        const int nStates; //number of states
        const struct Transition * const initial; //initial transition
        const struct Transition **const table; //transition table
        const struct Machine * parentM; //parent machine
        const State parentS; //parent state
        
        State current; //current state
    };
    
    int initializeMachine(struct Machine*);
    int handleEvent(struct Machine*,Event);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SFSM_H */
