#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#ifndef functions_h
#define functions_h

#endif /* functions_h */

extern _Bool check_invalid_instruction( const float );
extern void load( float * const );
extern void execute( float * const, float * const, float * const, int * const );
extern void dump( const float * const, const float, const float, const int );
extern void check_overflow( const float, int * const );
extern void give_intro( void );

#define MEM_SIZE 100
