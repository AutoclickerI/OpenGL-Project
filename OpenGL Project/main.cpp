#include <vector>
#include "Light.h"
#include "Sphere.h"
#include "Texture.h"

using namespace std;

#define WINDOW_X 0
#define WINDOW_Y 0

#define WINDOW_WIDTH 1280		// window's width
#define WINDOW_HEIGHT 720		// window's height

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2


clock_t start_t = clock();
clock_t end_t;

vector<Sphere> spheres;
Light light(0, 0, boundaryX / 2, GL_LIGHT0);
Texture texture;
float angle;

void initialize() {
	angle = 0;
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

	Sphere sphere1(30, 20, 20);
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
			if (spheres[i].getCenter()[0] - spheres[i].getRadius() < -boundaryX || spheres[i].getCenter()[0] + spheres[i].getRadius() > boundaryX)
				spheres[i].getVelocity()[0] *= -1;
			if (spheres[i].getCenter()[1] - spheres[i].getRadius() < -boundaryY || spheres[i].getCenter()[1] + spheres[i].getRadius() > boundaryY)
				spheres[i].getVelocity()[1] *= -1;
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
	glClearColor(.3f, .3f, .3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Implement: Draw 2D (texture, ID and name)*/
	glPushMatrix();
	glScalef(150, 150, 150);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	texture.drawSquareWithTexture();

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

void keyboardDown(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */
	switch (key) {
	case 'q':
		angle += 3;
		break;
	case 'w':
		angle -= 3;
		break;
	default:
		break;
	}
}
void MyReshape(int NewWidth, int NewHeight) {
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
int main(int argc, char** argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Draw three spheres");
	initialize();
	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(keyboardDown);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}