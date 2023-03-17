#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int isQuadLeaf (QuadtreeNode node) {
  if(node.top_left == -1) return 1;
  //daca e unu toate sunt
  return 0;
}

void createQTree(QNode *root, QuadtreeNode *arr, unsigned long index){
   if(isQuadLeaf(arr[index]) == 0){//not leaf
      insert4QNode(root);
      root->topLeft->area = arr[arr[index].top_left].area;
      root->topLeft->colour.blue = arr[arr[index].top_left].blue;
      root->topLeft->colour.green = arr[ arr[index].top_left].green;
      root->topLeft->colour.red = arr[ arr[index].top_left].red;

      root->topRight->area = arr[arr[index].top_right].area;
      root->topRight->colour.blue = arr[ arr[index].top_right].blue;
      root->topRight->colour.green = arr[ arr[index].top_right].green;
      root->topRight->colour.red = arr[ arr[index].top_right].red;

      root->bottomRight->area = arr[arr[index].bottom_right].area;
      root->bottomRight->colour.blue = arr[ arr[index].bottom_right].blue;
      root->bottomRight->colour.green = arr[ arr[index].bottom_right].green;
      root->bottomRight->colour.red = arr[ arr[index].bottom_right].red;

      root->bottomLeft->area = arr[arr[index].bottom_left].area;
      root->bottomLeft->colour.blue = arr[ arr[index].bottom_left].blue;
      root->bottomLeft->colour.green = arr[ arr[index].bottom_left].green;
      root->bottomLeft->colour.red = arr[ arr[index].bottom_left].red;

      createQTree(root->topLeft, arr, arr[index].top_left);
      createQTree(root->topRight, arr, arr[index].top_right);
      createQTree(root->bottomRight, arr, arr[index].bottom_right);
      createQTree(root->bottomLeft, arr, arr[index].bottom_left);

   }
   else return;
}

void CreateGrid( Pixel **grid, QNode *root, unsigned long size, Point A){
   if( isLeaf(root) ){

      unsigned long i = A.y, j = A.x;
      unsigned long imax= i + size -1;
      unsigned long jmax = j + size -1;
      for(i = A.y ; i <= imax; i++)
        for(j = A.x ; j <= jmax; j++)
         grid[i][j] = root->colour;
   }
   else{
      Point a1,a2,a3,a4;
      a1 = A;
      a2.x = a1.x + size/2;
      a2.y = a1.y;
      a3.x = a1.x + size/2;
      a3.y = a1.y + size/2;
      a4.x = a1.x;
      a4.y = a1.y + size/2;

     CreateGrid(grid,root->topLeft, size/2, a1);
     CreateGrid(grid,root->topRight, size/2, a2);
     CreateGrid(grid,root->bottomRight, size/2, a3);
     CreateGrid(grid,root->bottomLeft, size/2, a4);

   }


}

void cerinta2(char* name1, char *name2){
//  printf("am intrat in functie\n");
  FILE *file1,*file2;
  file1 = fopen(name1,"rb"); //compress
  file2 = fopen(name2,"wb"); //ppm

  fwrite("P6\n",sizeof(char),3,file2);

  unsigned long width; // area prima frunza *
  int i = 0, j = 0;
  uint32_t numberLeaves, numberNodes;

  fread(&numberLeaves, sizeof(uint32_t), 1, file1);

  fread(&numberNodes, sizeof(uint32_t), 1, file1);

  QuadtreeNode * arr = (QuadtreeNode*) malloc( numberNodes * sizeof(QuadtreeNode));

  for(i = 0;i < numberNodes; i++){

    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;

    fread(&red, sizeof(unsigned char), 1, file1);
    fread(&green, sizeof(unsigned char), 1, file1);
    fread(&blue, sizeof(unsigned char), 1, file1);

    arr[i].blue = blue;
    arr[i].green = green;
    arr[i].red = red;

    fread(&area, sizeof(uint32_t), 1, file1);
    arr[i].area = area;

    fread(&top_left, sizeof(int32_t), 1, file1);
    fread(&top_right, sizeof(int32_t), 1, file1);
    fread(&bottom_right, sizeof(int32_t), 1, file1);
    fread(&bottom_left, sizeof(int32_t), 1, file1);

    arr[i].top_left = top_left;
    arr[i].top_right = top_right;
    arr[i].bottom_left = bottom_right;
    arr[i].bottom_right = bottom_left;

  }// citire din fisier creare vector
  width = (unsigned long ) sqrt(arr[0].area);

  fprintf(file2,"%lu ",width);
  fprintf(file2,"%lu\n",width);

  fwrite("255\n", sizeof(char), 4 ,file2);

  Point A;
  A.x = A.y = 0;

  QNode *root = initQNode();

  root->area = arr[0].area;

  root->colour.blue = arr[0].blue;
  root->colour.green = arr[0].green;
  root->colour.red = arr[0].red;

  createQTree(root,arr,0);

  Pixel **grid = (Pixel **) malloc(width*sizeof(Pixel*));

  for (i = 0; i < width; i++)
    grid[i] = (Pixel *) malloc(width*sizeof(Pixel));


   CreateGrid( grid, root, width, A);

  for ( i = 0; i < width; i++)
    for( j = 0; j < width; j++){

     fwrite( & grid[i][j].blue, sizeof(unsigned char), 1,file2);
     fwrite( & grid[i][j].green, sizeof(unsigned char), 1,file2);
     fwrite( & grid[i][j].red, sizeof(unsigned char), 1,file2);

    }


  destroyGrid(grid, width);
  destroyQTree(root);
  fclose(file1);
  fclose(file2);
  free(arr);
}//end cerinta 2

