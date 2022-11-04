#pragma once
#include "Declare.h"

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();

	if (end_t - start_t > 1000 / 60) {
		vector<Sphere>::size_type i = 0;
		while (i < shootings.size()) {
			shootings[i].move();
			if (shootings[i].getCenter()[0] - shootings[i].getRadius() < -boundaryX || shootings[i].getCenter()[0] + shootings[i].getRadius() > boundaryX) {
				shootings[i].getVelocity()[0] *= -1;
				if (rand() % 100 < delete_probability)
					shootings.erase(shootings.begin() + i);
				i -= 1;
			}
			else if (shootings[i].getCenter()[1] - shootings[i].getRadius() < -boundaryY || shootings[i].getCenter()[1] + shootings[i].getRadius() > boundaryY) {
				shootings[i].getVelocity()[1] *= -1;
				if (rand() % 100 < delete_probability)
					shootings.erase(shootings.begin() + i);
				i -= 1;
			}
			i++;
		}
		start_t = end_t;
		glutPostRedisplay();
	}
}
