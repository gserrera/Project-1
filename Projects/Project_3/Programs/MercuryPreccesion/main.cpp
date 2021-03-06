// This code uses standard c++ allocation of arrays

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <random>
#include <chrono>
#include <time.h>
#include "planet.h"
#include "solver.h"


using namespace std;


int main()
{
	int IntegrationPoints;  // Integration points
	double FinalTime;       // End time of calculation (in years)
	int Dimension;           // No. of spatial dimensions

	cout << "Mercury preccesion(Velocity Verlet)" << endl;
	Dimension = 2;
	int relativity;

	cout << "Introduce the type of gravitational force (0 for Newtonian, 1 for general relativity): ";
	cin >> relativity;

	IntegrationPoints = 100000000;
	FinalTime = 100.0;

	double TimeStep = FinalTime / ((double)IntegrationPoints); //Calculates the time step
	// initial position x = 1AU, y = z = 0, vx = 2pi, vy=0, vz=0

	//DEFINE ALL PLANETS AND SOLVER SYSTEM

	planet planet1(0.000000165, 0.3075, 0.0, 0.0, 12.44); // Mercury: (relative mass,x,y,vx,vy)
	planet planet2(1., 0.0, 0.0, 0.0, 0.0);           // Sun

	
	solver mercury_vv;

	//Add planets to solver

	mercury_vv.add(planet1);
	mercury_vv.add(planet2);




    //Solving of the ODE's and simulation of the whole system
	mercury_vv.VelocityVerlet(Dimension, IntegrationPoints, FinalTime, 2, relativity);
	

	return 0;
}