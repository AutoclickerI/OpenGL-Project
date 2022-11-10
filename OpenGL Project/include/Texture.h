#pragma once
#include <cmath>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>

using namespace std;

class Texture {
public:
	FIBITMAP* createBitMap(char const* filename);
	void settextureID(GLuint tID);
	void setFilename(char const* filename);
	void generateTexture();
	void initTexture();
	void drawSquareWithTexture(float width, float height);
	void drawCircleWithTexture(float radius, int slices);

private:
	GLuint textureID = 0;
	GLubyte* textureData = 0;
	int imageWidth = 1280, imageHeight = 720;
	char const* Filename = "snu.png";
	const double pi = 3.141592653589793;
};