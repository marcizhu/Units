#include "Units/Units.h"
#include "Units/IO.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Unit input parsing", "[unit][input]")
{
	Units::Unit temp = Units::Unit();

	SECTION("Basic SI units")
	{
		CHECK(from_string("m  ", temp)); CHECK(temp == Units::m  );
		CHECK(from_string("s  ", temp)); CHECK(temp == Units::s  );
		CHECK(from_string("kg ", temp)); CHECK(temp == Units::kg );
		CHECK(from_string("mol", temp)); CHECK(temp == Units::mol);
		CHECK(from_string("Cd ", temp)); CHECK(temp == Units::Cd );
		CHECK(from_string("K  ", temp)); CHECK(temp == Units::K  );
		CHECK(from_string("A  ", temp)); CHECK(temp == Units::A  );
	}

	SECTION("Derived SI units")
	{
		CHECK(from_string("sr ", temp)); CHECK(temp == Units::sr );
		CHECK(from_string("Hz ", temp)); CHECK(temp == Units::Hz );
		CHECK(from_string("N  ", temp)); CHECK(temp == Units::N  );
		CHECK(from_string("Pa ", temp)); CHECK(temp == Units::Pa );
		CHECK(from_string("J  ", temp)); CHECK(temp == Units::J  );
		CHECK(from_string("W  ", temp)); CHECK(temp == Units::W  );
		CHECK(from_string("C  ", temp)); CHECK(temp == Units::C  );
		CHECK(from_string("V  ", temp)); CHECK(temp == Units::V  );
		CHECK(from_string("F  ", temp)); CHECK(temp == Units::F  );
		CHECK(from_string("S  ", temp)); CHECK(temp == Units::S  );
		CHECK(from_string("Wb ", temp)); CHECK(temp == Units::Wb );
		CHECK(from_string("T  ", temp)); CHECK(temp == Units::T  );
		CHECK(from_string("H  ", temp)); CHECK(temp == Units::H  );
		CHECK(from_string("lm ", temp)); CHECK(temp == Units::lm );
		CHECK(from_string("lx ", temp)); CHECK(temp == Units::lx );
		CHECK(from_string("Bq ", temp)); CHECK(temp == Units::Bq );
		CHECK(from_string("Gy ", temp)); CHECK(temp == Units::Gy );
		CHECK(from_string("Sv ", temp)); CHECK(temp == Units::Sv );
		CHECK(from_string("kat", temp)); CHECK(temp == Units::kat);
	}
}
