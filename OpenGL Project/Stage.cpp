#include "Stage.h"

void Stage::setMTL(const Material& m) {
	stage_color = m;
}

void Stage::stage1(double pos) {
	if (pos < 17) {
		center[0] = 60 * pos - 670;
		center[1] = 250;
	}
	else if (pos < 25.3) {
		center[0] = 350;
		center[1] = 250-60*(pos-17);
	}
	else {
		center[0] = 350-60*(pos-25.3);
		center[1] = -248;
	}
};

const double* Stage::getCenter() const {
	return center;
}

void Stage::draw_stage1() {
	glLineWidth(7.0f);
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_EMISSION, stage_color.emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, stage_color.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, stage_color.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, stage_color.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, stage_color.shininess);
	for (int i = 0; i < 1000; i++) {
		stage1(42 * i / 1000.0);
		glVertex3f(center[0], center[1], 0);
	}
	glEnd();
}