#define F_NUM 1

#include "sfsm.h"
#include <stdlib.h>
#include "customassert.h"
#include "errcodes.h"

static int applyTransition(volatile struct Machine*,
        const struct Transition*);

int initializeMachine(volatile struct Machine *m, int nEvents, int nStates,
        struct Transition *const initial,
        struct Transition **const table)
{
    cassert(nEvents>0);
    cassert(nStates>0);
    m->nEvents = nEvents;
    m->nStates = nStates;
    m->initial = initial;
    m->table = table;
    m->current = 0;
	m->processing = -1; //-1 means: not processing
	m->eventBuffer = -1;
    return(SUCCESS);
}

int runMachine(volatile struct Machine* m)
{
    return(applyTransition(m,m->initial));
}

int _handleEvent(volatile struct Machine* m,Event e)
{
	const struct Transition *t;
    t = *(m->table + m->nEvents*m->current + e);
    if(t==NULL)
		return(0);
    return(applyTransition(m,t));
}

int handleEvent(volatile struct Machine * m, Event e)
{
    if(e>=m->nEvents)
        return(SFSM_E_OOR); //event not handled Out Of Range
		
	if(m->processing >= 0) //event is processing
		if(m->eventBuffer==-1) { //buffer is free
			m->eventBuffer = e;
			return(SFSM_E_BUF); //event buffered
		}
		else
			return(SFSM_E_BOF); //event buffer overflow
	
	else {
		m->processing = e;
		_handleEvent(m,e);
	}
	
	if(m->eventBuffer!=-1) {//we have to process event in buffer
		_handleEvent(m,m->eventBuffer);
		m->eventBuffer = -1;
	}
	m->processing = -1;
	return(0);
}

static int applyTransition(volatile struct Machine* m,
        const struct Transition * t)
{
    int (*actionptr)(volatile struct Machine*) = t->action;
    (actionptr)(m);
    m->current = t->to;
    return(0);
}
