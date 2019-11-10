#include <vector>
#include <fstream>

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
private:
    unsigned int height;
    unsigned int width;
    std::vector <std::vector <bool>> matrix;

public:
    Matrix(std::istream &);
    void displayMatrix();

    //getters
    unsigned int getHeight();
    unsigned int getWidth();
};

#endif