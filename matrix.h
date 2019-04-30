#ifndef VARIABLE
#define VARIABLE
#include <iostream>

class Matrix {
public:
    Matrix(int m, int n);
    Matrix(const Matrix& other);
    // TODO can we disable the default constructor Matrix()?
    ~Matrix();
    
    std::string shape() const;
    int nrows() const;
    int ncols() const;
    int get(int i, int j);
    void set(int i, int j, int val); //XXX can we do this with operator[] without exposing the whole column array?
    
    Matrix& operator=(const Matrix& rhs);
    Matrix& operator+=(const Matrix& rhs);
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