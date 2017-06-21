/**** atomType.c ****/

#include "atomType.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct AtomType_str
{
   int iType;
   double fMass;
   double fCharge;
   double fRadius;
};

AtomType AtomType_new(int iType, double fMass, double fCharge, double fRadius)
{
   AtomType oAtomType;

   oAtomType = (AtomType)malloc(sizeof(struct AtomType_str));
   if (oAtomType == NULL)
      return NULL;
  
   oAtomType->iType = iType;

   oAtomType->fMass = fMass;
   
   oAtomType->fCharge = fCharge;
   
   oAtomType->fRadius = fRadius;
 
   return oAtomType;
}

int AtomType_getType(AtomType oAtomType)
{
   assert(oAtomType != NULL);

   return oAtomType->iType;
}

void AtomType_print(AtomType oAtomType)

{
   int i;

   assert(oAtomType != NULL);
   i = printf("type: %i\n" + oAtomType->iType);
   printf("\tmass: %f\n\tcharge: %f\n\tradius: %f\n", oAtomType->fMass,
          oAtomType->fCharge, oAtomType->fRadius);      
   printf("check");
   return;
}
 
void AtomType_free(AtomType oAtomType)

{
   assert(oAtomType != NULL);

   free(oAtomType);

/* is this function even necessary...? */

   return;
}
 
