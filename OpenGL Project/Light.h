#pragma once
#include <GL/glut.h>
class Light {
public:
	Light(float x, int y, int z, int LID);
	void setLightID(int LID);
	void setPosition(float x, float y, float z);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void enableLight(bool bOn);
	bool isLightOn() const;
	void draw() const;
private:
	int lightID;
	float pos[3];
	float ambient[4], noambient[4] = { 0,0,0,0 };
	float diffuse[4];
	float specular[4];
	bool bLightOn;
};