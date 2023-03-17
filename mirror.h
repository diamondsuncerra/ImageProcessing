#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void cerinta3(char* name1, char *name2, char type, unsigned long factor){
  int mirrorType;
  if(type == 'h')
     mirrorType = 1;
  else mirrorType = 2; //codificarex
  char *name = malloc(sizeof(char)*12);
  strcpy(name,"compresFile");
  cerinta1(name1, name, factor, mirrorType);
  cerinta2(name, name2);
  free(name);
}
