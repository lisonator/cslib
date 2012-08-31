#include "circularBuffer.h"
#include <string.h>
#include <assert.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int initializeCb(struct CircularBuffer *this,
        void *buffer, int nElements, int eSize, int mode)
{
    assert(nElements>1 && eSize>0);
    this->buffer = buffer;
    
    this->end = (char*)buffer + nElements*eSize;
    this->nElements = nElements;
    this->eSize = eSize;
    this->mode = mode;
    this->head = buffer;
    this->tail = buffer;
    this->stored = 0;
    
    return(EXIT_SUCCESS);
}

int popCb(struct CircularBuffer *this,
        void *item)
{
   if(this->stored == 0)
       return(EXIT_FAILURE);
   int i;
   memcpy(item, this->tail, this->eSize);
   this->tail = (char*)this->tail + this->eSize;
   if(this->tail == this->end)
       this->tail = this->buffer;
   this->stored--;
   return(EXIT_SUCCESS);
}

int pushCb(struct CircularBuffer *this,
        const void *item)
{   
    memcpy(this->head, item, this->eSize);
    this->head = (char*)this->head + this->eSize;
    if(this->head == this->end)
        this->head = this->buffer;
    this->stored++;
    if(this->stored>this->nElements){
        this->stored = this->nElements;
        this->tail = this->head;
        return(EXIT_FAILURE);
        //EXIT_FAILURE means that data has been overwritten
    }
    return(EXIT_SUCCESS);
}
void flush(struct CircularBuffer *this)
{
    this->head = this->buffer;
    this->tail = this->buffer;
    this->stored = 0;
}
