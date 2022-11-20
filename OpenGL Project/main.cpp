#include "Initilize.h"

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
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(SpecialInput);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}