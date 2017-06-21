/**** atom.c ****/

#include "atom.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


struct Atom_str
{
   int iType;
   int iID;
   Vector position;
   Vector velocity;
   Vector prevPos;
   Vector scaledVels;
   Vector forces;
};


Atom Atom_new(int iType, int iID, Vector position, Vector velocity)
{
   Atom oAtom;

   assert(position != NULL);
   assert(velocity != NULL);

   oAtom = (Atom)malloc(sizeof(struct Atom_str));
   if (oAtom == NULL)
      return NULL;
  
   oAtom->iType = iType;

   oAtom->iID = iID;
   
   oAtom->position = position;
   
   oAtom->velocity = velocity;
 
   return oAtom;
}

int Atom_getID(Atom oAtom);
{
   assert(oAtoma != NULL);
   
   return oAtom->iID;
}


void Atom_setForces(Atom oAtom, Vector oVector)
{
   assert(oAtom != NULL);
   assert(oVector != NULL);

   oAtom->forces = oVector;

   return;
}

void Atom_setVel(Atom oAtom, Vector oVector)
{
   assert(oAtom != NULL);
   assert(oVector != NULL);

   oAtom->scaledVels = oVector;

   return;
}

void Atom_setPrevPos(Atom oAtom, Vector oVector)
{
   assert(oAtom != NULL);
   assert(oVector != NULL);

/*   if (oAtom->prevPos != NULL)
      free(oAtom->prevPos);  could give rise to issues... */
   
   oAtom->prevPos = oVector;

   return;
}

void Atom_setCurPos(Atom oAtom, Vector oVector)
{
   assert(oAtom != NULL);
   assert(oVector != NULL);

   oAtom->position = oVector;

   return;
}

void Atom_free(Atom oAtom)
{
   assert(oAtom != NULL);

   if (oAtom->position != NULL)
      Vector_free(oAtom->position); 

   if (oAtom->velocity != NULL)
      Vector_free(oAtom->velocity);

   if (oAtom->prevPos != NULL)
      Vector_free(oAtom->prevPos);

   if (oAtom->scaledVels != NULL)
      Vector_free(oAtom->scaledVels);

   if (oAtom->forces != NULL)
      Vector_free(oAtom->forces);

   free(oAtom);

   return;
}

/* This whole thing makes me nervous... I'll come back and work on it later
char* Atom_stringRep(Atom oAtom)
{
   assert(oAtom != NULL);
   
   char buffer[33];
   char* str;
   
   char* id = (char*)sprintf(buffer, "%d", oAtom->iID);
   char* type = (char*)sprintf(buffer, "%d", oAtom->iType);
   char* pos1 = (char*)sprintf(buffer, "%f", oAtom->pdPosition[0]);
   char* pos2 = (char*)sprintf(buffer, "%f", oAtom->pdPosition[1]);   
   char* pos3 = (char*)sprintf(buffer, "%f", oAtom->pdPosition[2]); 
   char* vel1 = (char*)sprintf(buffer, "%f", oAtom->pdVelocity[0]); 
   char* vel2 = (char*)sprintf(buffer, "%f", oAtom->pdVelocity[1]);   
   char* vel3 = (char*)sprintf(buffer, "%f", oAtom->pdVelocity[2]); 
      
   return str;
}
*/
void Atom_print(Atom oAtom, FILE* out)
{
   assert(oAtom != NULL);
   assert(out != NULL);
   
   fprintf(out, "%i: type %i\n", oAtom->iID, oAtom->iType);
   fprintf(out, "\tposition: ");
   Vector_print(oAtom->position, out);
   fprintf(out, "\tvelocity: ");
   Vector_print(oAtom->velocity, out);
 
   return;   
}

Vector Atom_getCurPos(Atom oAtom)
{
   assert (oAtom != NULL);

   return oAtom->position;
}

Vector Atom_getPrevPos(Atom oAtom)
{
   assert (oAtom != NULL);

   return oAtom->prevPos;
}

Vector Atom_getVel(Atom oAtom)
{
   assert (oAtom != NULL);

   return oAtom->velocity;
}


Vector Atom_getForces(Atom oAtom)
{
   assert (oAtom != NULL);

   return oAtom->forces;
}

/*
double Atom_getXPos(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getX(oAtom->position);
}

double Atom_getYPos(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getY(oAtom->position);
}

double Atom_getZPos(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getZ(oAtom->position);
}

double Atom_getXVel(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getX(oAtom->velocity);
}

double Atom_getYVel(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getY(oAtom->velocity);
}

double Atom_getZVel(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getZ(oAtom->velocity);
}

double Atom_getXForce(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getX(oAtom->forces);
}

double Atom_getYForce(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getY(oAtom->forces);
}

double Atom_getZForce(Atom oAtom)
{
   assert(oAtom != NULL);

   return Vector_getZ(oAtom->forces);
}*/

