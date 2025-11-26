#ifndef SPARSE_H
#define SPARSE_H

#include <stdio.h>
#include <stdlib.h>


//Structs

//Basic structure of a node
typedef struct cell {
    int value;
    int row;
    int col;
    struct cell *next_row;
    struct cell *next_col;
}cell;

//Basic structure of the Matrix
typedef struct SparseMatrix {
    int num_rows;
    int num_cols;
    cell **row_headers;
    cell **col_headers;
}SparseMatrix;

//Prototypes

SparseMatrix* createMatrix(int R, int C);
void insertElement(SparseMatrix *matrix, int value, int row, int col);
void removeElement (SparseMatrix *matrix, int row, int col);
int search(SparseMatrix *matrix, int row, int col);
void toList(SparseMatrix *matrix);
void destroyMatrix(SparseMatrix *matrix);
