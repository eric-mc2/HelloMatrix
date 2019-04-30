#ifndef VARIABLE
#define VARIABLE
#include <iostream>

class Matrix {
public:
    Matrix(int m, int n);
    Matrix(std::initializer_list<std::initializer_list<int>> col_lst);
    Matrix(const Matrix& other);
    ~Matrix();
    
    std::string shape() const;
    int nrows() const;
    int ncols() const;
    int get(int i, int j);
    void set(int i, int j, int val); //XXX can we do this with operator[] without exposing the whole column array?
    
    Matrix& operator=(const Matrix& rhs);
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix operator*=(int);
    const Matrix operator+(const Matrix &other);
    const Matrix operator-(const Matrix &other);
    const Matrix operator*(const Matrix &other);
    // TODO: static Matrix transp(Matrix);
    // TODO: static Matrix inv(Matrix);
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    
private:
    int **cols;
    int m, n;
};

#endif