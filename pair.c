/**** pair.c ****/

#include "pair.h"
#include <assert.h>
#include <stdio.h>

struct Pair_str
{
   double A;
   double B;
};

Pair Pair_new(double A, double B)
{
   Pair oPair;
 
   oPair = (Pair)malloc(sizeof(struct Pair_str));
   if (oPair == NULL)
      return NULL;

   oPair->A = A;
   oPair->B = B;

   return oPair;
}

double Pair_getA(Pair oPair)
{
   assert(oPair != NULL);

   return oPair->A;
}

double Pair_getB(Pair oPair)
{
   assert(oPair != NULL);

   return oPair->B;
}
void Vector_setX(Vector oVector, double x)
{
   assert(oVector != NULL);
 
   oVector->x = x;

   return;
}

void Pair_free(Pair oPair)
{
   assert(oPair != NULL);

   free(oPair);

   return;
}
void Pair_print(Pair oPair, FILE* out)
{
   assert(oPair != NULL);
   
   if (out == NULL)
      printf("A: %f\tB: %f\n", oPair->A, oPair->B);
   else
      fprintf(out, "A: %f\tB: %f\n", oPair->A, oPair->B);

   return;
}




