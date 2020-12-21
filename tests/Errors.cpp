#include <array>
#include <limits>

#include "Units/Units.h"
#include "Units/IO.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Unit errors", "[unit][error]")
{
	using namespace Units;

	std::array<Unit, 16> test_units = { m, s, kg, N, m / s, m / (s^2), N*m, A, C, ppm, count, currency, cal, mile, L, (m^3) };

	SECTION("error + error == error") { CHECK(error + error == error); }
	SECTION("error - error == error") { CHECK(error - error == error); }
	SECTION("error * error == error") { CHECK(error * error == error); }
	SECTION("error / error == error") { CHECK(error / error == error); }

	SECTION("error + unit == error") { for(Unit un : test_units) CHECK(error + un == error); }
	SECTION("error - unit == error") { for(Unit un : test_units) CHECK(error - un == error); }
	SECTION("error * unit == error") { for(Unit un : test_units) CHECK(error * un == error); }
	SECTION("error / unit == error") { for(Unit un : test_units) CHECK(error / un == error); }
	SECTION("unit + error == error") { for(Unit un : test_units) CHECK(un + error == error); }
	SECTION("unit - error == error") { for(Unit un : test_units) CHECK(un - error == error); }
	SECTION("unit * error == error") { for(Unit un : test_units) CHECK(un * error == error); }
	SECTION("unit / error == error") { for(Unit un : test_units) CHECK(un / error == error); }

	SECTION("error == error is true" ) { CHECK((error == error) == true ); }
	SECTION("error != error is false") { CHECK((error != error) == false); }
	SECTION("error  > error is false") { CHECK((error  > error) == false); }
	SECTION("error  < error is false") { CHECK((error  < error) == false); }
	SECTION("error >= error is true" ) { CHECK((error >= error) == true ); }
	SECTION("error <= error is true" ) { CHECK((error <= error) == true ); }

	SECTION("error == unit is false") { for(Unit un : test_units) CHECK((error == un) == false); }
	SECTION("error != unit is true" ) { for(Unit un : test_units) CHECK((error != un) == true ); }
	SECTION("error  > unit is false") { for(Unit un : test_units) CHECK((error  > un) == false); }
	SECTION("error  < unit is false") { for(Unit un : test_units) CHECK((error  < un) == false); }
	SECTION("error >= unit is false") { for(Unit un : test_units) CHECK((error >= un) == false); }
	SECTION("error <= unit is false") { for(Unit un : test_units) CHECK((error <= un) == false); }

	SECTION("unit == error is false") { for(Unit un : test_units) CHECK((un == error) == false); }
	SECTION("unit != error is true" ) { for(Unit un : test_units) CHECK((un != error) == true ); }
	SECTION("unit  > error is false") { for(Unit un : test_units) CHECK((un  > error) == false); }
	SECTION("unit  < error is false") { for(Unit un : test_units) CHECK((un  < error) == false); }
	SECTION("unit >= error is false") { for(Unit un : test_units) CHECK((un >= error) == false); }
	SECTION("unit <= error is false") { for(Unit un : test_units) CHECK((un <= error) == false); }
}

TEST_CASE("Quantity errors", "[quant][error]")
{
	using namespace Units;

	std::array<Quantity, 16> test_units =
		{
			5 * m, 10 * s, 2 * kg, 3 * N, 2 * m / s, 7 * m / (s^2), N*m, 1 * A, 2.3 * C,
			10.3 * ppm, 4.2 * count, 69 * currency, 77 * cal, 10 * mile, 0.20 * L, 1 * (m^3)
		};

	SECTION("error + error == error") { CHECK((Quantity(error) + Quantity(error)).unit() == error); }
	SECTION("error - error == error") { CHECK((Quantity(error) - Quantity(error)).unit() == error); }
	SECTION("error * error == error") { CHECK((Quantity(error) * Quantity(error)).unit() == error); }
	SECTION("error / error == error") { CHECK((Quantity(error) / Quantity(error)).unit() == error); }

	SECTION("error == error is true" ) { CHECK((error == error) == true ); }
	SECTION("error != error is false") { CHECK((error != error) == false); }
	SECTION("error  > error is false") { CHECK((error  > error) == false); }
	SECTION("error  < error is false") { CHECK((error  < error) == false); }
	SECTION("error >= error is true" ) { CHECK((error >= error) == true ); }
	SECTION("error <= error is true" ) { CHECK((error <= error) == true ); }

	SECTION("error == quantity is false") { for(Quantity qn : test_units) CHECK((error == qn) == false); }
	SECTION("error != quantity is true" ) { for(Quantity qn : test_units) CHECK((error != qn) == true ); }
	SECTION("error  > quantity is false") { for(Quantity qn : test_units) CHECK((error  > qn) == false); }
	SECTION("error  < quantity is false") { for(Quantity qn : test_units) CHECK((error  < qn) == false); }
	SECTION("error >= quantity is false") { for(Quantity qn : test_units) CHECK((error >= qn) == false); }
	SECTION("error <= quantity is flase") { for(Quantity qn : test_units) CHECK((error <= qn) == false); }

	SECTION("quantity == error is false") { for(Quantity qn : test_units) CHECK((qn == error) == false); }
	SECTION("quantity != error is true" ) { for(Quantity qn : test_units) CHECK((qn != error) == true ); }
	SECTION("quantity  > error is false") { for(Quantity qn : test_units) CHECK((qn  > error) == false); }
	SECTION("quantity  < error is false") { for(Quantity qn : test_units) CHECK((qn  < error) == false); }
	SECTION("quantity >= error is false") { for(Quantity qn : test_units) CHECK((qn >= error) == false); }
	SECTION("quantity <= error is false") { for(Quantity qn : test_units) CHECK((qn <= error) == false); }
}

TEST_CASE("Quantity errors: error and NaN quantity", "[quant][error]")
{
	using namespace Units;

	std::array<Quantity, 16> test_units =
		{
			std::numeric_limits<double>::quiet_NaN() * m,
			std::numeric_limits<double>::quiet_NaN() * s,
			std::numeric_limits<double>::quiet_NaN() * kg,
			std::numeric_limits<double>::quiet_NaN() * N,
			std::numeric_limits<double>::quiet_NaN() * m / s,
			std::numeric_limits<double>::quiet_NaN() * m / (s^2),
			std::numeric_limits<double>::quiet_NaN() * N * m,
			std::numeric_limits<double>::quiet_NaN() * A,
			std::numeric_limits<double>::quiet_NaN() * C,
			std::numeric_limits<double>::quiet_NaN() * ppm,
			std::numeric_limits<double>::quiet_NaN() * count,
			std::numeric_limits<double>::quiet_NaN() * currency,
			std::numeric_limits<double>::quiet_NaN() * cal,
			std::numeric_limits<double>::quiet_NaN() * mile,
			std::numeric_limits<double>::quiet_NaN() * L,
			std::numeric_limits<double>::quiet_NaN() * (m^3)
		};

	SECTION("error == NaN quantity is false") { for(Quantity qn : test_units) CHECK((error == qn) == false); }
	SECTION("error != NaN quantity is true" ) { for(Quantity qn : test_units) CHECK((error != qn) == true ); }
	SECTION("error  > NaN quantity is false") { for(Quantity qn : test_units) CHECK((error  > qn) == false); }
	SECTION("error  < NaN quantity is false") { for(Quantity qn : test_units) CHECK((error  < qn) == false); }
	SECTION("error >= NaN quantity is false") { for(Quantity qn : test_units) CHECK((error >= qn) == false); }
	SECTION("error <= NaN quantity is flase") { for(Quantity qn : test_units) CHECK((error <= qn) == false); }

	SECTION("NaN quantity == error is false") { for(Quantity qn : test_units) CHECK((qn == error) == false); }
	SECTION("NaN quantity != error is true" ) { for(Quantity qn : test_units) CHECK((qn != error) == true ); }
	SECTION("NaN quantity  > error is false") { for(Quantity qn : test_units) CHECK((qn  > error) == false); }
	SECTION("NaN quantity  < error is false") { for(Quantity qn : test_units) CHECK((qn  < error) == false); }
	SECTION("NaN quantity >= error is false") { for(Quantity qn : test_units) CHECK((qn >= error) == false); }
	SECTION("NaN quantity <= error is false") { for(Quantity qn : test_units) CHECK((qn <= error) == false); }
}

TEST_CASE("Quantity errors: custom error and NaN quantity", "[quant][error]")
{
	using namespace Units;

	std::array<Quantity, 16> test_units =
		{
			std::numeric_limits<double>::quiet_NaN() * m,
			std::numeric_limits<double>::quiet_NaN() * s,
			std::numeric_limits<double>::quiet_NaN() * kg,
			std::numeric_limits<double>::quiet_NaN() * N,
			std::numeric_limits<double>::quiet_NaN() * m / s,
			std::numeric_limits<double>::quiet_NaN() * m / (s^2),
			std::numeric_limits<double>::quiet_NaN() * N * m,
			std::numeric_limits<double>::quiet_NaN() * A,
			std::numeric_limits<double>::quiet_NaN() * C,
			std::numeric_limits<double>::quiet_NaN() * ppm,
			std::numeric_limits<double>::quiet_NaN() * count,
			std::numeric_limits<double>::quiet_NaN() * currency,
			std::numeric_limits<double>::quiet_NaN() * cal,
			std::numeric_limits<double>::quiet_NaN() * mile,
			std::numeric_limits<double>::quiet_NaN() * L,
			std::numeric_limits<double>::quiet_NaN() * (m^3)
		};

	Quantity my_error = Quantity(std::numeric_limits<double>::quiet_NaN(), error);

	SECTION("my_error == NaN quantity is false") { for(Quantity qn : test_units) CHECK((my_error == qn) == false); }
	SECTION("my_error != NaN quantity is true" ) { for(Quantity qn : test_units) CHECK((my_error != qn) == true ); }
	SECTION("my_error  > NaN quantity is false") { for(Quantity qn : test_units) CHECK((my_error  > qn) == false); }
	SECTION("my_error  < NaN quantity is false") { for(Quantity qn : test_units) CHECK((my_error  < qn) == false); }
	SECTION("my_error >= NaN quantity is false") { for(Quantity qn : test_units) CHECK((my_error >= qn) == false); }
	SECTION("my_error <= NaN quantity is flase") { for(Quantity qn : test_units) CHECK((my_error <= qn) == false); }

	SECTION("NaN quantity == my_error is false") { for(Quantity qn : test_units) CHECK((qn == my_error) == false); }
	SECTION("NaN quantity != my_error is true" ) { for(Quantity qn : test_units) CHECK((qn != my_error) == true ); }
	SECTION("NaN quantity  > my_error is false") { for(Quantity qn : test_units) CHECK((qn  > my_error) == false); }
	SECTION("NaN quantity  < my_error is false") { for(Quantity qn : test_units) CHECK((qn  < my_error) == false); }
	SECTION("NaN quantity >= my_error is false") { for(Quantity qn : test_units) CHECK((qn >= my_error) == false); }
	SECTION("NaN quantity <= my_error is false") { for(Quantity qn : test_units) CHECK((qn <= my_error) == false); }
}

TEST_CASE("Quantity comparisons: invalid comparisons", "[quant][error][inv]")
{
	using namespace Units;

	std::array<Quantity, 16> test_units =
		{
			std::numeric_limits<double>::quiet_NaN() * m,
			std::numeric_limits<double>::quiet_NaN() * s,
			std::numeric_limits<double>::quiet_NaN() * kg,
			std::numeric_limits<double>::quiet_NaN() * N,
			std::numeric_limits<double>::quiet_NaN() * m / s,
			std::numeric_limits<double>::quiet_NaN() * m / (s^2),
			std::numeric_limits<double>::quiet_NaN() * N * m,
			std::numeric_limits<double>::quiet_NaN() * A,
			std::numeric_limits<double>::quiet_NaN() * C,
			std::numeric_limits<double>::quiet_NaN() * ppm,
			std::numeric_limits<double>::quiet_NaN() * count,
			std::numeric_limits<double>::quiet_NaN() * currency,
			std::numeric_limits<double>::quiet_NaN() * cal,
			std::numeric_limits<double>::quiet_NaN() * mile,
			std::numeric_limits<double>::quiet_NaN() * L,
			std::numeric_limits<double>::quiet_NaN() * (m^3)
		};

	SECTION("unit == NaN quantity is false") { for(Quantity qn : test_units) CHECK((5.0 * K == qn) == false); }
	SECTION("unit != NaN quantity is true" ) { for(Quantity qn : test_units) CHECK((5.0 * K != qn) == true ); }
	SECTION("unit  > NaN quantity is false") { for(Quantity qn : test_units) CHECK((5.0 * K  > qn) == false); }
	SECTION("unit  < NaN quantity is false") { for(Quantity qn : test_units) CHECK((5.0 * K  < qn) == false); }
	SECTION("unit >= NaN quantity is false") { for(Quantity qn : test_units) CHECK((5.0 * K >= qn) == false); }
	SECTION("unit <= NaN quantity is flase") { for(Quantity qn : test_units) CHECK((5.0 * K <= qn) == false); }

	SECTION("NaN quantity == unit is false") { for(Quantity qn : test_units) CHECK((qn == 5.0 * K) == false); }
	SECTION("NaN quantity != unit is true" ) { for(Quantity qn : test_units) CHECK((qn != 5.0 * K) == true ); }
	SECTION("NaN quantity  > unit is false") { for(Quantity qn : test_units) CHECK((qn  > 5.0 * K) == false); }
	SECTION("NaN quantity  < unit is false") { for(Quantity qn : test_units) CHECK((qn  < 5.0 * K) == false); }
	SECTION("NaN quantity >= unit is false") { for(Quantity qn : test_units) CHECK((qn >= 5.0 * K) == false); }
	SECTION("NaN quantity <= unit is false") { for(Quantity qn : test_units) CHECK((qn <= 5.0 * K) == false); }
}
