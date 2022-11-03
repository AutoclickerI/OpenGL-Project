#pragma once
#include "Material.h"
#include <GL/glut.h>
class Sphere {
public:
	Sphere(float r, int sl, int st);
	Sphere(const Sphere& shape);
	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	void setStack(int st);
	void setCenter(float x, float y, float z);
	const float* getCenter() const;
	void setVelocity(float x, float y, float z);
	float* getVelocity() const;
	void setMTL(const Material& m);
	void move();
	void draw() const;
private:
	float radius;
	int slice;
	int stack;
	float center[3];
	mutable float velocity[3];
	Material mtl;
};