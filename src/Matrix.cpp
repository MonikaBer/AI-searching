#include <iostream>
#include "Matrix.hpp"

using namespace std;

Matrix::Matrix(istream & in){
    string str;
    
    in >> height;
    in.get();
    in >> width;
    in.get();
    
    for(unsigned int i = 0; i < height; i++){
        vector<bool> row;
        getline(in, str);
        for(unsigned int j = 0; j < width; j++){
            if(str[j] == '0')        row.push_back(false);
            else if (str[j] == '1')  row.push_back(true);
            else                     throw "Incorrect file format";
        }
        matrix.push_back(row);
    }
}

void Matrix::displayMatrix(){
    for(unsigned int i = 0; i < this->height; i++){
        for(unsigned int j = 0; j < this->width; j++){
            if (this->matrix[i][j] == true)  cout << "1";
            else cout << "0";
        }
        cout << "\n";
    }
}

//getters
unsigned int Matrix::getHeight(){
    return this->height;
}

unsigned int Matrix::getWidth(){
    return this->width;
}