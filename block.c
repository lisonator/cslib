#include "block.h"
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1
/*
 * private functions prototypes
 */
static int defaultCompute(Block *,
            const float *inputs, int nInputs);

/*
 * function declarations
 */
int blockInitialization(Block *this, 
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

    this->compute = &defaultCompute;
    return(EXIT_SUCCESS);
}
    
int defaultCompute(Block * this,
        const float *inputs, int nInputs)
{
    int i;
    if(nInputs != this->nInputs)
        return(EXIT_FAILURE);
    for(i=0;i<this->nSignals;++i)
        *(this->signals+i) = i;
    return(EXIT_SUCCESS);
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
    return(EXIT_SUCCESS);
}

float *getOutputs(Block * this)
{
    return(this->signals);
}