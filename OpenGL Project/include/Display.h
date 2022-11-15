#pragma once
#include "Declare.h"

void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < (int)str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

void display() {
	glClearColor(.0f, .0f, .0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (!pause) {
		switch (mode) {
		case MAINMENU1:
			if (start_t % 1200 > 600)
				mainmenu1_1.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			else
				mainmenu1_2.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			glPushMatrix();
			glTranslatef(-220, arrow_pos, 0);
			arrow.drawCircleWithTexture(30, 3);
			glPopMatrix();
			break;
		case MAINMENU2:
			if (start_t % 1200 > 600)
				mainmenu2_1.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			else
				mainmenu2_2.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			glPushMatrix();
			glTranslatef(-220, arrow_pos_2, 0);
			arrow.drawCircleWithTexture(30, 3);
			glPopMatrix();
			break;
		case DEVELOPERS:
			developers.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case MOVING:
		case BOOM:
		case CHAIN_BOOM:
		case DRAG:
		case CHAIN_DRAG:
			background.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			light.draw();
			glShadeModel(GL_SMOOTH);
			/* Implement: Draw 2D (texture, ID and name)*/
			stage.draw_stage(STAGE_NOW);
			glPushMatrix();
			glRotatef(angle, 0.0f, 0.0f, -1.0f);
			//show track if we are not in hard mode
			if (difficulty != HARD) {
				glLineWidth(5.0f);
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(6, 0xAAAA);
				glMaterialfv(GL_FRONT, GL_AMBIENT, cannon[0].getMTL().ambient);
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(0, 700, 0);
				glEnd();
				glDisable(GL_LINE_STIPPLE);
			}
			switch (theme) {
			case SNU:
				canon.drawCircleWithTexture(75, 30);
				break;
			default:
				canon.drawSquareWithTexture(150, 150);
				break;
			}
			for (vector<Sphere>::size_type i = 0; i < cannon.size(); i++)
				cannon[i].draw();
			glPopMatrix();
			/* Implement: Draw 3D (light and spheres)*/
			for (vector<Sphere>::size_type i = 0; i < stage_Sphere.size(); i++)
				stage_Sphere[i].draw();

			for (vector<Sphere>::size_type i = 0; i < shootings.size(); i++)
				shootings[i].draw();

			for (vector<pair<Sphere, int>>::size_type i = 0; i < merge.size(); i++)
				merge[i].first.draw();

			glDisable(GL_LIGHTING);
			glDisable(GL_DEPTH_TEST);
			break;
		case CLEAR:
			clear.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case GAMEOVER:
			gameover.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		default:
			break;
		}
	}
	else
		Pause.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	/* Implement: Draw 2D (texture, ID and name)*/

	glutSwapBuffers();
}

void Reshape(int NewWidth, int NewHeight) {
	bool W;
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)WINDOW_WIDTH;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)WINDOW_HEIGHT;
	if (WidthFactor > HeightFactor) {
		WidthFactor = HeightFactor;
		W = 0;
	}
	else {
		HeightFactor = WidthFactor;
		W = 1;
	}
	if (W)
		glViewport(0, (NewHeight - WINDOW_HEIGHT * HeightFactor) / 2, WINDOW_WIDTH * WidthFactor, WINDOW_HEIGHT * HeightFactor);
	else
		glViewport((NewWidth - WINDOW_WIDTH * WidthFactor) / 2, 0, WINDOW_WIDTH * WidthFactor, WINDOW_HEIGHT * HeightFactor);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);

}	