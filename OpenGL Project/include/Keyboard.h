#pragma once
#include "Declare.h"

void SpecialInput(int key, int x, int y) {
	switch (mode) {
	case MAINMENU1:
		switch (key)
		{
		case GLUT_KEY_UP:
			//do something here
			if (arrow_pos < -80)
				arrow_pos += 80;
			break;
		case GLUT_KEY_DOWN:
			//do something here
			if (arrow_pos > -320)
				arrow_pos -= 80;
			break;
		case GLUT_KEY_LEFT:
			//do something here
			break;
		case GLUT_KEY_RIGHT:
			switch (arrow_pos) {
			case -80:
				mode = MAINMENU2;
				score = 0;
				break;
			case -160:
				mode = HIGHSCORE;
				break;
			case -240:
				//mode = SETTING;
				mode = SCORESAVE; //임시
				break;
			case -320:
				mode = DEVELOPERS;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case MAINMENU2:
		switch (key)
		{
		case GLUT_KEY_LEFT:
			mode = MAINMENU1;
			break;
		case GLUT_KEY_RIGHT:
			switch (arrow_pos_2) {
			case -110:
				cannon.clear();
				difficulty = EASY;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
				break;
			case -200:
				cannon.clear();
				difficulty = NORMAL;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
				break;
			case -290:
				cannon.clear();
				difficulty = HARD;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
				break;
			default:
				break;
			}
			break;
		case GLUT_KEY_UP:
			//do something here
			if (arrow_pos_2 < -110)
				arrow_pos_2 += 90;
			break;
		case GLUT_KEY_DOWN:
			//do something here
			if (arrow_pos_2 > -290)
				arrow_pos_2 -= 90;
			break;
		default:
			break;
		}
		break;
	case HIGHSCORE:
	case SETTING:
	case DEVELOPERS:
		switch (key)
		{
		case GLUT_KEY_LEFT:
			mode = MAINMENU1;
			break;
		default:
			break;
		}
		break;
	case MOVING:
	case BOOM:
	case CHAIN_BOOM:
	case DRAG:
	case CHAIN_DRAG:
		if (manual == KEYBOARD2) {
			switch (key) {
			case GLUT_KEY_RIGHT:
				if (270 < angle || angle < 90)
					angle += 3;
				if (90 < angle && angle < 270)
					angle -= 3;
				break;
			case GLUT_KEY_LEFT:
				if (270 < angle || angle < 90)
					angle -= 3;
				if (90 < angle && angle < 270)
					angle += 3;
				break;
			case GLUT_KEY_UP:
				if (180 < angle && angle != 360)
					angle += 3;
				if (angle < 180 && angle != 0)
					angle -= 3;
				break;
			case GLUT_KEY_DOWN:
				if (180 < angle && angle != 360)
					angle -= 3;
				if (angle < 180 && angle != 0)
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
		break;
	default:
		break;
	}
}

void keyboardDown(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */
	switch (mode) {
	case MOVING:
	case BOOM:
	case CHAIN_BOOM:
	case DRAG:
	case CHAIN_DRAG:
		if (manual == KEYBOARD1) {
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
		break;
	case CLEAR:
		switch (key) {
		case 'C':
		case 'c':
			mode = MOVING;
			moving_speed *= 1.3;
			angle = 0;
			delete_probability -= 10;
			shootings.clear();
			merge.clear();
			level++;
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
			for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
				Sphere sphere_cache(30, 20, 20);
				sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
				sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
				MTL_num = rand() % color_num[difficulty];
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
			angle = level = 0;
			moving_speed = 0.02;
			delete_probability = 100;
			cannon.clear();
			MTL_num = rand() % color_num[difficulty];
			sphere1.setMTL(materials[MTL_num], MTL_num);
			cannon.push_back(sphere1);
			MTL_num = rand() % color_num[difficulty];
			sphere2.setMTL(materials[MTL_num], MTL_num);
			cannon.push_back(sphere2);
			stage_Location.clear();
			stage_Sphere.clear();
			shootings.clear();
			merge.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
			for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
				Sphere sphere_cache(30, 20, 20);
				sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
				sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
				MTL_num = rand() % color_num[difficulty];
				sphere_cache.setMTL(materials[MTL_num], MTL_num);
				stage_Sphere.push_back(sphere_cache);
			}
			break;
		case 'Q':
		case 'q':
			mode = MAINMENU1;
			angle = level = 0;
			moving_speed = 0.02;
			delete_probability = 100;
			stage_Location.clear();
			stage_Sphere.clear();
			shootings.clear();
			merge.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
			break;
		//case 'S':
		//case 's':
		//	mode = SCORESAVE;
			break;
		default:
			break;
		}
		break;
	case SCORESAVE:
		if ((key >= 65) && (key <= 90) || (key >= 97) && (key <= 122)) {
			if (currentplayer[0] == 0) {
				currentplayer[0] = key;
			}
			else if (currentplayer[1] == 0) {
				currentplayer[1] = key;
			}
			else if (currentplayer[2] == 0) {
				currentplayer[2] = key;
			}
			break;
		}
		switch (key) {
		case '.':
			for (int i = 0; i < 3; i++) {
				currentplayer[i] = 0;
			}
			break;
		case ',':
			if (scorechange == 1) {
				fullname[0] = currentplayer[0];
				fullname[1] = currentplayer[1];
				fullname[2] = currentplayer[2];
				cout << ranking;
				playername.insert(playername.begin() + ranking, fullname);
				ofstream oscore("score/top10.ini");
				if (oscore.is_open()) {
					for (int i = 0; i < 10; i++) {
						oscore << playername[i] << " " << scoredata[i] << " " << difficultydata[i] << " " << themedata[i] << " " << framedata[i] << endl;
					}
					scorechange = 0;
					oscore.close();
				}
			}
			mode = MAINMENU1;
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */
	bool No_add = true;
	switch (key) {
	case ' ':
		switch (mode) {
		case MAINMENU1:
			switch (arrow_pos) {
			case -80:
				mode = MAINMENU2;
				score = 0;
				break;
			case -160:
				mode = HIGHSCORE;
				break;
			case -240:
				//mode = SETTING;
				mode = SCORESAVE; //임시
				break;
			case -320:
				mode = DEVELOPERS;
				break;
			default:
				break;
			}
			break;
		case MAINMENU2:
			switch (arrow_pos_2) {
			case -110:
				cannon.clear();
				difficulty = EASY;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
				break;
			case -200:
				cannon.clear();
				difficulty = NORMAL;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
				break;
			case -290:
				cannon.clear();
				difficulty = HARD;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
				break;
			default:
				break;
			}
			break;
		case MOVING:
			sound[SHOOT].playsound();
			shootings.push_back(cannon.front());
			cannon.erase(cannon.begin());
			cannon.push_back(Sphere(cannon[0]));
			cannon[0].setCenter(0.0f, 50.0f, 0.0f);
			while (No_add) {
				if (!stage_Location.size()) {
					mode = CLEAR;
					sound[STAGECLEAR].playsound();
					break;
				}
				MTL_num = rand() % color_num[difficulty];
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
			break;
		default:
			break;
		}
		break;
	case 'p':
	case 'P':
		switch (mode) {
		case MOVING:
		case BOOM:
		case CHAIN_BOOM:
		case DRAG:
		case CHAIN_DRAG:
			if (!pause) {
				sound[BGM].pausesound();
				pause = 1;
			}
			break;
		default:
			break;
		}
		break;
	case 'q':
	case 'Q':
		if (pause) {
			mode = MAINMENU1;
			sound[BGM].resumesound();
			angle = level = pause = 0;
			moving_speed = 0.02;
			delete_probability = 100;
			stage_Location.clear();
			stage_Sphere.clear();
			shootings.clear();
			merge.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
			break;
		}
		break;
	case 'r':
	case 'R':
		if (pause) {
			pause = 0;
			sound[BGM].resumesound();
		}
		break;
	default:
		break;
	}
}
void mouse(int button, int state, int x, int y) {
	/* Implement */
	bool No_add = true;
	printf("(%d, %d, %d, %d)\n", button, state, x, y);
	switch (mode) {
	case MAINMENU1:
		if (480 < x && x < 800 && 380 < y && button == 0 && state == 1) {
			if (y < 465) {
				arrow_pos = -80;
				mode = MAINMENU2;
				score = 0;
			}
			else if (y < 550) {
				arrow_pos = -160;
				mode = HIGHSCORE;
			}
			else if (y < 635) {
				arrow_pos = -240;
				mode = SETTING;
			}
			else if (y < 720) {
				arrow_pos = -320;
				mode = DEVELOPERS;
			}
		}
		break;
	case MAINMENU2:
		if (510 < x && x < 780 && 435 < y && button == 0 && state == 1) {
			if (y < 518) {
				arrow_pos_2 = -110;
				cannon.clear();
				difficulty = EASY;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
			}
			else if (y < 601) {
				arrow_pos_2 = -200;
				cannon.clear();
				difficulty = NORMAL;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
			}
			else if (y < 685) {
				arrow_pos_2 = -290;
				cannon.clear();
				difficulty = HARD;
				mode = MOVING;
				MTL_num = rand() % color_num[difficulty];
				sphere1.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere1);
				MTL_num = rand() % color_num[difficulty];
				sphere2.setMTL(materials[MTL_num], MTL_num);
				cannon.push_back(sphere2);
				for (vector<double>::size_type i = 0; i < stage_Location.size(); i++) {
					Sphere sphere_cache(30, 20, 20);
					sphere_cache.setCenter(0.0f, 50.0f, 0.0f);
					sphere_cache.setVelocity(0.0f, 0.0f, 0.0f);
					MTL_num = rand() % color_num[difficulty];
					sphere_cache.setMTL(materials[MTL_num], MTL_num);
					stage_Sphere.push_back(sphere_cache);
				}
			}
		}
	case HIGHSCORE:
	case SETTING:
	case DEVELOPERS:
		if (30 < x && x < 80 && 30 < y && y < 90 && button == 0 && state == 1)
			mode = MAINMENU1;
		break;
	case MOVING:
		if (manual == MOUSE && button == 0 && state == 1) {
			sound[SHOOT].playsound();
			shootings.push_back(cannon.front());
			cannon.erase(cannon.begin());
			cannon.push_back(Sphere(cannon[0]));
			cannon[0].setCenter(0.0f, 50.0f, 0.0f);
			while (No_add) {
				if (!stage_Location.size()) {
					mode = CLEAR;
					sound[STAGECLEAR].playsound();
					break;
				}
				MTL_num = rand() % color_num[difficulty];
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
	default:
		break;
	}
}

void mouseMove(int x, int y) {
	/* Implement */
	double posx, posy;
	posx = x - WINDOW_WIDTH / 2;
	posy = -y + WINDOW_HEIGHT / 2;
	if (manual == MOUSE) {
		if (posx)
			angle = atan2(posx, posy) * 180 / PI;
		else
			angle = (posy < 0) * 180;
	}
	switch (mode) {
	case MAINMENU1:
		if (480 < x && x < 800 && 380 < y) {
			if (y < 465)
				arrow_pos = -80;
			else if (y < 550)
				arrow_pos = -160;
			else if (y < 635)
				arrow_pos = -240;
			else if (y < 720)
				arrow_pos = -320;
		}
		break;
	case MAINMENU2:
		if (510 < x && x < 780 && 435 < y) {
			if (y < 518)
				arrow_pos_2 = -110;
			else if (y < 601)
				arrow_pos_2 = -200;
			else if (y < 685)
				arrow_pos_2 = -290;
		}
		break;
	default:
		break;
	}
}

void mousePassiveMove(int x, int y) {
	/* Implement */
	double posx, posy;
	posx = x - WINDOW_WIDTH / 2;
	posy = -y + WINDOW_HEIGHT / 2;
	if (manual == MOUSE) {
		if (posx)
			angle = (atan2(posx, posy) * 180 / PI);
		else
			angle = (posy < 0) * 180;
	}
	switch (mode) {
	case MAINMENU1:
		if (480 < x && x < 800 && 380 < y) {
			if (y < 465)
				arrow_pos = -80;
			else if (y < 550)
				arrow_pos = -160;
			else if (y < 635)
				arrow_pos = -240;
			else if (y < 720)
				arrow_pos = -320;
		}
		break;
	case MAINMENU2:
		if (510 < x && x < 780 && 435 < y) {
			if (y < 518)
				arrow_pos_2 = -110;
			else if (y < 601)
				arrow_pos_2 = -200;
			else if (y < 685)
				arrow_pos_2 = -290;
		}
		break;
	default:
		break;
	}
}