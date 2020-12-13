#include "Units/Units.h"
#include "Units/IO.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

TEST_CASE("Unit input parsing", "[unit][input]")
{
	Units::Unit temp = Units::Unit();

	SECTION("Basic SI units")
	{
		temp = Units::to_unit(""   ); CHECK(temp != Units::error); CHECK(temp == Units::none);
		temp = Units::to_unit("m"  ); CHECK(temp != Units::error); CHECK(temp == Units::m  );
		temp = Units::to_unit("s"  ); CHECK(temp != Units::error); CHECK(temp == Units::s  );
		temp = Units::to_unit("kg" ); CHECK(temp != Units::error); CHECK(temp == Units::kg );
		temp = Units::to_unit("mol"); CHECK(temp != Units::error); CHECK(temp == Units::mol);
		temp = Units::to_unit("Cd" ); CHECK(temp != Units::error); CHECK(temp == Units::Cd );
		temp = Units::to_unit("K"  ); CHECK(temp != Units::error); CHECK(temp == Units::K  );
		temp = Units::to_unit("A"  ); CHECK(temp != Units::error); CHECK(temp == Units::A  );
	}

	SECTION("Derived SI units")
	{
		temp = Units::to_unit("sr" ); CHECK(temp != Units::error); CHECK(temp == Units::sr );
		temp = Units::to_unit("Hz" ); CHECK(temp != Units::error); CHECK(temp == Units::Hz );
		temp = Units::to_unit("N"  ); CHECK(temp != Units::error); CHECK(temp == Units::N  );
		temp = Units::to_unit("Pa" ); CHECK(temp != Units::error); CHECK(temp == Units::Pa );
		temp = Units::to_unit("J"  ); CHECK(temp != Units::error); CHECK(temp == Units::J  );
		temp = Units::to_unit("W"  ); CHECK(temp != Units::error); CHECK(temp == Units::W  );
		temp = Units::to_unit("C"  ); CHECK(temp != Units::error); CHECK(temp == Units::C  );
		temp = Units::to_unit("V"  ); CHECK(temp != Units::error); CHECK(temp == Units::V  );
		temp = Units::to_unit("F"  ); CHECK(temp != Units::error); CHECK(temp == Units::F  );
		temp = Units::to_unit("S"  ); CHECK(temp != Units::error); CHECK(temp == Units::S  );
		temp = Units::to_unit("Wb" ); CHECK(temp != Units::error); CHECK(temp == Units::Wb );
		temp = Units::to_unit("T"  ); CHECK(temp != Units::error); CHECK(temp == Units::T  );
		temp = Units::to_unit("H"  ); CHECK(temp != Units::error); CHECK(temp == Units::H  );
		temp = Units::to_unit("lm" ); CHECK(temp != Units::error); CHECK(temp == Units::lm );
		temp = Units::to_unit("lx" ); CHECK(temp != Units::error); CHECK(temp == Units::lx );
		temp = Units::to_unit("Bq" ); CHECK(temp != Units::error); CHECK(temp == Units::Bq );
		temp = Units::to_unit("Gy" ); CHECK(temp != Units::error); CHECK(temp == Units::Gy );
		temp = Units::to_unit("Sv" ); CHECK(temp != Units::error); CHECK(temp == Units::Sv );
		temp = Units::to_unit("kat"); CHECK(temp != Units::error); CHECK(temp == Units::kat);
	}
}
