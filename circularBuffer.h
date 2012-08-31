/* 
 * File:   circularBuffer.h
 * Author: Jakub Lisowski
 *
 * Created on 29 sierpień 2012, 17:13
 */

#ifndef CIRCULARBUFFER_H
#define	CIRCULARBUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

    /*mode = 0 - buffer discards oldest data when overflow*/
    /*mode = 1 - temporarily not implemented */
    struct CircularBuffer{
        void *buffer;
        void *end;
        int nElements;
        int eSize;
        int mode;
        int stored;
        void *head;
        void *tail;
    };

    int initializeCb(struct CircularBuffer*,
            void *buffer, int nElements, int eSize, int mode);
    
    int popCb(struct CircularBuffer*,
            void *item);
    int pushCb(struct CircularBuffer*,
            const void *item);
    void flush(struct CircularBuffer*);


#ifdef	__cplusplus
}
#endif

#endif	/* CIRCULARBUFFER_H */

