/* 
 * File:   pid.h
 * Author: Jakub Lisowski
 *
 * Created on 1 sierpień 2012, 19:52
 * 
 * This file consists of multiple implementations of 
 * PID regulator using Block object
 */

#ifndef PID_H
#define	PID_H

#include "block.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /* PI regulator
     * parameters[6]:
     * [kp, ki, minI, maxI, minU, maxU]
     * signals[3]:
     * [u(k), i(k), e(k)]
     * outputs[1]:
     * u(k)
     * inputs[1]:
     * e(k)
     */
    int initializePi(Block *, 
            float *parameters, int nParameters,
            float *signals, int nSignals,
            int nInputs, int nOutputs);    
    
    /* PD regulator
     * parameters[4]:
     * [kp, kd, minU, maxU]
     * signals[3]:
     * [u(k), d(k), e(k)]
     * outputs[1]:
     * u(k)
     * inputs[1]:
     * e(k)
     */
    int initializePd(Block *,
            float *parameters, int nParameters,
            float *signals, int nSignals,
            int nInputs, int nOutputs);


#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

