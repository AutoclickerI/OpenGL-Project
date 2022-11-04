#pragma once
#include "Declare.h"

void keyboardDown(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */
	switch (key) {
	case 'Q':
	case 'q':
		angle -= 3;
		break;
	case 'W':
	case 'w':
		angle += 3;
		break;
	default:
		break;
	}
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
}

void keyboardUp(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */

	switch (key) {
	case ' ':
		shootings.push_back(cannon.front());
		cannon.erase(cannon.begin());
		cannon.push_back(Sphere(cannon[0]));
		cannon[0].setCenter(0.0f, 50.0f, 0.0f);
		MTL_num = rand() % 7;
		cannon[1].setMTL(materials[MTL_num], MTL_num);
		(shootings.end() - 1)->setCenter(50 * sin(angle * PI / 180), 50 * cos(angle * PI / 180), 0.0f);
		(shootings.end() - 1)->setVelocity(speed * sin(angle * PI / 180), speed * cos(angle * PI / 180), 0.0f);
	default:
		break;
	}
}