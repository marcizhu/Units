#include "catch2/catch.hpp"
#include "Units/Units.h"
#include "Units/extras/StdAdditions.h"

using namespace Units;

TEST_CASE("Basic operations", "[unit][op]")
{
	SECTION("Addition of same unit returns same unit")
	{
		CHECK(m  + m  == m);
		CHECK(J  + J  == J);
		CHECK(V  + V  == V);
		CHECK(N  + N  == N);
		CHECK(A  + A  == A);
		CHECK(C  + C  == C);
		CHECK(W  + W  == W);
		CHECK(kg + kg == kg);
	}

	SECTION("Subtraction of same unit returns same unit")
	{
		CHECK(m  - m  == m);
		CHECK(J  - J  == J);
		CHECK(V  - V  == V);
		CHECK(N  - N  == N);
		CHECK(A  - A  == A);
		CHECK(C  - C  == C);
		CHECK(W  - W  == W);
		CHECK(kg - kg == kg);
	}

	SECTION("Multiplication of same unit squares it")
	{
		CHECK(m  * m  == (m^2) );
		CHECK(J  * J  == (J^2) );
		CHECK(V  * V  == (V^2) );
		CHECK(N  * N  == (N^2) );
		CHECK(A  * A  == (A^2) );
		CHECK(C  * C  == (C^2) );
		CHECK(W  * W  == (W^2) );
		CHECK(kg * kg == (kg^2));
	}

	SECTION("Division of same unit returns 1")
	{
		CHECK(m  / m  == Unit());
		CHECK(J  / J  == Unit());
		CHECK(V  / V  == Unit());
		CHECK(N  / N  == Unit());
		CHECK(A  / A  == Unit());
		CHECK(C  / C  == Unit());
		CHECK(W  / W  == Unit());
		CHECK(kg / kg == Unit());
	}

	SECTION("Addition of different unit throws an exception")
	{
		CHECK_THROWS(m  + J );
		CHECK_THROWS(J  + V );
		CHECK_THROWS(V  + N );
		CHECK_THROWS(N  + A );
		CHECK_THROWS(A  + C );
		CHECK_THROWS(C  + W );
		CHECK_THROWS(W  + kg);
		CHECK_THROWS(kg + m );
	}

	SECTION("Subtraction of different unit throws an exception")
	{
		CHECK_THROWS(m  - J );
		CHECK_THROWS(J  - V );
		CHECK_THROWS(V  - N );
		CHECK_THROWS(N  - A );
		CHECK_THROWS(A  - C );
		CHECK_THROWS(C  - W );
		CHECK_THROWS(W  - kg);
		CHECK_THROWS(kg - m );
	}

	SECTION("Multiplication of different unit doesn't throw an exception")
	{
		CHECK_NOTHROW(m  * J );
		CHECK_NOTHROW(J  * V );
		CHECK_NOTHROW(V  * N );
		CHECK_NOTHROW(N  * A );
		CHECK_NOTHROW(A  * C );
		CHECK_NOTHROW(C  * W );
		CHECK_NOTHROW(W  * kg);
		CHECK_NOTHROW(kg * m );
	}

	SECTION("Division of different unit doesn't throw an exception")
	{
		CHECK_NOTHROW(m  / J );
		CHECK_NOTHROW(J  / V );
		CHECK_NOTHROW(V  / N );
		CHECK_NOTHROW(N  / A );
		CHECK_NOTHROW(A  / C );
		CHECK_NOTHROW(C  / W );
		CHECK_NOTHROW(W  / kg);
		CHECK_NOTHROW(kg / m );
	}
}

TEST_CASE("Basic arithmetic", "[unit][op]")
{
	SECTION("A * B = B * A")
	{
		CHECK(m  * J  == J  * m );
		CHECK(J  * V  == V  * J );
		CHECK(V  * N  == N  * V );
		CHECK(N  * A  == A  * N );
		CHECK(A  * C  == C  * A );
		CHECK(C  * W  == W  * C );
		CHECK(W  * kg == kg * W );
		CHECK(kg * m  == m  * kg);
	}

	SECTION("A * B = A / (B^-1)")
	{
		CHECK(m  * J  == m  / (J ^-1));
		CHECK(J  * V  == J  / (V ^-1));
		CHECK(V  * N  == V  / (N ^-1));
		CHECK(N  * A  == N  / (A ^-1));
		CHECK(A  * C  == A  / (C ^-1));
		CHECK(C  * W  == C  / (W ^-1));
		CHECK(W  * kg == W  / (kg^-1));
		CHECK(kg * m  == kg / (m ^-1));
	}

	SECTION("A / B = A * (B^-1)")
	{
		CHECK(m  / J  == m  * (J ^-1));
		CHECK(J  / V  == J  * (V ^-1));
		CHECK(V  / N  == V  * (N ^-1));
		CHECK(N  / A  == N  * (A ^-1));
		CHECK(A  / C  == A  * (C ^-1));
		CHECK(C  / W  == C  * (W ^-1));
		CHECK(W  / kg == W  * (kg^-1));
		CHECK(kg / m  == kg * (m ^-1));
	}

	SECTION("(A^0) = 0")
	{
		CHECK((m ^0) == Unit());
		CHECK((J ^0) == Unit());
		CHECK((V ^0) == Unit());
		CHECK((N ^0) == Unit());
		CHECK((A ^0) == Unit());
		CHECK((C ^0) == Unit());
		CHECK((W ^0) == Unit());
		CHECK((kg^0) == Unit());
	}

	SECTION("(A^1) = A")
	{
		CHECK((m ^1) == m );
		CHECK((J ^1) == J );
		CHECK((V ^1) == V );
		CHECK((N ^1) == N );
		CHECK((A ^1) == A );
		CHECK((C ^1) == C );
		CHECK((W ^1) == W );
		CHECK((kg^1) == kg);
	}

	SECTION("A * A = (A^2)")
	{
		CHECK(m  * m  == (m ^2));
		CHECK(J  * J  == (J ^2));
		CHECK(V  * V  == (V ^2));
		CHECK(N  * N  == (N ^2));
		CHECK(A  * A  == (A ^2));
		CHECK(C  * C  == (C ^2));
		CHECK(W  * W  == (W ^2));
		CHECK(kg * kg == (kg^2));
	}

	SECTION("A * A * A = (A^3)")
	{
		CHECK(m  * m  * m  == (m ^3));
		CHECK(J  * J  * J  == (J ^3));
		CHECK(V  * V  * V  == (V ^3));
		CHECK(N  * N  * N  == (N ^3));
		CHECK(A  * A  * A  == (A ^3));
		CHECK(C  * C  * C  == (C ^3));
		CHECK(W  * W  * W  == (W ^3));
		CHECK(kg * kg * kg == (kg^3));
	}

	SECTION("A * (A^2) = (A^3)")
	{
		CHECK(m  * (m ^2) == (m ^3));
		CHECK(J  * (J ^2) == (J ^3));
		CHECK(V  * (V ^2) == (V ^3));
		CHECK(N  * (N ^2) == (N ^3));
		CHECK(A  * (A ^2) == (A ^3));
		CHECK(C  * (C ^2) == (C ^3));
		CHECK(W  * (W ^2) == (W ^3));
		CHECK(kg * (kg^2) == (kg^3));
	}

	SECTION("sqrt(A^2) = A")
	{
		CHECK(std::sqrt(m ^2) == m );
		CHECK(std::sqrt(J ^2) == J );
		CHECK(std::sqrt(V ^2) == V );
		CHECK(std::sqrt(N ^2) == N );
		CHECK(std::sqrt(A ^2) == A );
		CHECK(std::sqrt(C ^2) == C );
		CHECK(std::sqrt(W ^2) == W );
		CHECK(std::sqrt(kg^2) == kg);
	}

	SECTION("cbrt(A^3) = A")
	{
		CHECK(std::cbrt(m ^3) == m );
		CHECK(std::cbrt(Hz^3) == Hz);
		CHECK(std::cbrt(J ^3) == J );
		CHECK(std::cbrt(N ^3) == N );
		CHECK(std::cbrt(A ^3) == A );
		CHECK(std::cbrt(C ^3) == C );
		CHECK(std::cbrt(kg^3) == kg);
	}

	SECTION("sqrt(A^3) returns error")
	{
		CHECK(std::sqrt(m ^3) == Unit::error());
		CHECK(std::sqrt(J ^3) == Unit::error());
		CHECK(std::sqrt(V ^3) == Unit::error());
		CHECK(std::sqrt(N ^3) == Unit::error());
		CHECK(std::sqrt(A ^3) == Unit::error());
		CHECK(std::sqrt(C ^3) == Unit::error());
		CHECK(std::sqrt(W ^3) == Unit::error());
		CHECK(std::sqrt(kg^3) == Unit::error());
	}

	SECTION("cbrt(A^2) returns error")
	{
		CHECK(std::cbrt(m ^2) == Unit::error());
		CHECK(std::cbrt(J ^2) == Unit::error());
		CHECK(std::cbrt(V ^2) == Unit::error());
		CHECK(std::cbrt(N ^2) == Unit::error());
		CHECK(std::cbrt(A ^2) == Unit::error());
		CHECK(std::cbrt(C ^2) == Unit::error());
		CHECK(std::cbrt(W ^2) == Unit::error());
		CHECK(std::cbrt(kg^2) == Unit::error());
	}
}

TEST_CASE("Unit comparisons", "[unit][cmp]")
{
	SECTION("A == A")
	{
		CHECK(m  == m );
		CHECK(J  == J );
		CHECK(V  == V );
		CHECK(N  == N );
		CHECK(A  == A );
		CHECK(C  == C );
		CHECK(W  == W );
		CHECK(kg == kg);
		CHECK(L  == L);
		CHECK(lm == lm);
		CHECK(Bq == Bq);
		CHECK(lx == lx);
	}

	SECTION("A != B")
	{
		CHECK(m  != kg);
		CHECK(J  != m );
		CHECK(V  != J );
		CHECK(N  != V );
		CHECK(A  != N );
		CHECK(C  != A );
		CHECK(W  != C );
		CHECK(kg != W );
		CHECK(m  != W );
		CHECK(J  != kg);
		CHECK(V  != m );
		CHECK(N  != J );
		CHECK(A  != V );
		CHECK(C  != N );
		CHECK(W  != A );
		CHECK(kg != C );
		CHECK(m  != C );
		CHECK(J  != W );
		CHECK(V  != kg);
		CHECK(N  != m );
		CHECK(A  != J );
		CHECK(C  != V );
		CHECK(W  != N );
		CHECK(kg != A );
	}
}
