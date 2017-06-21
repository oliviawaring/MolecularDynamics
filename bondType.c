/**** bondType.c ****/

#include "bondType.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct BondType_str
{
   double k;
   double b0;
   /* int type; */
};

/* BondType BondType_new(double k, double b0, AtomType atomType1, AtomType atomType2, int numAtomTypes)
{
   BondType oBondType;
   int i, index1, index2, hash, width;

   assert(atomType1 != NULL);
   assert(atomType2 != NULL);

   index1 = AtomType_getType(atomType1) - 1;
   index2 = AtomType_getType(atomType2) - 1;

   oBondType = (BondType)malloc(sizeof(struct BondType_str));
   if (oBondType == NULL)
      return NULL;
   width = numAtomTypes;
   hash = index1 * width + index2;
   for (i = 1; i < index1 + 1; i++)
   {
      hash = hash - width + i; 
   }
   oBondType->k = k;
   oBondType->b0 = b0;
   oBondType->type = hash + 1;
 
   return oBondType;
}
 */

BondType BondType_new(double k, double b0)
{
   BondType oBondType;
   
   oBondType->k = k;
   oBondType->b0 = b0;
 
   return oBondType;
}

double BondType_getK(BondType oBondType)
{
   assert(oBondType != NULL);

   return oBondType->k;
}

double BondType_getB(BondType oBondType)
{
   assert(oBondType != NULL);

   return oBondType->b0;
}

void BondType_print(BondType oBondType)

{
   int i;

   assert(oBondType != NULL);
   printf("k: %f\nb0: %f\n", oBondType->k, oBondType->b0);      
   return;
}
 
void BondType_free(BondType oBondType)

{
   assert(oBondType != NULL);

   free(oBondType);

/* is this function even necessary...? */

   return;
}
 
