/**** pairType.c ****/

#include "pairType.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct PairType_str
{
   double A;
   double B;
   /* int type; */
};

PairType PairType_new(double A, double B)
{
   PairType oPairType;

   oPairType->A = A;
   oPairType->B = B;
 
   return oPairType;
}

double PairType_getA(PairType oPairType)
{
   assert(oPairType != NULL);

   return oPairType->A;
}

double PairType_getB(PairType oPairType)
{
   assert(oPairType != NULL);

   return oPairType->B;
}

void PairType_print(PairType oPairType)

{
   int i;

   assert(oPairType != NULL);
   printf("A: %f\nB0: %f\n", oPairType->A, oPairType->B);      
   return;
}
 
void PairType_free(PairType oPairType)

{
   assert(oPairType != NULL);

   free(oPairType);

/* is this function even necessary...? */

   return;
}
 
