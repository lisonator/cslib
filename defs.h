/* 
 * File:   defs.h
 * Author: Jakub Lisowski
 *
 * Created on 31 sierpień 2012, 12:08
 */

#ifndef DEFS_H
#define	DEFS_H

#include <stddef.h>

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

#ifdef	__cplusplus
extern "C" {
#endif

    
    
    



#ifdef	__cplusplus
}
#endif

#endif	/* DEFS_H */

