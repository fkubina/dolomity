#ifndef global_h
#define global_h
#include <iostream>
#include <stdlib.h>
#include "glut.h"
using namespace std;
#include "blok.h"
#include "mountains.h"
#include "ogl.h"

#define nx 30
#define ny 30
#define FORALL for (int i = 0; i<nx; i++) for (int j = 0; j<ny; j++)

extern float fi,psi;
extern void hlavna(int kolo);
extern const int nmat;

extern float z1,z2,z3,zupatie;
extern Blok a[nx][ny];
extern double tokx[nx][ny],toky[nx][ny];
#endif