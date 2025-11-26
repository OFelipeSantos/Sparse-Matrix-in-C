# Sparse-Matrix-in-C
This project implements a dynamic and efficient sparse matrix in C using two orthogonal linked lists (one for rows, another for columns). 
This matrix only stores the non-zero elements, reducing memory usage and improving perfomance for large matrice with many empty position.


### Files

- `src/sparse.h` —> definitions of data structures and prototypes  
- `src/sparse.c` —> implementation of create, insert, remove, search, destroy  
- `examples/sparse_main.c` —> interactive CLI example program demonstrating usage

### How to compile

```bash
gcc src/sparse.c examples/sparse_main.c -o sparse_example
./sparse_example
