#include <math.h>
#include "lib.hpp"
#include "Individual.hpp"

float pointsDistance(int x, int y, int i, int j){
    return sqrt(pow(i-x,2) + pow(j-y,2));
}

void cameraSettingView(CameraView & cameraView, int x, int y, int radius, std::vector<std::vector<bool>> matrix) {
	int wasCornerTherei = radius+1;
	int wasCornerTherej = radius+1;

	for(int i = 0; i <= radius; i++) {
		if(x+i >= Individual::height)  break;
		if(pointsDistance(x,y,x+i,y) > radius)  break;
		for(int j = 0; j <= radius; j++) {
			if(y+j >= Individual::width)  break;
			if(matrix[x+i][y+j] == false){
				if(wasCornerTherei > i)
				wasCornerTherei = i;
				if(wasCornerTherej > j)
				wasCornerTherei = j;
				continue;
			}
			else if(wasCornerTherej  > j && wasCornerTherei > i){
				cameraView.view[x+i][y+j]++;
				//printf("ok\n");
			}
			else if(isCornerOnLine(x,y,x+i,y+j,matrix) == false){
				cameraView.view[x+i][y+j]++;
				//printf("ok\n");
			}
			if(pointsDistance(x,y,x+i,y+j) > radius)  break;
		}
		int wasCornerTherej = 0-radius-1;
		for(int j = -1; j >= -radius; j--) {
			if(y+j < 0)  break;
			if(matrix[x+i][y+j] == false){
				if(wasCornerTherei > i)
					wasCornerTherei = i;
				if(wasCornerTherej < j)
					wasCornerTherei = j;
				continue;
			}
			else if(wasCornerTherej  < j && wasCornerTherei > i)
				cameraView.view[x+i][y+j]++;
			else if(isCornerOnLine(x,y,x+i,y+j,matrix) == false)
				cameraView.view[x+i][y+j]++;
			if(pointsDistance(x,y,x+i,y+j) >= radius)  break;
		}
	}
	wasCornerTherei = 0-radius-1;
	wasCornerTherej = radius+1;
	for(int i = -1; i >= -radius; i--) {
		if(x+i < 0)  break;
		if(pointsDistance(x,y,x+i,y) > radius)  break;
		for(int j = 0; j <= radius; j++) {
			if(y+j >= Individual::width)  break;
			if(matrix[x+i][y+j] == false){
				if(wasCornerTherei < i)
					wasCornerTherei = i;
				if(wasCornerTherej > j)
					wasCornerTherei = j;
				continue;
			}
			else if(wasCornerTherej  > j && wasCornerTherei < i)
				cameraView.view[x+i][y+j]++;
			else if(isCornerOnLine(x,y,x+i,y+j,matrix) == false)
				cameraView.view[x+i][y+j]++;
			if(pointsDistance(x,y,x+i,y+j) > radius)  break;
		}
		int wasCornerTherej = 0-radius-1;
		for(int j = -1; j >= -radius; j--) {
			if(y+j < 0)  break;
			if(matrix[x+i][y+j] == false){
				if(wasCornerTherei < i)
					wasCornerTherei = i;
				if(wasCornerTherej < j)
					wasCornerTherei = j;
				continue;
			}
			else if(wasCornerTherej  < j && wasCornerTherei < i)
				cameraView.view[x+i][y+j]++;
			else if(isCornerOnLine(x,y,x+i,y+j,matrix) == false)
				cameraView.view[x+i][y+j]++;
			if(pointsDistance(x,y,x+i,y+j) >= radius)  break;
		}
	}
}

bool isCornerOnLine(int x1, int y1, int x2, int y2, std::vector<std::vector<bool>> matrix) {
     //auxiliary variables
     int d, dx, dy, ai, bi, xi, yi;
     int x = x1, y = y1;
     //setting the drawing direction
     if (x1 < x2) {
         xi = 1;
         dx = x2 - x1;
     } else {
         xi = -1;
         dx = x1 - x2;
     }
     // setting the drawing direction
     if (y1 < y2) {
         yi = 1;
         dy = y2 - y1;
     } else {
         yi = -1;
         dy = y1 - y2;
     }
     // OX leading axis
     if (dx > dy) {
         ai = (dy - dx) * 2;
         bi = dy * 2;
         d = bi - dx;
         while (x != x2) {
             // factor test
             if (d >= 0) {
                 x += xi;
                 y += yi;
                 d += ai;
             } else {
                 d += bi;
                 x += xi;
             }
             if(matrix[x][y] == false)
				return true;
         }
     } else {  // OY leading axis
         ai = ( dx - dy ) * 2;
         bi = dx * 2;
         d = bi - dy;

         while (y != y2) {
             //factor test
             if (d >= 0) {
                 x += xi;
                 y += yi;
                 d += ai;
             } else {
                 d += bi;
                 y += yi;
             }
			 if(matrix[x][y] == false)
				 return true;
         }
     }
	 return false;
}
