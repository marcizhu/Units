#include <iostream> // for std::cout

#include "Units/Units.h" // provides commonly used units and conversions
#include "Units/Quantity.h" // for Units::Unit
#include "Units/IO.h" // provides operator<< for units & quantities
#include "Units/extras/StdAdditions.h" // provides common std:: math functions

int main()
{
	using namespace Units;

	Unit vel = meter / second;

	Quantity speed1 = 25.0 * m / s; // Represents 25 m/s
	Quantity speed2 = 25.0 * vel; // Same as above, but using a predefined unit
	Quantity speed3 = 60.0 * mile / h; // This will convert the 60.0 mph to m/s internally

	std::cout << speed1 << std::endl; // Will print "25.00 m/s"
	std::cout << speed2 << std::endl; // Will print "25.00 m/s"
	std::cout << speed3 << std::endl; // Will print "6.706 m/s"

	std::string formatted = to_string(speed1); // formatted == "25.00 m/s"

	Quantity input3;
	std::cin >> input3; // Read quantity from std::cin
	Quantity input4 = to_quantity("100.3 kHz"); // Read quantity from string. Represents 100.3 kilohertz

	// Comparison operators
	if(speed3 > speed1)
		std::cout << "60 mph > 25 m/s" << std::endl;

	// Arithmetic functions
	Quantity q1 = std::pow(speed1, 2); // 625 m²/s²
	Quantity q2 = speed1^2; // Same as above
	Quantity q3 = std::sqrt(q1); // 25 m/s again
}
