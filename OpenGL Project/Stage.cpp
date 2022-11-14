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
		center[1] = 250 - 60 * (pos - 17);
	}
	else {
		center[0] = 350 - 60 * (pos - 25.3);
		center[1] = -248;
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
};

void Stage::stage4(double pos) {
	int stageR = 400;
	if (pos < -3) {
		center[0] = 0;
		center[1] = 400 - pos;
	}
	else if (pos <= 12) {
		center[0] = stageR * sin(((pos * 360) / (2 * PI * stageR)) + 30 * PI / 180);
		center[1] = stageR * cos(((pos * 360) / (2 * PI * stageR)) + 30 * PI / 180);
	}
	else if (pos < 16) {
		stageR = 70;
		center[0] = stageR * sin((pos * 360) / (2 * PI * stageR) - 80 * PI / 180) + 256.5;	//400 * sin(((12 * 360) / (2 * PI * 330)) + 30 * PI / 180);
		center[1] = stageR * cos((pos * 360) / (2 * PI * stageR) - 80 * PI / 180) - 209;		//400 * cos(((12 * 360) / (2 * PI * 330)) + 30 * PI / 180);
	}
	else if (pos < 35) {
			stageR = 260;
			center[0] = stageR * sin(((-pos * 360) / (2 * PI * stageR)) - 30 * PI / 180);
			center[1] = stageR * cos(((-pos * 360) / (2 * PI * stageR)) - 30 * PI / 180);
		}
	else if (pos < 39) {
			stageR = 70;
			center[0] = stageR * sin(((-pos * 360) / (2 * PI * stageR)) + 90 * PI / 180) - 177;
			center[1] = stageR * cos(((-pos * 360) / (2 * PI * stageR)) + 90 * PI / 180) - 73;
		}
	else if (pos < 49.7) {
			stageR = 120;
			center[0] = stageR * sin(((pos * 360) / (2 * PI * stageR)) - 96 * PI / 180);
			center[1] = stageR * cos(((pos * 360) / (2 * PI * stageR)) - 96 * PI / 180);
		}
	else {
			center[0] = 0;
			center[1] = -120 - 60 * (pos - 49.7);
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
	for (int i = -2; i < 500; i++) {
		setPos(42 * i / 300.0, stage);
		glVertex3f(center[0], center[1], 0);
	}
	glEnd();
}