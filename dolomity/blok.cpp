#include "global.h"
#include "blok.h"

float max;
void Blok::heat_transfer(const int &i, const int &j) {
	int n = 10;
	t = 10 * t;
	if (i > 0) {
		t += a[i - 1][j].t;
		n++;
	}
	if (i < nx - 1) {
		t += a[i + 1][j].t;
		n++;
	}
	if (j > 0) {
		t += a[i][j - 1].t;
		n++;
	}
	if (j < ny - 1) {
		t += a[i][j + 1].t;
		n++;
	}
	t /= n;
}
void Blok::compute_temperature(const int &i, const int &j) {
	heat_transfer(i,j);
	if (j<ny-1) {
		t=t*0.9+0.1*(35-4*h[nmat-1]);
		//tien
		if (h[nmat-1]+1<a[i][j+1].h[nmat-1])
			t-=10;
		//svetlo
		if (h[nmat-1]>a[i][j+1].h[nmat-1]+1)
			t+=10;
	}
	else {
		t=a[i][j-1].t;
	}
}

void Blok::padanieskal(int i, int j)
{
	if (h[1]>a[i][j].h[nmat-1]+1)
		{
		double dif=h[1]-a[i][j].h[nmat-1];
		dif/=2;
		if (dif>1) dif=1;
	
		for (int k=2;k<nmat;k++)
			a[i][j].h[k]+=dif;
		for (int k=1;k<nmat;k++)
			h[k]-=dif;
		}
}

void Blok::padaniesute(int i, int j)
{
	if (h[2]>a[i][j].h[nmat-1]+0.3)
		{
		double dif=h[2]-a[i][j].h[nmat-1];
		dif/=2;
		if (dif>h[2]-h[1]) dif=h[2]-h[1];
	
		for (int k=2;k<nmat;k++)
			{
			a[i][j].h[k]+=dif;
			h[k]-=dif;
			}
		}
}

void Blok::spravtvar(int i, int j)
{

	float vys[4];
	if (i>0)	vys[0]=a[i-1][j].h[nmat-1]; else vys[0]=a[i][j].h[nmat-1];
	if (i<nx-1) vys[1]=a[i+1][j].h[nmat-1]; else vys[1]=a[i][j].h[nmat-1];
	if (j>0)	vys[2]=a[i][j-1].h[nmat-1]; else vys[2]=a[i][j].h[nmat-1];
	if (j<ny-1) vys[3]=a[i][j+1].h[nmat-1]; else vys[3]=a[i][j].h[nmat-1];
		
	for (int ii=0;ii<3;ii++)
	for (int jj=ii+1;jj<4;jj++)
		{
		if (vys[ii]>vys[jj]) 
			{
			max=vys[jj];
			vys[jj]=vys[ii];
			vys[ii]=max;
			}
		}
	max=vys[3];

	if (max<h[nmat-1])
		tvar=1;

	int vrcholy=0;
	if (i>0)	if (a[i-1][j].h[nmat-1]>h[nmat-1]) vrcholy+=1;
	if (j>0)	if (a[i][j-1].h[nmat-1]>h[nmat-1]) vrcholy+=10;
	if (i<nx-1)	if (a[i+1][j].h[nmat-1]>h[nmat-1]) vrcholy+=100;
	if (j<ny-1) if (a[i][j+1].h[nmat-1]>h[nmat-1]) vrcholy+=1000;
	
	//sikmy
	/*
		if (vrcholy==1) tvar=11;
		if (vrcholy==10) tvar=12;
		if (vrcholy==100) tvar=13;
		if (vrcholy==1000) tvar=14;
		*/
	
	//chybajuci roh
		if (vrcholy==1100) tvar=21;
		if (vrcholy==1001) tvar=22;
		if (vrcholy==11) tvar=23;
		if (vrcholy==110) tvar=24;

	if (tvar==1)
		{
		zupatie=max;
		if (zupatie<z1) zupatie=z1;
		}
	if ((tvar>20)&&(tvar<25))
		{
		zupatie=vys[1]; //druhy najvyssi
		if (zupatie<z1) zupatie=z1;

		if (z2-zupatie<0.05) tvar=1;
		}
}