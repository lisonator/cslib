
#include "customassert.h"
#include <stdio.h>

void assertFailed (int fileid, int linenum){
    printf("assertion failed! FILEID: %d, LINE: %d\n",fileid,linenum);
}
