#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "compress.h"
#include "decompress.h"
#include "mirror.h"

int main(int argc, char **argv) {
  char *buffer = (char*) malloc (sizeof(char)*256);
  strcpy(buffer,argv[1]);
  unsigned long factor;
  char *name1,*name2;

  name1 = (char*) malloc(256*sizeof(char));
  name2 = (char*) malloc(256*sizeof(char));

  if( strcmp ( buffer,"-c") == 0 ) {//cerinta 1

    factor = (unsigned long) atoi(argv[2]);
    strcpy(name1,argv[3]);
    strcpy(name2,argv[4]);

    cerinta1(name1,name2,factor,0); //mirror 0
    //copiez numele fisierelor de intrare/iesire
  }//end if cerinta 1
  else if ( strcmp( buffer,"-d") == 0) {//cerinta 2

    strcpy(name1,argv[2]);
    strcpy(name2,argv[3]);

    cerinta2(name1,name2);
  }//end if cerinta 2
  else{//cerinta 3
    char type = *(char*) argv[2]; //h sau v
    unsigned long factor = (unsigned long) atoi(argv[3]);
    strcpy(name1,argv[4]);
    strcpy(name2,argv[5]);

    cerinta3(name1, name2, type, factor);
  }  //end else cerinta 3
  free(buffer);
  free(name1);
  free(name2);
  return 0;;
}
