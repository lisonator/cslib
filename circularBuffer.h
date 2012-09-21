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
    /**
    * initializeCb - Initialize Circular Buffer
    * @buffer: pointer to place in memory where data will be stored
    * @nElements: number of elements in buffer
    * @eSize: size of single element (in bytes)
    * @mode: mode of operation (currently mode==0)     !!!TODO!!!
    * 
    * Initialize circular/ring/fifo buffer, return(0) when success
    * mode == 0 - buffer discards oldest data when overflow
    * mode == 1 - buffer not accepts new data when full
    */
    int initializeCb(struct CircularBuffer*,
            void *buffer, int nElements, int eSize, int mode);

    /**
    * popCb - take one element from buffer and write it to memory 
     * pointed by item
    * @item: pointer to place in memory where data will be copied
    * 
    * return(0) when success
    * return(1) when no element in buffer
    */    
    int popCb(struct CircularBuffer*,
            void *item);
    
    /**
    * multiPopCb - take multiple elements from buffer and write it to memory 
     * pointed by item
    * @item: pointer to place in memory where data will be copied
    * @nItems: number of items you want to copy
    * 
    * function returns the number of copied elements
    */    
    int multiPopCb(struct CircularBuffer*,
            void *item, int maxItems);
    
    /**
    * allPopCb - take all elements from buffer and write them to memory 
     * pointed by item
    * @item: pointer to place in memory where data will be copied
    * @maxItems: maximum number of copied items
    * 
    * function returns the number of copied elements
    */
    int allPopCb(struct CircularBuffer*, 
            void *items, int nItems);  
    
    /**
    * pushCb - add an element to buffer
    * @item: pointer element
    * 
    * function returns 1 if tail has been overwritten
    * function returns 2 if data is not written (mode=1)
    */
    int pushCb(struct CircularBuffer*,
            const void *item);

    /**
    * flush - buffer tail = buffer head
    */    
    void flushCb(struct CircularBuffer*);


#ifdef	__cplusplus
}
#endif

#endif	/* CIRCULARBUFFER_H */

