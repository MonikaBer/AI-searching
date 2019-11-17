#include <iostream>
#include <random> 
#include <functional>
#include "Individual.hpp"
#include "lib.hpp"

using namespace std;

int Individual::height;
int Individual::width;
int Individual::radius;
int Individual::minNumberOfCameras;
int Individual::roomSurface;


Individual::Individual(Input & input){
    vector<vector<bool>> matrix = input.getMatrix();

    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> cameraSetting(0, 1);
    int isCamera;
    camerasNumber = 0;

    for(int i = 0; i < height; i++) {
        vector<Point> row;
        for(int j = 0; j < width; j++){
            Point point;
            point.room = matrix[i][j];
            
            if(point.room == true) {
                isCamera = cameraSetting(mt);
                if(isCamera == 1) {
                    point.camera = true; 
                    camerasNumber++;
                } else {
                    point.camera = false;
                } 
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
                this->cameraSettingView(i, j);
        }
    }

    this->calcFitness();
}

Individual::Individual() {}

void Individual::cameraSettingView(Input input){
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(arrangement[i][j].camera == true)
                this->cameraSettingView(i, j);
        }
    }
}

void Individual::cameraSettingView(int x, int y){
    //int i = x;
    //int j = y;
    //int counter;
	bool wasTherecorner = false;

	for(int i = 0; i <= radius; i++){
		if(x+i >= this->height) 
			break;
		if(pointsDistance(x,y,x+i,y) > radius)
				break;
		for(int j = 0; j <= radius; j++){
			if(y+j >= this->width)
				break;
			if(this->arrangement[x+i][y+j].room == false){
				wasTherecorner = true;
				continue;
			}
			else if(wasTherecorner == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			else if(isCornerOnLine(x,y,x+i,y+j) == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			if(pointsDistance(x,y,x+i,y+j) > radius)
				break;
		}
		for(int j = -1; j >= -radius; j--){
			if(y+j<0)
				break;
			if(this->arrangement[x+i][y+j].room == false){
				wasTherecorner = true;
				continue;
			}
			else if(wasTherecorner == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			else if(isCornerOnLine(x,y,x+i,y+j) == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			if(pointsDistance(x,y,x+i,y+j) >= radius)
				break;
		}
	}
	wasTherecorner = false;
	for(int i = -1; i >= -radius; i--){
		if(x+i < 0)
			break;
		if(pointsDistance(x,y,x+i,y) > radius)
				break;
		for(int j = 0; j <= radius; j++){
			if(y+j>=this->width)
				break;
			if(this->arrangement[x+i][y+j].room == false){
				wasTherecorner = true;
				continue;
			}
			else if(wasTherecorner == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			else if(isCornerOnLine(x,y,x+i,y+j) == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			if(pointsDistance(x,y,x+i,y+j) > radius)
				break;
		}
		for(int j = -1; j >= -radius; j--){
			if(y+j<0)
				break;
			if(this->arrangement[x+i][y+j].room == false){
				wasTherecorner = true;
				continue;
			}
			else if(wasTherecorner == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			else if(isCornerOnLine(x,y,x+i,y+j) == false)
				this->arrangement[x+i][y+j].numberOfCameras++;
			if(pointsDistance(x,y,x+i,y+j) >= radius)
				break;
		}
	}

}

void Individual::calcFitness() {  //think of changing target function
    this->fitness = 0.0;
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(this->arrangement[i][j].room == true && this->arrangement[i][j].numberOfCameras >= this->minNumberOfCameras)
                this->fitness++;
        }
    }

    this->fitness /= (float)(this->roomSurface);
}

void Individual::cleanNumberOfCamerasForEachPoint() {
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            this->arrangement[i][j].numberOfCameras = 0;
        }
    }
}

void Individual::clearCameras(){
	for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            arrangement[i][j].camera = false;
        }
    }
}

void Individual::findCameraCoordinates(int cameraNumber, int & x, int & y) {
    int counter = 0;
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(this->arrangement[i][j].camera == true) {
                counter++;
                if(counter == cameraNumber) {
                    x = i;
                    y = j;
                    return;
                }
            }
        }
    }

    throw "Number of cameras in Individual is calculated invalidly";
}

// Individual Individual::randomCrossover(Individual & secondParent) {
// 	Individual offspring(this->arrangement);
	
// 	srand(time(NULL));	
// 	for(int i = 0; i < this->height; i++) {
//         for(int j = 0; j < this->width; j++) {
// 			if(rand()%2 == 0)
// 				offspring.setPoint(i,j,arrangement[i][j]);
// 			else
// 				offspring.setPoint(i,j,secondParrent.getPoint(i,j));
//         }
//     }
	
// 	offspring.cleanNumbersOfCameras();
	
// 	for(int i = 0; i < height; i++) {
//         for(int j = 0; j < width; j++) {
//             if(offspring.arrangement[i][j].camera == true)
//                 offspring.cameraSettingView(i, j, radius);
//         }
//     }
	
// 	return	offspring;
// }

//think of changing (without clean all cameras views)
Individual Individual::crossover(Individual & secondParent) {
    int x, y;
    int parentNumber, cameraNumber;
    vector<Point2d> camerasToCrossover;                //cameras' coordinates
    
    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> whichParent(1,2);
    
    Individual offspring;
    //a greater part of arrangement from parent who will be selected in drawing
    if(whichParent(mt) == 1) {
        offspring.setArrangementAndCamerasNumber(this->arrangement, this->camerasNumber);
        parentNumber = 1;
    } else {
        offspring.setArrangementAndCamerasNumber(secondParent.getArrangement(), secondParent.getCamerasNumber());
        parentNumber = 2;
    }

    std::random_device prob2;
    std::mt19937 mt2(prob2());
    std::uniform_int_distribution<int> whichCamera(1, offspring.camerasNumber);

    //draw cameras to crossover	
    for(int k = 0; k < CAMERAS_TO_CROSSOVER; k++) {                
        cameraNumber = whichCamera(mt2);                           //draw camera number to crossover
        offspring.findCameraCoordinates(cameraNumber, x, y);
        Point2d point;
        point.x = x;
        point.y = y;
        //cout << "\nx: " << x << ", y: " << y << endl;
        camerasToCrossover.push_back(point);
    }

    for(int k = 0; k < CAMERAS_TO_CROSSOVER; k++) {  
        x = camerasToCrossover[k].x;
        y = camerasToCrossover[k].y;

        if(whichParent(mt) == 1) {                     //whom camera will be selected
            if(parentNumber == 2){
                if(offspring.arrangement[x][y].camera == true && this->arrangement[x][y].camera == false) {
                    offspring.camerasNumber--;
                    offspring.arrangement[x][y].camera = false;
                } else if (offspring.arrangement[x][y].camera == false && this->arrangement[x][y].camera == true) {
                    offspring.camerasNumber++;
                    offspring.arrangement[x][y].camera = true;
                }
            } //else do nothing
        } else { //second parent
            if(parentNumber == 1) {
                if(offspring.arrangement[x][y].camera == true && secondParent.getArrangement()[x][y].camera == false) {
                    offspring.camerasNumber--;
                    offspring.arrangement[x][y].camera = false;
                } else if (offspring.arrangement[x][y].camera == false && secondParent.getArrangement()[x][y].camera == true) {
                    offspring.camerasNumber++;
                    offspring.arrangement[x][y].camera = true;
                }
            } //else do nothing
        }
    }

	offspring.cleanNumberOfCamerasForEachPoint();
	
	for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(offspring.arrangement[i][j].camera == true)
                offspring.cameraSettingView(i, j);
        }
    }

	return offspring;
}

bool Individual::isCornerOnLine(int x1, int y1, int x2, int y2){
     //auxiliary variables
     int d, dx, dy, ai, bi, xi, yi;
     int x = x1, y = y1;
     //setting the drawing direction
     if (x1 < x2){
         xi = 1;
         dx = x2 - x1;
     }
     else{
         xi = -1;
         dx = x1 - x2;
     }
     // setting the drawing direction
     if (y1 < y2){
         yi = 1;
         dy = y2 - y1;
     }
     else{
         yi = -1;
         dy = y1 - y2;
     }
     // OX leading axis
     if (dx > dy){
         ai = (dy - dx) * 2;
         bi = dy * 2;
         d = bi - dx;
         while (x != x2){
             // factor test
             if (d >= 0){
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else{
                 d += bi;
                 x += xi;
             }
             if(this->arrangement[x][y].room == false)
				 return true;
         }
     }
     // OY leading axis
     else{
         ai = ( dx - dy ) * 2;
         bi = dx * 2;
         d = bi - dy;
		 
         while (y != y2){
             //factor test
             if (d >= 0){
                 x += xi;
                 y += yi;
                 d += ai;
             }
             else{
                 d += bi;
                 y += yi;
             }
			 if(this->arrangement[x][y].room == false)
				 return true;
         }
     }
	 return false;
}

void Individual::mutation(int populationSize) {
    int pointNumber, counter = 0;
    
    std::random_device prob;
    std::mt19937 mt(prob());
    std::uniform_int_distribution<int> ifMutation(1, populationSize);

    std::random_device prob2;
    std::mt19937 mt2(prob2());
    std::uniform_int_distribution<int> whichRoomPoint(1, this->roomSurface);

    // (1/populationSize) -> probability of mutation
    if(ifMutation(mt) == 1) {                               //mutation
        pointNumber = whichRoomPoint(mt2);
        for(int i = 0; i < this->height; i++) {
            for(int j = 0; j < this->width; j++) {
                if(this->arrangement[i][j].room == true) {
                    counter++;
                    if(counter == pointNumber) {
                        if(this->arrangement[i][j].camera == true) {
                            this->arrangement[i][j].camera = false;
                            this->camerasNumber--;
                        } else {
                            this->arrangement[i][j].camera = true;
                            this->camerasNumber++;
                        }
                        this->cleanNumberOfCamerasForEachPoint();

                        i = this->height;
                        j = this->width;
                    }
                }
            }
        }
    } else {               //without mutation
        return;
    }

    //set cameras' view (increment for room points)
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if(this->arrangement[i][j].camera == true)
                this->cameraSettingView(i, j);
        }
    }
}


//helpers

void Individual::displayRoomAppearance() {
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            cout << this->arrangement[i][j].room;
        }
        cout << "\n";
    }
}

void Individual::displayHowManyCamerasForEachPoint() {
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

void Individual::displayCamerasCoordinates() {
    int counter = 1;
    for(int i = 0; i < this->height; i++) {
		for(int j = 0; j < this->width; j++) {
			if(this->arrangement[i][j].camera == true) {
				cout << "\tCamera " << counter << ": (" << i << ", " << j << ")\n"; 
				counter++;
			}
		}
	}
}


//getters

int Individual::getCamerasNumber() {
    return this->camerasNumber;
}

vector<vector<Point>> Individual::getArrangement() {
    return this->arrangement;
}

float Individual::getFitness() {
    return this->fitness;
}


//setters
void Individual::setCamera(int rowNumber, int columnNumber){
	arrangement[rowNumber][columnNumber].camera = true;
}

void Individual::setArrangementAndCamerasNumber(vector<vector<Point>> parentArrangement, int parentCamerasNumber){
    this->arrangement = parentArrangement;
    this->camerasNumber = parentCamerasNumber;
}