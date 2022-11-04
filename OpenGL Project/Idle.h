#pragma once
#include "Declare.h"
#include "Initilize.h"

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();
	if (end_t - start_t > 1000 / 60) {
		for (vector<double>::size_type i = stage_Location.size(); i--!= 0;) {
			if(stage_Location[0]<0)
				stage_Location[i] += 0.1;
			else
				stage_Location[i] += 0.02;
			stage.stage1(stage_Location[i]);
			stage_Sphere[i].setCenter(stage.getCenter()[0], stage.getCenter()[1], 0);
		}
		for (vector<Sphere>::size_type i = 0; i < shootings.size(); i++) {
			for (vector<Sphere>::size_type j = i + 1; j < shootings.size(); j++) {
				handleCollision(shootings[i], shootings[j]);
				if (isCollisionDetected(shootings[i], shootings[j])) {
					shootings[i].move();
					shootings[j].move();
				}
			}
		}
		vector<Sphere>::size_type i = 0;
		while (i < shootings.size()) {
			shootings[i].move();
			if (shootings[i].getCenter()[0] - shootings[i].getRadius() < -boundaryX || shootings[i].getCenter()[0] + shootings[i].getRadius() > boundaryX) {
				shootings[i].getVelocity()[0] *= -1;
				
				while (shootings[i].getCenter()[0] - shootings[i].getRadius() < -boundaryX || shootings[i].getCenter()[0] + shootings[i].getRadius() > boundaryX)
					shootings[i].move();
				
				if (rand() % 100 < delete_probability) {
					shootings.erase(shootings.begin() + i);
					i -= 1;
				}
			}
			else if (shootings[i].getCenter()[1] - shootings[i].getRadius() < -boundaryY || shootings[i].getCenter()[1] + shootings[i].getRadius() > boundaryY) {
				shootings[i].getVelocity()[1] *= -1;
				
				while (shootings[i].getCenter()[1] - shootings[i].getRadius() < -boundaryY || shootings[i].getCenter()[1] + shootings[i].getRadius() > boundaryY)
					shootings[i].move();
				
				if (rand() % 100 < delete_probability) {
					shootings.erase(shootings.begin() + i);
					i -= 1;
				}
			}
			i++;
		}
		start_t = end_t;
		glutPostRedisplay();
	}
}
