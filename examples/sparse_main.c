#include <stdio.h>
#include "sparse.h"

int main(){
    SparseMatrix *M;
    int R, C;
    int value, row, col;
    int opt;
    int result;

    printf("Enter the number of rows: ");
    scanf("%d", &R);
    printf("Enter the number of columns: ");
    scanf("%d", &C);

    M = createMatrix(R,C);
    if (M==NULL){
        printf("Failed to allocate memory for the matrix.\n");
        return 1;
    }
    printf("\nMatrix %d x %d successfully created.\n", R, C);

    do {
        printf ("1- Insert\n2- Remove\n3- Search by Index\n4- List Elements\n5- Exit\n\nOption[ ]\b\b");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                printf("Row (0 to %d): ", R-1);
                scanf("%d", &row);
                printf("Column (0 to %d): ", C-1);
                scanf("%d", &col);
                printf("Insert value: ");
                scanf("%d", &value);
                insertElement(M, value, row, col);
                printf("Done!\n");
                break;

            case 2:
                printf("Enter the row of the element to remove: ");
                scanf("%d", &row);
                printf("Enter the column of the element to remove: ");
                scanf("%d", &col);
                removeElement(M, row, col);
                printf("Done!\n");
                break;

            case 3:
                printf("Enter the row to query: ");
                scanf("%d", &row);
                printf("Enter the column to query: ");
                scanf("%d", &col);

                result = search(M, row, col);
                if (result == 0)
                    printf("Position [%d,%d] contains value 0\n", row, col);
            else
                printf("Position [%d,%d] contains value: %d\n", row, col, result);
            break;

            case 4:
                toList(M);
                break;

        }
    }while (opt !=5);
    destroyMatrix(M);
    printf("\n\nF I M\n\n");
    return 0;
}
