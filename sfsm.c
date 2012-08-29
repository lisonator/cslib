#include "sfsm.h"
#include <stdlib.h>
#include <stdio.h>

static int applyTransition(struct Machine*,
        const struct Transition*);

int test(void)
{
    printf("srututut\n");
    return(5);
}

int initializeMachine(struct Machine* m)
{
    return(applyTransition(m,m->initial));
}

int handleEvent(struct Machine* m,Event e)
{
    /*check if parent machine is in parent state*/
    if(m->parentM!=NULL)
        if(m->parentM->current != m->parentS)
            return(EXIT_FAILURE); //event not handled

    if(e>=m->nEvents)
        return(EXIT_FAILURE);

    const struct Transition *t;
    t = *(m->table + m->nEvents*m->current + e);
    if (t==NULL)
        return(EXIT_FAILURE);

    return(applyTransition(m,t));
}

static int applyTransition(struct Machine* m,
        const struct Transition * t)
{
    int ret;
    //int (*funptr)(struct Machine *) = &initializeMachine;
    int (*actionptr)(void) = t->action;
    //printf("actioning...\n");
    ret = (actionptr)();
    printf("action return: %d\n",ret);
    if(ret)
        return(EXIT_FAILURE);
    m->current = t->to;
    if(t->sub!=NULL)
        return(applyTransition(t->sub,t->sub->initial));
    return(EXIT_SUCCESS);
}