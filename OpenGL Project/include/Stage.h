#pragma once
#include "Material.h"
#include <GL/glut.h>

class Stage {
public:
	void setPos(double pos, int stage);
	void stage1(double pos);
	void stage2(double pos);
	void draw_stage(int stage);
	void setMTL(const Material& m);
	const double* getCenter() const;
private:
	int screen_size = 1280;
	double center[2] = { 0,0 };
	Material stage_color;
};