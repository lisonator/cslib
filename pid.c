#include "pid.h"

//enum Transition {T0=2,P1,T2,T3};

/*
 * private functions prototypes
 */
static int pidCompute(Block *,
            const float *inputs, int nInputs);

static int piCompute(Block *,
            const float *inputs, int nInputs);

static int pdCompute(Block *,
            const float *inputs, int nInputs);
/*
 * function declarations
 */
int piInitialization(Block *this, 
        float *parameters, int nParameters,
        float *signals, int nSignals,
        int nInputs, int nOutputs)
{
    if(nParameters!=6)
        return(EXIT_FAILURE);
    if(nSignals!=2)
        return(EXIT_FAILURE);
    if(nOutputs!=1)
        return(EXIT_FAILURE);
    if(nInputs!=1)
        return(EXIT_FAILURE);
    
    this->parameters = parameters;
    this->signals = signals;
    this->nParameters = nParameters;
    this->nSignals = nSignals;
    this->nInputs = nInputs;
    this->nOutputs = nOutputs;

    this->compute = &piCompute;
    
    return(EXIT_SUCCESS);
}

static int piCompute(Block * this,
        const float *inputs, int nInputs)
{
    float temp;
    float *par = this->parameters;
    float *sig = this->signals;
    
    if(nInputs != this->nInputs)
        return(EXIT_FAILURE);
        
    /* compute integral signal*/
    temp = sig[1] + par[1]*inputs[0];
    sig[1] = temp > par[3] ? par[3] :
        (temp < par[2] ? par[2] : temp);
    
    /* compute regulator output*/
    temp = par[0]*inputs[0] + sig[1];
    sig[0] = temp > par[5] ? par[5] :
        (temp < par[4] ? par[4] : temp);
    return(EXIT_SUCCESS);
}

int pdInitialization(Block *this, 
        float *parameters, int nParameters,
        float *signals, int nSignals,
        int nInputs, int nOutputs)
{
    if(nParameters!=4)
        return(EXIT_FAILURE);
    if(nSignals!=2)
        return(EXIT_FAILURE);
    if(nOutputs!=1)
        return(EXIT_FAILURE);
    if(nInputs!=1)
        return(EXIT_FAILURE);
    
    this->parameters = parameters;
    this->signals = signals;
    this->nParameters = nParameters;
    this->nSignals = nSignals;
    this->nInputs = nInputs;
    this->nOutputs = nOutputs;

    this->compute = &pdCompute;
    
    return(EXIT_SUCCESS);
}

static int pdCompute(Block * this,
        const float *inputs, int nInputs)
{
    float temp;
    float *par = this->parameters;
    float *sig = this->signals;
    
    if(nInputs != this->nInputs)
        return(EXIT_FAILURE);
        
    /* compute derivative signal*/
    temp = (inputs[0]-sig[1])*par[1];
    sig[1] = inputs[0];
    
    /* compute regulator output*/
    temp = par[0]*inputs[0] + temp;
    sig[0] = temp > par[3] ? par[3] :
        (temp < par[2] ? par[2] : temp);
    
    return(EXIT_SUCCESS);
}