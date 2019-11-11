#include <vector>
#include "Input.hpp"

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

struct Point {
    bool room;             //false - point beyond the room, true - point in the room
    int numberOfCameras;   //number of cameras which see the point
    bool camera;           //true - camera is here, false - lack of camera
};


class Individual {
private:    
    int height;                      //matrix's height
    int width;                       //matrix's width
    std::vector <std::vector <Point>> arrangement;       //arrangement 
    int fitness;                     //fitness function

public:
    Individual(Input);
    void cameraSettingView(int, int, int);  //setting camera visibility for every point in cameras' view
    void calculateFitness(); 
    void completeArrangement();
    void crossover(Individual);
    void mutation();
    void displayCamerasCoordinates();
    //getters:
    void displayRoomAppearance();
    void displayHowMuchCamerasForEachPoint();
    void displayWhereCamerasAre();

    //setters:      

    friend class Population;
};

#endif