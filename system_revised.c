
/*****************************************************************/
/* system.c                                                         
/* Author: Olivia M. Waring                                              
/* The "engine" of my C molecular dynamics code (small accessory
/* files omitted); models the effect of a Lennard-Jones potential
/* function on a system of atoms.                  
/* ***************************************************************/

// include header files for any necessary classes or packages
#include "atom.h"
#include "atomType.h"
#include "vector.h"
#include "system.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

// define the fields of the System data type
struct System_str
{
   Atom* atoms;
   AtomType* atomTypes;
   Vector* distances;
   Vector boxDims;
   int numAtoms;
   int numTypes;
   double temperature;
   double timestep;
   double rCutoff;
   double energy;
};

/* generate a random velocity value on a uniform distribution between -0.5 and 0.5 */
static double randomVelocity(void)
{
   double num = (rand()/(double)RAND_MAX) - 0.5;
   return num;
}

/* Determine whether a string encodes a numeral */
static int isNumeric(const char *s)
{
  /* To be implemented later (using a Deterministic Finite-State Automaton) */
   return 1;
}

/* Return a list of atom types */ 
static AtomType* updateAtomTypes(FILE* atoms, System oSystem)
{   
   int iType, count;    
   double fMass, fCharge, fRadius;
   char* line;
   AtomType* atomTypes;

   assert(atoms != NULL);
   assert(oSystem != NULL);   

   oSystem->numTypes = 3;
   /* In a future version, I would obviously make this more versatile... 
      One should be able to read in the number of types from an input file. */

   atomTypes = malloc(oSystem->numTypes*sizeof(*oSystem->atomTypes));
   line = malloc(81*sizeof(char));
   count = 0;       
   while (fgets(line, 80, atoms) != NULL)  /* assumes only 80 chars per line */
   {
       char* tok1;
       char* tok2;
       char* tok3;
       char* tok4;  
  
       tok1 = strtok(line, " \t\n");
       if ((tok1 != NULL) && (tok1[0] != '*')) /* the first character in the line */
       {
          if (!(isNumeric(tok1))) 
          {
             perror("Bad format");
             exit(EXIT_FAILURE);
          }
          else
          {
             tok2 = strtok(NULL, " \t\n");
             tok3 = strtok(NULL, " \t\n");
             tok4 = strtok(NULL, " \t\n");
             iType = atoi(tok1);
             fMass = atof(tok2);
             fCharge = atof(tok3);
             fRadius = atof(tok4);
             atomTypes[count] = AtomType_new(iType, fMass, fCharge, fRadius);
             count++;
          }
       }
   }
   free(line); 

   return atomTypes;    
}

/* Return a System object with the desired properites */
System buildSystem(FILE* atomListFile, FILE* atomTypesFile, double temp, double dt, Vector box, double rCut)
{
   System oSystem;
   int iType, iID, count, N;
   double posX, posY, posZ, velX, velY, velZ;
   Vector position, velocity;
   char* line;

   assert(atomListFile != NULL);
   assert(atomTypesFile != NULL);
   assert(box != NULL);
   
   count = -1;
   oSystem = (System)malloc(sizeof(struct System_str));

   oSystem->atomTypes = updateAtomTypes(atomTypesFile, oSystem); 
   oSystem->numAtoms = 0;
   oSystem->temperature = temp;
   oSystem->timestep = dt;
   oSystem->rCutoff = rCut;
   oSystem->boxDims = box;
   srand((unsigned)time(NULL));
   line = malloc(81*sizeof(char));      
   while (fgets(line, 80, atomListFile) != NULL)  /* assumes only 80 chars per line */
   {
       char* tok1;
       char* tok2;
       char* tok3;
       char* tok4;  
       tok1 = strtok(line, " \t\n");
       if ((tok1 != NULL) && (tok1[0] != '*')) /* the first character in that line */
       {
          if (!(isNumeric(tok1)))
          {
             perror("Bad format");
             exit(EXIT_FAILURE);
          }
          if (count < 0)
          {
             oSystem->numAtoms = atoi(tok1);
             N = oSystem->numAtoms;
             oSystem->atoms = malloc(N*sizeof(*oSystem->atoms));
             count++;
          }
          
          /* Insert atoms into the system */
          else
          {
             tok2 = strtok(NULL, " \t\n");
             tok3 = strtok(NULL, " \t\n");
             tok4 = strtok(NULL, " \t\n");
             iType = atoi(tok1);
             iID = count;
             posX = atof(tok2);
             posY = atof(tok3);
             posZ = atof(tok4);
             velX = randomVelocity();
             velY = randomVelocity();
             velZ = randomVelocity();
             if (oSystem->numAtoms < count)
             {
                Atom *temp = realloc(oSystem->atoms, 
                             oSystem->numAtoms*sizeof(*oSystem->atoms));
                oSystem->numAtoms += 1;
                if (temp == NULL)
                {
                   perror("Reallocation failed");
                   exit(EXIT_FAILURE);
                }
                oSystem->atoms = temp;
             }
             position = Vector_new(posX, posY, posZ);
             velocity = Vector_new(velX, velY, velZ);
             oSystem->atoms[count] = Atom_new(iType, iID, position, velocity);
             count++;
          }
       }
   }
    
    oSystem->distances = malloc(((N-1)*N/2)*sizeof(*oSystem->distances));
    free(line);  
   
    return oSystem;
}


/* Print the salient features of the system for examination */
void System_print(System oSystem, FILE* out)
{
   int N, i;
   Atom currentAtom;

   assert (oSystem != NULL);
   assert (out != NULL);
   
   N = oSystem->numAtoms;
   for (i = 0; i < N; i++)
   {
      currentAtom = oSystem->atoms[i];
      fprintf(out, "Atom number: %i\n", i);
      fprintf(out, "%s", "\tprevious position: ");
      Vector_print(Atom_getPrevPos(currentAtom), out);
      fprintf(out, "%s", "\tcurrent position: ");
      Vector_print(Atom_getCurPos(currentAtom), out);
      fprintf(out, "%s", "\tvelocity: ");
      Vector_print(Atom_getVel(currentAtom), out);
      fprintf(out, "%s", "\tforces: ");
      Vector_print(Atom_getForces(currentAtom), out);
   }
   return;
}

/* Free the memory allocated to the system */
void System_free(System oSystem)
{
   int i;
   assert(oSystem != NULL);

   if (oSystem->atoms != NULL)
   {
      for (i=0; i<oSystem->numAtoms; i++)
      {
         Atom_free(oSystem->atoms[i]);
      }
      free(oSystem->atoms);
   }
 
   if (oSystem->atomTypes != NULL)
   {
      for (i=0; i<3; i++) /*hard coded! bad! */
      {
         AtomType_free(oSystem->atomTypes[i]);
      }
      free(oSystem->atomTypes);
   }   
   if (oSystem->distances != NULL)
      free(oSystem->distances);
   
   free(oSystem); 
}

/* Prepare the system for molecular dynamics by scaling velocities and 
 * setting temperature */
void initialize(System oSystem)
{  
   int N, i;
   double TEMP;
   double TIMESTEP;
   Vector totalV, totalV2, avgV, avgV2, scaling, scaledVels, 
          prevPos, curPos, vel;
   Atom currentAtom;

   assert(oSystem != NULL);

   N = oSystem->numAtoms;
   TEMP = oSystem->temperature;
   TIMESTEP = oSystem->timestep;
   totalV = Vector_new(0,0,0);
   totalV2 = Vector_new(0,0,0);
   avgV = Vector_new(0,0,0);
   avgV2 = Vector_new(0,0,0);
   scaling = Vector_new(0,0,0);

   for (i = 0; i < N; i++)
   {
      currentAtom = oSystem->atoms[i];
      if (currentAtom == NULL)
      {
         perror("Tried to access nonexistant atom");
         exit(EXIT_FAILURE);
      }
      vel = Atom_getVel(currentAtom);
      Vector_setX(totalV, Vector_getX(vel) + Vector_getX(totalV));
      Vector_setY(totalV, Vector_getY(vel) + Vector_getY(totalV));
      Vector_setZ(totalV, Vector_getZ(vel) + Vector_getZ(totalV));
      Vector_setX(totalV2, pow(Vector_getX(vel),2) + Vector_getX(totalV2));
      Vector_setY(totalV2, pow(Vector_getY(vel),2) + Vector_getY(totalV2));
      Vector_setZ(totalV2, pow(Vector_getZ(vel),2) + Vector_getZ(totalV2));
   }
   Vector_setX(avgV, Vector_getX(totalV)/N);
   Vector_setY(avgV, Vector_getY(totalV)/N);
   Vector_setZ(avgV, Vector_getZ(totalV)/N);
   Vector_setX(avgV2, Vector_getX(totalV2)/N);
   Vector_setY(avgV2, Vector_getY(totalV2)/N);
   Vector_setZ(avgV2, Vector_getZ(totalV2)/N);
   Vector_setX(scaling, sqrt(3*TEMP/Vector_getX(avgV2)));
   Vector_setY(scaling, sqrt(3*TEMP/Vector_getY(avgV2)));
   Vector_setZ(scaling, sqrt(3*TEMP/Vector_getZ(avgV2)));
   for (i = 0; i < N; i++)
   {
      currentAtom = oSystem->atoms[i];
      Atom_setForces(currentAtom, Vector_new(0, 0, 0));
      scaledVels = Vector_new(0,0,0);
      prevPos = Vector_new(0,0,0);     
      vel = Atom_getVel(currentAtom);
      curPos = Atom_getCurPos(currentAtom);
      Vector_setX(scaledVels, Vector_getX(scaling) * 
                 (Vector_getX(vel)- Vector_getX(avgV)));
      Vector_setY(scaledVels, Vector_getY(scaling) * 
                 (Vector_getY(vel)- Vector_getY(avgV)));
      Vector_setZ(scaledVels, Vector_getZ(scaling) * 
                 (Vector_getZ(vel)- Vector_getZ(avgV)));
      Vector_setX(prevPos, Vector_getX(curPos)- 
                 (Vector_getX(vel)* TIMESTEP));
      Vector_setY(prevPos, Vector_getY(curPos)- 
                 (Vector_getY(vel)* TIMESTEP));
      Vector_setZ(prevPos, Vector_getZ(curPos) - 
                 (Vector_getZ(vel)* TIMESTEP));
      Atom_setVel(currentAtom, scaledVels);
      Atom_setPrevPos(currentAtom, prevPos);   
   }
   Vector_free(totalV);
   Vector_free(totalV2);
   Vector_free(avgV);
   Vector_free(avgV2);
   Vector_free(scaling);
   return;
}

/* Account for periodic boundary conditions */
static Vector adjustPBC(System oSystem, Vector oVector)
{
   double distX, distY, distZ, boxX, boxY, boxZ;

   assert(oSystem != NULL);
   assert(oVector != NULL);
   
   distX = Vector_getX(oVector);
   distY = Vector_getY(oVector);
   distZ = Vector_getZ(oVector);
   boxX = Vector_getX(oSystem->boxDims);
   boxY = Vector_getY(oSystem->boxDims);
   boxZ = Vector_getZ(oSystem->boxDims);

   if (distX > boxX)
      distX = distX - boxX;
   else if (distX < 0)
      distX = distX + boxX; 

   if (distY > boxY)
      distY = distY - boxY;
   else if (distY < 0)
      distY = distY + boxY;

   if (distZ > boxZ)
      distZ = distZ - boxZ;
   else if (distZ < 0)
      distZ = distZ + boxZ;

   Vector_setX(oVector, distX);
   Vector_setY(oVector, distY);
   Vector_setZ(oVector, distZ);

   return oVector;
  
}

/* Return a vector corresponding to the distance between atom1 and atom2 */
static Vector getDist(Atom atom1, Atom atom2) 
{
   double distX, distY, distZ; 
   Vector oVector, curPos1, curPos2;
 
   assert(atom1 != NULL);
   assert(atom2 != NULL);

   curPos1 = Atom_getCurPos(atom1);
   curPos2 = Atom_getCurPos(atom2);
   distX = Vector_getX(curPos1) - Vector_getX(curPos2);
   distY = Vector_getY(curPos1) - Vector_getY(curPos2);
   distZ = Vector_getZ(curPos1) - Vector_getZ(curPos2);    
 
   oVector = Vector_new(distX, distY, distZ);
   return oVector;
}

/* Update the force vector acting upon each atom */
void updateForces(System oSystem)
{
   int N, i, j;
   Atom atom1, atom2;
   Vector dist, force, force1, force2;
   double distX, distY, distZ, forceX, forceY, forceZ, forceFactor, r2, rc2;
   double A, B;
   
   assert(oSystem != NULL); 
   
   /* placeholders! (Will eventually read in values from an input file) */
   A = 1.31; 
   B = 3.19; 
   N = oSystem->numAtoms;
   rc2 = pow(oSystem->rCutoff,2);

   for (i = 0; i < N-1; i++)
   {
      for (j = i+1; j < N; j++)
      {
         printf("%i, %i", i, j);
         atom1 = oSystem->atoms[i];
         atom2 = oSystem->atoms[j];
         dist = getDist(atom1, atom2);
         dist = adjustPBC(oSystem, dist);
         printf("\ndist: ");
         Vector_print(dist, NULL);
         distX = Vector_getX(dist);
         distY = Vector_getY(dist);
         distZ = Vector_getZ(dist);
         r2 = pow(distX, 2) + pow(distY, 2) + pow(distZ, 2);
         
         /* Account for LJ Potential */
         if (r2 < rc2)
         {   
           forceFactor = 48 * ((A/pow(r2,6)) - (B/pow(r2,3))) / r2; 
           printf("\nfactor: %f", forceFactor);
           force1 = Atom_getForces(atom1);
           force2 = Atom_getForces(atom2);
           forceX = Vector_getX(force1) + forceFactor * distX;
           forceY = Vector_getY(force1) + forceFactor * distY;
           forceZ = Vector_getZ(force1) + forceFactor * distZ;
           force = Vector_new(forceX, forceY, forceZ);
           Atom_setForces(atom1, force);
           forceX = Vector_getX(force2) - forceFactor * distX;
           forceY = Vector_getY(force2) - forceFactor * distY;
           forceZ = Vector_getZ(force2) - forceFactor * distZ;
           force = Vector_new(forceX, forceY, forceZ);
           Atom_setForces(atom2, force);
        }
      }
   }
   return; 
}

/* Update atomic positions */
void integrate(System oSystem)
{
   int N, i;
   Vector prevPos, curPos, totalV, totalV2, force;
   double prevPosX, prevPosY, prevPosZ, curPosX, curPosY, curPosZ, 
          nextPosX, nextPosY, nextPosZ, forceX, forceY, forceZ, dt,
          velX, velY, velZ;
   Atom currentAtom;

   assert(oSystem != NULL); 
   
   N = oSystem->numAtoms;
   dt = oSystem->timestep;
   totalV = Vector_new(0,0,0);
   totalV2 = Vector_new(0,0,0);

   for (i = 0; i < N; i++)
   {
      currentAtom = oSystem->atoms[i];
      curPos = Atom_getCurPos(currentAtom);
      force = Atom_getForces(currentAtom);
      prevPos = Atom_getPrevPos(currentAtom);
      curPosX = Vector_getX(curPos);
      curPosY = Vector_getY(curPos);
      curPosZ = Vector_getZ(curPos);
      forceX = Vector_getX(force);
      forceY = Vector_getY(force);
      forceZ = Vector_getZ(force);
      prevPosX = Vector_getX(prevPos);
      prevPosY = Vector_getY(prevPos);
      prevPosZ = Vector_getZ(prevPos);
      nextPosX = 2*curPosX - prevPosX + dt*2*forceX;
      nextPosY = 2*curPosY - prevPosY + dt*2*forceY;
      nextPosZ = 2*curPosZ - prevPosZ + dt*2*forceZ;   
      velX = (nextPosX - prevPosX)/(2*dt);
      velY = (nextPosY - prevPosY)/(2*dt);
      velZ = (nextPosZ - prevPosZ)/(2*dt);
      curPos = Vector_new(nextPosX, nextPosY, nextPosZ);  
      prevPos = Atom_getCurPos(currentAtom);
      Atom_setPrevPos(currentAtom, prevPos);
      Atom_setCurPos(currentAtom, curPos);
      Vector_setX(totalV, Vector_getX(totalV) + velX);
      Vector_setY(totalV, Vector_getY(totalV) + velY);
      Vector_setZ(totalV, Vector_getZ(totalV) + velZ);
      Vector_setX(totalV2, Vector_getX(totalV2) + pow(velX,2));
      Vector_setY(totalV2, Vector_getY(totalV2) + pow(velY,2));
      Vector_setZ(totalV2, Vector_getZ(totalV2) + pow(velZ,2));
   }
     
   return;

}
