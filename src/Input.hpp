#include <vector>
#include <fstream>

#ifndef INPUT_HPP
#define INPUT_HPP

class Input {
private:
    unsigned int height;                        //matrix's height
    unsigned int width;                         //matrix's width
    unsigned int radius;                        //defines camera's view
    unsigned int minNumberOfCameras;            //minimum number of cameras monitoring every point
    std::vector <std::vector <bool>> matrix;    //input matrix

public:
    Input(std::istream &);
    void displayMatrix();

    //getters
    unsigned int getHeight();
    unsigned int getWidth();
    unsigned int getRadius();
    unsigned int getMinNumberOfCameras();
    std::vector <std::vector <bool>> getMatrix();

    friend class Individual;
};

#endif