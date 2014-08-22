#ifndef blok_h
#define blok_h

class Blok
{
public:
	double h[20];
	double t;
	void compute_temperature(const int &i, const int &j), heat_transfer(const int &i, const int &j);
	void padanieskal(int i, int j);
	void padaniesute(int i, int j);
	void spravtvar(int i,int j);
	int tvar;
};

#endif