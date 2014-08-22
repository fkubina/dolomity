#include "global.h"
#include "blok.h"
#include "vec3f.h"

Blok a[nx][ny]; 

int kolo=0;
void update(int value) {
	kolo++;
	kolo%=4;
	hlavna(kolo);

	if (kolo%2==0)
		glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Dolomity");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	//zapinanie, nulovanie, priprava
	FORALL {
		int dh=rand()%100;
		for (int k=1;k<nmat;k++) {
			a[i][j].h[k]=5+dh/1000;
		}
		a[i][j].h[0]=0;
		a[i][j].t=20;
	}

	glutTimerFunc(25, update, 0); //Add a timer
	glutMainLoop();
	return 0;
}
