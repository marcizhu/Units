#include <iostream>

#include "Units/Units.h"
#include "Units/IO.h"

using namespace Units;

Quantity work(const Quantity& force, const Quantity& dx)
{
	// If the unit of the parameter F is not Newton (N), throw
	if(force.unit() != N) throw "Invalid quantity!";

	return force * dx;
}

int main()
{
	Quantity dx = 5.0 * m;

	Quantity X = work(2.0 * N, dx); // this doesn't throw
	Quantity Y = work(2.0 * J, dx); // this one does throw
}
