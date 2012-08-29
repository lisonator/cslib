/* 
 * File:   block.h
 * Author: Jakub Lisowski
 *
 * Created on 30 lipiec 2012, 12:56
 * 
 * This file defines custom type Block - dynamic system block with 
 * arbitrary number of parameters, signals, inputs and outputs
 * (nOutputs <= nSignals!!!)
 * 
 * Using struct Block arbitrary dynamic blocks can be implemented
 * by using custom xInitialization functions, and implementing 
 * custom compute functions (sample implementation - pid.c/h)
 */
 

#ifndef BLOCK_H
#define	BLOCK_H

#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct Block Block;
    struct Block{
        /*first nOutputs signals are block outputs*/
        float * parameters;
        float * signals;
        
        /*system dimensions, nSignals >= nOutputs!!!*/
        int nParameters;
        int nSignals;
        int nInputs;
        int nOutputs;
        
        /*function pointer to compute function - function which
         computes block signals from current block state
         (state stored in signals field) and inputs argument.
         Return type: int - error handling/debugging*/
        int (*compute)(Block *,
                const float *inputs, int nInputs);
    };

    
    /*default block Initialization function which is different with
     every implementation (compare pid.c)*/
    int blockInitialization(Block *, 
            float *parameters, int nParameters,
            float *signals, int nSignals,
            int nInputs, int nOutputs);
    
    /*function which computes block signals (evaluates function,
     which is pointed by *compute field */
    int computeSignals(Block*,
            const float *inputs, int nInputs);
    
    /*function to reset block signals (to zero)*/
    int resetSignals(Block*);
    
    /* returns pointer to outputs array (equivalent to
     * pointer to signals array)*/
    float *getOutputs(Block*);
    


#ifdef	__cplusplus
}
#endif

#endif	/* BLOCK_H */

