#ifndef OGL_H
#define OGL_H

extern void handleKeypress(unsigned char key, int x, int y);
extern float gluposx, gluposy, gluposz, glunax, glunay, glunaz, glurotx, gluroty, glurotz;
extern void initRendering(), drawScene(), handleResize(int w, int h);
#endif