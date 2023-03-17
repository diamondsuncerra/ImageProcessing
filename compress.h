#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include "queueFunctions.h"

void destroyGrid( Pixel **grid, unsigned long size){
  unsigned long i = 0;
  for(i = 0; i < size; i++)
     free(grid[i]);
  free(grid);

}
void destroyQTree( QNode *root){

    if (root == NULL) {
        return;
    }

    destroyQTree(root->topLeft);
    destroyQTree(root->topRight);
    destroyQTree(root->bottomLeft);
    destroyQTree(root->bottomRight);

    free(root);

    root = NULL;

}

QNode* initQNode(){

   QNode *nod = (QNode *) malloc(sizeof(QNode));
   nod -> parent = NULL;
   nod -> topLeft = NULL;
   nod -> topRight = NULL;
   nod -> bottomLeft = NULL;
   nod -> bottomRight = NULL;
   nod -> area = 0;
   nod -> colour.blue = 0;
   nod -> colour.green = 0;
   nod -> colour.red = 0;
   return nod;

} // aditional file with only QNode function
int isLeaf(QNode * nod){
  if( nod == NULL ) return 0;

  if( nod -> topLeft == NULL && nod->topRight == NULL && nod->bottomLeft == NULL && nod->bottomRight == NULL)
    return 1;

  return 0; //is not leaf

}

double computeMean(Pixel **grid,unsigned long size, Point A, Pixel mediumPixel){
  double mean = 0;
  unsigned long i = A.y;
  unsigned long j = A.x;
  unsigned long imax = i - 1 + size;
  unsigned long jmax = j - 1 + size;
  if (size == 1) return 0;
  unsigned long blue = (unsigned long) mediumPixel.blue;
  unsigned long green = (unsigned long) mediumPixel.green;
  unsigned long red = (unsigned long) mediumPixel.red;
  for(i = A.y; i <= imax; i++)
    for(j = A.x;j <= jmax; j++){
      mean = mean + (blue - (unsigned long) grid[i][j].blue)*(blue - (unsigned long)grid[i][j].blue);
      mean = mean + (green - (unsigned long) grid[i][j].green)*(green - (unsigned long ) grid[i][j].green);
      mean = mean + (red - (unsigned long)grid[i][j].red)*(red - (unsigned long) grid[i][j].red);
  }//functie average
  if(size == 0) return 0;
  mean = mean / (3*size*size);

  return mean;
}

Pixel computeMediumColour(Pixel **grid, unsigned long size, Point A){ //size ez to find

  Pixel mediumPixel;
  unsigned long i = A.y;
  unsigned long j = A.x;
  unsigned long imax = i + size -1;
  unsigned long jmax = j + size -1;
  if(size == 1)
    return grid[i][j];
  unsigned  long numberPixels = size * size;
  unsigned long long  blue, green, red;
  blue = 0;
  green = 0;
  red = 0;

  for( i = A.y ; i <= imax ; i++)
    for(j = A.x ; j <= jmax; j++){
      blue += grid[i][j].blue;
      green += grid[i][j].green;
      red += grid[i][j].red;
    }

  red =  (double) red / (double) numberPixels;
  blue = (double)  blue / (double) numberPixels ;
  green =  (double) green / (double) numberPixels;

  mediumPixel.blue = (unsigned char) blue;
  mediumPixel.green = (unsigned char) green;
  mediumPixel.red = (unsigned char) red;


  return mediumPixel;
}
unsigned long countLeaves (QNode *root){
  if( root == NULL) return 0;
  if(isLeaf(root)) return 1;
  return  countLeaves(root->topLeft) + countLeaves(root->topRight) + countLeaves(root->bottomRight) + countLeaves(root->bottomLeft) ;
}
unsigned long countNodes (QNode *root){
  if(root == NULL) return 0;
  return 1 + countNodes(root->topLeft) + countNodes(root->topRight) +
  countNodes(root->bottomRight) + countNodes(root->bottomLeft) ;
}
void insert4QNode (QNode *root){
//create and initialise the 4 sons of node root
  QNode * nod1 = initQNode();
  QNode * nod2 = initQNode();
  QNode * nod3 = initQNode();
  QNode * nod4 = initQNode();

  nod1->parent = root;
  nod2->parent = root;
  nod3->parent = root;
  nod4->parent = root;

  root->topLeft = nod1;
  root->topRight = nod2;
  root->bottomLeft = nod3;
  root->bottomRight = nod4;
}
void QTree(QNode * root,Pixel **grid, unsigned long size, Point A, unsigned long prag, int mirrorType){ // size e lungimea patratului actual
  unsigned long mean = 0;

  Pixel mediumPixel = computeMediumColour(grid, size, A);

  mean = (unsigned long )computeMean(grid, size,A, mediumPixel);

  root->colour = mediumPixel;

  root->area = size*size;

  if(mean > prag){

     insert4QNode(root);

     Point a1,a2,a3,a4;
     a1 = A;
     a2.x = a1.x + size/2;
     a2.y = a1.y;
     a3.x = a1.x + size/2;
     a3.y = a1.y + size/2;
     a4.x = a1.x;
     a4.y = a1.y + size/2;
     if(mirrorType == 0){

       QTree(root -> topLeft, grid, size/2, a1, prag, mirrorType);
       QTree(root -> topRight, grid, size/2, a2, prag, mirrorType);
       QTree(root -> bottomRight, grid, size/2, a3, prag, mirrorType);
       QTree(root -> bottomLeft, grid, size/2, a4, prag, mirrorType);
 //no mirror
     }
     else if(mirrorType == 1){

       QTree(root -> topRight, grid, size/2, a1, prag, mirrorType);
       QTree(root -> topLeft, grid, size/2, a2, prag, mirrorType);
       QTree(root -> bottomLeft, grid, size/2, a3, prag, mirrorType);
       QTree(root -> bottomRight, grid, size/2, a4, prag, mirrorType);

     } // h mirror
     else if(mirrorType == 2){
//v mirror
       QTree(root -> bottomLeft, grid, size/2, a1, prag, mirrorType);
       QTree(root -> bottomRight, grid, size/2, a2, prag, mirrorType);
       QTree(root -> topRight, grid, size/2, a3, prag, mirrorType);
       QTree(root -> topLeft, grid, size/2, a4, prag, mirrorType);
 //no mirror
     }
  }//endif


}


void cerinta1 (char * name1, char * name2, unsigned long prag, int mirrorType){
  char *type = (char*) malloc (3*sizeof(char)); //p6
  unsigned long i = 0,j = 0;
  unsigned long maxColour = 0;
  unsigned long width, height;
  FILE *file1,*file2;
  file1 = fopen(name1,"rb");
  file2 = fopen(name2,"wb");

  fread(type, sizeof(char), 3, file1);

  fscanf(file1,"%lu%lu",&width, &height);
  fscanf(file1,"%lu",&maxColour);//255

  char *buffer = (char *) malloc(sizeof(char));

  fread(buffer,sizeof(char),1,file1);

  free(buffer);

  Pixel **grid = (Pixel **) malloc(height*sizeof(Pixel*));

  for (i = 0; i < height; i++)
    grid[i] = (Pixel *) malloc(width*sizeof(Pixel));

  i = 0;
  unsigned char read1, read2, read3;
  for( i = 0; i < width; i++)
   for(j = 0; j < height; j++){

      fread( &read1,sizeof(unsigned char),1,file1);
      fread( &read2,sizeof(unsigned char),1,file1);
      fread( &read3,sizeof(unsigned char),1,file1);

      grid[i][j].blue = read3;
      grid[i][j].green = read2;
      grid[i][j].red = read1;
   }

  //am obtinut matricea de pixeli. acum incerc sa fac in arbore
  Point A;
  A.x = 0;
  A.y = 0;
  QNode *root = initQNode();
  QTree(root, grid, height, A, prag, mirrorType);

  unsigned long numberLeaves, numberNodes;
  numberLeaves = countLeaves(root);
  numberNodes = countNodes(root);

  fwrite(&numberLeaves, sizeof(uint32_t), 1, file2);
  fwrite(&numberNodes, sizeof(uint32_t), 1, file2);

  QNode *cpy_root = root;
  QuadtreeNode * arr = (QuadtreeNode *) malloc(numberNodes * sizeof(QuadtreeNode));

  queue_t *queue = initQueue();
  int index = -1;
  int queue_index = 0;
  enqueue(queue, root);

  while(queue->len){
    root = dequeue(queue);
    QuadtreeNode nod;
    if(root->topLeft){ //daca exista una exista toate
      queue_index ++;
      enqueue(queue, root->topLeft);
      nod.top_left = queue_index;

      queue_index ++;
      enqueue(queue, root->topRight);
      nod.top_right = queue_index;


      queue_index ++;
      enqueue(queue, root->bottomRight);
      nod.bottom_right = queue_index;

      queue_index ++;
      nod.bottom_left = queue_index;
      enqueue(queue, root->bottomLeft);


    }
    else{

      nod.top_left = -1;
      nod.top_right = -1;
      nod.bottom_left = -1;
      nod.bottom_right = -1;

    }
    nod.area = root->area;
    nod.blue = root->colour.blue;
    nod.green = root->colour.green;
    nod.red = root->colour.red;

    index ++;

    arr[index] = nod;
  }
  index++;

  for(i = 0; i < index; i++){
    unsigned char write1, write2, write3;
    write3 = arr[i].blue;
    write2 = arr[i].green;
    write1 = arr[i].red;

    fwrite(& write3 , sizeof(unsigned char),1,file2);
    fwrite(& write2 , sizeof(unsigned char),1,file2);
    fwrite(& write1 , sizeof(unsigned char),1,file2);

    fwrite(& (arr[i].area), sizeof(uint32_t),1,file2);

    fwrite(& (arr[i].top_left), sizeof(int32_t),1,file2);
    fwrite(& (arr[i].top_right), sizeof(int32_t),1,file2);
    fwrite(& (arr[i].bottom_left), sizeof(int32_t),1,file2);
    fwrite(& (arr[i].bottom_right), sizeof(int32_t),1,file2);

  }
  free(arr);
  root = cpy_root;
  destroyQueue(queue);
  destroyQTree(root);
  destroyGrid(grid, width);
  free(type);
  fclose(file1);
  fclose(file2);
}//endfunction
