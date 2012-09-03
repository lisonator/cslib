#include "block.h"
#include "errcodes.h"
/*
 * private functions prototypes
 */
static int defaultCompute(Block *,
            const float *inputs, int nInputs);

/*
 * function declarations
 */
int initializeBlock(Block *this, 
        float *parameters, int nParameters,
        float *signals, int nSignals,
        int nInputs, int nOutputs)
{
    this->parameters = parameters;
    this->signals = signals;
    this->nParameters = nParameters;
    this->nSignals = nSignals;
    this->nInputs = nInputs;
    this->nOutputs = nOutputs;

    this->ts = 1.0;
    
    this->compute = &defaultCompute;
    return(SUCCESS);
}
    
int defaultCompute(Block * this,
        const float *inputs, int nInputs)
{
    int i;
    if(nInputs != this->nInputs)
        return(ERR_BLK_CMP);
    for(i=0;i<this->nSignals;++i)
        *(this->signals+i) = i;
    return(SUCCESS);
}

int computeSignals(Block * this,
        const float *inputs, int nInputs)
{
    return(this->compute(this, inputs, nInputs));
}

int resetSignals(Block* this)
{
    int i;
    for(i=0;i<this->nSignals;++i)
        *(this->signals+i) = 0;
    return(SUCCESS);
}

float *getOutputs(Block * this)
{
    return(this->signals);
}