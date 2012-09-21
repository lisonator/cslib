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

#ifdef	__cplusplus
extern "C" {
#endif
    /*States and events are implemented as int */
    typedef int State; 
    typedef int Event;
    
    enum event_returns{
        SFSM_E_APP = 0, //event handled
        SFSM_E_PMDS = 1000,
        SFSM_E_OOR,
        SFSM_E_TT
    };
    
    /*forward declaration of Machine struct*/
    struct Machine;
    /*State transition stuct
     * If transition takes place to state with submachine within, the
     * sub pointer to this machine must be specified during initialization.
     * Otherwise sub = NULL  */
    struct Transition{
        const State to; //transition occurs to State 'to'
        int (* action)(struct Machine *); //during transition action is made
        struct Machine *const sub; //machine within target state
    };
    
    /*Machine struct
     * all variables must be specified during initialization.
     * if machine is nested in others machine state parentM and parentS
     * members must be specified. Otherwise parentM = NULL, parentS = -1 */
    struct Machine{
        int nEvents; //number of events
        int nStates; //number of states
        struct Transition * initial; //initial transition
        struct Transition **table; //transition table
        struct Machine * parentM; //parent machine
        State parentS; //parent state
        
        State current; //current state
    };
    
    int runMachine(struct Machine*);
    int initializeMachine(struct Machine*, int nEvents, int nStates,
            struct Transition *const initial,
            struct Transition **const table,
            struct Machine* parent, State parentS);
    /**
    * handleEvent
    * @Event: int variable representing event
    * 
    * Function returns variable from event_returns enum list. 
     * if return value != SFSM_E_APP it means that either:
     * - event not handled - parent machine is not in parent state SFSM_E_PMDS
     * - event not handled - event number out of range (SFSM_E_OOR)
     * - if action defined to given transition returns non-zero value, then
     * this value is returned. In such situation action is performed, but
     * state is not changed
     * 
     * if machine has submachine within target state, then submachine's
     * initial transition is performed
     * 
     * FIXME: machine will break when initial transition returns non-zero value
    */    
    int handleEvent(struct Machine*,Event);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SFSM_H */

