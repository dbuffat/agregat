#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "agregat.h"

using namespace std;



//**************************************//
// Definition des methodes de la classe //
//**************************************//

//Constructeur de la classe avec calcul du centre de masse
Agregat::Agregat(const donnees &values) : Taille(values.taille), Nombre(values.nombre), FonctionRayon(values.rayon_max)
{
	Map.resize(Taille, vector<bool> (Taille, false));
	X.resize(Nombre, 0);
	Y.resize(Nombre, 0);

	int moyenne_x=0;
	int moyenne_y=0;
	vector<int> R_Max(2);

	R_Max[0]=values.x_grains[0];
	R_Max[1]=values.y_grains[0];

	for(int ind=0; ind<values.nombre_grains; ind++)
	{
		moyenne_x+=values.x_grains[ind];
		moyenne_y+=values.y_grains[ind];

		if(values.x_grains[ind]*values.x_grains[ind]+values.y_grains[ind]*values.y_grains[ind]>R_Max[0]*R_Max[0]+R_Max[1]*R_Max[1])
		{
			R_Max[0]=values.x_grains[ind];
			R_Max[1]=values.y_grains[ind];
		}
	}

	CdM.resize(2);

	CdM[0]=moyenne_x/values.nombre_grains;
	CdM[1]=moyenne_y/values.nombre_grains;
	Rayon=sqrt(R_Max[0]*R_Max[0]+R_Max[1]*R_Max[1])-sqrt(CdM[0]*CdM[0]+CdM[1]*CdM[1]);
	RayonInitial=Rayon+values.rayon_initial;

	FindRayonMax();
}



Agregat::~Agregat(){}



int Agregat::RayonAgregat()
{
	int retour=round(Rayon);

	if(retour<=Rayon)
		retour++;

	return retour;
}


//Initialisation de la Map

void Agregat::Initialisation(const donnees &values)
{
	for(int ind=0; ind<values.nombre_grains; ind++)
	{
		X[ind]=values.x_grains[ind];
		Y[ind]=values.y_grains[ind];
		Map[X[ind]][Y[ind]]=true;
	}
}


//Calcul de la distance depuis le Centre de Masse (CdM)

double Agregat::Distance(int a, int b)
{
	return sqrt((a-CdM[0])*(a-CdM[0])+(b-CdM[1])*(b-CdM[1]));
}


//Verifie si la case est deja occuper

bool Agregat::MapCheck(int i, int j)											
{
	return Map[i][j];
}


//Verifie si la particule en touche une autre

bool Agregat::GlueCheck(int x, int y)						
{
	bool GlueTest=false;

	if(MapCheck(x+1,y)==true || MapCheck(x-1,y)==true || MapCheck(x,y+1)==true || MapCheck(x,y-1)==true)
		GlueTest=true;

	return GlueTest;	
}


//Verifie si l'on peut abandonner la particule dans une simulation en rayon

bool Agregat::BordCheckRayon(int x, int y)
{
	bool BordTest=false;

	if((Distance(x,y)<RayonMax-1) && (RayonAgregat()*FonctionRayon<RayonMax-1))		//Securite au cas ou le rayon est superieur a la demi-taille de la grille
	{
		if(Distance(x,y)>RayonAgregat()*FonctionRayon)
			BordTest=true;
	}
	else
	{
		if(x<=1 || x>=(Taille-2) || y<=1 || y>=(Taille-2))
			BordTest=true;
	}

	Wall=BordTest;
	return BordTest;
}


//Condition pour les boucles dans les simulations

bool Agregat::ConditionDirectionRayon(int x, int y)
{
	if(BordCheckRayon(x,y)==true)
		return true;
	else if(GlueCheck(x,y)==true && MapCheck(x,y)==false)
		return true;
	else
		return false;
}


//Verifie si l'on est au bord de la grille

bool Agregat::BordCheck(int x, int y)
{
	bool BordTest=false;

	if(x<=1 || x>=(Taille-2) || y<=1 || y>=(Taille-2))
		BordTest=true;

	Wall=BordTest;
	return BordTest;
}


//Condition pour les boucles de simulation

bool Agregat::ConditionGeneration(int x, int y)
{
	if(MapCheck(x,y)==false && BordCheck(x,y)==false)
		return true;

	else
		return false;
}


//Condition pour les boucles de simulation

bool Agregat::ConditionDirection(int x, int y)
{
	if(BordCheck(x,y)==true)
		return true;
	else if(GlueCheck(x,y)==true && MapCheck(x,y)==false)
		return true;
	else
		return false;
}


//Stockage des coordonnees de la nouvelle particule de l'agregat

void Agregat::Stock(int ind, int i, int j)  											
{
	X[ind]=i;
	Y[ind]=j;
	Map[i][j]=true;

	double R=Distance(i, j);

	if(R>Rayon)
		Rayon=R;
}


//Stockage des donnees dans un ficher .txt

void Agregat::Imprimante(string number)													
{
	fstream f;
	f.open("Data/DonneesAgregat_"+number+".txt", ios::out);
	int numero=0;

	for(int i=0; i<Nombre; i++)
	{
		if(X[i]!=0 && Y[i]!=0)
		{
			f<<X[i]<<" "<<Y[i]<<" "<<numero<<endl;
			numero++;
		}
	}

	f.close();
}


//Retourne la valeur de wall pour gagner en temps de calcul

bool Agregat::BordCheck()
{
	return Wall;
}


//Probabilite de collage de la particule

bool Agregat::GlueProba(double p)
{
	double t = (double)rand()/(RAND_MAX);

	if(t<=p)
		return true;
	else
		return false;
}


//Cherche le rayon maximal de l'agregat a l'interieur de la grille

void Agregat::FindRayonMax()
{
	vector<int> RayonTest(4);
	RayonTest[0]=CdM[0]+RayonInitial;
	RayonTest[1]=CdM[0]-RayonInitial;
	RayonTest[2]=CdM[1]+RayonInitial;
	RayonTest[3]=CdM[1]-RayonInitial;

	do{
		RayonTest[0]++;
		RayonTest[1]--;
		RayonTest[2]++;
		RayonTest[3]--;
	}while(RayonTest[1]!=0 && RayonTest[3]!=0 && RayonTest[0]!=Taille && RayonTest[2]!=Taille);

	if(RayonTest[0]==Taille)
		RayonMax=Taille-CdM[0];
	else if(RayonTest[1]==0)
		RayonMax=CdM[0];
	else if(RayonTest[2]==Taille)
		RayonMax=Taille-CdM[1];
	else
		RayonMax=CdM[1];
}


//Renvoi la position du CdM

vector<int> Agregat::Centre()
{
	return CdM;
}


/////////////////////////////////
////		Fractale		/////
/////////////////////////////////


//Calcul et stocke dans un .txt toutes les donnees permettant de connaitre la dimension fractale

void Agregat::CalculFractale(string number)
{
	int n;
	vector<double> R(0);
	vector<int> N(0);

	for(int i=RayonInitial+10; i<Rayon/3; i++)
	{
		R.push_back(i);
		n=0;

		for(int j=0; j<Nombre; j++)
		{
			if(X[j]!=0 && Y[j]!=0)
			{
				if(Distance(X[j], Y[j])<= i)
					n++;
			}
		}
		N.push_back(n);
	}

	fstream f;
	f.open("Data/DonneesFractale_"+number+".txt", ios::out);

	for(int i=0; i<R.size(); i++)
		f<<log10(R[i])<<" "<<log10(N[i])<<endl;

	f.close();
}