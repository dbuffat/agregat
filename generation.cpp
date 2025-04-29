#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include "agregat.h"

using namespace std;


//Chargement de la data depuis Data.txt

donnees LoadData()
{
	donnees D;
	string poubelle;

	fstream f;
	f.open("Data/Data.txt", ios::in);

	f>>poubelle>>D.taille;
	f>>poubelle>>D.nombre;
	f>>poubelle>>D.pas;
	f>>poubelle>>D.proba;
	f>>poubelle>>D.generation_rayon;
	f>>poubelle>>D.fonction_rayon;
	f>>poubelle>>D.rayon_initial;
	f>>poubelle>>D.rayon_max;
	f>>poubelle>>D.nombre_grains;

	D.x_grains.resize(D.nombre_grains);
	D.y_grains.resize(D.nombre_grains);

	for(int ind=0; ind<D.nombre_grains; ind++)
		f>>D.x_grains[ind]>>D.y_grains[ind];

	f.close();

	return D;
}



//Generation aleatoire d'une particule sur la grille

vector<int> Particule(int t)											
{
	vector<int> particule(2);

	particule[0]=rand()%t;
	particule[1]=rand()%t;

	return particule;
}



//Generation aleatoire d'une particule dans un cercle

vector<int> ParticuleRayon(int Rayon, double Fonction, vector<int> Centre)
{
	vector<int> particule(2);

	double angle = (double)rand()/(RAND_MAX) * 2*M_PI;

	particule[0] = Centre[0] + round((Rayon*Fonction)*cos(angle));
	particule[1] = Centre[1] + round((Rayon*Fonction)*sin(angle));

	return particule;
}



//Generation aleatoire de la direction du pas de la particule

int Direction()														
{
	double direction=0;

	direction=((double)rand()/(RAND_MAX));

	if(direction>=0 && direction<0.25)
		direction=1;
	else if(direction>=0.25 && direction<0.5)
		direction=2;
	else if(direction>=0.5 && direction<0.75)
		direction=3;
	else
		direction=4;

	return direction;
}



//Generation aleatoire de la valeur du pas

int Marche(int pied)													
{
	int pas=0;

	if(pied!=0)
		pas=rand()%pied + 1;

	else
		pas=pied+1;

	return pas;
}