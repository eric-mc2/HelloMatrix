#include <iostream>
#include <string>
#include <exception>
#include "matrix.h"

Matrix::Matrix(int m, int n) : m{m}, n{n} {
		if (m <= 0 || n <= 0) throw std::argument_exception("m and n must be positive")
        cols = new int*[n];
        for (int i = 0; i < n; i++){
            cols[i] = new int[m];
        }
    }

std::string Matrix::shape() {
	return std::to_string(m) + "x" + std::to_string(n);
}