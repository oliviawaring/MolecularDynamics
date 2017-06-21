/**** vector.c ****/

#include "vector.h"
#include <assert.h>
#include <stdio.h>

struct Vector_str
{
   double x;
   double y;
   double z;
};

Vector Vector_new(double x, double y, double z)
{
   Vector oVector;
 
   oVector = (Vector)malloc(sizeof(struct Vector_str));
   if (oVector == NULL)
      return NULL;

   oVector->x = x;
   oVector->y = y;
   oVector->z = z;

   return oVector;
}

double Vector_getX(Vector oVector)
{
   assert(oVector != NULL);

   return oVector->x;
}

double Vector_getY(Vector oVector)
{
   assert(oVector != NULL);

   return oVector->y;
}

double Vector_getZ(Vector oVector)

{
   assert(oVector != NULL);

   return oVector->z;
}

void Vector_setX(Vector oVector, double x)
{
   assert(oVector != NULL);
 
   oVector->x = x;

   return;
}

void Vector_setY(Vector oVector, double y)
{
   assert(oVector != NULL);
 
   oVector->y = y;

   return;
}

void Vector_setZ(Vector oVector, double z)
{
   assert(oVector != NULL);
 
   oVector->z = z;

   return;
}

void Vector_free(Vector oVector)
{
   assert(oVector != NULL);

   free(oVector);

   return;
}
void Vector_print(Vector oVector, FILE* out)
{
   assert(oVector != NULL);
   
   if (out == NULL)
      printf("x: %f\ty: %f\tz: %f\n", oVector->x, oVector->y, oVector->z);
   else
      fprintf(out, "x: %f\ty: %f\tz: %f\n", oVector->x, oVector->y, oVector->z);

   return;
}




