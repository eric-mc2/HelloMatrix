#include <string>
#include <exception>
#include <initializer_list>
#include "matrix.h"

Matrix::Matrix(int m, int n) : m{m}, n{n} 
{
	if (m <= 0 || n <= 0) throw std::invalid_argument("m and n must be positive");
	cols = new int*[n];
    for (int j = 0; j < n; j++){
    	cols[j] = new int[m];
    	for (int i = 0; i < m; i ++) {
    		cols[j][i] = 0;
    	}
    }
}

Matrix::~Matrix() {
	 for (int j = 0; j < n; j++){
            delete cols[j];
     }
     delete cols;
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> col_lst){
	n = col_lst.size();
	m = -1;
	if (n == 0) {
		throw std::invalid_argument("must provide at least one column");
	}
	for (auto col : col_lst) {
		if (m == -1) m = col.size();
		if (m == 0) throw std::invalid_argument("must provide at least one row");
		if (m != col.size()) throw std::invalid_argument("columns must all have same size");
	}
	cols = new int*[n];
	int j = 0;
	for (auto col : col_lst) {
		cols[j] = new int[m];
		std::copy(col.begin(), col.end(), cols[j]);
		j++;
	}
}

Matrix::Matrix(const Matrix& other) {
	n = other.n;
	m = other.m;
	cols = new int*[n];
	for (int j = 0; j < n; j++) {
		cols[j] = new int[m];
		for (int i = 0; i < m; i ++) {
			cols[j][i] = other.cols[j][i];
		}
	}
}
    
Matrix& Matrix::operator=(const Matrix& rhs){
	// TODO: This probably still isn't exception-safe
	if (this != &rhs){
		for (int j = 0; j < n; j++){
            delete cols[j];
     	}
     	delete cols;
     	m = rhs.m;
     	n = rhs.n;
     	cols = new int*[n];
        for (int j = 0; j < n; j++){
            cols[j] = new int[m];
            for (int i = 0; i < m; i ++) {
            	cols[j][i] = rhs.cols[j][i];
            }
        }
	}
	return (*this);
}

std::string Matrix::shape() const{
	return std::to_string(m) + "x" + std::to_string(n);
}

int Matrix::nrows() const{
	return m;
}

int Matrix::ncols() const{
	return n;
}

int Matrix::get(int i, int j){
	if (i < 0 || j < 0 || i >= m || j >= n) {
		throw std::out_of_range("i and j must be inside " + shape());
	}
	return cols[j][i];
}

void Matrix::set(int i, int j, int val){
	if (i < 0 || j < 0 || i >= m || j >= n) {
		throw std::out_of_range("i and j must be inside " + shape());
	}
	cols[j][i] = val;
}

Matrix& Matrix::operator+=(const Matrix& rhs){
	if (rhs.nrows() != m || rhs.ncols() != n) {
		throw std::length_error("must have same shape");
	}
	for (int j = 0; j < n; j ++) {
		for (int i = 0; i < m; i ++) {
			cols[j][i] += rhs.cols[j][i];
		}
	}
	return *this;
}