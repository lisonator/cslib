#include "pid.h"
#include "errcodes.h"
//enum Transition {T0=2,P1,T2,T3};

/*
 * private functions prototypes
 */
static int piCompute(Block *,
            const float *inputs, int nInputs);

static int pdCompute(Block *,
            const float *inputs, int nInputs);
/*
 * function declarations
 */
int initializePi(Block *this, 
        float *parameters, int nParameters,
        float *signals, int nSignals,
        int nInputs, int nOutputs)
{
    int err;
    if(nParameters!=6)
        return(ERR_BLK_INIT);
    if(nSignals!=2)
        return(ERR_BLK_INIT);
    if(nOutputs!=1)
        return(ERR_BLK_INIT);
    if(nInputs!=1)
        return(ERR_BLK_INIT);
    
    err = initializeBlock(this,parameters,nParameters,
            signals,nSignals,
            nInputs,nOutputs);
    this->compute = &piCompute;
    return(err);
}

static int piCompute(Block * this,
        const float *inputs, int nInputs)
{
    float temp;
    float *par = this->parameters;
    float *sig = this->signals;
    
    if(nInputs != this->nInputs)
        return(ERR_BLK_CMP);
        
    /* compute integral signal*/
    temp = sig[1] + par[1]*inputs[0];
    sig[1] = temp > par[3] ? par[3] :
        (temp < par[2] ? par[2] : temp);
    
    /* compute regulator output*/
    temp = par[0]*inputs[0] + sig[1];
    sig[0] = temp > par[5] ? par[5] :
        (temp < par[4] ? par[4] : temp);
    return(SUCCESS);
}

int initializePd(Block *this, 
        float *parameters, int nParameters,
        float *signals, int nSignals,
        int nInputs, int nOutputs)
{
    int err;
    if(nParameters!=4)
        return(ERR_BLK_INIT);
    if(nSignals!=2)
        return(ERR_BLK_INIT);
    if(nOutputs!=1)
        return(ERR_BLK_INIT);
    if(nInputs!=1)
        return(ERR_BLK_INIT);
    
    err = initializeBlock(this,parameters,nParameters,
            signals,nSignals,
            nInputs,nOutputs);
    this->compute = &pdCompute;
    return(err);
}

static int pdCompute(Block * this,
        const float *inputs, int nInputs)
{
    float temp;
    float *par = this->parameters;
    float *sig = this->signals;
    
    if(nInputs != this->nInputs)
        return(ERR_BLK_CMP);
        
    /* compute derivative signal*/
    temp = (inputs[0]-sig[1])*par[1];
    sig[1] = inputs[0];
    
    /* compute regulator output*/
    temp = par[0]*inputs[0] + temp;
    sig[0] = temp > par[3] ? par[3] :
        (temp < par[2] ? par[2] : temp);
    return(SUCCESS);
}