#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct QuadtreeNode { //arr node
  unsigned char blue, green, red;
  uint32_t area;
  int32_t top_left, top_right;
  int32_t bottom_left, bottom_right;
}__attribute__((packed)) QuadtreeNode;


typedef struct Pixel {
  unsigned char  blue;
  unsigned char  green;
  unsigned char  red;
} Pixel;

typedef struct QNode{ // tree node
  Pixel colour;
  uint32_t area;
  struct QNode *parent;
  struct QNode *topLeft;
  struct QNode *topRight;
  struct QNode *bottomLeft;
  struct QNode *bottomRight;

} __attribute__((packed)) QNode;

typedef struct Point{
  int x;
  int y;
} __attribute__((packed)) Point;
typedef struct QueueNode { //queue node
    QNode *data; //quad tree node
    struct QueueNode *next;
    struct QueueNode *prev;
} QueueNode_t;

typedef struct queue {
    QueueNode_t *head;
    QueueNode_t *tail;
    size_t len;
} queue_t;

