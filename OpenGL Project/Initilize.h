#pragma once
#include "Declare.h"
#include "Display.h"
#include "Keyboard.h"
#include "Idle.h"

void initialize() {
	theme = SNU;
	angle = 0;
	speed = 10;
	delete_probability = 15;
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

	Material mtl2(mtl1), mtl3(mtl1), mtl4(mtl1), mtl5(mtl1), mtl6(mtl1), mtl7(mtl1);
	mtl2.setAmbient(0.1f, 0.8f, 0.8f, 1.0f);
	mtl3.setAmbient(0.8f, 0.1f, 0.8f, 1.0f);
	mtl4.setAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	mtl5.setAmbient(0.8f, 0.1f, 0.1f, 1.0f);
	mtl6.setAmbient(0.1f, 0.8f, 0.1f, 1.0f);
	mtl7.setAmbient(0.1f, 0.1f, 0.8f, 1.0f);
	materials.push_back(mtl1);
	materials.push_back(mtl2);
	materials.push_back(mtl3);
	materials.push_back(mtl4);
	materials.push_back(mtl5);
	materials.push_back(mtl6);
	materials.push_back(mtl7);

	Sphere sphere1(30, 20, 20);
	sphere1.setCenter(0.0f, 50.0f, 0.0f);
	sphere1.setVelocity(0.0f, 0.0f, 0.0f);
	MTL_num = rand() % 7;
	sphere1.setMTL(materials[MTL_num], MTL_num);
	cannon.push_back(sphere1);

	Sphere sphere2(sphere1);
	sphere2.setCenter(0.0f, 0.0f, 0.0f);
	sphere2.setVelocity(0.0f, 0.0f, 0.0f);
	MTL_num = rand() % 7;
	sphere2.setMTL(materials[MTL_num], MTL_num);
	cannon.push_back(sphere2);

	/* Implement: initialize texture*/
	background.setFilename("textures/background/snu.png");
	background.settextureID(0);
	background.initTexture();

	canon.setFilename("textures/cannon/snu.png");
	canon.settextureID(0);
	canon.initTexture();
}