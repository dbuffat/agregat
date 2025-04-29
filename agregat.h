#ifndef AGREGAT_H_INCLUDED
#define AGREGAT_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Recuperation des donnees

struct donnees
{
	int taille;
	int nombre;
	int pas;
	double proba;
	bool generation_rayon;
	double fonction_rayon;
	int rayon_initial;
	double rayon_max;
	int nombre_grains;
	vector<int> x_grains;
	vector<int> y_grains;
};


//Declaration de la classe

class Agregat
{
	protected:
		int Taille;
		int Nombre;
		double Rayon;
		double RayonMax;
		double FonctionRayon;
		double RayonInitial;
		bool Wall;
		vector<int> X;
		vector<int> Y;
		vector<vector<bool>> Map;
		vector<int> CdM;

	public:
		Agregat(const donnees &D);
		~Agregat();
		int RayonAgregat();
		void Initialisation(const donnees &D);
		double Distance(int x, int y);
		bool MapCheck(int i, int j);
		bool GlueCheck(int x, int y);
		bool BordCheckRayon(int x, int y);
		bool ConditionDirectionRayon(int x, int y);
		bool BordCheck(int x, int y);
		bool ConditionGeneration(int x, int y);
		bool ConditionDirection(int x, int y);
		void Stock(int ind, int i, int j);
		void Imprimante(string n);
		bool BordCheck();
		void CalculFractale(string n);
		bool GlueProba(double p);
		void FindRayonMax();
		vector<int> Centre();
};


//Methode des autres cpp

donnees LoadData();
vector<int> Particule(int a);
vector<int> ParticuleRayon(int a, double b, vector<int> c);
int Direction();
int Marche(int p);

void SimulationRayon(const donnees &D, string n);
void Simulation(const donnees &D, string n);

#endif