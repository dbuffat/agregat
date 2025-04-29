#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <cmath>
#include "agregat.h"
#include <omp.h>

using namespace std;

int main()
{
	donnees D=LoadData();

	int n=omp_get_num_procs();

	#pragma omp parallel for
	for (int i=0;i<n;i++)
	{
		std::stringstream ss;
		ss<<i+1;
		string s;
		ss>>s;
		if(D.generation_rayon==false)
			Simulation(D,s);
		else
			SimulationRayon(D,s);
	}

	return 0;
}