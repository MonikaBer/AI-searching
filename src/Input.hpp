#include <vector>
#include <fstream>

#ifndef INPUT_HPP
#define INPUT_HPP

class Input {
private:
    int height;                        //matrix's height
    int width;                         //matrix's width
    int radius;                        //defines camera's view
    int minNumberOfCameras;            //minimum number of cameras monitoring every point
    std::vector <std::vector <bool>> matrix;    //input matrix

public:
    Input(std::istream &);
    void displayMatrix();

    //getters
    int getHeight();
    int getWidth();
    int getRadius();
    int getMinNumberOfCameras();
    std::vector <std::vector <bool>> getMatrix();

    friend class Individual;
};

#endif