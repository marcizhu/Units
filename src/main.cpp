#include <iostream>

#include "Units/Units.h"
#include "Units/IO.h"
#include "Units/Constants.h"
#include "Units/extras/StdAdditions.h"

// NOTE: Make example using imaginary units (VA, VAR, W). Maybe a small example with directions could also be helpful

int main()
{
	using namespace Units;

//	Quantity test = 23.5;
//	std::cout << test << std::endl;

	constexpr Quantity earth_mass   = 5.972e24 * kg;
	constexpr Quantity earth_radius = 6371.0 * km;

	constexpr Quantity gravity = Constants::Physics::G * earth_mass / (earth_radius^2);

	constexpr Quantity test1 = 15.0 * m;
	constexpr Quantity test2 = m * 15.0;
	constexpr Quantity test3 = m / 10.0;
	constexpr Quantity test4 = 15.0 / m;

	constexpr Quantity test5 = 15.0 * mile / h;

	std::cout << test1 << std::endl;
	std::cout << test2 << std::endl;
	std::cout << test3 << std::endl;
	std::cout << test4 << std::endl;
	std::cout << test5 << std::endl << std::endl;

	static_assert((1.0 * V / (kilo * m)) == (milli * V / m), "units not static equivalent");

	auto temp = std::sqrt(4.0 * Hz);

	std::cout << to_string(2.0 * std::sqrt(Hz)) << std::endl; 		// Should print 2.000 √Hz
	std::cout << to_string(5.0 * Hz * iflag) << std::endl;			// Should print 5.000 √Hz
	std::cout << to_string(7 * Hz) << std::endl;					// Should print 7.000 Hz
	std::cout << to_string(temp) << std::endl;						// Should print 2.000 √Hz
	std::cout << to_string(temp^2) << std::endl;					// Should print 4.000 Hz
	std::cout << to_string(temp * temp) << std::endl;				// Should print 4.000 Hz
	std::cout << to_string(9.87 * (s^-2)) << std::endl;				// Should print 9.870 Hz^2
	std::cout << to_string(V / (Hz * iflag)) << std::endl;			// Should print 1.000 V/√Hz
	std::cout << to_string(V * std::sqrt(Hz)) << std::endl;			// Should print 1.000 V*√Hz
	std::cout << to_string(Hz / std::sqrt(Hz)) << std::endl;		// Should print 1.000 √Hz
	std::cout << to_string((2.5 * A / temp) * temp) << std::endl;	// Should print 2.500 A
	std::cout << to_string((temp / A) * A) << std::endl;			// Should print 2.000 √Hz
	std::cout << to_string(25 * micro * A) << std::endl;			// Should print 25.00 uA
	std::cout << to_string(100.33 * kilo * ohm) << std::endl;		// Should print 100.3 kΩ
	std::cout << (12.0 * (std::sqrt(Hz)^4)) << std::endl;			// Should print 12.00 Hz^2
	std::cout << to_string_scientific(Constants::Physics::G) << std::endl;
	std::cout << to_string_scientific(Constants::Physics::R) << std::endl;

	std::cout << (((Hz * iflag)) == std::sqrt(Hz)) << std::endl;

	std::cout << "Calculated earth gravity:  " << gravity << std::endl;
	std::cout << "Theoretical earth gravity: " << Constants::Physics::g << std::endl;
	std::cout << "5 V * 3 A * 10 s = " << to_string(10 * rad / (5 * s)) << std::endl;
	std::cout << "15 N * 10 m = " << to_string(15 * N * 10 * m * rad / s) << std::endl << std::endl;

	static_assert((Log::dB / Hz) * Hz == Log::dB, "");

	std::cout << 20.0 * Log::dB / Hz << std::endl << std::endl;
	std::cout << 10.0 * ft << std::endl << std::endl;
	//std::cout << to_string(75.0 * W^-1) << std::endl << std::endl;
	std::cout << 25 * Log::dBm << std::endl;
	std::cout << 25 * Log::BmV << std::endl;
	std::cout << 50 * std::cbrt(CFM * min) << std::endl << std::endl;
	std::cout << 5000 * ppm << std::endl << std::endl; // < This has to be removed. No km, no mm, no short units

	std::cout << 5 * Log::dBmV << std::endl;
	std::cout << 5 * Log::dBuV << std::endl;
	std::cout << 5 * Log::dBc << std::endl;

	std::cout << 15 * Chinese::li << std::endl;
	std::cout << 72.8 * kilo * J / mol << std::endl;
	std::cout << 10.0 * kilo * g << std::endl;
	std::cout << 10.0 * milli * g << std::endl << std::endl;

	std::cout << 750 * std::sqrt(Pressure::mmHg^2) << std::endl;
	std::cout << 750 * std::sqrt(Pressure::torr^2) << std::endl;

	//std::string tempstr;
	Quantity unit;
	while(std::cin >> unit)
	{
		//from_string(tempstr, unit);
		std::cout << unit << std::endl;
	}
}
