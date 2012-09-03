/* 
 * File:   errcodes.h
 * Author: Jakub Lisowski
 *
 * Created on 3 wrzesień 2012, 16:49
 */

#ifndef ERRCODES_H
#define	ERRCODES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SUCCESS 0
    
    enum errcodes{
        ERR_DIVZERO = 1,
        ERR_BLK_INIT,
        ERR_BLK_CMP,
    };


#ifdef	__cplusplus
}
#endif

#endif	/* ERRCODES_H */

