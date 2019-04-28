#ifndef VARIABLE
#define VARIABLE
#include <iostream>

class Matrix {
public:
    Matrix(int m, int n);
    std::string shape();
private:
    int **cols;
    int m, n;
};

#endif