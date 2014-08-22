#include "global.h"
#include "math.h"

extern void vypni(void);
float fi=0;
float psi=-50;

	float gluposx=-5;
	float gluposy=5;
	float gluposz=0;
	
	float glunax=0;
	float glunay=5;
	float glunaz=0;
	
	float glurotx=0;
	float gluroty=1;
	float glurotz=0;

	float px,py,pz;

void handleKeypress(unsigned char key, int x, int y) {
	px=0;
	py=0;
	pz=0;
	switch (key) {
		case 27: //Escape key
			vypni();
			break;
		case 'a':
			fi-=5;
			break;
		case 'd':
			fi+=5;
			break;
		case 'w':
			psi+=5;
			break;
		case 's':
			psi-=5;
			break;
		case 'o':
			pz=1;
			break;
		case 'm':
			pz=-1;
			break;
		case 'i':
			px=-1;
			break;
		case 'k':
			px=1;
			break;
		case 'j':
			py=1;
			break;
		case 'l':
			py=-1;
			break;
	}	
	
	float pxx,pyy;
	pxx=px*cos(fi/360)-py*sin(fi/360);
	pyy=py*cos(fi/360)+px*sin(fi/360);

	gluposx-=pxx;
	gluposz-=pyy;
	gluposy+=pz;
	
	glunax=gluposx+5*cos(fi/360)*cos(psi/360);
	glunaz=gluposz+5*sin(fi/360)*cos(psi/360);
	glunay=gluposy+5*sin(psi/360);

	glurotx=0;
	gluroty=1;
	glurotz=0;
}