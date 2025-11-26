#include <stdio.h>
#include <stdlib.h>
#include "sparse.h"

SparseMatrix* createMatrix(int R, int C){
    SparseMatrix *matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if (matrix == NULL) return NULL;

    matrix->num_rows = R;
    matrix->num_cols = C;
    matrix->row_headers = (cell**)malloc(R * sizeof(cell*));
    if (matrix->row_headers == NULL) {
        free(matrix);
        return NULL;
    }
    matrix->col_headers = (cell**)malloc(C * sizeof(cell*));
    if (matrix->col_headers == NULL){
        free(matrix->row_headers);
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < R; i++)
        matrix->row_headers[i] = NULL;
    for (int i = 0; i < C; i++)
        matrix->col_headers[i] = NULL;

    return matrix;
}

void insertElement(SparseMatrix *matrix, int value, int row, int col) {
    cell *new_cell, *prev_row, *curr_row, *prev_col, *curr_col;

    if (row < 0 || row >= matrix->num_rows || col < 0 || col >= matrix->num_cols) {
        printf("Error: Indexes [%d, %d] out of bounds.\n", row, col);
        return;
    }

    prev_row = NULL;
    curr_row = matrix->row_headers[row];
    prev_col = NULL;
    curr_col = matrix->col_headers[col];

    while (curr_row != NULL && curr_row->col < col) {
        prev_row = curr_row;
        curr_row = curr_row->next_row;
    }
    while (curr_col != NULL && curr_col->row < row) {
        prev_col = curr_col;
        curr_col = curr_col->next_col;
    }

    if (curr_row != NULL && curr_row->col == col) {
        if (value != 0) {
            curr_row->value = value;
            printf("Position [%d, %d] updated to %d\n", row, col, value);
        } else {
            removeElement(matrix, row, col);
        }
    }
    else {
        if (value == 0) {
            return;
        }
        new_cell = (cell*)malloc(sizeof(cell));
        if (new_cell == NULL) {
            printf("Error: Unable to allocate memory for new node.\n");
            return;
        }

        new_cell->value = value;
        new_cell->row = row;
        new_cell->col = col;
        new_cell->next_row = NULL;
        new_cell->next_col = NULL;

        if (prev_row == NULL) {
            new_cell->next_row = matrix->row_headers[row];
            matrix->row_headers[row] = new_cell;
        } else {
            new_cell->next_row = prev_row->next_row;
            prev_row->next_row = new_cell;
        }

        if (prev_col == NULL) {
            new_cell->next_col = matrix->col_headers[col];
            matrix->col_headers[col] = new_cell;
        } else {
            new_cell->next_col = prev_col->next_col;
            prev_col->next_col = new_cell;
        }
    }
}

void removeElement(SparseMatrix *matrix, int row, int col) {
    cell *prev_row, *target_cell_row, *prev_col, *target_cell_col;

    if (row < 0 || row >= matrix->num_rows || col < 0 || col >= matrix->num_cols) {
        printf("Error in removal: Indexes out of bounds.\n");
        return;
    }
    prev_row = NULL;
    target_cell_row = matrix->row_headers[row];

    while (target_cell_row != NULL && target_cell_row->col < col) {
        prev_row = target_cell_row;
        target_cell_row = target_cell_row->next_row;
    }

    if (target_cell_row == NULL || target_cell_row->col != col) {
        printf("Removal: Element at position [%d, %d] is already zero.\n", row, col);
        return;
    }

    prev_col = NULL;
    target_cell_col = matrix->col_headers[col];
    while (target_cell_col != NULL && target_cell_col->row < row) {
        prev_col = target_cell_col;
        target_cell_col = target_cell_col->next_col;
    }

    if (target_cell_col == NULL || target_cell_col->row != row) {
        printf("Error: Inconsistency in the matrix structure.\n");
        return;
    }

    cell *target_cell = target_cell_row;
    if (prev_row == NULL) {
        matrix->row_headers[row] = target_cell->next_row;
    } else {
        prev_row->next_row = target_cell->next_row;
    }

    if (prev_col == NULL) {
        matrix->col_headers[col] = target_cell->next_col;
    } else {
        prev_col->next_col = target_cell->next_col;
    }

    free(target_cell);
}

int search(SparseMatrix *matrix, int row, int col) {
    if (row < 0 || row >= matrix->num_rows || col < 0 || col >= matrix->num_cols) {
        printf("Error: Index out of bounds.\n");
        return 0;
    }

    cell *current = matrix->row_headers[row];

    while (current != NULL && current->col <= col) {
        if (current->col == col) {
            return current->value;
        }
        current = current->next_row;
    }
    return 0;
}

void toList(SparseMatrix *matrix) {
    for (int i = 0; i < matrix->num_rows; i++) {
        cell *current = matrix->row_headers[i];

        while (current != NULL) {
            printf("%d at [%d, %d]\n", current->value, current->row, current->col);
            current = current->next_row;
        }
    }
    printf("/\n");
}

void destroyMatrix(SparseMatrix *matrix) {
    for (int i = 0; i < matrix->num_rows; i++) {
        cell *current = matrix->row_headers[i];
        while (current != NULL) {
            cell *aux = current;
            current = current->next_row;
            free(aux);
        }
    }
    free(matrix->row_headers);
    free(matrix->col_headers);
    free(matrix);
}
