#include "circularBuffer.h"
#include <string.h>
#include <assert.h>
#include "defs.h"
#include "errcodes.h"

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
    
    return(SUCCESS);
}

int popCb(struct CircularBuffer *this,
        void *item)
{
   if(this->stored == 0)
       return(1);
   int i;
   memcpy(item, this->tail, this->eSize);
   this->tail = (char*)this->tail + this->eSize;
   if(this->tail == this->end)
       this->tail = this->buffer;
   this->stored--;
   return(SUCCESS);
}

int multiPopCb(struct CircularBuffer *this,
        void *items, int nItems)
{
    int i;
    if(this->stored<nItems)
        nItems = this->stored;
    for(i=0;i<nItems;++i)
        popCb(this,(char*)items + this->eSize * i);
    return(nItems);
}

int allPopCb(struct CircularBuffer *this, 
        void *items, int maxItems)
{
    maxItems = maxItems>this->stored ? this->stored : maxItems;
    return(multiPopCb(this,items,this->stored));
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
        return(1);
    }
    return(SUCCESS);
}
void flush(struct CircularBuffer *this)
{
    this->head = this->buffer;
    this->tail = this->buffer;
    this->stored = 0;
}
