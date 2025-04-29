#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include "agregat.h"

using namespace std;


//Methode de simulation sans conditions sur la generation des particules

void Simulation(const donnees &Values, string number)
{
	srand(time(NULL));

	int time=clock();

	int Way=0;
	Agregat Blob(Values);
	Blob.Initialisation(Values);

	vector<int> Grain(2);

	for(int m=1; m<=Values.nombre; m++)
	{
		if(number=="1")
			cout<<'\r'<<"Simulation en cours : "<<m<<" / "<<Values.nombre<<flush;
			
		do
		{
			Grain=Particule(Values.taille);
		}while(Blob.ConditionGeneration(Grain[0],Grain[1])==false);

		while(Blob.ConditionDirection(Grain[0],Grain[1])==false || Blob.GlueProba(Values.proba)==false)
		{
			Way=Direction();

			if(Way==1)
				Grain[0]+=Marche(Values.pas);
			else if(Way==2)
				Grain[1]+=Marche(Values.pas);
			else if(Way==3)
				Grain[0]-=Marche(Values.pas);
			else
				Grain[1]-=Marche(Values.pas);
		}

		if(Blob.BordCheck()==false)
			Blob.Stock(m, Grain[0], Grain[1]);
	}
	Blob.Imprimante(number);
	
	Blob.CalculFractale(number);

	double temps=(clock()-(double)time)/CLOCKS_PER_SEC;

	cout<<endl<<"Temps d'execution du programme "<<number<<" : "<<temps<<" secondes"<<endl;
}


//Methode de simulation avec une condition sur la generation des coordonnees des particules

void SimulationRayon(const donnees &Values, string number)
{
	srand(time(NULL));

	int time=clock();

	int Way=0;
	Agregat Blob(Values);
	Blob.Initialisation(Values);

	vector<int> Grain(2);

	for(int m=1; m<=Values.nombre; m++)
	{
		if(number=="1")
			cout<<'\r'<<"Simulation en cours : "<<m<<" / "<<Values.nombre<<flush;
		
		Grain=ParticuleRayon(Blob.RayonAgregat(), Values.fonction_rayon, Blob.Centre());			

		while(Blob.ConditionDirectionRayon(Grain[0], Grain[1])==false || Blob.GlueProba(Values.proba)==false)
		{
			Way=Direction();

			if(Way==1)
				Grain[0]+=Marche(Values.pas);
			else if(Way==2)
				Grain[1]+=Marche(Values.pas);
			else if(Way==3)
				Grain[0]-=Marche(Values.pas);
			else
				Grain[1]-=Marche(Values.pas);
			
		}

		if(Blob.BordCheck()==false)
			Blob.Stock(m, Grain[0], Grain[1]);	
	}
	Blob.Imprimante(number);

	Blob.CalculFractale(number);

	double temps=(clock()-(double)time)/CLOCKS_PER_SEC;

	cout<<endl<<"Temps d'execution du programme "<<number<<" : "<<temps<<" secondes"<<endl;
}