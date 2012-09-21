/* 
 * File:   customassert.h
 * Author: Jakub Lisowski
 *
 * Created on 16 wrzesień 2012, 18:20
 * Based on mingw-runtime assert.h
 */

/* We should be able to include this file multiple times to allow the assert
   macro to be enabled/disabled for different parts of code.  So don't add a
   header guard.  */ 

#undef cassert

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef NDEBUG
/*
 * If not debugging, assert does nothing.
 */
#define cassert(x)	((void)0)

#elif defined STD_ASSERT
/*
 * Use standard library assert
 */
#include <assert.h>
#define cassert(x) assert(x)
    
#else

extern void assertFailed (unsigned int, unsigned int);
/*
 * Use custom assert
 */
#define cassert(e) \
        if(!(e)) \
        assertFailed (F_NUM, __LINE__)

#endif	/* NDEBUG */
    
    


#ifdef	__cplusplus
}
#endif


