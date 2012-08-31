#include "blockLogger.h"
#include "sfsm.h"
#include <assert.h>
#include "defs.h"
#include <stdio.h>

enum states{
    S1_STANDBY,
    S2_RUNNING,
    nStates
};

enum events{
    E1_FLUSH,
    E2_RUN,
    E3_STOP,
    E4_TICK,
    nEvents
};

static int aInit(struct Machine *m){
    //struct BlockLogger * b = container_of(m,struct BlockLogger,logic);
    return(EXIT_SUCCESS);
}

static int aFlush(struct Machine *m){
    struct BlockLogger * b = container_of(m,struct BlockLogger,logic);
    flush(&b->buf);
    return(EXIT_SUCCESS);
}

static int aRun(struct Machine *m){   
    return(EXIT_SUCCESS);
}

static int aStop(struct Machine *m){
    return(EXIT_SUCCESS);
}

static int aTick(struct Machine *m){
    struct BlockLogger * b = container_of(m,struct BlockLogger,logic);
    pushCb(&b->buf,(void*)b->watched->signals);
}

static struct Transition tInitial = {S1_STANDBY, &aInit, NULL};
static struct Transition t11f = {S1_STANDBY, &aFlush, NULL};
static struct Transition t12r = {S2_RUNNING, &aRun, NULL};
static struct Transition t21s = {S1_STANDBY, &aStop, NULL};
static struct Transition t22f = {S2_RUNNING, &aFlush, NULL};
static struct Transition t22t = {S2_RUNNING, &aTick, NULL};

struct Transition *logicTT[nStates*nEvents] = {
    &t11f,&t12r,NULL ,NULL ,
    &t22f,NULL ,&t21s,&t22t};

int initializeBlockLogger(struct BlockLogger *this, struct Block *towatch, 
        float *storage, int storageSize)
{
    this->watched = towatch;
    this->storage = storage;
    this->storageSize = storageSize;
    this->nSignals = towatch->nSignals;
    int error = initializeCb(&this->buf,(void*)storage,
            storageSize/this->nSignals,
            sizeof(float)*this->nSignals,0);
    error = initializeMachine(&this->logic,nEvents,nStates,
            &tInitial,&logicTT[0],NULL,-1) || error;
    return(runMachine(&this->logic)||error);
}

int flushBl(struct BlockLogger* this){
    return(handleEvent(&this->logic, E1_FLUSH));
}

int startBl(struct BlockLogger* this){
    return(handleEvent(&this->logic, E2_RUN));
}

int pauseBl(struct BlockLogger* this){
    return(handleEvent(&this->logic, E3_STOP));
}

int stopBl(struct BlockLogger* this){
    int error = handleEvent(&this->logic, E3_STOP);
    return(handleEvent(&this->logic, E1_FLUSH) || error);
}