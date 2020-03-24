#include <cmath>
#include <array>
#include <ostream>
#include <string>
#include <unordered_map>

#include "Units/Units.h"
#include "Units/IO.h"
#include "Units/extras/StdAdditions.h"

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

		// units to divide into tests to explore common unit products
		static std::array<PAIR_TYPE, 20> testUnits
		{{
			PAIR_TYPE { s            , "s"    },
			PAIR_TYPE { s^2          , "s²"   },
			PAIR_TYPE { h            , "h"    },
			PAIR_TYPE { min          , "min"  },
			PAIR_TYPE { Time::day    , "d"    },
			PAIR_TYPE { m            , "m"    },
			PAIR_TYPE { ft           , "ft"   },
			PAIR_TYPE { ft^2         , "ft²"  },
			PAIR_TYPE { ft^3         , "ft³"  },
			PAIR_TYPE { m^2          , "m²"   },
			PAIR_TYPE { m^3          , "m³"   },
			PAIR_TYPE { L            , "L"    },
			PAIR_TYPE { kg           , "kg"   },
			PAIR_TYPE { lb           , "lb"   },
			PAIR_TYPE { currency     , "$"    },
			PAIR_TYPE { std::sqrt(Hz), "√Hz"  },
			PAIR_TYPE { volt         , "V"    },
			PAIR_TYPE { watt         , "W"    },
			PAIR_TYPE { count        , "item" },
			PAIR_TYPE { Energy::Wh   , "Wh" },
		}};

#undef PAIR_TYPE

		// TODO: Change pair with tuple, so that every tuple holds a unit, its name and a bool that tells if this unit is "SI-friendly"
		// or not. If so, the apropriate SI prefix will be added (if nedded). If not, the number will be represented in scientific notation.

		constexpr Unit gram__ = Unit(0.001, kg);

		static std::unordered_map<Unit, const char*> unit_names =
		{
			// Base SI units
			{ none, ""    },
			{ m,    "m"   },
			{ m^2, u8"m\u00B2" },
			{ m^3, u8"m\u00B3" },
			{ kg,   "kg"  },
			{ s,    "s"   },
			{ A,    "A"   },
			{ K,    "K"   },
			{ mol,  "mol" },
			{ rad,  "rad" },
			{ Cd,   "Cd"  },

			{ gram__,   "g"  },

			// Derived SI units
			{ sr           , "sr"   },
			{ Hz           , "Hz"   },
			{ N            , "N"    },
			{ Pa           , "Pa"   },
			{ J            , "J"    },
			{ W            , "W"    },
			{ C            , "C"    },
			{ V            , "V"    },
			{ F            , "F"    },
			{ ohm          , "Ω"    },
			{ S            , "S"    },
			{ Wb           , "Wb"   },
			{ T            , "T"    },
			{ H            , "H"    },
			{ lm           , "lm"   },
			{ lx           , "lx"   },
			{ Bq           , "Bq"   },
			{ Gy           , "Gy"   },
			{ Sv           , "Sv"   },
			{ kat          , "kat"  },
			{ rad * W      , "W"    },
			{ currency     , "$"    },
			{ count        , "item" },
			{ std::sqrt(Hz), "√Hz"  },

			{ ft          , "ft"   },

			// Volume units
			{ L           , "L"    },

			// Atomic mass units
			{ Da, "u" },

			// CGS
			{ CGS::erg         , "erg" },
			{ CGS::dyn         , "dyn" },
			{ CGS::barye       , "Ba" },
			{ CGS::gal         , "Gal" },
			{ CGS::poise       , "P" },
			{ CGS::stokes      , "St" },
			{ CGS::kayser      , "K" },
			{ CGS::oersted     , "Oe" },
			{ CGS::gauss       , "G" },
			{ CGS::debye       , "D" },
			{ CGS::maxwell     , "Mx" },
			{ CGS::biot        , "Bi" },
			{ CGS::gilbert     , "Gb" },
			{ CGS::stilb       , "sb" },
			{ CGS::lambert     , "Lb" },
			{ CGS::phot        , "ph" },
			{ CGS::curie       , "Ci" },
			{ CGS::roentgen    , "R" },
			{ CGS::REM         , "rem" },
			{ CGS::RAD         , "rad" },
			{ CGS::emu         , "" },
			{ CGS::langley     , "" },
			{ CGS::unitpole    , "" },
			{ CGS::statC_charge, "" },
			{ CGS::statC_flux  , "" },

			// GM
			{ GM::pond, "gf" },
			{ GM::hyl, "hyl" },
			{ GM::at, "at" },
			{ GM::poncelet, "p" },
			{ GM::PS, "PS" },

			// MTS
			{ MTS::sthene, "sn" },
			{ MTS::pieze, "pz" },
			{ MTS::thermie, "th" },

			// Time
			{ Time::min, "min" },
			{ Time::hour, "h" },
			{ Time::day, "d" },
			{ Time::week, "w" },
			{ Time::year, "year" },

			// International
			{ i::grain, "gr" },
			{ i::point, "???" },
			{ i::pica, "???" },
			{ i::inch, "in" },
			{ i::foot, "ft" },
			{ i::yard, "yd" },
			{ i::mile, "mi" },
			{ i::league, "lea" },
			{ i::hand, "???" },
			{ i::cord, "cd-ft" },
			{ i::board_foot, "BDFT" },
			{ i::mil, "mil" },
			{ i::circ_mil, "cmil" },

			// Avoirdupois
			// Troy
			// US
			// Metric
			// Canada
			// Australia
			// Imperial
			// Apothecaries
			// Nautical
			// Japan

			// Chinese
			{ Chinese::jin,   u8"\u65A4" },
			{ Chinese::liang, u8"\u4E24" },
			{ Chinese::qian,  u8"\u9322" },
			{ Chinese::li,    u8"\u91CC" },
			{ Chinese::cun,   u8"\u5BF8" },
			{ Chinese::chi,   u8"\u5C3A" },
			{ Chinese::zhang, u8"\u4E08" },

			// Typografic

			// Distance
			{ Distance::ly, "ly" },
			{ Distance::au, "AU" },
			{ Distance::au_old, "AU" },
			{ Distance::angstrom, u8"\u212B" },
			{ Distance::parsec, "pc" },
//			{ Distance::arpent_us, "" },
//			{ Distance::arpent_fr, "" },
			{ Distance::xu, "xu" },

			// Area
			{ Area::barn, "b" },

			// Mass
			// Volume

			// Angle
			{ Angle::deg, u8"\u00B0" },
			{ Angle::grad, "grad" },
			{ Angle::brad, "brad" },
			{ Angle::gon, "gon" },
			{ Angle::arcmin, "'" },
			{ Angle::arcsec, "\"" },

			// Temperature
			{ Temperature::degC, u8"\u00B0C" },
			{ Temperature::degF, u8"\u00B0F" },
			{ Temperature::degR, u8"\u00B0R" },
			{ Temperature::degRe, u8"\u00B0Re" },

			// Pressure
			{ Pressure::bar, "bar" },
			{ Pressure::psi, u8"lbf/in\u00B2" },
			{ Pressure::inHg, "inHg" },
			{ Pressure::mmHg, "mmHg" },
			{ Pressure::torr, "torr" },
			{ Pressure::inH2O, u8"inH\u20820" },
			{ Pressure::mmH2O, u8"mmH\u20820" },
			{ Pressure::atm, "atm" },

			// Power
			{ Power::hpE, "hp"  }, // Review
			{ Power::hpI, "hp"  }, // Review
			{ Power::hpS, "hp"  }, // Review
			{ Power::hpM, "hp"  }, // Review
//			{ Power::VA , "VA"  }, // Volt-ampere
			{ Power::VAR, "VAR" }, // Volt-ampere reactive

			// Energy
			{ Energy::Wh, "Wh" },
			{ Energy::eV, "eV" },
			{ Energy::cal_4 , u8"cal [4\u00B0C]" },
			{ Energy::cal_15, u8"cal [15\u00B0C]" },
			{ Energy::cal_20, u8"cal [20\u00B0C]" },
			{ Energy::cal_mean, "cal" },
			{ Energy::cal_it, "cal" },
			{ Energy::cal_th, "cal" },
			{ Energy::btu_th, "BTU" },
			{ Energy::btu_39, u8"BTU [39\u00B0F]" },
			{ Energy::btu_59, u8"BTU [59\u00B0F]" },
			{ Energy::btu_60, u8"BTU [60\u00B0F]" },
			{ Energy::btu_mean, "BTU" },
			{ Energy::btu_it, "BTU" },
			{ Energy::btu_iso, "ISO BTU" },
			{ Energy::quad, "Quad" },
			{ Energy::therm_us, "Therm" }, // Review
			{ Energy::therm_br, "Therm" }, // Review
			{ Energy::therm_ec, "Therm" }, // Review
			{ Energy::ton_tnt, "t" },
//			{ Energy::boe, "" }, // Review
//			{ Energy::foeb, "" }, // Review
//			{ Energy::hartree, "" }, // Review
//			{ Energy::tonhour, "" }, // Review

			// Textile
			// Clinical

			// Log
			{ Log::neper , "Np" },
			{ Log::neperP, "Np" }, // Review
			{ Log::B , "B" },
			{ Log::BP, "B" },
			{ Log::BA, "BA" },
			{ Log::dB , "dB"  },
			{ Log::dBP, "dB" },
			{ Log::dBA, "dBA" },
			{ Log::dBc, "dBc" },
//			{ Log::log, "Np" }, // Review
			{ Log::log2, "log2" },
			{ Log::log10, "log10" },
			{ Log::neglog10, "-log10" },
			{ Log::neglog100, "-log100" },
			{ Log::neglog1000, "-log1000" },
			{ Log::neglog50000, "-log50000" },
			{ Log::B_SPL, "B SPL" },
			{ Log::dBSPL, "dB SPL" },
			{ Log::BV, "BV" },
			{ Log::BmV, "BmV" },
			{ Log::BuV, u8"B\u00B5V" },
			{ Log::B10nV, "B10nV" },
			{ Log::BW, "BW" },
			{ Log::Bk, "Bk" },
			{ Log::dBV, "dBV" },
			{ Log::dBmV, "dBmV" },
			{ Log::dBuV, "dBuV" },
			{ Log::dB10nV, "dB10nV" },
			{ Log::dBW, "dBW" },
			{ Log::dBk, "dBk" },
			{ Log::dBm, "dBm" },

			// Laboratory
			{ Laboratory::svedberg, "S" },
			{ Laboratory::PFU, "PFU" },
			{ Laboratory::pH, "pH" },

			// Data
			{ Data::bit   , "b" },
			{ Data::nibble, "nibble" },
			{ Data::byte  , "B" }, // Add "i"? this is so that it shows kiB, MiB, GiB, etc...

			// Computation
			{ Computation::FLOP , "FLOP" },
			{ Computation::FLOPS, "FLOPS" },
			{ Computation::MIPS , "MIPS" },

			// Misc
			{ ppm, "ppm" },
			{ ppb, "ppb" },
			{ rpm, "rpm" },

			{ J / mol, "J/mol" },
			{ J / (kg * K), "J/(kg·K)" },
			{ W / (m * K), "W/(m·K)" },
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
					1.0e-24, 1.0e-23, 1.0e-22, 1.0e-21,  1.0e-20,  1.0e-19,  1.0e-18,  1.0e-17,  1.0e-16,  1.0e-15,
					1.0e-14, 1.0e-13, 1.0e-12, 1.0e-11,  1.0e-10,  1.0e-9 ,  1.0e-8 ,  1.0e-7 ,  1.0e-6 ,  1.0e-5 ,
					1.0e-4 , 1.0e-3 , 1.0e-2 , 1.0e-1 ,  1.0e0  ,  1.0e1  ,  1.0e2  ,  1.0e3  ,  1.0e4  ,  1.0e5  ,
					1.0e6  , 1.0e7  , 1.0e8  , 1.0e9  ,  1.0e10 ,  1.0e11 ,  1.0e12 ,  1.0e13 ,  1.0e14 ,  1.0e15 ,
					1.0e16 , 1.0e17 , 1.0e18 , 1.0e19 ,  1.0e20 ,  1.0e21 ,  1.0e22 ,  1.0e23 ,  1.0e24 ,  1.0e25
				};

			return pow10[n + 24];
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

			constexpr const char* prefix[] = { "y", "z", "a", "f", "p", "n", u8"\u00B5", "m", "", "k", "M", "G", "T", "P", "E", "Z", "Y" };

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

	std::string to_string_scientific(const Quantity& q)
	{
		using namespace details;
		return magnitude_scientific(q.getMagnitude()) + ' ' + unit_raw(q.getUnit());
	}

	std::string to_string(const Unit& un)
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

		for(auto& tu : testUnits) if(find_unit(std::sqrt(un * tu.first), str)) return str + "²/" + tu.second;
		for(auto& tu : testUnits) if(find_unit(std::sqrt(un / tu.first), str)) return str + "²⋅" + tu.second;
		for(auto& tu : testUnits) if(find_unit(std::cbrt(un * tu.first), str)) return str + "³/" + tu.second;
		for(auto& tu : testUnits) if(find_unit(std::cbrt(un / tu.first), str)) return str + "³⋅" + tu.second;

		// TODO: If unit was not found, perform conversion to SI units. For example, if km/min was not found, perform
		// a conversion using thw raw unit (m/s) and a multiplier of 1, such that a valid unit is always displayed.

		return "???"; //unit_raw(un);
	}

	std::string to_string(const Quantity& q)
	{
		using namespace details;
		if(q.getUnit().eflag()) return "ERROR";
		if(q.getUnit() == Unit()) return magnitude_scientific(q.getMagnitude());

		if(q.getUnit() == kg) return to_string(convert(q, gram__));

		return magnitude_prefix(q.getMagnitude()) + to_string(q.getUnit());
	}
}
