#include <iostream>
#include "matrix.h"

int main()
{
    Matrix mat(1,1);
    std::cout << "Testing matrix class!!\n";
    std::cout << mat.shape();
    std::cout << "\n";
}