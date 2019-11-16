#include <vector>
#include "Input.hpp"

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

struct Point {
    bool room;            		  	//false - point beyond the room, true - point in the room
    int numberOfCameras;   	//number of cameras which see the point
    bool camera;           			//true - camera is here, false - lack of camera
};


class Individual {
private:    
    int height;                      	//matrix's height
    int width;                       	//matrix's width
    std::vector <std::vector <Point>> arrangement;       //arrangement 
    int fitness;                     	//fitness function
    int radius;                         //defines camera's view 

public:
    Individual(Input);
	Individual(int,int,std::vector <std::vector <Point>>,int	);
    void cameraSettingView(int, int, int);  //setting camera visibility for every point in cameras' view
    void calculateFitness(); 
    void completeArrangement();
	void cleanNumbersOfCameras();			//set numberOfCameras of every pool on 0;
    Individual crossover(Individual);
    void mutation();
    void displayCamerasCoordinates();
    //getters:
    void displayRoomAppearance();
    void displayHowMuchCamerasForEachPoint();
    void displayWhereCamerasAre();
	Point getPoint(int,int);			//get point from arragement by its number of row and number of column

    //setters:
	
	void setPoint(int,int,Point);	//set point from arragement by its number of row and number of column

    friend class Population;
};

#endif