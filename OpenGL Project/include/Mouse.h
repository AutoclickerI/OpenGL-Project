#pragma once
#include "Declare.h"
#include "Functions.h"

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
			}
			else if (y < 601) {
				arrow_pos_2 = -200;
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
			}
			else if (y < 685) {
				arrow_pos_2 = -290;
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
			}
		}
		if (30 < x && x < 80 && 30 < y && y < 90 && button == 0 && state == 1)
			mode = MAINMENU1;
		break;
	case SETTING:
		if (290 < y && y < 330 && button == 0 && state == 1) {
			if (505 < x && x < 545) {
				sound[BUTTON].playsound();
				Frame = 180 - Frame;
				arrow_pos_3.first = 50;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				sound[BUTTON].playsound();
				Frame = 180 - Frame;
				arrow_pos_3.first = 50;
				arrow_pos_3.second = 1;
			}
		}
		if (400 < y && y < 440 && button == 0 && state == 1) {
			if (505 < x && x < 545) {
				sound[BUTTON].playsound();
				theme = static_cast<Theme>((theme + 2) % 3);
				if (scoredata[0] != 999999999 && theme == Theme2)
					theme = Theme1;
				arrow_pos_3.first = -60;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				sound[BUTTON].playsound();
				theme = static_cast<Theme>((theme + 1) % 3);
				if (scoredata[0] != 999999999 && theme == Theme2)
					theme = SNU;
				arrow_pos_3.first = -60;
				arrow_pos_3.second = 1;
			}
		}
		if (510 < y && y < 550 && button == 0 && state == 1) {
			if (505 < x && x < 545) {
				sound[BUTTON].playsound();
				manual = static_cast<MANUAL>((manual + 2) % 3);
				if (scoredata[0] != 999999999 && manual == MOUSE)
					manual = KEYBOARD2;
				angle = 0;
				arrow_pos_3.first = -170;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				sound[BUTTON].playsound();
				manual = static_cast<MANUAL>((manual + 1) % 3);
				if (scoredata[0] != 999999999 && manual == MOUSE)
					manual = KEYBOARD1;
				angle = 0;
				arrow_pos_3.first = -170;
				arrow_pos_3.second = 1;
			}

		}
		if (620 < y && y < 660 && button == 0 && state == 1) {
			if (505 < x && x < 545) {
				angle = 0;
				arrow_pos_3.first = -280;
				arrow_pos_3.second = 0;
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
			}
			if (920 < x && x < 960) {
				angle = 0;
				arrow_pos_3.first = -280;
				arrow_pos_3.second = 1;
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
			}
		}
		if (30 < x && x < 80 && 30 < y && y < 90 && button == 0 && state == 1) {
			mode = MAINMENU1;
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
		}
	case HIGHSCORE:
	case DEVELOPERS:
		if (30 < x && x < 80 && 30 < y && y < 90 && button == 0 && state == 1)
			mode = MAINMENU1;
		break;
	case MOVING:
		if (0 < x && x < 130 && 0 < y && y < 130 && button == 0 && state == 1 && item == 1) {
			item_t = end_t;
			velocityrevert = 0;
			item = 0;
			sound[ITEMSOUND].playsound();
			moving_speed /= 10.0f;
		}
		else if (manual == MOUSE && button == 0 && state == 1) {
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
	case SETTING:
		if (290 < y && y < 330) {
			if (505 < x && x < 545) {
				arrow_pos_3.first = 50;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				arrow_pos_3.first = 50;
				arrow_pos_3.second = 1;
			}
		}
		if (400 < y && y < 440) {
			if (505 < x && x < 545) {
				arrow_pos_3.first = -60;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				arrow_pos_3.first = -60;
				arrow_pos_3.second = 1;
			}
		}
		if (510 < y && y < 550) {
			if (505 < x && x < 545) {
				angle = 0;
				arrow_pos_3.first = -170;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				angle = 0;
				arrow_pos_3.first = -170;
				arrow_pos_3.second = 1;
			}
		}
		if (620 < y && y < 660) {
			if (505 < x && x < 545) {
				angle = 0;
				arrow_pos_3.first = -280;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				angle = 0;
				arrow_pos_3.first = -280;
				arrow_pos_3.second = 1;
			}
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
	case SETTING:
		if (290 < y && y < 330) {
			if (505 < x && x < 545) {
				arrow_pos_3.first = 50;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				arrow_pos_3.first = 50;
				arrow_pos_3.second = 1;
			}
		}
		if (400 < y && y < 440) {
			if (505 < x && x < 545) {
				arrow_pos_3.first = -60;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				arrow_pos_3.first = -60;
				arrow_pos_3.second = 1;
			}
		}
		if (510 < y && y < 550) {
			if (505 < x && x < 545) {
				angle = 0;
				arrow_pos_3.first = -170;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				angle = 0;
				arrow_pos_3.first = -170;
				arrow_pos_3.second = 1;
			}
		}
		if (620 < y && y < 660) {
			if (505 < x && x < 545) {
				angle = 0;
				arrow_pos_3.first = -280;
				arrow_pos_3.second = 0;
			}
			if (920 < x && x < 960) {
				angle = 0;
				arrow_pos_3.first = -280;
				arrow_pos_3.second = 1;
			}
		}
		break;
	default:
		break;
	}
}