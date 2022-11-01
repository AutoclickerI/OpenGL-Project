#pragma once
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
	void drawSquareWithTexture();

private:
	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;
	char const* Filename;
};