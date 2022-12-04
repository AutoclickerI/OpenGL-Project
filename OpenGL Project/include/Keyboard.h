#pragma once
#include "Declare.h"
#include "Functions.h"

void SpecialInput(int key, int x, int y) {
	switch (mode) {
	case PREMAINMENU:
		mode = MAINMENU1;
		break;
	case MAINMENU1:
		switch (key)
		{
		case GLUT_KEY_UP:
			//do something here
			if (arrow_pos < 238)
				arrow_pos += 160;
			break;
		case GLUT_KEY_DOWN:
			//do something here
			if (arrow_pos > -242)
				arrow_pos -= 160;
			break;
		case GLUT_KEY_LEFT:
			//do something here
			break;
		case GLUT_KEY_RIGHT:
			switch (arrow_pos) {
			case 238:
				mode = MAINMENU2;
				score = 0;
				break;
			case 78:
				mode = HIGHSCORE;
				break;
			case -82:
				mode = SETTING;
				break;
			case -242:
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
			case 210:
				cannon.clear();
				difficulty = EASY;
				mode = MOVING;
				item = 1;
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
			case 20:
				cannon.clear();
				difficulty = NORMAL;
				mode = MOVING;
				item = 1;
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
			case -170:
				cannon.clear();
				difficulty = HARD;
				mode = MOVING;
				item = 1;
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
			if (arrow_pos_2 < 210)
				arrow_pos_2 += 190;
			break;
		case GLUT_KEY_DOWN:
			//do something here
			if (arrow_pos_2 > -170)
				arrow_pos_2 -= 190;
			break;
		default:
			break;
		}
		break;
	case SETTING:
		switch (key)
		{
		case GLUT_KEY_LEFT:
			sound[BUTTON].playsound();
			arrow_pos_3.second = 0;
			switch (arrow_pos_3.first) {
			case 50:
				Frame = 180 - Frame;
				moving_speed = 1.2f / Frame;
				break;
			case -60:
				theme = static_cast<Theme>((theme + 2) % 3);
				if (scoredata[0] != 999999999 && theme == Theme2)
					theme = SPACE;
				switch (theme) {
				case SNU:
					background.setFilename("textures/background/snu.png");
					canon.setFilename("textures/cannon/snu.png");
					break;
				case SPACE:
					background.setFilename("textures/background/space.png");
					canon.setFilename("textures/cannon/space.png");
				default:
					break;
				}
				background.initTexture();
				canon.initTexture();
				break;
			case -170:
				manual = static_cast<MANUAL>((manual + 2) % 3);
				if (scoredata[0] != 999999999 && manual == MOUSE)
					manual = KEYBOARD2;
				angle = 0;
				break;
			case -280:
				if (!colormode) {
					materials[0].setAmbient(0.00392156862745098, 0.45098039215686275, 0.6980392156862745, 1.0f);
					materials[1].setAmbient(0.00784313725490196, 0.6196078431372549, 0.45098039215686275, 1.0f);
					materials[2].setAmbient(0.984313725490196, 0.6862745098039216, 0.8941176470588236, 1.0f);
					materials[3].setAmbient(0.9254901960784314, 0.8823529411764706, 0.2, 1.0f);
					materials[4].setAmbient(0.5803921568627451, 0.5803921568627451, 0.5803921568627451, 1.0f);
					materials[5].setAmbient(0.33725490196078434, 0.7058823529411765, 0.9137254901960784, 1.0f);
					materials[6].setAmbient(0.8352941176470589, 0.3686274509803922, 0.0, 1.0f);
				}
				else {
					materials[0].setAmbient(0.8f, 0.8f, 0.1f, 1.0f);
					materials[1].setAmbient(0.1f, 0.8f, 0.8f, 1.0f);
					materials[2].setAmbient(0.8f, 0.1f, 0.8f, 1.0f);
					materials[3].setAmbient(0.8f, 0.8f, 0.8f, 1.0f);
					materials[4].setAmbient(0.8f, 0.1f, 0.1f, 1.0f);
					materials[5].setAmbient(0.1f, 0.8f, 0.1f, 1.0f);
					materials[6].setAmbient(0.1f, 0.1f, 0.8f, 1.0f);
				}
				colormode = static_cast<COLORMODE>((colormode + 1) % 2);
				break;
			default:
				break;
			}
			break;
		case GLUT_KEY_RIGHT:
			sound[BUTTON].playsound();
			arrow_pos_3.second = 1;
			switch (arrow_pos_3.first) {
			case 50:
				Frame = 180 - Frame;
				moving_speed = 1.2f / Frame;
				break;
			case -60:
				theme = static_cast<Theme>((theme + 1) % 3);
				if (scoredata[0] != 999999999 && theme == Theme2)
					theme = SNU;
				switch (theme) {
				case SNU:
					background.setFilename("textures/background/snu.png");
					canon.setFilename("textures/cannon/snu.png");
					break;
				case SPACE:
					background.setFilename("textures/background/space.png");
					canon.setFilename("textures/cannon/space.png");
				default:
					break;
				}
				background.initTexture();
				canon.initTexture();
				break;
			case -170:
				manual = static_cast<MANUAL>((manual + 1) % 3);
				if (scoredata[0] != 999999999 && manual == MOUSE)
					manual = KEYBOARD1;
				angle = 0;
				break;
			case -280:
				if (!colormode) {
					materials[0].setAmbient(0.00392156862745098, 0.45098039215686275, 0.6980392156862745, 1.0f);
					materials[1].setAmbient(0.00784313725490196, 0.6196078431372549, 0.45098039215686275, 1.0f);
					materials[2].setAmbient(0.984313725490196, 0.6862745098039216, 0.8941176470588236, 1.0f);
					materials[3].setAmbient(0.9254901960784314, 0.8823529411764706, 0.2, 1.0f);
					materials[4].setAmbient(0.5803921568627451, 0.5803921568627451, 0.5803921568627451, 1.0f);
					materials[5].setAmbient(0.33725490196078434, 0.7058823529411765, 0.9137254901960784, 1.0f);
					materials[6].setAmbient(0.8352941176470589, 0.3686274509803922, 0.0, 1.0f);
				}
				else {
					materials[0].setAmbient(0.8f, 0.8f, 0.1f, 1.0f);
					materials[1].setAmbient(0.1f, 0.8f, 0.8f, 1.0f);
					materials[2].setAmbient(0.8f, 0.1f, 0.8f, 1.0f);
					materials[3].setAmbient(0.8f, 0.8f, 0.8f, 1.0f);
					materials[4].setAmbient(0.8f, 0.1f, 0.1f, 1.0f);
					materials[5].setAmbient(0.1f, 0.8f, 0.1f, 1.0f);
					materials[6].setAmbient(0.1f, 0.1f, 0.8f, 1.0f);
				}
				colormode = static_cast<COLORMODE>((colormode + 1) % 2);
				break;
			default:
				break;
			}
			break;
		case GLUT_KEY_UP:
			if (arrow_pos_3.first < 50)
				arrow_pos_3.first += 110;
			break;
		case GLUT_KEY_DOWN:
			if (arrow_pos_3.first > -280)
				arrow_pos_3.first -= 110;
			break;
		default:
			break;
		}
		break;
	case HIGHSCORE:
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
			moving_speed = 1.2f / Frame;
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
			STAGE_NOW = STAGE1;
			angle = level = 0;
			moving_speed = 1.2f / Frame;
			delete_probability = 100;
			stage_Location.clear();
			stage_Sphere.clear();
			shootings.clear();
			merge.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
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
				playername.insert(playername.begin() + ranking, fullname);
				ofstream oscore("config.ini");
				if (oscore.is_open()) {
					oscore << trash << " ";
					for (int i = 0; i < 10; i++) {
						oscore << playername[i] << " " << scoredata[i] << " " << difficultydata[i] << " ";
					}
					oscore << Frame << " " << manual << " " << theme << endl;
					scorechange = 0;
					oscore.close();
				}
			}
			mode = MAINMENU1;
			angle = level = 0;
			moving_speed = 1.2f / Frame;
			delete_probability = 100;
			stage_Location.clear();
			stage_Sphere.clear();
			shootings.clear();
			merge.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
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
	if (mode == PREMAINMENU)
		mode = MAINMENU1;
	switch (key) {
	case 27:
		switch (mode) {
		case SETTING:
			if (1) {
				ofstream oscore("config.ini");
				if (oscore.is_open()) {
					oscore << trash << " ";
					for (int i = 0; i < 10; i++) {
						oscore << playername[i] << " " << scoredata[i] << " " << difficultydata[i] << " ";
					}
					oscore << Frame << " " << manual << " " << theme << endl;
					scorechange = 0;
					oscore.close();
				}
			}
		case MAINMENU2:
		case HIGHSCORE:
		case DEVELOPERS:
			mode = MAINMENU1;
			break;
		default:
			break;
		}
		break;
	case ' ':
		switch (mode) {
		case MAINMENU1:
			switch (arrow_pos) {
			case 238:
				mode = MAINMENU2;
				score = 0;
				break;
			case 78:
				mode = HIGHSCORE;
				break;
			case -82:
				mode = SETTING;
				break;
			case -242:
				mode = DEVELOPERS;
				break;
			default:
				break;
			}
			break;
		case MAINMENU2:
			switch (arrow_pos_2) {
			case 210:
				cannon.clear();
				difficulty = EASY;
				mode = MOVING;
				item = 1;
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
			case 20:
				cannon.clear();
				difficulty = NORMAL;
				mode = MOVING;
				item = 1;
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
			case -170:
				cannon.clear();
				difficulty = HARD;
				mode = MOVING;
				item = 1;
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
			(shootings.end() - 1)->setVelocity((600.0f / Frame) * sin(angle * PI / 180), (600.0f / Frame) * cos(angle * PI / 180), 0.0f);
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
			STAGE_NOW = STAGE1;
			angle = level = pause = 0;
			moving_speed = 1.2f / Frame;
			delete_probability = 100;
			stage_Location.clear();
			stage_Sphere.clear();
			shootings.clear();
			merge.clear();
			for (int i = -10; i < 2; i++)
				stage_Location.push_back(i);
		}
		break;
	case 'r':
	case 'R':
		if (pause) {
			pause = 0;
		}
		break;
	case 'm':
	case 'M':
		if (mode != SCORESAVE) {
			if (!musicpause) {
				sound[BGM].pausesound();
				musicpause = 1;
			}
			else {
				sound[BGM].resumesound();
				musicpause = 0;
			}
		}
		break;
	default:
		break;
	}
}