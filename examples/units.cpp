#include <iostream> // for std::cout

#include "Units/Units.h" // provides commonly used units and conversions
#include "Units/Unit.h" // for Units::Unit
#include "Units/IO.h" // provides operator<< for units & quantities

int main()
{
	using namespace Units;

	Unit velocity = meter / second; // Now velocity is a unit of "m/s"
	Unit vel = m / s; // same as before, but using short unit names
	Unit accel = m / (s^2); // accleration, in m/s^2
	Unit power1 = W; // Watt
	Unit power2 = J / s; // Same as W

	Unit input1, input2;
	std::cin >> input1; // Read unit from std::cin
	from_string("Sv", input2); // Read unit from string. input2 == Units::Sv (Sievert)

	std::cout << velocity << std::endl; // Will print "m/s"
	std::cout << accel << std::endl; // Will print "m/s²"
	std::cout << power1 << std::endl; // Will print "W"
	std::cout << power2 << std::endl; // Will print "W"

	std::string formatted = to_string(accel); // formatted == "m/s²"
}
