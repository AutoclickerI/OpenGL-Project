#pragma once
#include <fstream>
#include "Declare.h"
#include "Texture.h"
#include <iomanip>
#include <stdio.h>
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
			glTranslatef(-580, 300, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(30, 3);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-220, arrow_pos_2, 0);
			arrow.drawCircleWithTexture(30, 3);
			glPopMatrix();
			break;
		case DEVELOPERS:
			developers.displayStrokeCharacters(GLUT_STROKE_ROMAN, "DEVELOPERS", 7.0f, WINDOW_WIDTH * (-0.2), WINDOW_HEIGHT * (0.3), 1.5);
			developers.displayStrokeCharacters(GLUT_STROKE_ROMAN, "2021-13314 KIM JI HOON", 5.0f, WINDOW_WIDTH * ((-0.35) + 0.01 * sin(start_t/300)), WINDOW_HEIGHT * ((0) + 0.01 * cos(start_t/300)), 2.5);
			developers.displayStrokeCharacters(GLUT_STROKE_ROMAN, "2016-12767 LEE KANG MIN", 5.0f, WINDOW_WIDTH * ((-0.15) - 0.01 * sin(start_t/300)), WINDOW_HEIGHT * ((-0.3) - 0.01 * cos(start_t/300)), 2.5);
			glPushMatrix();
			glTranslatef(-580, 300, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(30, 3);
			glPopMatrix();
			break;
		case SETTING:
			if (start_t % 1200 > 600)
				settings_1.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			else 
				settings_2.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			glColor3f(0.0f, 0.0f, 0.0f);
			if(Frame==60)
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, to_string(Frame), 1.5f, WINDOW_WIDTH * (0.04), WINDOW_HEIGHT * (0.05), 3.0);
			else
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, to_string(Frame), 1.5f, WINDOW_WIDTH * (0.02), WINDOW_HEIGHT * (0.05), 3.0);
			switch (theme){
			case 0:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "SNU", 1.5f, WINDOW_WIDTH * (0.02), WINDOW_HEIGHT * (-0.1), 3.0);
				break;
			case 1:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "THEME1", 1.5f, WINDOW_WIDTH * (-0.01), WINDOW_HEIGHT * (-0.1), 3.0);
				break;
			case 2:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "THEME2", 1.5f, WINDOW_WIDTH * (-0.01), WINDOW_HEIGHT * (-0.1), 3.0);
				break;
			default:
				break;
			}
			switch (manual) {
			case 0:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "KEYBOARD1", 1.5f, WINDOW_WIDTH * (-0.05), WINDOW_HEIGHT * (-0.25), 3.0);
				break;
			case 1:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "KEYBOARD2", 1.5f, WINDOW_WIDTH * (-0.05), WINDOW_HEIGHT * (-0.25), 3.0);
				break;
			case 2:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "MOUSE", 1.5f, WINDOW_WIDTH * (-0.0), WINDOW_HEIGHT * (-0.25), 3.0);
				break;
			default:
				break;
			}
			switch (colormode) {
			case 0:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "PRIMARY", 1.5f, WINDOW_WIDTH * (-0.025), WINDOW_HEIGHT * (-0.4), 3.0);
				glColor3f(1.0f, 1.0f, 1.0f);
				break;
			case 1:
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "COLORBLIND", 1.5f, WINDOW_WIDTH * (-0.065), WINDOW_HEIGHT * (-0.4), 3.0);
				glColor3f(1.0f, 1.0f, 1.0f);
				break;
			default:
				break;
			}
			glPushMatrix();
			glTranslatef(-580, 300, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(30, 3);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-115, 50, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(20, 3);
			glRotatef(-60, 0, 0, 1);
			glTranslatef(0, -110, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(20, 3);
			glRotatef(-60, 0, 0, 1);
			glTranslatef(0, -110, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(20, 3);
			glRotatef(-60, 0, 0, 1);
			glTranslatef(0, -110, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(20, 3);
			glRotatef(-60, 0, 0, 1);
			glTranslatef(405, 0, 0);
			arrow.drawCircleWithTexture(20, 3);
			glTranslatef(0, 110, 0);
			arrow.drawCircleWithTexture(20, 3);
			glTranslatef(0, 110, 0);
			arrow.drawCircleWithTexture(20, 3);
			glTranslatef(0, 110, 0);
			arrow.drawCircleWithTexture(20, 3);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(290, arrow_pos_3.first, 1);
			if (!arrow_pos_3.second) {
				glTranslatef(-405, 0, 0);
				glRotatef(-60, 0, 0, 1);
			}
			arrow_2.drawCircleWithTexture(20, 3);
			glPopMatrix();
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

			char S1[100];
			sprintf(S1, "%09d", scoredata[0]);
			char S2[100];
			sprintf(S2, "%09lld", score);		

			if (scoredata[0] > score) background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, S1, 1.5f, WINDOW_WIDTH * (0.33), WINDOW_HEIGHT * (0.41), 5.0);
			else background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, S2, 1.5f, WINDOW_WIDTH * (0.33), WINDOW_HEIGHT * (0.41), 5.0);
			background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "SCORE", 1.5f, WINDOW_WIDTH * (0.33), WINDOW_HEIGHT * (0.36), 5.0);
			background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, S2, 1.5f, WINDOW_WIDTH * (0.33), WINDOW_HEIGHT * (0.31), 5.0);
			
			if (item == 1) background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "<ITEM>", 3.0f, WINDOW_WIDTH * (-0.48), WINDOW_HEIGHT * (0.45), 5.0);
			else background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "<USED>", 3.0f, WINDOW_WIDTH * (-0.48), WINDOW_HEIGHT * (0.45), 5.0);

			if (end_t - item_t > 0 && end_t - item_t < 5000 && item_t != NULL)
				background.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, to_string(-(end_t - item_t) / 1000 + 5), 1.5, WINDOW_WIDTH * (-0.2), WINDOW_WIDTH * (0), 5.0);
			break;

		case CLEAR:
			clear.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case GAMEOVER:
			gameover.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case HIGHSCORE:
			glPushMatrix();
			glTranslatef(-580, 300, 0);
			glRotatef(60, 0, 0, 1);
			arrow.drawCircleWithTexture(30, 3);
			glPopMatrix();
			highscore.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "HIGHSCORES", 5.0f, WINDOW_WIDTH * (-0.2), WINDOW_HEIGHT * (0.4), 3);

			for (int i = 0; i < 10; i++)
			{
				highscore.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, ordnum[i], 5.0f, WINDOW_WIDTH * (-0.45), WINDOW_HEIGHT * (0.3 - (0.08 * i)), 3);
				highscore.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, playername[i], 5.0f, WINDOW_WIDTH * (-0.25), WINDOW_HEIGHT * (0.3 - (0.08 * i)), 3);
				char S3[100];
				sprintf(S3, "%09d", scoredata[i]);
					highscore.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, S3, 5.0f, WINDOW_WIDTH * (-0.1), WINDOW_HEIGHT * (0.3 - (0.08 * i)), 3);
				highscore.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, difficultydata[i], 5.0f, WINDOW_WIDTH * (0.26), WINDOW_HEIGHT * (0.3 - (0.08 * i)), 3);
			}
			break;
		case SCORESAVE:
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "INPUT YOUR NAME", 5.0f, WINDOW_WIDTH * (-0.4), WINDOW_HEIGHT * (0.4), 2);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "YOUR RANK IS", 5.0f, WINDOW_WIDTH * (-0.4), WINDOW_HEIGHT * (0.3), 2);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, to_string(ranking+1), 5.0f, WINDOW_WIDTH * (0.25), WINDOW_HEIGHT * (0.3), 2);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "PRESS '.' TO RE-ENTER" , 5.0f, WINDOW_WIDTH * (-0.4), WINDOW_HEIGHT * (0.2), 2);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "PRESS ',' TO SAVE", 5.0f, WINDOW_WIDTH * (-0.4), WINDOW_HEIGHT * (0.1), 2);
			for (int i = 0; i < 3; i++) {
				string S4;
				S4 += currentplayer[i];
				scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, S4, 5.0f, WINDOW_WIDTH * (-0.1 + 0.07 * i), WINDOW_HEIGHT * (-0.2), 2);
			}
			break;
		default:
			break;
		}
	}
	else {
		Pause.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

		float i = fmod(0.07f * start_t, 360);
		glPushMatrix();

		if (i < 90.0 || i > 270.0) {
			glRotatef(i, 0.0f, 1.0f, 0.0f);
			cout << 1 << endl;
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "PAUSE", 10.0f, WINDOW_WIDTH * (-0.15), WINDOW_HEIGHT * (0.3), 1.5);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "R - RESUME", 10.0f, WINDOW_WIDTH * (-0.3), WINDOW_HEIGHT * (0.1), 1.5);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "Q - MAINMENU", 10.0f, WINDOW_WIDTH * (-0.35), WINDOW_HEIGHT * (-0.1), 1.5);
		}
		else {
			glRotatef(-i + 180, 0.0f, 1.0f, 0.0f);
			cout << 2 << endl;
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "PAUSE", 10.0f, WINDOW_WIDTH * (-0.15), WINDOW_HEIGHT * (0.3), 1.5);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "R - RESUME", 10.0f, WINDOW_WIDTH * (-0.3), WINDOW_HEIGHT * (0.1), 1.5);
			scoresave.displayStrokeCharacters(GLUT_STROKE_MONO_ROMAN, "Q - MAINMENU", 10.0f, WINDOW_WIDTH * (-0.35), WINDOW_HEIGHT * (-0.1), 1.5);
		}
		glPopMatrix();
	}
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