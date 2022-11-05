#pragma once
#include "Material.h"
#include <GL/glut.h>

class Stage {
public:
	void stage1(double pos);
	void draw_stage1();
	void setMTL(const Material& m);
	const double* getCenter() const;
private:
	int screen_size = 1280;
	double center[2];
	Material stage_color;
};