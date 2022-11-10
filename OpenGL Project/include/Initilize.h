#pragma once
#include "Declare.h"
#include "Display.h"
#include "Keyboard.h"
#include "Functions.h"
#include "Idle.h"

void initialize() {
	theme = SNU;
	angle = 0;
	merge_step = 10;
	speed = 10;
	Frame = 60;
	color_num = 2;
	STAGE_NOW = STAGE1;
	delete_probability = 100;
	moving_speed = 0.02;
	mode = MOVING;

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
	stage.setMTL(stage_color);
	materials.push_back(mtl1);
	materials.push_back(mtl2);
	materials.push_back(mtl3);
	materials.push_back(mtl4);
	materials.push_back(mtl5);
	materials.push_back(mtl6);
	materials.push_back(mtl7);

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

	Sphere sphere1(30, 20, 20);
	sphere1.setCenter(0.0f, 50.0f, 0.0f);
	sphere1.setVelocity(0.0f, 0.0f, 0.0f);
	MTL_num = rand() % color_num;
	sphere1.setMTL(materials[MTL_num], MTL_num);
	cannon.push_back(sphere1);

	Sphere sphere2(sphere1);
	sphere2.setCenter(0.0f, 0.0f, 0.0f);
	MTL_num = rand() % color_num;
	sphere2.setMTL(materials[MTL_num], MTL_num);
	cannon.push_back(sphere2);

	/* Implement: initialize texture*/
	background.setFilename("textures/background/snu.png");
	background.settextureID(0);
	background.initTexture();

	canon.setFilename("textures/cannon/snu.png");
	canon.settextureID(0);
	canon.initTexture();

	clear.setFilename("textures/state/clear.png");
	clear.settextureID(0);
	clear.initTexture();

	gameover.setFilename("textures/state/gameover.png");
	gameover.settextureID(0);
	gameover.initTexture();

	sound.push_back(bgm);
	sound.push_back(shoot);

	sound[BGM].initsound(1);
	sound[SHOOT].initsound(0);

}