#include "Stage.h"

void Stage::setMTL(const Material& m1, const Material& m2) {
	stage_color = m1;
	red = m2;
}

void Stage::stage1(double pos) {
	if (pos < 17) {
		center[0] = 60 * pos - 670;
		center[1] = 250;
	}
	else if (pos < 25.3) {
		center[0] = 350;
		center[1] = 250 - 60 * (pos - 17);
	}
	else {
		center[0] = 350 - 60 * (pos - 25.3);
		center[1] = -248;
	}
}

void Stage::stage2(double pos) {
	if (pos < 17) {
		center[0] = -60 * pos + 670;
		center[1] = -250;
	}
	else if (pos < 25.3) {
		center[0] = -350;
		center[1] = -250 + 60 * (pos - 17);
	}
	else {
		center[0] = -350 + 60 * (pos - 25.3);
		center[1] = 248;
	}
}

void Stage::stage3(double pos) {
	double stageR = 400 - 4 * pos;
	if (pos > -3) {
		center[0] = (stageR)*sin(((pos * 360) / (2 * PI * 400.0 - 15 * pos)) + 30 * PI / 180);
		center[1] = (stageR)*cos(((pos * 360) / (2 * PI * 400.0 - 15 * pos)) + 30 * PI / 180);
	}
	else {
		center[0] = 0;
		center[1] = 400 - pos;
	}

}

void Stage::stage4(double pos) {
	int stageR = 400;
	if (pos < -3) {
		center[0] = 11;
		center[1] = 400 - pos;
	}
	else if (pos <= 12) {
		center[0] = stageR * sin(((pos * 360) / (2 * PI * stageR)) + 30 * PI / 180) + 11;
		center[1] = stageR * cos(((pos * 360) / (2 * PI * stageR)) + 30 * PI / 180);
	}
	else if (pos < 16) {
		stageR = 70;
		center[0] = stageR * sin((pos * 360) / (2 * PI * stageR) - 80 * PI / 180) + 265.5;	//400 * sin(((12 * 360) / (2 * PI * 330)) + 30 * PI / 180);
		center[1] = stageR * cos((pos * 360) / (2 * PI * stageR) - 80 * PI / 180) - 211;		//400 * cos(((12 * 360) / (2 * PI * 330)) + 30 * PI / 180);
	}
	else if (pos < 35) {
		stageR = 260;
		center[0] = stageR * sin(((-pos * 360) / (2 * PI * stageR)) - 30 * PI / 180) + 8;
		center[1] = stageR * cos(((-pos * 360) / (2 * PI * stageR)) - 30 * PI / 180) - 5;
	}
	else if (pos < 39) {
		stageR = 70;
		center[0] = stageR * sin(((-pos * 360) / (2 * PI * stageR)) + 90 * PI / 180) - 168;
		center[1] = stageR * cos(((-pos * 360) / (2 * PI * stageR)) + 90 * PI / 180) - 77;
	}
	else if (pos < 49.7) {
		stageR = 120;
		center[0] = stageR * sin(((pos * 360) / (2 * PI * stageR)) - 96 * PI / 180) + 7;
		center[1] = stageR * cos(((pos * 360) / (2 * PI * stageR)) - 96 * PI / 180) - 4;
	}
	else {
		center[0] = 0;
		center[1] = -120 - 60 * (pos - 49.7) - 3;
	}
}

void Stage::stage5(double pos) {
	int stageR;
	if (pos <= 7) {
		center[0] = -363;
		center[1] = 474 - 60 * pos;
	}
	else if (pos < 10) {
		stageR = 70;
		center[0] = stageR * sin((-(pos - 2) * 360) / (2 * PI * stageR) - 220 * PI / 180) - 293.5;	//400 * sin(((12 * 360) / (2 * PI * 330)) + 30 * PI / 180);
		center[1] = stageR * cos((-(pos - 2) * 360) / (2 * PI * stageR) - 220 * PI / 180) + 61;		//400 * cos(((12 * 360) / (2 * PI * 330)) + 30 * PI / 180);
	}
	else if (pos < 25) {
		stageR = 220;
		center[0] = stageR * sin(((pos * 360) / (2 * PI * stageR)) + 130 * PI / 180) - 19;
		center[1] = stageR * cos(((pos * 360) / (2 * PI * stageR)) + 130 * PI / 180) - 14;
	}
	else if (pos < 38) {
		stageR = 350;
		center[0] = stageR * sin(((-pos * 360) / (2 * PI * stageR)) + 190 * PI / 180) - 220;
		center[1] = stageR * cos(((-pos * 360) / (2 * PI * stageR)) + 190 * PI / 180) + 40;
	}
	else {
		stageR = 320;
		center[0] = stageR * sin(((pos * 360) / (2 * PI * stageR)) - 80 * PI / 180);
		center[1] = stageR * cos(((pos * 360) / (2 * PI * stageR)) - 80 * PI / 180);
	}
}

void Stage::setPos(double pos, int stage) {
	switch (stage) {
	case 0:
		stage1(pos);
		break;
	case 1:
		stage2(pos);
		break;
	case 2:
		stage3(pos);
		break;
	case 3:
		stage4(pos);
		break;
	case 4:
		stage5(pos);
		break;
	default:
		break;
	}
}

const double* Stage::getCenter() const {
	return center;
}

void Stage::draw_stage(int stage) {
	glLineWidth(7.0f);
	glBegin(GL_LINE_STRIP);
	glMaterialfv(GL_FRONT, GL_AMBIENT, stage_color.ambient);
	switch (stage) {
	case 0:
	case 1:
		for (int i = -2; i < 300; i++) {
			setPos(44 * i / 300.0, stage);
			if (i == 278)
				glMaterialfv(GL_FRONT, GL_AMBIENT, red.ambient);
			glVertex3f(center[0], center[1], 0);
		}
		break;
	case 2:
		for (int i = -2; i < 300; i++) {
			setPos(70 * i / 300.0, stage);
			if (i == 293)
				glMaterialfv(GL_FRONT, GL_AMBIENT, red.ambient);
			glVertex3f(center[0], center[1], 0);
		}
		break;
	case 3:
		for (int i = -2; i < 300; i++) {
			setPos(55 * i / 300.0, stage);
			if (i == 287)
				glMaterialfv(GL_FRONT, GL_AMBIENT, red.ambient);
			glVertex3f(center[0], center[1], 0);
		}
		break;
	case 4:
		for (int i = -2; i < 150; i++) {
			setPos(25 * i / 150.0, stage);
			glVertex3f(center[0], center[1], 0);
		}
		glEnd();
		glPushMatrix();
		glTranslatef(center[0], center[1], 1);
		blackhole.drawCircleWithTexture(50, 30);
		glPopMatrix();
		setPos(25 + 13 * 1 / 300.0, stage);
		glPushMatrix();
		glTranslatef(center[0], center[1], 1);
		whitehole.drawCircleWithTexture(50, 30);
		glPopMatrix();
		glBegin(GL_LINE_STRIP);
		for (int i = 1; i < 150; i++) {
			setPos(25 + 13 * i / 150.0, stage);
			glVertex3f(center[0], center[1], 0);
		}
		glEnd();
		glPushMatrix();
		glTranslatef(center[0], center[1], 1);
		blackhole.drawCircleWithTexture(50, 30);
		glPopMatrix();
		setPos(38 + 13 * 1 / 300.0, stage);
		glPushMatrix();
		glTranslatef(center[0], center[1], 1);
		whitehole.drawCircleWithTexture(50, 30);
		glPopMatrix();
		glBegin(GL_LINE_STRIP);
		for (int i = 1; i < 150; i++) {
			setPos(38 + 30 * i / 150.0, stage);
			if (i == 142)
				glMaterialfv(GL_FRONT, GL_AMBIENT, red.ambient);
			glVertex3f(center[0], center[1], 0);
		}
		break;
	default:
		break;
	}
	glEnd();
}