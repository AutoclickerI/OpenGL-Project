#pragma once
#include <windows.h>
#include "Declare.h"
#include "Display.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Idle.h"

void initialize() {
	score = level = 0;
	theme = SNU;
	angle = 0;
	arrow_pos = 238;
	arrow_pos_2 = 210;
	arrow_pos_3.first = 50; arrow_pos_3.second = 0;
	STAGE_NOW = STAGE1;
	delete_probability = 100;
	difficulty = NORMAL;
	mode = PREMAINMENU;

	srand((unsigned int)time(NULL));
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	Material mtl1;
	mtl1.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl1.setAmbient(0.8f, 0.8f, 0.1f, 1.0f);
	mtl1.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	mtl1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl1.setShininess(30.0f);

	Material mtl2(mtl1), mtl3(mtl1), mtl4(mtl1), mtl5(mtl1), mtl6(mtl1), mtl7(mtl1), stage_color(mtl1);
	mtl2.setAmbient(0.1f, 0.8f, 0.8f, 1.0f);
	mtl3.setAmbient(0.8f, 0.1f, 0.8f, 1.0f);
	mtl4.setAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	mtl5.setAmbient(0.8f, 0.1f, 0.1f, 1.0f);
	mtl6.setAmbient(0.1f, 0.8f, 0.1f, 1.0f);
	mtl7.setAmbient(0.1f, 0.1f, 0.8f, 1.0f);

	stage_color.setAmbient(1, 1, 1, 1.0f);
	stage.setMTL(stage_color, mtl5);
	materials.push_back(mtl1);
	materials.push_back(mtl2);
	materials.push_back(mtl3);
	materials.push_back(mtl4);
	materials.push_back(mtl5);
	materials.push_back(mtl6);
	materials.push_back(mtl7);

	for (int i = -10; i < 2; i++)
		stage_Location.push_back(i);

	sphere1.setCenter(0.0f, 50.0f, 0.0f);
	sphere1.setVelocity(0.0f, 0.0f, 0.0f);
	sphere2.setCenter(0.0f, 0.0f, 0.0f);

	/* Implement: initialize texture*/

	clear.setFilename("textures/state/clear.png");
	clear.settextureID(0);
	clear.initTexture();

	gameover.setFilename("textures/state/gameover.png");
	gameover.settextureID(0);
	gameover.initTexture();

	premainmenu_1.setFilename("textures/state/premainmenu1_1.png");
	premainmenu_1.settextureID(0);
	premainmenu_1.initTexture();

	premainmenu_2.setFilename("textures/state/premainmenu1_2.png");
	premainmenu_2.settextureID(0);
	premainmenu_2.initTexture();

	mainmenu1_1.setFilename("textures/state/mainmenu1_1.png");
	mainmenu1_1.settextureID(0);
	mainmenu1_1.initTexture();

	mainmenu1_2.setFilename("textures/state/mainmenu1_2.png");
	mainmenu1_2.settextureID(0);
	mainmenu1_2.initTexture();

	mainmenu2_1.setFilename("textures/state/mainmenu2_1.png");
	mainmenu2_1.settextureID(0);
	mainmenu2_1.initTexture();

	mainmenu2_2.setFilename("textures/state/mainmenu2_2.png");
	mainmenu2_2.settextureID(0);
	mainmenu2_2.initTexture();

	highscore.setFilename("textures/state/highscore.png");
	highscore.settextureID(0);
	highscore.initTexture();

	arrow.setFilename("textures/object/gray.png");
	arrow.settextureID(0);
	arrow.initTexture();

	arrow_2.setFilename("textures/object/yellow.png");
	arrow_2.settextureID(0);
	arrow_2.initTexture();

	settings_1.setFilename("textures/state/settings_1.png");
	settings_1.settextureID(0);
	settings_1.initTexture();

	settings_2.setFilename("textures/state/settings_2.png");
	settings_2.settextureID(0);
	settings_2.initTexture();

	developers.setFilename("textures/state/developers.png");
	developers.settextureID(0);
	developers.initTexture();

	scoresave.setFilename("textures/state/scoresave.png");
	scoresave.settextureID(0);
	scoresave.initTexture();

	Pause.setFilename("textures/state/pause.png");
	Pause.settextureID(0);
	Pause.initTexture();

	blackhole.setFilename("textures/object/blackhole.png");
	blackhole.settextureID(0);
	blackhole.initTexture();

	whitehole.setFilename("textures/object/whitehole.png");
	whitehole.settextureID(0);
	whitehole.initTexture();

	sound.push_back(bgm);
	sound.push_back(shoot);
	sound.push_back(boomsound);
	sound.push_back(stageclear);
	sound.push_back(stagefailed);
	sound.push_back(button);
	sound.push_back(itemsound);

	glColor3f(1.0f, 1.0f, 1.0f);

	for (vector<Sound>::size_type i = 0; i < sound.size(); i++) {
		sound[i].initsound(0);
	}
	sound[BGM].initsound(1);

	iscore >> word;
	trash = word;
	for (int i = 0; (!iscore.eof()) && i < 10; i++) {
		iscore >> word;
		playername[i] = word;

		iscore >> number;
		scoredata[i] = number;

		iscore >> word;
		difficultydata[i] = word;
	}

	iscore >> number;
	if (number != NULL)	Frame = number;
	else Frame = 60;

	iscore >> number;
	switch (number) {
	case 0:
		manual = KEYBOARD1;
		break;
	case 1:
		manual = KEYBOARD2;
		break;
	case 2:
		manual = MOUSE;
		break;
	default:
		manual = MOUSE;
		break;
	}
	iscore >> number;
	switch (number) {
	case 0:
		theme = SNU;
		break;
	case 1:
		theme = SPACE;
		break;
	case 2:
		theme = CANDY;
		break;
	default:
		theme = SNU;
		break;
	}
	iscore >> number;
	switch (number) {
	case 0:
		colormode = PRIMARY;
		break;
	case 1:
		colormode = COLORBLIND;
		break;
	default:
		colormode = PRIMARY;
		break;
	}
	iscore.close();
	moving_speed = 1.2f / Frame;
	switch (theme) {
	case SNU:
		background.setFilename("textures/background/snu.png");
		canon.setFilename("textures/cannon/snu.png");
		break;
	case SPACE:
		background.setFilename("textures/background/space.png");
		canon.setFilename("textures/cannon/space.png");
		break;
	case CANDY:
		background.setFilename("textures/background/candy.png");
		canon.setFilename("textures/cannon/candy.png");
		break;
	default:
		break;
	}

	background.settextureID(0);
	background.initTexture();

	canon.settextureID(0);
	canon.initTexture();
}