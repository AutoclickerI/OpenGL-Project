#pragma once
#include "Material.h"
#include <cmath>
#include <GL/glut.h>

class Stage {
public:
	void setPos(double pos, int stage);
	void stage1(double pos);
	void stage2(double pos);
	void stage3(double pos);
	void stage4(double pos);
	void draw_stage(int stage);
	void setMTL(const Material& m);
	const double* getCenter() const;
private:
	int screen_size = 1280;
	double center[2] = { 0,0 };
	Material stage_color;
	const double PI = 3.141592653589793;

};