#ifndef VARIABLE
#define VARIABLE
#include <iostream>

class Matrix {
public:
    Matrix(int m, int n);
    // TODO can we disable the default constructor Matrix()?
    ~Matrix();
    
    std::string shape(); // todo make 'this' const
    
    Matrix operator+=(Matrix);
    Matrix operator-=(Matrix);
    Matrix operator*=(int);
    Matrix operator/=(int);
    const Matrix operator+(const Matrix &other);
    const Matrix operator-(const Matrix &other);
    const Matrix operator*(const Matrix &other);
    // TODO: static Matrix transp(Matrix);
    // TODO: static Matrix inv(Matrix);
    bool operator==(const Matrix &other);
    bool operator!=(const Matrix &other);
    
private:
    int **cols;
    int m, n;
};

#endif