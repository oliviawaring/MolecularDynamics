#include "atom.h"
#include "atomType.h"
#include "system.h"
#include "vector.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "pairType.h"
#include "bondType.h"
#include "engine.h"

int main(int argc, char *argv[])
{
  FILE* check;
  FILE* exp;
  System oSystem;
  Vector box;
  double TEMP;
  double DT;
  double RCUT;
  double MAX_TIME;
  double time;
  int count;

  check = fopen("testout.txt", "a+"); 
  exp = fopen("toMatlab.txt", "a+"); 

  TEMP = 273;
  DT = 0.001;
  RCUT = 10;
  box = Vector_new(1.0, 1.0, 1.0);
  time = 0;
  MAX_TIME = 0.01;
  count = 0;

  oSystem = buildSystem(TEMP, DT, box, RCUT);

  initialize(oSystem); 

  fprintf(check, "**************   initial   ***************\n");
  System_print(oSystem, check);

  fprintf(exp, "%i\n", System_getNumAtoms(oSystem));
  
  while (time < MAX_TIME)
  {
     updateForces(oSystem);
     integrate(oSystem);
     time += DT;
 /*  if (count % 10 == 0)  { */
        fprintf(check, "****************  time=%f   ***************\n", time);
        System_print(oSystem, check);
        System_export(oSystem, exp);
 /*  } */
     count++;
  }

  System_free(oSystem);
  
  Vector_free(box);

  return 0;
}
