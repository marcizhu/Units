#include <iostream>

#include "Units/Constants.h"
#include "Units/Units.h"
#include "Units/IO.h"

using namespace Units;

int main()
{
	Quantity earth_mass   = 5.972e24 * kg;
	Quantity earth_radius = 6371.0   * km;

	Quantity gravity = Constants::Physics::G * earth_mass / (earth_radius^2);

	std::cout << "Calculated earth gravity:  " << gravity << std::endl;
	std::cout << "Theoretical earth gravity: " << Constants::Physics::g << std::endl;
}

/* Generated output:

Calculated earth gravity:  9.820 m/s²
Theoretical earth gravity: 9.807 m/s²
*/
