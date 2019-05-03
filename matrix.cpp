#include <string>
#include <iostream>
#include <exception>
#include <initializer_list>
#include "matrix.h"

Matrix::Matrix(int m, int n) : m{m}, n{n} 
{
	if (m <= 0 || n <= 0) throw std::invalid_argument("m and n must be positive");
	int j = 0;
	try {
		cols = new int*[n];
    	for (; j < n; j++){
    		cols[j] = new int[m];
    		for (int i = 0; i < m; i ++) {
    			cols[j][i] = 0;
    		}
    	}
	} catch (std::bad_alloc e) {
		std::cerr << "malloc failed on column " << std::to_string(j);
		for (int d = 0; d < j; d++){
			// i.e. if malloc fails at j=2 we must only free columns 0 and 1.
			delete cols[d];
		}
		delete cols;
	}
}

Matrix::~Matrix() {
	if (cols != nullptr) {
	 	for (int j = 0; j < n; j++){
            delete cols[j];
     	}
    	delete cols;
 	}
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> col_lst){
	n = col_lst.size();
	m = -1;
	cols = nullptr;
	if (n == 0) {
		throw std::invalid_argument("must provide at least one column");
	}
	for (auto col : col_lst) {
		if (m == -1) m = col.size();
		if (m == 0) throw std::invalid_argument("must provide at least one row");
		if (static_cast<unsigned int>(m) != col.size()) throw std::invalid_argument("columns must all have same size");
	}
	Matrix tmp(m, n);
	int j = 0;
	for (auto col : col_lst) {
		std::copy(col.begin(), col.end(), tmp.cols[j]);
		j++;
	}
	tmp.swap(*this);
}

Matrix::Matrix(const Matrix& other) {
	cols = nullptr;
	Matrix tmp(other.m, other.n);
	for (int j = 0; j < other.n; j++) {
		for (int i = 0; i < other.m; i ++) {
			tmp.cols[j][i] = other.cols[j][i];
		}
	}
	tmp.swap(*this);
}
    
Matrix& Matrix::operator=(const Matrix& rhs){
	if (this != &rhs){
		Matrix tmp(rhs);
		tmp.swap(*this);
	}
	return (*this);
}

void Matrix::swap(Matrix& other){
	int ti = n;
	n = other.n;
	other.n = ti;
	
	ti = m;
	m = other.m;
	other.m = ti;
	
	int** tp = cols;
	cols = other.cols;
	other.cols = tp;
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

Matrix& Matrix::operator-=(const Matrix& rhs){
	if (rhs.nrows() != m || rhs.ncols() != n) {
		throw std::length_error("must have same shape");
	}
	for (int j = 0; j < n; j ++) {
		for (int i = 0; i < m; i ++) {
			cols[j][i] -= rhs.cols[j][i];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(int c) {
	for (int j = 0; j < n; j ++) {
		for (int i = 0; i < m; i ++) {
			cols[j][i] *= c;
		}
	}
	return *this;
}

const Matrix Matrix::operator+(const Matrix &other) {
	Matrix rtn(*this);
	rtn += other;
	return rtn;
}

const Matrix Matrix::operator-(const Matrix &other) {
	Matrix rtn(*this);
	rtn -= other;
	return rtn;
}

const Matrix Matrix::operator*(const Matrix &other) {
	if (this->n != other.m) throw std::length_error("mismatched shape for matrix multiplication");
	Matrix rtn(this->m, other.n);
	for (int j = 0; j < rtn.n; j ++){
		for (int i = 0; i < rtn.m; i++) {
			for (int k = 0; k < this->n; k ++){
				rtn.cols[j][i] += this->cols[k][i] * other.cols[j][k];
			}
		}
	}
	return rtn;
}

const Matrix Matrix::operator*(int c) {
	Matrix rtn(*this);
	rtn *= c;
	return rtn;
}


bool Matrix::operator==(const Matrix& other) const {
	if (this == &other) return true;
	if (this->n != other.n || this->m != other.m) return false;
	for (int j = 0; j < n; j++){
		for (int i = 0; i < m; i ++) {
			if (this->cols[j][i] != other.cols[j][i]) return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& other) const{
	if (this == &other) return false;
	if (this->n != other.n || this->m != other.m) return true;
	for (int j = 0; j < n; j++){
		for (int i = 0; i < m; i ++) {
			if (this->cols[j][i] != other.cols[j][i]) return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream &os, Matrix &rhs) {
	os << "[";
	for (int j = 0; j < rhs.n; j ++){
		os << "[";
		for (int i = 0; i < rhs.m; i++){
			os << std::to_string(rhs.cols[j][i]) << (i == rhs.m-1 ? "" : ",");
		}
		os << (j==rhs.n-1 ? "]" : "],");
	}
	os << "]";
	return os;
}

