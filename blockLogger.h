/* 
 * File:   blockLogger.h
 * Author: Jakub Lisowski
 *
 * Created on 29 sierpień 2012, 16:04
 */

#ifndef BLOCKLOGGER_H
#define	BLOCKLOGGER_H

#include "block.h"
#include "circularBuffer.h"
#include "sfsm.h"

#ifdef	__cplusplus
extern "C" {
#endif

    struct BlockLogger{
        struct Block *watched;
        float *storage;
        int storageSize;
        int nSignals;
        
        struct CircularBuffer buf;
        struct Machine logic;
    };

    int initializeBlockLogger(struct BlockLogger*,
            struct Block *towatch, float *storage, int storageSize);
    
    int flushBl(struct BlockLogger*);
    int startBl(struct BlockLogger*);
    int pauseBl(struct BlockLogger*);
    int stopBl(struct BlockLogger*); //pause + flush

#ifdef	__cplusplus
}
#endif

#endif	/* BLOCKLOGGER_H */

