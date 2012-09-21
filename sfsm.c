#define F_NUM 1

#include "sfsm.h"
#include <stdlib.h>
#include "customassert.h"
#include "errcodes.h"

static int applyTransition(struct Machine*,
        const struct Transition*);

int initializeMachine(struct Machine *m, int nEvents, int nStates,
        struct Transition *const initial,
        struct Transition **const table,
        struct Machine* parent, State parentS)
{
    cassert(nEvents>0);
    cassert(nStates>0);
    m->nEvents = nEvents;
    m->nStates = nStates;
    m->initial = initial;
    m->table = table;
    m->parentM = parent;
    m->parentS = parentS;
    m->current = 0;
    return(SUCCESS);
}

int runMachine(struct Machine* m)
{
    return(applyTransition(m,m->initial));
}

int handleEvent(struct Machine* m,Event e)
{
    /*check if parent machine is in parent state*/
    if(m->parentM!=NULL)
        if(m->parentM->current != m->parentS)
            return(SFSM_E_PMDS); //event not handled parent m in dif state

    if(e>=m->nEvents)
        return(SFSM_E_OOR); //event not handled Out Of Range

    const struct Transition *t;
    t = *(m->table + m->nEvents*m->current + e);
    if(t==NULL)
        return(SFSM_E_TT);//no transition prescribed to event-state pair
    return(applyTransition(m,t));
}

static int applyTransition(struct Machine* m,
        const struct Transition * t)
{
    int ret;
    int (*actionptr)(struct Machine*) = t->action;
    ret = (actionptr)(m);
    if(ret)
        return(ret);
    m->current = t->to;
    if(t->sub!=NULL)
        return(applyTransition(t->sub,t->sub->initial));
    return(SFSM_E_APP);
}