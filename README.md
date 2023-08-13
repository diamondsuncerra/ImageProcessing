# Image Processing

This project demonstrates three ways of image processing using C. Each mode focuses on different aspects
of image manipulation.

## Requirements

1. **Image Compression**: Compresses an image into a file with image-related information.
2. **Decompression**: Reconstructs the image from the compressed file created in Requirement 1.
3. **Mirroring**: Reflects an image horizontally or vertically using algorithms from Requirements 1 and 2.

For studying the implementation of this project, consider the following key points:

### Used Structures

Several structures are employed in this implementation:

1. **QuadtreeNode**: Represents a node for the vector created in Requirement 1.
2. **Pixel**: Stores the colors of an image pixel.
3. **QNode**: Node structure for the quadtree.
4. **Point**: Represents a point in the image matrix.
5. **QueueNode**: Node structure for the queue implementation.
6. **Queue**: Implements the queue data structure.

### Main

The main file `quadtree.c` reads the command-line argument into the `buffer`. The commands are as follows:
- `-c`: Compress an image.
- `-d`: Decompress a file.
- `-m`: Mirror an image.

Depending on the chosen command, the following arguments are read from the command line:

#### Compression:
```shell
./quadtree -c factor inputFile outputFile
```
### Decompression:

```shell

./quadtree -d inputFile outputFile
```
### Mirroring:

```shell

./quadtree -m type factor inputFile outputFile
```
## Implementation of Requirement 1 (compress.h)

The function for Requirement 1 is located in the header file compress.h:


void cerinta1(char *name1, char *name2, unsigned long prag, int mirrorType);

This function compresses an image by creating a quadtree and vector. The algorithm segments the image
recursively, calculates the mean and medium values, and generates the quadtree nodes. It also creates 
the vector, which contains pixel information.
## Implementation of Requirement 2 (decompress.h)

Requirement 2 is implemented in decompress.h. The function cerinta2 decompresses a compressed binary
file and recreates the image. It reconstructs the quadtree from the vector and creates the image pixel matrix.
## Implementation of Requirement 3 (mirror.h)

mirror.h is responsible for Requirement 3. The function cerinta3 takes care of mirroring the image
by leveraging the quadtree implementation from Requirement 1 and decompression from Requirement 2.
## Header Files

    queueFunctions.h
    mirror.h
    compress.h
    decompress.h
    structs.h

## Makefile

The provided Makefile compiles the project. Use the command make to build the executable quadtree.
Usage
    Compile the project using make.
    Run the compiled executable with appropriate command-line arguments.
