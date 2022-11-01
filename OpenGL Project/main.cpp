#include <vector>
#include <windows.h>
#include "Light.h"
#include "Sphere.h"
#include "Texture.h"

using namespace std;

#define WINDOW_X 200
#define WINDOW_Y 200

#define WINDOW_WIDTH 640		// window's width
#define WINDOW_HEIGHT 640		// window's height

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2


clock_t start_t = clock();
clock_t end_t;

vector<Sphere> spheres;
Light light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
Texture texture;

void initialize() {
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	Material mtl1;
	mtl1.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl1.setAmbient(0.4f, 0.4f, 0.1f, 1.0f);
	mtl1.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	mtl1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl1.setShininess(10.0f);

	Material mtl2(mtl1), mtl3(mtl1);
	mtl2.setAmbient(0.1f, 0.4f, 0.4f, 1.0f);
	mtl3.setAmbient(0.4f, 0.1f, 0.4f, 1.0f);

	Sphere sphere1(50, 20, 20);
	sphere1.setCenter(0.0f, -200.0f, 0.0f);
	sphere1.setVelocity(0.3f, 0.6f, 0.0f);
	sphere1.setMTL(mtl1);
	spheres.push_back(sphere1);

	Sphere sphere2(sphere1);
	sphere2.setCenter(100.0f, 200.0f, 0.0f);
	sphere2.setVelocity(-0.6f, -0.5f, 0.0f);
	sphere2.setMTL(mtl2);
	spheres.push_back(sphere2);

	Sphere sphere3(sphere1);
	sphere3.setCenter(-100.0f, 0.0f, 0.0f);
	sphere3.setVelocity(-2.0f, 2.0f, 0.0f);
	sphere3.setMTL(mtl3);
	spheres.push_back(sphere3);

	/* Implement: initialize texture*/
	texture.setFilename("snu.png");
	texture.settextureID(0);
	texture.initTexture();
}

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();

	if (end_t - start_t > 1000 / 60) {
		for (vector<Sphere>::size_type i = 0; i < spheres.size(); i++) {
			spheres[i].move();
			for (int j = 0; j < 3; j++)
				if (spheres[i].getCenter()[j] - spheres[i].getRadius() < -boundaryX || spheres[i].getCenter()[j] + spheres[i].getRadius() > boundaryX)
					spheres[i].getVelocity()[j] *= -1;
		}
		start_t = end_t;
		glutPostRedisplay();
	}
}

void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	/* Implement: Draw 2D (texture, ID and name)*/
	glPushMatrix();
	glScalef(350, 350, 350);
	texture.drawSquareWithTexture();
	glColor3f(1.0f, 1.0f, 1.0f);
	displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "2021-13314 Jihoon Kim", -0.8f, -0.8f);

	glPopMatrix();
	/* Implement: Draw 3D (light and spheres)*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();
	glShadeModel(GL_SMOOTH);
	for (vector<Sphere>::size_type i = 0; i < spheres.size(); i++)
		spheres[i].draw();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// hide Window Console
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Draw three spheres");
	initialize();
	// register callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}