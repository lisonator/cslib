/* 
 * File:   defs.h
 * Author: Jakub Lisowski
 *
 * Created on 31 sierpień 2012, 12:08
 */

#ifndef DEFS_H
#define	DEFS_H

#include <stddef.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * FILENUM makro assigns number num to file and makes sure it is unique
 * file identifiers are used by customassert.h
 */
#define FILENUM(num) \
    enum { F_NUM=num }; \
    void _dummy##num(void) {}

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 * FROM: linux/kernel.h
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})    
    
#define saturate_value(value,max,min) ({\
        (value > max) ? max : ((value >= min) ? value : min);})    

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define get_value_from(type,addr) *(type*)(addr)
    
#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

