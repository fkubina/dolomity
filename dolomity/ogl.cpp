#include "global.h"
#include "imageloader.h"

float x, y, d;
float z1, z2, z3, zupatie;
GLuint tex_rock, tex_lake, tex_soil, tex_snow, tex_river, tex_grass, tex_forest;
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //vytvori "izbu pre texturu"
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,                //stale GL_TEXTURE_2D
		0,                            //0 pre teraz
		GL_RGB,                       //format OpenGL pouzivany pre obrazok
		image->width, image->height,
		0,                            //hranice obrazka
		GL_RGB,						//pixely su ulozene v RGB formate
		GL_UNSIGNED_BYTE,				//pixely su ulozene ako unsigned
		image->pixels);               //aktualne data pixelov
	return textureId; //vrati id textury
}

void vypni() {
	exit(0);
};

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading

	//Image* image = loadBMP("./img/rock1.bmp");
	Image* image = loadBMP("./img/rock3.bmp");
	tex_rock = loadTexture(image);

	image = loadBMP("./img/soil1.bmp");
	tex_soil = loadTexture(image);

	image = loadBMP("./img/water1.bmp");
	tex_lake = loadTexture(image);

	image = loadBMP("./img/snow1.bmp");
	tex_snow = loadTexture(image);

	image = loadBMP("./img/river1.bmp");
	tex_river = loadTexture(image);

	image = loadBMP("./img/grass1.bmp");
	tex_grass = loadTexture(image);

	image = loadBMP("./img/forest1.bmp");
	tex_forest = loadTexture(image);
	delete image;
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (double)w / (double)h, 1.0, 200.0);
}

void gltop(Blok a, int k) {

	if ((a.tvar == 1) && (a.h[nmat - 1] - a.h[k]<0.1))
	{
		glEnd();
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y);
		glTexCoord2f(1.0, 0.5);
		glVertex3f(x + d / 2, z2, y + d / 2);

		glNormal3f(0.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y + d);
		glTexCoord2f(1.0, 0.5);
		glVertex3f(x + d / 2, z2, y + d / 2);

		glNormal3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, zupatie, y + d);
		glTexCoord2f(1.0, 0.5);
		glVertex3f(x + d / 2, z2, y + d / 2);

		glNormal3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x + d, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y + d);
		glTexCoord2f(1.0, 0.5);
		glVertex3f(x + d / 2, z2, y + d / 2);

		z2 = zupatie;
		glEnd();
		glBegin(GL_QUADS);
	}

	else if ((a.tvar == 21) && (a.h[nmat - 1] - a.h[k]<0.1))
	{
		glEnd();
		glBegin(GL_TRIANGLES);
		glNormal3f(-1.0f, 1.0f, -1.0f);
		//sikmy
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, z2, y);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x, z2, y + d);

		//horny
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x, z2, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, z2, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, z2, y + d);

		//2 bocne
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, z2, y);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, zupatie, y + d);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x, z2, y + d);

		z2 = zupatie;
		glEnd();
		glBegin(GL_QUADS);
	}
	else if ((a.tvar == 22) && (a.h[nmat - 1] - a.h[k]<0.1))
	{
		glEnd();
		glBegin(GL_TRIANGLES);
		glNormal3f(1.0f, 1.0f, -1.0f);
		//sikmy
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x + d, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, z2, y + d);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x, z2, y);

		//horny
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x + d, z2, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, z2, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x, z2, y + d);

		//2 bocne
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x, z2, y);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x + d, zupatie, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y + d);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, z2, y + d);

		z2 = zupatie;
		glEnd();
		glBegin(GL_QUADS);
	}
	else if ((a.tvar == 23) && (a.h[nmat - 1] - a.h[k]<0.1))
	{
		glEnd();
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 1.0f, 0.0f);
		//horny
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, z2, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, z2, y);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x, z2, y + d);

		//sikmy
		glNormal3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x, z2, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, z2, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, zupatie, y + d);

		//2 bocne
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x + d, zupatie, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, z2, y);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x + d, zupatie, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, zupatie, y + d);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x, z2, y + d);

		z2 = zupatie;
		glEnd();
		glBegin(GL_QUADS);
	}
	else if ((a.tvar == 24) && (a.h[nmat - 1] - a.h[k]<0.1))
	{
		glEnd();
		glBegin(GL_TRIANGLES);
		glNormal3f(-1.0f, 1.0f, 1.0f);
		//sikmy
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, z2, y + d);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x, z2, y);

		//horny
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x + d, z2, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, z2, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, z2, y);

		//2 bocne
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, zupatie, y + d);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, z2, y + d);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, zupatie, y + d);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, zupatie, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x, z2, y);

		z2 = zupatie;
		glEnd();
		glBegin(GL_QUADS);
	}
	else if (a.tvar == 0)
	{
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x, z2, y);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x + d, z2, y);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + d, z2, y + d);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x, z2, y + d);
	}
}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//textury
	glEnable(GL_TEXTURE_2D); //povoli textury
	//	glEnable(GL_LINE_SMOOTH); //antialiasing hran
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear nearest
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Add ambient light
	GLfloat ambientColor[] = { 0.3f, 0.3f, 0.4f, 1.0f }; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add directed light
	GLfloat lightColor1[] = { 2.0f, 2.0f, 1.9f, 1.0f }; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { 0.0f, 1.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


	gluPerspective(50.0, 1.0, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(gluposx, gluposy, gluposz,
		glunax, glunay, glunaz,
		glurotx, gluroty, glurotz);

	d = 1.0f;

	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, tex_river);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear nearest
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	//toky	
	for (int i = 0; i<nx - 1; i++)
		for (int j = 0; j<ny - 1; j++)
		{
		x = i - nx / 2 + d / 2;
		y = j - ny / 2 + d / 2;
		z1 = a[i][j].h[2] + 0.01;
		z2 = a[i + 1][j].h[2] + 0.01;
		z3 = a[i][j + 1].h[2] + 0.01;

		double wid = (tokx[i][j]);
		wid = sqrt(wid) / 8;
		if (wid>0.03)
		{
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, z1, y - wid);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x + d / 2, z1, y - wid);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x + d / 2, z1, y + wid);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x, z1, y + wid);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x + d / 2, z2, y - wid);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x + d, z2, y - wid);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x + d, z2, y + wid);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x + d / 2, z2, y + wid);
		}
		wid = (toky[i][j]);
		wid = sqrt(wid) / 8;
		if (wid>0.03)
		{
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x - wid, z1, y);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x - wid, z1, y + d / 2);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x + wid, z1, y + d / 2);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x + wid, z1, y);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x - wid, z3, y + d / 2);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x - wid, z3, y + d);
			glTexCoord2f(1.0, 1.0);
			glVertex3f(x + wid, z3, y + d);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x + wid, z3, y + d / 2);
		}

		}
	glEnd();

	for (int i = 0; i<nx; i++)
		for (int j = 0; j<ny; j++)
			a[i][j].tvar = 0;

	glColor3f(1.0f, 1.0f, 1.0f);
	//bloky
	for (int k = 1; k<nmat; k++)
	{
		for (int i = 0; i<nx; i++)
			for (int j = 0; j<ny; j++)
			{

			//Front
			x = i - nx / 2;
			y = j - ny / 2;
			z1 = a[i][j].h[k - 1];
			z2 = a[i][j].h[k];

			//spicate
			a[i][j].spravtvar(i, j);

			if (z2 - z1>0.1)
			{
				if (k == 1) if (z2>5)
				{
					glBindTexture(GL_TEXTURE_2D, tex_rock);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear nearest
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
				else if (k == 1) if (z2>2)
				{
					glBindTexture(GL_TEXTURE_2D, tex_grass);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear nearest
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
				else if (k == 1)
				{
					glBindTexture(GL_TEXTURE_2D, tex_forest);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear nearest
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}

				if (k == 2) glBindTexture(GL_TEXTURE_2D, tex_soil);
				if (k == 3) glBindTexture(GL_TEXTURE_2D, tex_lake);
				if (k == 4) glBindTexture(GL_TEXTURE_2D, tex_snow);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //linear nearest
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glBegin(GL_QUADS);

				//top
				gltop(a[i][j], k);


				//ab
				glNormal3f(0.0f, 0.0f, -1.0f);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x, z1, y);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(x + d, z1, y);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(x + d, z2, y);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(x, z2, y);

				//bc
				glNormal3f(1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x + d, z1, y);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(x + d, z1, y + d);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(x + d, z2, y + d);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(x + d, z2, y);

				//ab
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x, z1, y + d);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(x + d, z1, y + d);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(x + d, z2, y + d);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(x, z2, y + d);

				//bc
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x, z1, y);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(x, z1, y + d);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(x, z2, y + d);
				glTexCoord2f(1.0, 0.0);
				glVertex3f(x, z2, y);

				glEnd();
			}
			}
	}

	glutSwapBuffers();
}