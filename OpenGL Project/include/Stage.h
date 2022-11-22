#pragma once
#include "Material.h"
#include "texture.h"
#include <cmath>
#include <GL/glut.h>

extern Texture blackhole;
extern Texture whitehole;

class Stage {
public:
	void setPos(double pos, int stage);
	void stage1(double pos);
	void stage2(double pos);
	void stage3(double pos);
	void stage4(double pos);
	void stage5(double pos);
	void draw_stage(int stage);
	void setMTL(const Material& m1, const Material& m2);
	const double* getCenter() const;
private:
	int screen_size = 1280;
	double center[2] = { 0,0 };
	Material stage_color;
	Material red;
	const double PI = 3.141592653589793;

};