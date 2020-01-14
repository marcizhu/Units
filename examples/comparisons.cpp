#include <iostream>

#include "Units/Units.h"
#include "Units/IO.h"

using namespace Units;

Quantity work(const Quantity& F, const Quantity& dx)
{
	// If the unit of the parameter F is not Newton (N), throw
	if(F.unit() != N) throw "Invalid quantity!";

	return F * dx;
}

int main()
{
	Quantity dx = 5.0 * m;

	Quantity A = work(2.0 * N, dx); // this doesn't throw
	Quantity B = work(2.0 * J, dx); // this one does throw
}
