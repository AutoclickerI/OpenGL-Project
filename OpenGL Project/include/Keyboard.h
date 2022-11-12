#pragma once
#include "Declare.h"

void keyboardDown(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */
	switch (mode) {
	case MOVING:
	case BOOM:
	case CHAIN_BOOM:
	case DRAG:
	case CHAIN_DRAG:
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
		break;

	case CLEAR:
		switch (key) {
		case 'C':
		case 'c':
			mode = MOVING;
			moving_speed *= 2;
			angle = 0;
			delete_probability -= 10;
			shootings.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
			for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
				Sphere sphere_cache(30, 20, 20);
				sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
				sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
				MTL_num = rand() % color_num;
				sphere_cache.setMTL(materials[MTL_num], MTL_num);
				stage_Sphere.push_back(sphere_cache);
			}
			break;

		default:
			break;
		}
		break;

	case GAMEOVER:
		switch (key) {
		case 'R':
		case 'r':
			mode = MOVING;
			angle = 0;
			moving_speed = 0.02;
			delete_probability = 100;
			stage_Location.clear();
			stage_Sphere.clear();
			shootings.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
			for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
				Sphere sphere_cache(30, 20, 20);
				sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
				sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
				MTL_num = rand() % color_num;
				sphere_cache.setMTL(materials[MTL_num], MTL_num);
				stage_Sphere.push_back(sphere_cache);
			}
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */

	switch (key) {
	case ' ':
 		if (mode == MOVING) {
			bool No_add = true;
			sound[SHOOT].playsound();
			shootings.push_back(cannon.front());
			cannon.erase(cannon.begin());
			cannon.push_back(Sphere(cannon[0]));
			cannon[0].setCenter(0.0f, 50.0f, 0.0f);
			while (No_add) {
				MTL_num = rand() % color_num;
				if (difficulty == HARD) {
					No_add = false;
				}
				for (vector<Sphere>::size_type l = 0; l < stage_Sphere.size(); l++)
					if (MTL_num == stage_Sphere[l].getnum())
						No_add = false;
			}
			cannon[1].setMTL(materials[MTL_num], MTL_num);
			(shootings.end() - 1)->setCenter(50 * sin(angle * PI / 180), 50 * cos(angle * PI / 180), 0.0f);
			(shootings.end() - 1)->setVelocity(speed * sin(angle * PI / 180), speed * cos(angle * PI / 180), 0.0f);
		}
		break;
	case 'p':
	case 'P':
		if (pause == 0) {
			sound[BGM].pausesound();
			pause = 1;
			
		}
		 else if (pause == 1) {
			sound[BGM].resumesound();
			pause = 0;
			
		}
		 break;
	default:
		break;
	}
}