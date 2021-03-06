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

void PrintInitialValues(int, double, double, double *, double *, int);
void PrintFinalValues(int, double *, double *);


int main()
{
	int IntegrationPoints;  // Integration points
	double FinalTime;       // End time of calculation (in years)
	int Dimension;           // No. of spatial dimensions

	cout << "Earth-Sun system (Velocity Verlet)" << endl;
	Dimension = 2;

	IntegrationPoints = 10000;
	FinalTime = 200.;

	double TimeStep = FinalTime / ((double)IntegrationPoints); //Calculates the time step
	double x[2], v[2];  // positions and velocities
	// initial position x = 1AU, y = z = 0, vx = 2pi, vy=0, vz=0
	double r0 []= {1.0,0.0};
	double v0 []= {0.0,6.3};

	//DEFINE ALL PLANETS AND SOLVER SYSTEM

	planet planet1(0.000003, 1.0, 0.0, 0.0, 6.3); // Earth: (relative mass,x,y,vx,vy)
	planet planet2(1., 0.0, 0.0, 0.0, 0.0);           // Sun

	
	solver earthsun_vv;

	//Add planets to solver

	earthsun_vv.add(planet2);
	earthsun_vv.add(planet1);


	PrintInitialValues(Dimension, TimeStep, FinalTime, r0, v0, IntegrationPoints);

    //Solving of the ODE's and simulation of the whole system
	earthsun_vv.VelocityVerlet(Dimension, IntegrationPoints, FinalTime, 2);
	
	for (int j = 0; j < Dimension; j++) {
		x[j] = earthsun_vv.all_planets[1].position[j];
		v[j] = earthsun_vv.all_planets[1].velocity[j];
	}
	PrintFinalValues(Dimension, x, v);
	return 0;
}



void PrintInitialValues(int Dimension, double TimeStep, double FinalTime, double *x_initial, double *v_initial, int N) {
	// A function that prints out the set up of the calculation

	cout << "Time step = " << TimeStep << "; final time = " << FinalTime << "; integration points = " << N << endl;

	cout << "Initial position = ";
	for (int j = 0; j < Dimension; j++) cout << x_initial[j] << " ";
	cout << endl;

	cout << "Initial velocity = ";
	for (int j = 0; j < Dimension; j++) cout << v_initial[j] << " ";
	cout << endl;
}

void PrintFinalValues(int Dimension, double *x_final, double *v_final) {
	// A function that prints out the final results of the calculation

	cout << "Final position = ";
	for (int j = 0; j < Dimension; j++) cout << x_final[j] << " ";
	cout << endl;

	cout << "Final velocity = ";
	for (int j = 0; j < Dimension; j++) cout << v_final[j] << " ";
	cout << endl;
}