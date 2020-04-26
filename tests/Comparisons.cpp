#include "Units/Units.h"
#include "Units/IO.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

using namespace Units;

TEST_CASE("Quantity comparisons", "[quant][comp]")
{
	SECTION("10 mi > 10 km") { CHECK(10 * mile > 10 * km); }
	SECTION("10 mi > 16 km") { CHECK(10 * mile > 16 * km); }
	SECTION("10 mi < 17 km") { CHECK(10 * mile < 17 * km); }


}
