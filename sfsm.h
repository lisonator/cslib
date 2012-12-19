/* 
 * File:   sfsm.h
 * Author: Jakub Lisowski
 *
 * Created on 6 sierpień 2012, 18:55
 * 
 * Simple Finite State Machine implementation with hierarchical support.
 * Code uses static memory allocation and is based on the lookup table 
 * approach to state machines.
 * 
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
        SFSM_E_OOR,
        SFSM_E_TT,
		SFSM_E_BOF, //buffer overflow
		SFSM_E_BUF //event buffered
    };
    
    /*forward declaration of Machine struct*/
    struct Machine;
    /*State transition stuct
     * If transition takes place to state with submachine within, the
     * sub pointer to this machine must be specified during initialization.
     * Otherwise sub = NULL  */
    struct Transition{
        const State to; //transition occurs to State 'to'
        int (* action)(volatile struct Machine *); //during transition action is made
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
        
        State current; //current state
		Event processing; //currently processing event
		
		Event eventBuffer; //eventBuffer
    };
    
    int runMachine(volatile struct Machine*);
    int initializeMachine(volatile struct Machine*, int nEvents, int nStates,
            struct Transition *const initial,
            struct Transition **const table);
    /**
    * handleEvent
    * @Event: int variable representing event
    * 
    * Function returns variable from event_returns enum list. 
     * if return value != SFSM_E_APP it means that either:
     * - event not handled - event number out of range (SFSM_E_OOR)
     * - if action defined to given transition returns non-zero value, then
     * this value is returned. In such situation action is performed, but
     * state is not changed - UPDATE: Thic behaviour is deprecated - since
	 * 2012-12-18 transition ocurrance is independent of return value - to
	 * make things simplier, and always returns the same value as action
     *  
     * FIXME: machine will break when initial transition returns non-zero value
    */    
    int handleEvent(volatile struct Machine*,Event);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SFSM_H */

