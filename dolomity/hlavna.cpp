#include "global.h"
#include "blok.h"
#include "vec3f.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

const int nmat=5; //nmat +1
bool b[400][400];
double tokx[nx][ny];
double toky[nx][ny];
int indx,indy,indx2,indy2;
double dif,q;

void hlavna(int kolo) {
	FORALL {
		tokx[i][j]*=0.9;
		toky[i][j]*=0.9;
	}

if (kolo==0)
	{
	//rast
	srand(time(NULL));
	double indw;
	indw=rand()+nx;
	indx=(int)indw;
	indw=rand()+ny;
	indy=(int)indw;

	float ddh=0.1f;
	for (int k=1;k<nmat;k++)
		{
		a[(indx+1)%nx][(indy+1)%ny].h[k]+=ddh;
		a[(indx+1)%nx][(indy)%ny].h[k]+=ddh;
		a[(indx+1)%nx][(indy-1)%ny].h[k]+=ddh;
		a[(indx)%nx][(indy+1)%ny].h[k]+=ddh;
		a[(indx)%nx][(indy)%ny].h[k]+=2*ddh;
		a[(indx)%nx][(indy-1)%ny].h[k]+=ddh;
		a[(indx-1)%nx][(indy+1)%ny].h[k]+=ddh;
		a[(indx-1)%nx][(indy)%ny].h[k]+=ddh;
		a[(indx-1)%nx][(indy-1)%ny].h[k]+=ddh;
		}
	for (int ii=-2;ii<3;ii++)
	for (int jj=-2;jj<3;jj++)
	for (int k=1;k<nmat;k++)
		a[(indx+ii)%nx][(indy+jj)%ny].h[k]+=ddh;

	//teplota
	for (int i=0;i<nx;i++)
	for (int j=0;j<ny;j++)
		a[i][j].compute_temperature(i,j);
	//sneh
	for (int i=0;i<nx;i++)
	for (int j=0;j<ny;j++)
		a[i][j].h[4]+=0.01;
	
	for (int i=0;i<nx;i++)
	for (int j=0;j<ny;j++)
		{
		q=0; //topenie
		if (a[i][j].h[4]<10)
			{
			//q=(10-a[i][j].h[4])/50;
			q=a[i][j].t/1000;
			if (q<0) q=0;
			}
		dif=a[i][j].h[4]-a[i][j].h[3];
		if (dif<q)
			{
			a[i][j].h[3]+=dif/10;
			a[i][j].h[4]=a[i][j].h[3];
			}
		else
			{
			a[i][j].h[3]+=q/10;
			a[i][j].h[4]-=9*q/10;
			}
		}
	}

//tecenie vody
for (int ca=0;ca<9;ca++)
{
for (int i=0;i<nx;i++)
for (int j=0;j<ny;j++)
	{
	b[i][j]=true;
	}

for (int k=0;k<ny*nx;k++)
	{
	double min=9999999;
	for (int i=0;i<nx;i++)
	for (int j=0;j<ny;j++)
		{
		if (b[i][j])
		if (a[i][j].h[2]<min)
			{
			min=a[i][j].h[2];
			indx=i;
			indy=j;
			}
		}

	b[indx][indy]=false;

	//if (indy==0) //vysusenie na okraji
	//	{
	//	a[indx][indy].h[4]+=a[indx][indy].h[2]-a[indx][indy].h[3];
	//	a[indx][indy].h[3]=a[indx][indy].h[2];
	//	}
	//else
		{
		indx2=indx;
		indy2=indy;
		min=a[indx][indy].h[3];
		if (indx>0) if (a[indx-1][indy].h[3]<min)
			{
			min=a[indx-1][indy].h[3];
			indx2=indx-1;
			indy2=indy;
			}
		if (indx<nx-1) if (a[indx+1][indy].h[3]<min)
			{
			min=a[indx+1][indy].h[3];
			indx2=indx+1;
			indy2=indy;
			}
		if (indy>0) if (a[indx][indy-1].h[3]<min)
			{
			min=a[indx][indy-1].h[3];
			indy2=indy-1;
			indx2=indx;
			}
		if (indy<ny-1) if (a[indx][indy+1].h[3]<min)
			{
			min=a[indx][indy+1].h[3];
			indy2=indy+1;
			indx2=indx;
			}
		if ((indx2+indy2)!=(indx+indy))
			{
			//stecenie na najnizsi

			//stecenie vsetkeho
			if (a[indx][indy].h[2]>a[indx2][indy2].h[3])
					{
					dif=a[indx][indy].h[3]-a[indx][indy].h[2];
					a[indx2][indy2].h[3]+=dif;
					a[indx2][indy2].h[4]+=dif;
					a[indx][indy].h[3]-=dif;
					a[indx][indy].h[4]-=dif;
					}
			//vyrovnanie hladin
			else
				{
				dif=a[indx][indy].h[3]-a[indx2][indy2].h[3];
				dif/=2;
				a[indx2][indy2].h[3]+=dif;
				a[indx2][indy2].h[4]+=dif;
				a[indx][indy].h[3]-=dif;
				a[indx][indy].h[4]-=dif;
				//dif=0;
				}

			//vyratanie tokov;
			if (indx>indx2)
				tokx[indx2][indy]+=dif;
			if (indx<indx2)
				tokx[indx][indy]+=dif;
			if (indy>indy2)
				toky[indx][indy2]+=dif;
			if (indy<indy2)
				toky[indx][indy]+=dif;
			
			//erozia
			//dif*=0.5;
			dif=dif*(a[indx][indy].h[2]-a[indx2][indy2].h[2]);

			if (dif>0.00001)
				{
				bool eroziaskaly=false;
				bool strmak=false;
				bool sikmak=true;
				if (dif>a[indx][indy].h[2]-a[indx][indy].h[1])
					eroziaskaly=true;

				if (a[indx][indy].h[2]-a[indx2][indy2].h[2]>0.2) strmak=true;
				if (a[indx][indy].h[2]-a[indx2][indy2].h[2]>0.1) sikmak=true;

				if (a[indx][indy].h[2]-dif<a[indx2][indy2].h[2])
						{
						dif=a[indx][indy].h[2]-a[indx2][indy2].h[2];
						dif/=2;
						if (dif<0) dif=0;
						}					
				
				if (sikmak)
					{
					a[indx2][indy2].h[2]+=dif;
					a[indx2][indy2].h[3]+=dif;
					a[indx2][indy2].h[4]+=dif;

					q=a[indx][indy].h[2]-a[indx][indy].h[1];
					if (dif<q) q=dif;
					a[indx][indy].h[2]-=q;
					a[indx][indy].h[3]-=q;
					a[indx][indy].h[4]-=q;

					if (eroziaskaly) if (dif>q+0.000001) 
						{
						if (strmak)
							{
							q=(dif-q)/2;
							a[indx][indy].h[1]-=q;
							a[indx][indy].h[2]-=q;
							a[indx][indy].h[3]-=q;
							a[indx][indy].h[4]-=q;
							}
						}
					}
				}
			}
		}
	}

//vyparenie na hrane, odnos nanosov
for (int i=0;i<nx;i++)
	{
	//dif=a[i][ny-1].h[3]-a[i][ny-1].h[1];
	if (a[i][ny-1].h[1]>0.5) a[i][ny-1].h[1]-=(a[i][ny-1].h[3]-a[i][ny-1].h[2])/10;
	a[i][ny-1].h[2]=a[i][ny-1].h[1];
	a[i][ny-1].h[3]=a[i][ny-1].h[1];
	a[i][ny-1].h[4]=a[i][ny-1].h[1];
	}
}//koniec vodneho cyklu

//tecenie ladu
for (int ca=0;ca<1;ca++)
{
for (int i=0;i<nx;i++)
for (int j=0;j<ny;j++)
	{
	b[i][j]=true;
	}

for (int k=0;k<ny*nx;k++)
	{
	double min=9999999;
	for (int i=0;i<nx;i++)
	for (int j=0;j<ny;j++)
		{
		if (b[i][j])
		if (a[i][j].h[3]<min)
			{
			min=a[i][j].h[3];
			indx=i;
			indy=j;
			}
		}

	b[indx][indy]=false;
	//if (a[indx][indy].h[3]-a[indx][indy].h[2]>1) //tecu iba velke lady

		{
		indx2=indx;
		indy2=indy;
		min=a[indx][indy].h[4];
		if (indx>0) if (a[indx-1][indy].h[4]<min)
			{
			min=a[indx-1][indy].h[4];
			indx2=indx-1;
			indy2=indy;
			}
		if (indx<nx-1) if (a[indx+1][indy].h[4]<min)
			{
			min=a[indx+1][indy].h[4];
			indx2=indx+1;
			indy2=indy;
			}
		if (indy>0) if (a[indx][indy-1].h[4]<min)
			{
			min=a[indx][indy-1].h[4];
			indy2=indy-1;
			indx2=indx;
			}
		if (indy<ny-1) if (a[indx][indy+1].h[4]<min)
			{
			min=a[indx][indy+1].h[4];
			indy2=indy+1;
			indx2=indx;
			}
		if ((indx2+indy2)!=(indx+indy))
			{
			//stecenie na najnizsi

			//stecenie vsetkeho
			if (a[indx][indy].h[3]>a[indx2][indy2].h[4])
					{
					dif=a[indx][indy].h[4]-a[indx][indy].h[3];
					a[indx2][indy2].h[4]+=dif;
					a[indx][indy].h[4]-=dif;
					}
			//vyrovnanie hladin
			else
				{
				dif=a[indx][indy].h[4]-a[indx2][indy2].h[4];
				dif/=2;
				a[indx2][indy2].h[4]+=dif;
				a[indx][indy].h[4]-=dif;
				//dif=0;
				}
			
			//erozia
			//dif*=0.5;
			dif=dif*(a[indx][indy].h[3]-a[indx2][indy2].h[3])*5;

			if (dif>0.00001)
				{
				bool eroziaskaly=false;
				bool sikmak=true;
				if (dif>a[indx][indy].h[2]-a[indx][indy].h[1])
					eroziaskaly=true;

				if (a[indx][indy].h[2]-a[indx2][indy2].h[2]>0.1) sikmak=true;

				if (a[indx][indy].h[2]-dif<a[indx2][indy2].h[2])
						{
						dif=a[indx][indy].h[2]-a[indx2][indy2].h[2];
						dif/=2;
						if (dif<0) dif=0;
						}					
				
				if (sikmak)
					{
					a[indx2][indy2].h[2]+=dif;
					a[indx2][indy2].h[3]+=dif;
					a[indx2][indy2].h[4]+=dif;

					q=a[indx][indy].h[2]-a[indx][indy].h[1];
					if (dif<q) q=dif;
					a[indx][indy].h[2]-=q;
					a[indx][indy].h[3]-=q;
					a[indx][indy].h[4]-=q;

					if (eroziaskaly) if (dif>q+0.000001) 
						{
						if (sikmak)
							{
							q=(dif-q)/2;
							a[indx][indy].h[1]-=q;
							a[indx][indy].h[2]-=q;
							a[indx][indy].h[3]-=q;
							a[indx][indy].h[4]-=q;
							}
						}
					}
				}
			}
		}
	}

//vyparenie na hrane, odnos nanosov
for (int i=0;i<nx;i++)
	{
	//dif=a[i][ny-1].h[3]-a[i][ny-1].h[1];
	if (a[i][ny-1].h[1]>0.5) a[i][ny-1].h[1]-=(a[i][ny-1].h[3]-a[i][ny-1].h[2])/10;
	a[i][ny-1].h[2]=a[i][ny-1].h[1];
	a[i][ny-1].h[3]=a[i][ny-1].h[1];
	a[i][ny-1].h[4]=a[i][ny-1].h[1];
	}
}//koniec ladoveho cyklu

//popadanie ladovcov
for (int i=0;i<nx;i++)
for (int j=0;j<ny;j++)
if (a[i][j].h[4]-a[i][j].h[3]>1)
	{
	indx=(kolo+1)%4-2;
	indy=kolo%4-2;
	if (indx==-2) indx=0;
	if (indy==-2) indy=0;

	indx+=i;
	indy+=j;
	
	if (indx>-1) if (indx<nx) if (indy>-1) if (indy<ny)
	if (a[i][j].h[4]>a[indx][indy].h[4]+2)
		{
		a[i][j].h[4]--;
		a[indx][indy].h[4]++;
		}
	}

//padanie skal
for (int i=0;i<nx;i++)
for (int j=0;j<ny;j++)
	{
	if (rand()%8==0)
		{
		indx2=rand()%3-1;
		indy2=rand()%3-1;

		if (i+indx2>-1) if (i+indx2<nx) if (j+indy2>-1) if (j+indy2<ny)
			a[i][j].padanieskal(i+indx2,j+indy2);
		}
	}
//padanie sute
for (int i=0;i<nx;i++)
for (int j=0;j<ny;j++)
	{
	if (rand()%2==0)
		{
		indx2=rand()%3-1;
		indy2=rand()%3-1;

		if (indx2+i>-1) if (indx2+i<nx) if (indy2+j>-1) if (indy2+j<ny)
			a[indx][indy].padaniesute(i+indx2,j+indy2);
		}
	}
} 
