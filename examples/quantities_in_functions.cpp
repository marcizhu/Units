#include <iostream>

#include "Units/Constants.h"
#include "Units/Units.h"
#include "Units/IO.h"

using namespace Units;

Quantity work(const Quantity& force, const Quantity& dx)
{
	return force * dx; // Defines the relation: work = force * distance.
}

int main()
{
	Quantity force  = 2.0 * N;         // Define a quantity of force
	Quantity dx     = 3.0 * m;         // and a distance
	Quantity energy = work(force, dx); // and calculate the work done

	std::cout << "F  = " << force  << std::endl
	          << "dx = " << dx     << std::endl
	          << "E  = " << energy << std::endl;
}

/* Generated output:

F  = 2.000 N
dx = 3.000 m
E  = 6.000 J
*/
