#include <stdio.h>
#include <stdarg.h>
#include "funny_debug.h"

void debug_printf(char *format, ...){
    if(DEBUG == 1){
        va_list args;
   
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

void error_printf(char *format, ...){
    va_list args;
   
    va_start(args, format);
    vprintf(format, args);
    va_end(args);  
}
