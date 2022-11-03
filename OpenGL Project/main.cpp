#include <ctime>
#include <vector>
#include <cstdlib>
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
const double PI = 3.141592653589793;
enum Theme {SNU, theme1, theme2};

Theme theme;
clock_t start_t = clock();
clock_t end_t;

vector<Sphere> shootings;
vector<Sphere> cannon;
vector<Material> materials;
Light light(0, 0, boundaryX / 2, GL_LIGHT0);
Texture background, canon;
float angle;
float speed = 10;

void initialize() {
	theme = SNU;
	angle = 0;
	srand((unsigned int)time(NULL));
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	Material mtl1;
	mtl1.setEmission(0.1f, 0.1f, 0.1f, 1.0f);
	mtl1.setAmbient(0.8f, 0.8f, 0.1f, 1.0f);
	mtl1.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	mtl1.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	mtl1.setShininess(30.0f);

	Material mtl2(mtl1), mtl3(mtl1), mtl4(mtl1), mtl5(mtl1), mtl6(mtl1), mtl7(mtl1);
	mtl2.setAmbient(0.1f, 0.8f, 0.8f, 1.0f);
	mtl3.setAmbient(0.8f, 0.1f, 0.8f, 1.0f);
	mtl4.setAmbient(0.8f, 0.8f, 0.8f, 1.0f);
	mtl5.setAmbient(0.8f, 0.1f, 0.1f, 1.0f);
	mtl6.setAmbient(0.1f, 0.8f, 0.1f, 1.0f);
	mtl7.setAmbient(0.1f, 0.1f, 0.8f, 1.0f);
	materials.push_back(mtl1);
	materials.push_back(mtl2);
	materials.push_back(mtl3);
	materials.push_back(mtl4);
	materials.push_back(mtl5);
	materials.push_back(mtl6);
	materials.push_back(mtl7);

	Sphere sphere1(30, 20, 20);
	sphere1.setCenter(0.0f, 50.0f, 0.0f);
	sphere1.setVelocity(0.0f, 0.0f, 0.0f);
	sphere1.setMTL(materials[rand() % 7]);
	cannon.push_back(sphere1);

	Sphere sphere2(sphere1);
	sphere2.setCenter(0.0f, 0.0f, 0.0f);
	sphere2.setVelocity(0.0f, 0.0f, 0.0f);
	sphere2.setMTL(materials[rand() % 7]);
	cannon.push_back(sphere2);

	/* Implement: initialize texture*/
	background.setFilename("textures/background/snu.png");
	background.settextureID(0);
	background.initTexture();

	canon.setFilename("textures/cannon/snu.png");
	canon.settextureID(0);
	canon.initTexture();
}

void idle() {
	/* Implement: update spheres and handle collision at boundary*/

	end_t = clock();

	if (end_t - start_t > 1000 / 60) {
		vector<Sphere>::size_type i = 0;
		while(i< shootings.size()){
			shootings[i].move();
			if (shootings[i].getCenter()[0] - shootings[i].getRadius() < -boundaryX || shootings[i].getCenter()[0] + shootings[i].getRadius() > boundaryX) {
				shootings[i].getVelocity()[0] *= -1;
				if (rand() % 10 > 4)
					shootings.erase(shootings.begin() + i);
				i -= 1;
			}
			else if (shootings[i].getCenter()[1] - shootings[i].getRadius() < -boundaryY || shootings[i].getCenter()[1] + shootings[i].getRadius() > boundaryY) {
				shootings[i].getVelocity()[1] *= -1;
				if (rand() % 10 > 4)
					shootings.erase(shootings.begin() + i);
				i -= 1;
			}
			i++;
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
	glClearColor(.0f, .0f, .0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Implement: Draw 2D (texture, ID and name)*/
	glPushMatrix();
	background.drawSquareWithTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	light.draw();
	glShadeModel(GL_SMOOTH);
	/* Implement: Draw 2D (texture, ID and name)*/
	glPushMatrix();
	glRotatef(angle, 0.0f, 0.0f, -1.0f);
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
	for (vector<Sphere>::size_type i = 0; i < shootings.size(); i++)
		shootings[i].draw();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void keyboardDown(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */
	switch (key) {
	case 'q':
		angle -= 3;
		break;
	case 'w':
		angle += 3;
		break;
	default:
		break;
	}
	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
}

void keyboardUp(unsigned char key, int x, int y) {
	/* Implement: turn on/off lights */
	int R(rand() % 7);
	switch (key) {
	case ' ':
		shootings.push_back(cannon.front());
		cannon.erase(cannon.begin());
		cannon.push_back(Sphere(cannon[0]));
		cannon[0].setCenter(0.0f, 50.0f, 0.0f);
		cannon[1].setMTL(materials[R]);
		cout << R << endl;
		(shootings.end() - 1)->setCenter(50 * sin(angle * PI / 180), 50 * cos(angle * PI / 180), 0.0f);
		(shootings.end() - 1)->setVelocity(speed * sin(angle * PI / 180), speed * cos(angle * PI / 180), 0.0f);
		cout << "TEST";
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
	glutCreateWindow("PUZZ LOOP");
	initialize();
	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}