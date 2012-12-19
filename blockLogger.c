#include "blockLogger.h"
#include "sfsm.h"
#include "customassert.h"
#include "defs.h"
#include "errcodes.h"

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

inline static int aInit(struct Machine *m){
    return(SUCCESS);
}

static int aFlush(struct Machine *m){
    struct BlockLogger * b = container_of(m,struct BlockLogger,logic);
    flushCb(&b->buf);
    return(SUCCESS);
}

static int aRun(struct Machine *m){   
    return(SUCCESS);
}

static int aStop(struct Machine *m){
    return(SUCCESS);
}

static int aTick(struct Machine *m){
    struct BlockLogger * b = container_of(m,struct BlockLogger,logic);
    pushCb(&b->buf,(void*)b->watched->signals);
    return(SUCCESS);
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
            &tInitial,&logicTT[0]) || error;
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

int tickBl(struct BlockLogger *this)
{
    return(handleEvent(&this->logic, E4_TICK));
}

int getSamples(struct BlockLogger *this,
            float* data, int size, int n)
{
    if(n*this->nSignals > size)
        return(0);

    return(multiPopCb(&this->buf,(void*)data,n));
}

int nSamples(struct BlockLogger* this)
{
	return(this->buf.stored);
}
