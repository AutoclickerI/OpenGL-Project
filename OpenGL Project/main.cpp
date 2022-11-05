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
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();
	for (vector<Sound>::size_type i = 0; i < sound.size(); i++){
		sound[i].releasesound();
	}
	return 0;
}