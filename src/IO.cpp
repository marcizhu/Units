#include <cmath>
#include <array>
#include <ostream>
#include <string>
#include <unordered_map>

#include "Units/Units.h"
#include "Units/IO.h"

namespace Units
{
	namespace details
	{
		static std::string generateExponent(int n)
		{
			static constexpr const char* exponents[] = { "⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹" };

			if(n == 0) return "";
			if(n < 0) return "⁻" + generateExponent(-n);

			return generateExponent(n / 10) + exponents[n % 10];
		}

#define PAIR_TYPE std::pair<Unit, const char*>

		// units to divide into tests to explore common multiplier units
		static std::array<PAIR_TYPE, 11> testUnits
		{{
			PAIR_TYPE { s, "s" },
			PAIR_TYPE { s^2, "s²" },
			PAIR_TYPE { m, "m" },
			PAIR_TYPE { m^2, "m²" },
			PAIR_TYPE { m^3, "m³" },
			PAIR_TYPE { kg, "kg" },
			PAIR_TYPE { currency, "$" },
			PAIR_TYPE { std::sqrt(Hz), "√Hz" },
			PAIR_TYPE { volt, "V" },
			PAIR_TYPE { watt, "W" },
			PAIR_TYPE { count, "item" }
		}};

#undef PAIR_TYPE

		static std::unordered_map<Unit, const char*> unit_names =
		{
			{ Unit(), "" },
			{ m, "m" },
			{ m^2, "m²" },
			{ m^3, "m³" },
			{ kg, "kg" },
			{ s, "s" },
			{ A, "A" },
			{ K, "K" },
			{ mol, "mol" },
			{ Cd, "Cd" },
			{ rad, "rad" },
			{ sr, "sr" },
			{ Hz, "Hz" },
			{ N, "N" },
			{ Pa, "Pa" },
			{ J, "J" },
			{ W, "W" },
			{ C, "C" },
			{ V, "V" },
			{ F, "F" },
			{ ohm, "Ω" },
			{ S, "S" },
			{ Wb, "Wb" },
			{ T, "T" },
			{ H, "H" },
			{ lm, "lm" },
			{ lx, "lx" },
			{ Bq, "Bq" },
			{ std::sqrt(Hz), "√Hz" },
		//	{ Gy, "Gy" },
			{ Sv, "Sv" },
			{ kat, "kat" },
			{ currency, "$" },
			{ count, "item" },
			{ rad * W, "W" },
			{ Power::VAR, "VAR" } // Volt-ampere reactive
		};

		static bool find_unit(Units::Unit un, std::string& ret)
		{
			if(un.eflag()) return false;

			auto it = unit_names.find(un);
			return (it != unit_names.end() ? ret = it->second, true : false);
		}

		constexpr const char* FORMATTED_NAN     = "N/A";
		constexpr const char* POSITIVE_INFINITY = "+∞";
		constexpr const char* NEGATIVE_INFINITY = "-∞";

		static double pow10(int n)
		{
			static constexpr double pow10[] =
				{
					1.0e-14, 1.0e-13, 1.0e-12, 1.0e-11,  1.0e-10,  1.0e-9,  1.0e-8,  1.0e-7,  1.0e-6,  1.0e-5,
					1.0e-4 , 1.0e-3 , 1.0e-2 , 1.0e-1 ,  1.0e0  ,  1.0e1 ,  1.0e2 ,  1.0e3 ,  1.0e4 ,  1.0e5 ,
					1.0e6  , 1.0e7  , 1.0e8  , 1.0e9  ,  1.0e10 ,  1.0e11,  1.0e12,  1.0e13,  1.0e14,  1.0e15
				};

			return pow10[n + 14];
		}

		static int magnitude(double n) { return (std::fabs(n) == 0.0 ? 0 : (int)std::floor(std::log10(std::fabs(n)))); }
		static std::string format_inf(double n) { return (std::isnan(n) ? FORMATTED_NAN : (n < 0 ? NEGATIVE_INFINITY : POSITIVE_INFINITY)); }

		static std::string to_string_precision(double a_value, int n)
		{
			char data[10];
			snprintf(data, 10, "%.*lf", n, a_value);
			return data;
		}

		static std::string magnitude_prefix(double qty)
		{
			if(!std::isfinite(qty)) return format_inf(qty);

			constexpr const char* prefix[] = { "y", "z", "a", "f", "p", "n", "µ", "m", "", "k", "M", "G", "T", "P", "E", "Z", "Y" };

			const int i = magnitude(qty);
			const int index = (i >= 0 ? i : (i - 2)) / 3;
			const int precision = (i >= 0 ? (3 - i % 3) : ((std::abs(i + 1) % 3) + 1));

			if(index + 8 > (int)(sizeof(prefix) / sizeof(prefix[0])) || index < -8) return std::to_string(qty);

			return to_string_precision(qty / pow10(3 * index), precision) + ' ' + prefix[index + 8];
		}

		static std::string unit_raw(Units::Unit un)
		{
			if(un.eflag()) return "ERROR";

			std::string ret;
			if(un.meter()    != 0) ret += 'm'    + (un.meter()    != 1 ? generateExponent(un.meter()   ) + ' ' : " ");
			if(un.kg()       != 0) ret += "kg"   + (un.kg()       != 1 ? generateExponent(un.kg()      ) + ' ' : " ");
			if(un.second()   != 0) ret += 's'    + (un.second()   != 1 ? generateExponent(un.second()  ) + ' ' : " ");
			if(un.ampere()   != 0) ret += 'A'    + (un.ampere()   != 1 ? generateExponent(un.ampere()  ) + ' ' : " ");
			if(un.kelvin()   != 0) ret += 'K'    + (un.kelvin()   != 1 ? generateExponent(un.kelvin()  ) + ' ' : " ");
			if(un.mole()     != 0) ret += "mol"  + (un.mole()     != 1 ? generateExponent(un.mole()    ) + ' ' : " ");
			if(un.radian()   != 0) ret += "rad"  + (un.radian()   != 1 ? generateExponent(un.radian()  ) + ' ' : " ");
			if(un.candela()  != 0) ret += "Cd"   + (un.candela()  != 1 ? generateExponent(un.candela() ) + ' ' : " ");
			if(un.currency() != 0) ret += "$"    + (un.currency() != 1 ? generateExponent(un.currency()) + ' ' : " ");
			if(un.count()    != 0) ret += "item" + (un.count()    != 1 ? generateExponent(un.count()   ) + ' ' : " ");
			return ret;
		}

		static std::string magnitude_scientific(double qty)
		{
			if(!std::isfinite(qty)) return format_inf(qty);

			const int i = magnitude(qty);
			return to_string_precision(qty / pow10(i), 3) + "⋅10" + (i == 0 ? "⁰" : generateExponent(i));
		}
	}

	std::string to_string_scientific(Quantity q)
	{
		using namespace details;
		return magnitude_scientific(q.magnitude()) + ' ' + unit_raw(q.unit());
	}

	std::string to_string(Unit un)
	{
		using namespace details;
		if(un.eflag()) return "ERROR";

		std::string str;

		/**/ if(find_unit(un, str)) return str;
		else if(find_unit(std::sqrt(un   ), str)) return str + "²";
		else if(find_unit(std::sqrt(un^-1), str)) return str + "⁻²";
		else if(find_unit(std::cbrt(un   ), str)) return str + "³";
		else if(find_unit(std::cbrt(un^-1), str)) return str + "⁻³";
		else if(find_unit(un^-1, str)) return str + "⁻¹";

		for(auto& tu : testUnits) if(find_unit(un * tu.first, str)) return str + "/" + tu.second;
		for(auto& tu : testUnits) if(find_unit(un / tu.first, str)) return str + "⋅" + tu.second;
		for(auto& tu : testUnits) if(find_unit((un / tu.first)^-1, str)) return str + "⁻¹⋅" + tu.second + "⁻¹";
		for(auto& tu : testUnits) if(find_unit((un * tu.first)^-1, str)) return str + "⁻¹/" + tu.second + "⁻¹";

		return unit_raw(un);
	}

	std::string to_string(Quantity q)
	{
		using namespace details;
		if(q.unit().eflag()) return "ERROR";
		if(q.unit() == Unit()) return magnitude_scientific(q.magnitude());

		return magnitude_prefix(q.magnitude()) + to_string(q.unit());
	}
}
