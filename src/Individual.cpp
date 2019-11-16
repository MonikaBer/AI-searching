#include <iostream>
#include <random> 
#include "Individual.hpp"
#include "lib.hpp"

using namespace std;

Individual::Individual(Input input){
    height = input.getHeight();
    width = input.getWidth();
    vector <vector <bool>> matrix = input.getMatrix();
	radius = input.getRadius();

    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> cameraSetting(0, 1);
    int isCamera;

    for(int i = 0; i < height; i++) {
        vector <Point> row;
        for(int j = 0; j < width; j++){
            Point point;
            point.room = matrix[i][j];
            
            if(point.room == true) {
                isCamera = cameraSetting(mt);
                if(isCamera == 1)  point.camera = true; 
                else  point.camera = false;
            } else  point.camera = false;
            
            point.numberOfCameras = 0;  //will be set later
            row.push_back(point);
        }
        arrangement.push_back(row);
    }

    //cameras view (increment for points)
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(arrangement[i][j].camera == true)
                this->cameraSettingView(i, j, radius);
        }
    }
}

Individual::Individual(int parrentsHeight, int parrentsWidth, std::vector <std::vector <Point>> parrentsArrangement, int parrentsRadius){
    height = parrentsHeight;
    width = parrentsWidth;

    arrangement = parrentsArrangement;

    //cameras view (increment for points)
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(arrangement[i][j].camera == true)
                this->cameraSettingView(i, j, parrentsRadius);
        }
    }
}

void Individual::cameraSettingView(int x, int y, int radius){
    this->arrangement[x][y].numberOfCameras++;   //increment for point with camera
    int i = x;
    int j = y;
    int counter;
              
    for(int l = 1; l <= radius; l++) {                 //first level; max level == radius
        i--;
        if(i>-1 && i<this->height && j>-1 && j<this->width && this->arrangement[i][j].room == true)  
            this->arrangement[i][j].numberOfCameras++;
        
        for(counter = 0; counter < l; counter++) {
            j++;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true)
                this->arrangement[i][j].numberOfCameras++;
        }
        
        for(counter = 0; counter < l; counter++) {
            i++;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true)
                this->arrangement[i][j].numberOfCameras++;
            i++;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true)
                this->arrangement[i][j].numberOfCameras++;
        }
        
        for(counter = 0; counter < l; counter++) {
            j--;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true)
                this->arrangement[i][j].numberOfCameras++;
            j--;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true)
                this->arrangement[i][j].numberOfCameras++;
        }    
        
        for(counter = 0; counter < l; counter++) {
            i--;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true)
                this->arrangement[i][j].numberOfCameras++;
            i--;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true)
                this->arrangement[i][j].numberOfCameras++;
        }
        
        for(counter = 0; counter < l-1; counter++) {
            j++;
            if(i>-1 && i<this->height && j>-1 && j<this->width && pointsDistance(x,y,i,j) <= radius && this->arrangement[i][j].room == true) 
                this->arrangement[i][j].numberOfCameras++;
        }
            
        j++;
    }
}

// void calculateFitness(){

// }

// void completeArrangement(){

// }

void Individual::cleanNumbersOfCameras()
{
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            arrangement[i][j].numberOfCameras = 0;
        }
    }
}

Individual* Individual::crossover(Individual secondParrent){
	Individual* child = new Individual(height,width,arrangement,radius);
	
	srand(time(NULL));	
	
	displayHowMuchCamerasForEachPoint();
	cout << endl;
	secondParrent.displayHowMuchCamerasForEachPoint();
	cout << endl;
	
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
			if(rand()%2 == 0)
				child->setPoint(i,j,arrangement[i][j]);
			else
				child->setPoint(i,j,secondParrent.getPoint(i,j));
        }
    }
	
	child->cleanNumbersOfCameras();
	
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(child->arrangement[i][j].camera == true)
                child->cameraSettingView(i, j, radius);
        }
    }
	
	child->displayHowMuchCamerasForEachPoint();
	
	delete child;
	
	return	NULL;
}

// void mutation(){

// }

// void displayCamerasCoordinates(){

// }

//getters
void Individual::displayRoomAppearance() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            cout << this->arrangement[i][j].room;
        }
        cout << "\n";
    }
}

void Individual::displayHowMuchCamerasForEachPoint() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            cout << this->arrangement[i][j].numberOfCameras << "\t";
        }
        cout << "\n";
    }
}

void Individual::displayWhereCamerasAre() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            cout << this->arrangement[i][j].camera;
        }
        cout << "\n";
    }
}

Point Individual::getPoint(int rowNumber, int columnNumber)
{
	return arrangement[rowNumber][columnNumber];
}

//setters
void Individual::setPoint(int rowNumber, int columnNumber, Point copiedPoint)
{
	arrangement[rowNumber][columnNumber].room = copiedPoint.room;
	arrangement[rowNumber][columnNumber].camera = copiedPoint.camera;
	
}