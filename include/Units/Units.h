#pragma once

#include "Unit.h"
#include "Quantity.h"

namespace Units
{
	// The standard SI prefixes
	static constexpr double yotta = 1e+24;
	static constexpr double zetta = 1e+21;
	static constexpr double exa   = 1e+18;
	static constexpr double peta  = 1e+15;
	static constexpr double tera  = 1e+12;
	static constexpr double giga  = 1e+9;
	static constexpr double mega  = 1e+6;
	static constexpr double kilo  = 1e+3;
	static constexpr double hecto = 1e+2;
	static constexpr double deca  = 1e+1;
	static constexpr double deci  = 1e-1;
	static constexpr double centi = 1e-2;
	static constexpr double milli = 1e-3;
	static constexpr double micro = 1e-6;
	static constexpr double nano  = 1e-9;
	static constexpr double pico  = 1e-12;
	static constexpr double femto = 1e-15;
	static constexpr double atto  = 1e-18;
	static constexpr double zepto = 1e-21;
	static constexpr double yocto = 1e-24;

	// Binary prefixes, pending adoption
	static constexpr double kibi = 1024;
	static constexpr double mebi = 1024 * kibi;
	static constexpr double gibi = 1024 * mebi;
	static constexpr double tebi = 1024 * gibi;
	static constexpr double pebi = 1024 * tebi;
	static constexpr double exbi = 1024 * pebi;
	static constexpr double zebi = 1024 * exbi;
	static constexpr double yobi = 1024 * zebi;

	// Handy values
	namespace Constants
	{
		static constexpr double pi  = 3.14159265358979323846264338327950288;
		static constexpr double tau = 6.28318530717958647692528676655900576;
	}

	static constexpr Unit one;
	static constexpr Unit error   = Unit::error();
	static constexpr Unit none    = one;

	// The base SI units
	static constexpr Unit meter    = Unit::meter();
	static constexpr Unit kilogram = Unit::kilogram();
	static constexpr Unit second   = Unit::second();
	static constexpr Unit ampere   = Unit::ampere();
	static constexpr Unit kelvin   = Unit::kelvin();
	static constexpr Unit mole     = Unit::mole();
	static constexpr Unit radian   = Unit::radian();
	static constexpr Unit candela  = Unit::candela();
	static constexpr Unit currency = Unit::currency();
	static constexpr Unit count    = Unit::count();

	static constexpr Unit m   = meter;
	static constexpr Unit kg  = kilogram;
	static constexpr Unit s   = second;
	static constexpr Unit A   = ampere;
	static constexpr Unit K   = kelvin;
	static constexpr Unit mol = mole;
	static constexpr Unit rad = radian;
	static constexpr Unit Cd  = candela;

	/** @brief i flag, imaginary flag */
	static constexpr Unit iflag = Unit::iflag();

	// Derived SI units
	static constexpr Unit steradian      = radian * radian;
	static constexpr Unit hertz          = second^-1;
	static constexpr Unit newton         = kilogram * meter / (second^2);
	static constexpr Unit pascal         = newton / (meter^2);
	static constexpr Unit joule          = newton * meter;
	static constexpr Unit watt           = joule / second;
	static constexpr Unit coulomb        = ampere * second;
	static constexpr Unit volt           = watt / ampere;
	static constexpr Unit farad          = coulomb / volt;
	static constexpr Unit ohm            = volt / ampere;
	static constexpr Unit siemens        = ampere / volt;
	static constexpr Unit weber          = volt * second;
	static constexpr Unit tesla          = weber / (meter^2);
	static constexpr Unit henry          = weber / ampere;
	static constexpr Unit degree_celsius = kelvin;
	static constexpr Unit lumen          = candela * steradian;
	static constexpr Unit lux            = lumen / (meter^-2);
	static constexpr Unit becquerel      = count / second;
	static constexpr Unit gray           = joule / kilogram;
	static constexpr Unit sievert        = joule / kilogram;
	static constexpr Unit katal          = mol / second;

	static constexpr Unit sr  = steradian;
	static constexpr Unit Hz  = hertz;
	static constexpr Unit N   = newton;
	static constexpr Unit Pa  = pascal;
	static constexpr Unit J   = joule;
	static constexpr Unit W   = watt;
	static constexpr Unit C   = coulomb;
	static constexpr Unit V   = volt;
	static constexpr Unit F   = farad;
	static constexpr Unit S   = siemens;
	static constexpr Unit Wb  = weber;
	static constexpr Unit T   = tesla;
	static constexpr Unit H   = henry;
	static constexpr Unit lm  = lumen;
	static constexpr Unit lx  = lux;
	static constexpr Unit Bq  = becquerel;
	static constexpr Unit Gy  = gray;
	static constexpr Unit Sv  = sievert;
	static constexpr Unit kat = katal;

	// Not approved for use alone (needed for use with prefixes)
	static constexpr Unit     liter = Unit(0.001, m^3);
	static constexpr Quantity gram  = 0.001 * kg;

	// Alternate (non-US) spellings:
	static constexpr Unit metre = meter;
	static constexpr Unit litre = liter;
	static constexpr double deka = deca;

	// Short unit names
	// Distance units
	static constexpr Quantity cm = centi * m;
	static constexpr Quantity km = kilo  * m;
	static constexpr Quantity mm = milli * m;
	static constexpr Quantity nm = nano  * m;

	// Volume units
	static constexpr Unit L      = liter;
	static constexpr Quantity mL = milli * L;

	// Mass units
	static constexpr Quantity g     = gram;
	static constexpr Quantity mg    = milli  *  g;
	static constexpr Quantity tonne = 1000.0 * kg;
	static constexpr Quantity t     = tonne;

	// Atomic mass units
	static constexpr Unit Da = Unit(1.66053906660e-27, kg);
	static constexpr Unit u  = Da;

	/** @brief Units from the CGS system */
	namespace CGS
	{
		static constexpr double c_const    = 29979245800.0; // speed of light in cm/s
		static constexpr Unit erg          = Unit(1e-7, J);
		static constexpr Unit dyn          = Unit(1e-5, N);
		static constexpr Unit barye        = Unit(0.1, Pa);
		static constexpr Unit gal          = Unit(0.01, m / (s^2));
		static constexpr Unit poise        = Unit(0.1, Pa * s);
		static constexpr Unit stokes       = Unit(1e-4, (m^2) / s);
		static constexpr Unit kayser       = Unit(100.0, one / m);
		static constexpr Unit oersted      = Unit(1000.0 / 4.0 / Constants::pi, A / m);
		static constexpr Unit gauss        = Unit(1e-4, T);
		static constexpr Unit debye        = Unit(1.0 / (c_const * 1e20), C * m);
		static constexpr Unit maxwell      = Unit(1e-8, Wb);
		static constexpr Unit biot         = Unit(10.0, A);
		static constexpr Unit gilbert      = Unit(0.01, oersted * m);
		static constexpr Unit stilb        = Unit(10000.0, Cd / (m^2));
		static constexpr Unit lambert      = Unit(10000.0 / Constants::pi, Cd / (m^2));
		static constexpr Unit phot         = Unit(10000, lx);
		static constexpr Unit curie        = Unit(3.7e10, Bq);
		static constexpr Unit roentgen     = Unit(2.58e-4, C / kg);
		static constexpr Unit REM          = Unit(0.01, Sv);
		static constexpr Unit RAD          = Unit(100000, erg / kg);
		static constexpr Unit emu          = Unit(0.001, A * m * m);
		static constexpr Unit langley      = Unit(41840.0, J / (m^2));
		static constexpr Unit unitpole     = Unit(1.256637061436e-7, Wb);
		static constexpr Unit statC_charge = Unit(10.0 / c_const, C);
		static constexpr Unit statC_flux   = Unit(10.0 / (4.0 * Constants::pi * c_const), V * m);

		static constexpr Quantity abOhm    = 1e-9 * ohm;
		static constexpr Quantity abFarad  = 1e09 * F;
		static constexpr Quantity abHenry  = 1e-9 * H;
		static constexpr Quantity abVolt   = 1e-8 * V;

		static constexpr Quantity statV     = c_const * abVolt;
		static constexpr Quantity statT     = c_const * 1e-4 * T;
		static constexpr Quantity statHenry = c_const * c_const * abHenry;
		static constexpr Quantity statOhm   = c_const * c_const * abOhm;
		static constexpr Quantity statFarad = (1.0 / (c_const * c_const)) * abFarad;
	}

	/** @brief meter-gram-force system of units (aka gravitational metric system) */
	namespace GM
	{
		static constexpr Unit pond     = Unit(980.665, CGS::dyn);
		static constexpr Unit hyl      = Unit(9.80665, kg);
		static constexpr Unit at       = Unit(98066.5, Pa); // technical atmosfere
		static constexpr Unit poncelet = Unit(980.665, W);
		static constexpr Unit PS       = Unit(735.49875, W); // metric horsepower
	}

	/** @brief Meter tonne second system of units */
	namespace MTS
	{
		static constexpr Unit sthene  = Unit(1000.0, N);
		static constexpr Unit pieze   = Unit(1000.0, Pa);
		static constexpr Unit thermie = Unit(4.1868 * mega, J);
	}

	/** @brief Units of time */
	namespace Time
	{
		/** @brief Minute */
		static constexpr Unit min  = Unit(60.0, s);
		/** @brief Hour */
		static constexpr Unit hour = Unit(3600, s);
		/** @brief Day */
		static constexpr Unit day  = Unit(24, hour);
		/** @brief Week */
		static constexpr Unit week = Unit(7, day);
		/** @brief Median calendar year */
		static constexpr Unit yr   = Unit(8760.0, hour);

		/** @brief Julian year */
		static constexpr Unit aj   = Unit(365.25, day);
		/** @brief Standard year */
		static constexpr Unit year = aj;

		/** @brief Fortnight (two weeks) */
		static constexpr Quantity fortnight = 14 * day;
		/** @brief Sidereal day */
		static constexpr Quantity sday = 365.24 / 366.24 * day;
		/** @brief Sidereal year */
		static constexpr Quantity syr  = 365.256363004 * day;
		/** @brief Mean tropical year */
		static constexpr Quantity at   = 365.24219 * day;
		/** @brief Gregorian year */
		static constexpr Quantity ag   = 365.2425 * day;
		/** @brief Synodal month */
		static constexpr Quantity mos  = 29.53059 * day;
		/** @brief Mean Julian month */
		static constexpr Quantity moj  = 1.0 / 12.0 * aj;
		/** @brief mean Gregorian month */
		static constexpr Quantity mog  = 1.0 / 12.0 * ag;
	}

	static constexpr Unit h   = Time::hour;
	static constexpr Unit min = Time::min;

	/** @brief International units */
	namespace i
	{
		static constexpr Unit grain = Unit(64.79891 * micro, kg);

		static constexpr Unit inch   = Unit(0.0254, m);
		static constexpr Unit foot   = Unit(0.3048, m);
		static constexpr Unit yard   = Unit(0.9144, m);
		static constexpr Unit mile   = Unit(1609.344, m);
		static constexpr Unit league = Unit(3.0, mile);

		static constexpr Unit cord       = Unit(128.0, foot^3);
		static constexpr Unit board_foot = Unit(144.0, inch^3);
		static constexpr Unit mil        = Unit(milli, inch);
		static constexpr Unit circ_mil   = Unit(Constants::pi / 4.0, mil^2);

		static constexpr Quantity point = (0.127 / 360.0) * m;
		static constexpr Quantity pica  = (0.127 / 30.0) * m;
		static constexpr Quantity hand  = 4.0 * inch;
	}

	static constexpr Unit in   = i::inch;
	static constexpr Unit ft   = i::foot;
	static constexpr Unit yd   = i::yard;
	static constexpr Unit mile = i::mile;

	/** @brief Avoirdupois units, common international standard */
	namespace av
	{
		static constexpr Unit dram              = Unit(0.0017718451953125, kg);
		static constexpr Unit ounce             = Unit(16.0, dram);
		static constexpr Unit pound             = Unit(0.45359237, kg);
		static constexpr Unit hundredweight     = Unit(100.0, pound);
		static constexpr Unit longhundredweight = Unit(112.0, pound);
		static constexpr Unit ton               = Unit(2000.0, pound);
		static constexpr Unit longton           = Unit(2240.0, pound);
		static constexpr Unit stone             = Unit(14.0, pound);
		static constexpr Unit poundal           = Unit(0.138254954376, N);
		static constexpr Unit lbf               = Unit(4.4482216152605, N);
		static constexpr Unit ozf               = Unit(1.0 / 16.0, lbf);
		static constexpr Unit slug              = lbf * (s^2) / ft;
	}

	static constexpr Unit lb  = av::pound;
	static constexpr Unit ton = av::ton;
	static constexpr Unit oz  = av::ounce;
	static constexpr Unit lbf = av::lbf;

	/** @brief Troy units */
	namespace Troy
	{
		static constexpr Unit pennyweight = Unit(24.0, i::grain);
		static constexpr Unit oz          = Unit(0.0311034768, kg);
		static constexpr Unit pound       = Unit(12.0, oz);
	}

	/** @brief Units used in the United States */
	namespace US
	{
		static constexpr Unit foot    = Unit(1200.0 / 3937.0, m);
		static constexpr Unit inch    = Unit(1.0 / 12.0, foot);
		static constexpr Unit mil     = Unit(0.001, inch);
		static constexpr Unit yard    = Unit(3.0, foot);
		static constexpr Unit rod     = Unit(16.5, foot);
		static constexpr Unit chain   = Unit(4.0, rod);
		static constexpr Unit link    = Unit(0.01, chain);
		static constexpr Unit furlong = Unit(10.0, chain);
		static constexpr Unit mile    = Unit(8.0, furlong);
		static constexpr Unit league  = Unit(3.0, mile);

		// Area
		static constexpr Unit acre      = Unit(43560.0, foot^2);
		static constexpr Unit homestead = Unit(160.0, acre);
		static constexpr Unit section   = Unit(640.0, acre);
		static constexpr Unit township  = Unit(36.0, section);

		// Volume
		static constexpr Unit minim    = Unit(61.611519921875 * micro, L);
		static constexpr Unit dram     = Unit(60.0, minim);
		static constexpr Unit floz     = Unit(29.5735295625e-6, m^3);
		static constexpr Unit tbsp     = Unit(0.5, floz);
		static constexpr Unit tsp      = Unit(1.0 / 6.0, floz);
		static constexpr Unit pinch    = Unit(0.125, tsp);
		static constexpr Unit dash     = Unit(0.5, pinch);
		static constexpr Unit shot     = Unit(3.0, tbsp);
		static constexpr Unit gill     = Unit(4.0, floz);
		static constexpr Unit cup      = Unit(8.0, floz);
		static constexpr Unit pint     = Unit(2.0, cup);
		static constexpr Unit quart    = Unit(2.0, pint);
		static constexpr Unit cord     = Unit(128.0, ft^3);
		static constexpr Unit gallon   = Unit(3.785411784, L);
		static constexpr Unit flbarrel = Unit(31.5, gallon);
		static constexpr Unit barrel   = Unit(42.0, gallon);
		static constexpr Unit hogshead = Unit(63.0, gallon);
		static constexpr Unit fifth    = Unit(0.2,  gallon);

		namespace Engineers
		{
			static constexpr Unit chain = Unit(100.0, foot);
			static constexpr Unit link  = Unit(0.01, chain);
		}

		/** @brief US customary dry measurements */
		namespace Dry
		{
			static constexpr Unit pint   = Unit(0.5506104713575, L);
			static constexpr Unit quart  = Unit(2.0, pint);
			static constexpr Unit gallon = Unit(4.0, quart);
			static constexpr Unit peck   = Unit(2.0, gallon);
			static constexpr Unit bushel = Unit(35.23907016688, L);
			static constexpr Unit barrel = Unit(7056.0, in^3);
			static constexpr Unit sack   = Unit(3.0, bushel);
			static constexpr Unit strike = Unit(2.0, bushel);
		}

		namespace Grain
		{
			static constexpr Unit bushel_corn   = Unit(56.0, av::pound);
			static constexpr Unit bushel_wheat  = Unit(60.0, av::pound);
			static constexpr Unit bushel_barley = Unit(48.0, av::pound);
			static constexpr Unit bushel_oats   = Unit(32.0, av::pound);
		}
	}

	static constexpr Unit acre = US::acre;
	static constexpr Unit gal  = US::gallon;

	/** @brief FDA-specific volume units in metric */
	namespace Metric
	{
		static constexpr Unit tbsp        = Unit(0.015, L);
		static constexpr Unit tsp         = Unit(0.005, L);
		static constexpr Unit floz        = Unit(0.030, L);
		static constexpr Unit cup         = Unit(0.250, L);
		static constexpr Unit cup_uslegal = Unit(0.240, L);
		static constexpr Unit carat       = Unit(0.0002, kg);
	}

	/** @brief Some Canada specific variants on the us units */
	namespace Canada
	{
		static constexpr Unit tbsp     = Unit(0.015, L);
		static constexpr Unit tsp      = Unit(0.005, L);
		static constexpr Unit cup      = Unit(0.250, L);
		static constexpr Unit cup_trad = Unit(0.2273045, L);

		namespace Grain
		{
			static constexpr Unit bushel_oats = Unit(34.0, av::pound);
		}
	}

	/** @brief Some Australia specific variants on the us units */
	namespace Australia
	{
		static constexpr Unit tbsp = Unit(0.020, L);
		static constexpr Unit tsp  = Unit(0.005, L);
		static constexpr Unit cup  = Unit(0.250, L);
	}

	/** @brief Imperial system units (British) */
	namespace Imperial
	{
		static constexpr Unit inch = Unit(0.02539998, m);
		static constexpr Unit foot = Unit(12.0, inch);

		static constexpr Unit thou          = Unit(0.0000254, m);
		static constexpr Unit barleycorn    = Unit(1.0 / 3.0, inch);
		static constexpr Unit rod           = Unit(16.5, foot);
		static constexpr Unit chain         = Unit(4.0, rod);
		static constexpr Unit link          = Unit(0.01, chain);
		static constexpr Unit pace          = Unit(2.5, foot);
		static constexpr Unit yard          = Unit(3.0, foot);
		static constexpr Unit furlong       = Unit(201.168, m);
		static constexpr Unit league        = Unit(4828.032, m);
		static constexpr Unit mile          = Unit(5280.0, foot);
		static constexpr Unit nautical_mile = Unit(6080, foot);
		static constexpr Unit knot          = nautical_mile / h;
		static constexpr Unit acre          = Unit(4840.0, yard^2);

		// Area
		static constexpr Unit perch = Unit(25.29285264, m^2);
		static constexpr Unit rood  = Unit(1011.7141056, m^2);

		// Volume
		static constexpr Unit gallon = Unit(4.54609, L);
		static constexpr Unit quart  = Unit(0.25, gallon);
		static constexpr Unit pint   = Unit(0.5, quart);
		static constexpr Unit gill   = Unit(0.25, pint);
		static constexpr Unit cup    = Unit(0.5, pint);
		static constexpr Unit floz   = Unit(0.1, cup);
		static constexpr Unit tbsp   = Unit(0.5, floz);
		static constexpr Unit tsp    = Unit(1.0 / 3.0, tbsp);

		static constexpr Unit barrel = Unit(36.0, gallon);
		static constexpr Unit peck   = Unit(2.0, gallon);
		static constexpr Unit bushel = Unit(4.0, peck);
		static constexpr Unit dram   = Unit(1.0 / 8.0, floz);
		static constexpr Unit minim  = Unit(1.0 / 60.0, dram);

		// Weight
		static constexpr Unit drachm        = Unit(0.0017718451953125, kg);
		static constexpr Unit stone         = Unit(6.35029318, kg);
		static constexpr Unit hundredweight = Unit(112.0,  av::pound);
		static constexpr Unit ton           = Unit(2240.0, av::pound);
		static constexpr Unit slug          = Unit(14.59390294, kg);
	}

	namespace Apothecaries
	{
		static constexpr Unit floz         = Imperial::floz;
		static constexpr Unit minim        = Unit(59.1938802083333333333 * micro, L);
		static constexpr Unit scruple      = Unit(20.0, i::grain);
		static constexpr Unit drachm       = Unit(3.0, scruple);
		static constexpr Unit ounce        = Unit(8.0, drachm);
		static constexpr Unit pound        = Unit(12.0, ounce);
		static constexpr Unit pint         = Imperial::pint;
		static constexpr Unit gallon       = Imperial::gallon;
		static constexpr Unit metric_ounce = Unit(0.028, kg);
	}

	/** @brief Nautical units */
	namespace Nautical
	{
		static constexpr Unit fathom = Unit(2.0, yd);
		static constexpr Unit cable  = Unit(120, fathom);
		static constexpr Unit mile   = Unit(1852.0, m);
		static constexpr Unit knot   = mile / h;
		static constexpr Unit league = Unit(3.0, mile);
	}

	/** @brief Some historical Japanese units */
	namespace Japan
	{
		static constexpr Unit shaku = Unit(10.0 / 33.0, m);
		static constexpr Unit sun   = Unit(0.1, shaku);
		static constexpr Unit ken   = Unit(1.0 + 9.0 / 11.0, m);
		static constexpr Unit tsubo = Unit(100.0 / 30.25, m^2);
		static constexpr Unit sho   = Unit(2401.0 / 1331.0, L);
		static constexpr Unit kan   = Unit(15.0 / 4.0, kg);
		static constexpr Unit go    = Unit(2401.0 / 13310, L);
		static constexpr Unit cup   = Unit(0.2, L);
	}

	/** @brief Some historical chinese units */
	namespace Chinese
	{
		static constexpr Unit jin   = Unit(0.5, kg);
		static constexpr Unit liang = Unit(0.0001, kg);
		static constexpr Unit qian  = Unit(0.00001, kg);

		static constexpr Unit li    = Unit(500.0, m);
		static constexpr Unit cun   = Unit(10.0 / 300.0, m);
		static constexpr Unit chi   = Unit(10.0, cun);
		static constexpr Unit zhang = Unit(10.0, chi);
	}

	/** @brief Typographic units for typesetting or printing */
	namespace Typographic
	{
		namespace American
		{
			static constexpr Unit line  = Unit(1.0 / 12.0, in);
			static constexpr Unit point = Unit(1.0 / 6.0, line);
			static constexpr Unit pica  = Unit(12.0, point);
			static constexpr Unit twip  = Unit(1.0 / 20.0, point);
		}

		namespace Printers
		{
			static constexpr Unit point = Unit(0.013837, in);
			static constexpr Unit pica  = Unit(12.0, point);
		}

		namespace French
		{
			static constexpr Unit point  = Unit(15.625 / 41559.0, m);
			static constexpr Unit ligne  = Unit(6.0, point);
			static constexpr Unit pouce  = Unit(12.0, ligne);
			static constexpr Unit didot  = point;
			static constexpr Unit cicero = Unit(12.0, didot);
			static constexpr Unit pied   = Unit(12.0, pouce);
			static constexpr Unit toise  = Unit(6.0, pied);
		}

		namespace Metric
		{
			static constexpr Unit point = Unit(375.0 * micro, m);
			static constexpr Unit quart = Unit(0.25 * milli, m);
		}
	}

	/** @brief Units related to distance */
	namespace Distance
	{
		/** @brief Smoot, or Oliver Smoot's height as of October 1958 (see https://en.wikipedia.org/wiki/Smoot) */
		static constexpr Quantity smoot     = 67.0 * in;
		/** @brief Cubit */
		static constexpr Quantity cubit     = 18.0 * in;
		/** @brief Long cubit */
		static constexpr Quantity longcubit = 21.0 * in;

		/** @brief Light-year */
		static constexpr Unit ly        = Unit(9.4607304725808e15, m);
		/** @brief Astronomical unit */
		static constexpr Unit au        = Unit(149597870700.0, m);
		/** @brief Astronomical unit (old definition) */
		static constexpr Unit au_old    = Unit(149597900000.0, m);
		/** @brief Angstrom, 10^-10 m (100 pm) */
		static constexpr Unit angstrom  = Unit(1e-10, m);
		/** @brief Parsec, as defined by the International Astronomical Union */
		static constexpr Unit parsec    = Unit(3.08567758149136727891e16, m);

		/** @brief Arpent (US) */
		static constexpr Unit arpent_us = Unit(58.47131, m);
		/** @brief Arpent (FR) */
		static constexpr Unit arpent_fr = Unit(71.46466, m);
		/** @brief The X unit */
		static constexpr Unit xu        = Unit(1.0021e-13, m);
	}

	/** @brief Units related to compass directions */
	namespace Direction
	{
		/** @brief North */
		static constexpr Quantity north =  1.0 * iflag;
		/** @brief South */
		static constexpr Quantity south = -1.0 * iflag;
		/** @brief East */
		static constexpr Quantity east  =  1.0;
		/** @brief West */
		static constexpr Quantity west  = -1.0;

		/** @brief North, short name */
		static constexpr Quantity N = north;
		/** @brief South, short name */
		static constexpr Quantity S = south;
		/** @brief East, short name */
		static constexpr Quantity E = east;
		/** @brief West, short name */
		static constexpr Quantity W = west;
	}

	/** @brief Additional Area units */
	namespace Area
	{
		static constexpr Unit are     = Unit(100.0, m^2);
		static constexpr Unit hectare = Unit(100.0, are);
		/** @brief Barn. 10^−28 m^2 (or 100 fm^2) */
		static constexpr Unit barn    = Unit(1e-28, m^2);
		static constexpr Unit arpent  = Unit(0.84628, acre);
	}

	/** @brief Additional mass units */
	namespace Mass
	{
		static constexpr Quantity quintal   = 100.0 * kg;
		static constexpr Unit ton_assay     = Unit((29.0 + 1.0 / 6.0) * milli, kg);
		static constexpr Unit longton_assay = Unit((32.0 + 2.0 / 3.0) * milli, kg);
	}

	/** @brief Some extra volume units */
	namespace Volume
	{
		static constexpr Unit stere     = m^3;
		static constexpr Unit acre_foot = acre * US::foot;
		static constexpr Unit drum      = Unit(55.0, US::gallon);
	}

	/** @brief Angle measurement units */
	namespace Angle
	{
		/** @brief Degree */
		static constexpr Unit deg    = Unit(Constants::pi  / 180.0, rad);
		/** @brief Gradian */
		static constexpr Unit grad   = Unit(Constants::pi  / 200.0, rad);
		/** @brief Binary radian */
		static constexpr Unit brad   = Unit(Constants::tau / 256.0, rad);

		/** @brief Gon */
		static constexpr Unit gon    = Unit(9.0 / 10.0, deg);
		/** @brief Arc minute */
		static constexpr Unit arcmin = Unit(1.0 / 60.0, deg);
		/** @brief Arc second */
		static constexpr Unit arcsec = Unit(1.0 / 60.0, arcmin);
	}

	/** @brief Units related to temperature */
	namespace Temperature
	{
		/** @brief Degree Celsius */
		static constexpr Unit celsius    = Unit(1.0, K);
		/** @brief Degree Fahrenheit */
		static constexpr Unit fahrenheit = Unit(5.0 / 9.0, celsius);
		/** @brief Degree Réaumur */
		static constexpr Unit reaumur    = Unit(5.0 / 4.0, celsius);
		/** @brief Degree Rankine */
		static constexpr Unit rankine    = Unit(5.0 / 9.0, K);

		/** @brief Degree Celsius, short name */
		static constexpr Unit degC  = celsius;
		/** @brief Degree Fahrenheit, short name */
		static constexpr Unit degF  = fahrenheit;
		/** @brief Degree Réaumur, short name */
		static constexpr Unit degRe = reaumur;
		/** @brief Degree Rankine, short name */
		static constexpr Unit degR  = rankine;
	}

	/** @brief Units related to pressure */
	namespace Pressure
	{
		/** @brief Bar, 100,000 Pascals */
		static constexpr Unit bar   = Unit(1.0e5, Pa);
		/** @brief PSI, Pound per square inch */
		static constexpr Unit psi   = Unit(6894.757293168, Pa);
		/** @brief Inches of mercury at 15.5°C or 60°F */
		static constexpr Unit inHg  = Unit(3376.849669, Pa);
		/** @brief Millimeters of mercury at 15.5°C or 60°F */
		static constexpr Unit mmHg  = Unit(133.322387415, Pa);
		/** @brief Torr */
		static constexpr Unit torr  = Unit(101325.0 / 760.0, Pa);
		/** @brief Inches of water at 15.5°C or 60°F */
		static constexpr Unit inH2O = Unit(248.843004, Pa);
		/** @brief Millimeters of water at 15.5°C or 60°F */
		static constexpr Unit mmH2O = Unit(1.0 / 25.4, inH2O);
		/** @brief Atmosphere */
		static constexpr Unit atm   = Unit(101325.0, Pa);
		/** @brief Technical atmosphere. Same as gravitational metric system */
		static constexpr Unit att   = GM::at;
	}

	/** @brief Power units */
	namespace Power
	{
		/** @brief Electric horsepower */
		static constexpr Unit hpE = Unit(746.0, W);
		/** @brief Mechanical horsepower */
		static constexpr Unit hpI = Unit(745.69987158227022, W);
		/** @brief Boiler horsepower */
		static constexpr Unit hpS = Unit(9812.5, W);
		/** @brief Metric horsepower */
		static constexpr Unit hpM = Unit(735.49875, W);

		/** @brief Volt-Ampere */
		static constexpr Unit VA  = V * A;
		/** @brief Volt-Ampere reactive */
		static constexpr Unit VAR = V * A * iflag;
	}

	/** @brief Horsepower */
	static constexpr Unit hp = Power::hpI;

	/** @brief Energy units */
	namespace Energy
	{
		/** @brief Watt-hour */
		static constexpr Unit Wh  = W * h;
		/** @brief ElectronVolt */
		static constexpr Unit eV  = Unit(1.602176634e-19, J);

		/** @brief Calorie at 4°C */
		static constexpr Unit cal_4    = Unit(4.20400, J);
		/** @brief Calorie at 15°C */
		static constexpr Unit cal_15   = Unit(4.18580, J);
		/** @brief Calorie at 20°C */
		static constexpr Unit cal_20   = Unit(4.18190, J);
		/** @brief Mean calorie */
		static constexpr Unit cal_mean = Unit(4.19002, J);
		/** @brief International table calorie */
		static constexpr Unit cal_it   = Unit(4.18680, J);
		/** @brief Thermochemical calorie */
		static constexpr Unit cal_th   = Unit(4.18400, J);
		/** @brief Thermochemical kilocalorie */
		static constexpr Quantity kcal = kilo * cal_th;

		/** @brief Thermochemical BTU (British Thermal Unit) */
		static constexpr Unit btu_th   = Unit(1054.350, J);
		/** @brief BTU (British Thermal Unit) at 39°F (3.9°C) */
		static constexpr Unit btu_39   = Unit(1059.67, J);
		/** @brief BTU (British Thermal Unit) at 59°F (15°C) */
		static constexpr Unit btu_59   = Unit(1054.80, J);
		/** @brief BTU (British Thermal Unit) at 60°F (15.6°C) */
		static constexpr Unit btu_60   = Unit(1054.68, J);
		/** @brief Mean BTU (British Thermal Unit) */
		static constexpr Unit btu_mean = Unit(1055.87, J);
		/** @brief International Table BTU (British Thermal Unit) */
		static constexpr Unit btu_it   = Unit(1055.05585, J);
		/** @brief International standard ISO 31-4 for BTU */
		static constexpr Unit btu_iso  = Unit(1055.06, J);
		/** @brief Quad, one quadrillion (10^15) BTUs */
		static constexpr Unit quad     = Unit(1055.05585262e15, J);
		/** @brief Ton of cooling, aka 12.000 BTU/h (3.52 kW) */
		static constexpr Quantity tonc = 12000.0 * btu_th / h;

		/** @brief Therm, 100,000 BTUs (US definition) */
		static constexpr Unit therm_us = Unit(100000.0, btu_59);
		/** @brief Therm, 100,000 BTUs (UK definition) */
		static constexpr Unit therm_br = Unit(105505585.257, J);
		/** @brief Therm, 100,000 ISO BTUs */
		static constexpr Unit therm_ec = Unit(100000, btu_iso);
		/** @brief Energy efficiency ratio */
		static constexpr Unit EER      = btu_th / (W * h);
		/** @brief Specific gravity */
		static constexpr Unit SG       = lb / (ft^3);

		/** @brief Ton of TNT (trinitrotoluene, or 2,4,6-trinitrotoluene) */
		static constexpr Unit ton_tnt = Unit(4.184 * giga, J);
 		/** @brief BOE, Barrel of Oil Equivalent */
 		static constexpr Unit boe     = Unit(5.8e6, btu_59);
 		/** @brief FOEB, Fuel of Oil Equivalent Barrel */
 		static constexpr Unit foeb    = Unit(6.05e6, btu_59);
 		/** @brief Hartree, an atomic unit of energy */
 		static constexpr Unit hartree = Unit(4.3597441775e-18, J);
 		static constexpr Unit tonhour = Unit(3516.8528421, Wh);
	}

	static constexpr Unit btu = Energy::btu_it;
	static constexpr Unit cal = Energy::cal_th;

	/** @brief Units used in the textile industry */
	namespace Textile
	{
		static constexpr Unit tex    = Unit(1e-6, kg / m);
		static constexpr Unit denier = Unit(1.0 / 9.0, tex);
		static constexpr Unit span   = Unit(0.2286, m);
		static constexpr Unit finger = Unit(0.1143, m);
		static constexpr Unit nail   = Unit(0.5, finger);
	}

	/** @brief Units used in clinical medicine */
	namespace Clinical
	{
		/** @brief Peripheral vascular resistance unit */
		static constexpr Unit pru           = Unit(milli, Pressure::mmHg * s / L);
		/** @brief Hybrid resistance units, or Wood units */
		static constexpr Unit woodu         = Pressure::mmHg * min / L;
		/** @brief Diopter */
		static constexpr Unit diopter       = m^-1;
		/** @brief Prism diopter */
		static constexpr Unit prism_diopter = Unit::eq(20);
		/** @brief Mesh size, aka number of holes per inch */
		static constexpr Unit mesh          = in^-1;
		/** @brief Charrière, French catheter scale */
		static constexpr Unit charriere     = Unit(1.0 * milli / 3.0, m);
		/** @brief Drop */
		static constexpr Unit drop          = Unit(0.05 * milli, L);
		/** @brief Metabolic equivalent of task */
		static constexpr Unit met           = Unit(3.5 * milli, L / min / kg);
	}

	// Log-based units
	namespace Log
	{
		/** @brief Neper */
		static constexpr Unit neper  = Unit::eq(0);

		/** @brief Bel */
		static constexpr Unit bel  = Unit::eq(1);
		/** @brief Bel. A-weighted */
		static constexpr Unit belA = Unit::eq(2);

		/** @brief Decibel */
		static constexpr Unit dB  = Unit::eq(3);
		/** @brief Decibel. A-weighted */
		static constexpr Unit dBA = Unit::eq(4);
		/** @brief Decibel. Ratio relative to carrier wave */
		static constexpr Unit dBc = Unit::eq(5);

		/** @brief Natural logarithm */
		static constexpr Unit log         = neper;
		/** @brief Base 2 logarithm */
		static constexpr Unit log2        = Unit::eq(6);
		/** @brief Base 10 logarithm */
		static constexpr Unit log10       = Unit::eq(7);
		/** @brief Negative base 10 logarithm */
		static constexpr Unit neglog10    = Unit::eq(8);

		/** @brief Short form for Bels */
		static constexpr Unit B = bel;
		/** @brief Short form for Bels, A-weighted */
		static constexpr Unit BA = belA;

		/** @brief Sound pressure level for Bels */
		static constexpr Unit B_SPL  = Unit(2e-5, Pa * B);
		/** @brief Sound pressure level for decibels */
		static constexpr Unit dB_SPL = Unit(2e-5, Pa * dB);
		/** @brief Voltage relative to 1 volt RMS, regardless of impedance */
		static constexpr Unit BV     = B * V;
		/** @brief Voltage relative to 1 millivolt RMS across 75-ohm impedance */
		static constexpr Unit BmV    = Unit(1e-3, B * V);
		/** @brief Voltage relative to 0.7746 volts RMS (1 mW across 600-ohm resistor) */
 		static constexpr Unit Bu     = Unit(0.7746, B * V);
		/** @brief Voltage relative to 1 microvolt RMS. */
		static constexpr Unit BuV    = Unit(1e-6, B * V);
		/** @brief Voltage relative to 10 nanovolt RMS. */
		static constexpr Unit B10nV  = Unit(10.0 * nano, B * V);
		/** @brief Power relative to 1 Watt. */
		static constexpr Unit BW     = B * W;
		/** @brief Power relative to 1 kiloWatt. */
		static constexpr Unit Bk     = Unit(kilo, B * W);
		/** @brief Voltage relative to 1 volt RMS, regardless of impedance */
		static constexpr Unit dBV    = dB * V;
		/** @brief Voltage relative to 1 millivolt RMS across 75-ohm impedance */
		static constexpr Unit dBmV   = Unit(1e-3, dB * V);
		/** @brief Voltage relative to 0.7746 volts RMS (1 mW across 600-ohm resistor) */
 		static constexpr Unit dBu    = Unit(0.7746, dB * V);
		/** @brief Voltage relative to 1 microvolt RMS. */
		static constexpr Unit dBuV   = Unit(1e-6, dB * V);
		/** @brief Voltage relative to 10 nanovolt RMS. */
		static constexpr Unit dB10nV = Unit(10.0 * nano, dB * V);
		/** @brief Power relative to 1 Watt. */
		static constexpr Unit dBW    = dB * W;
		/** @brief Power relative to 1 kiloWatt. */
		static constexpr Unit dBk    = Unit(kilo, dB * W);
		/** @brief Power relative to 1 milliWatt across 50-ohm impedance */
		static constexpr Unit dBm    = Unit(milli, dB * W);
	}

	/** @brief Units used in chemical and biological laboratories */
	namespace Laboratory
	{
		static constexpr Quantity enzyme_unit = 1.0 * micro * mol / min;

		/** @brief Svedberg, 10^-13 s */
		static constexpr Unit svedberg = Unit(1e-13, s);
		/** @brief Plaque-forming unit */
		static constexpr Unit PFU      = Unit(1.0, count);
		/** @brief pH, unit for acidity */
		static constexpr Unit pH       = mol / L * Log::neglog10;
		static constexpr Unit molarity = mol / L;
		static constexpr Unit molality = mol / kg;
	}

	/** @brief Units related to quantities of data */
	namespace Data
	{
		/** @brief Bit */
		static constexpr Unit bit    = Unit(1, count);
		/** @brief Nibble, 4 bits */
		static constexpr Unit nibble = Unit(4, bit);
		/** @brief Byte, 8 bits */
		static constexpr Unit byte   = Unit(8, bit);
	}

	/** @brief Units related to computation */
	namespace Computation
	{
		/** @brief Floating-point operation */
		static constexpr Unit FLOP  = Unit(1.0, count);
		/** @brief Floating-point operation per second */
		static constexpr Unit FLOPS = FLOP / s;
		/** @brief Million instructions per second */
		static constexpr Unit MIPS  = Unit(1.0e6, count / s);
	}

	/** @brief percent, 1 in one hundred */
	static constexpr Unit percent   = Unit(1e-2, count);
	/** @brief per mille, 1 in one thousand */
	static constexpr Unit per_mille = Unit(1e-3, count);
	/** @brief Basis points, 1 in ten thousand */
	static constexpr Unit bp        = Unit(1e-4, count);
	/** @brief ppm, parts per million */
	static constexpr Unit ppm       = Unit(1e-6, count);
	/** @brief ppb, parts per billion */
	static constexpr Unit ppb       = Unit(1e-9, count);

	/** @brief RPM, revolutions per minute */
	static constexpr Unit rpm = Unit(2.0 * Constants::pi / 60.0, rad / s);
	/** @brief CFM, cubic feet per minute */
	static constexpr Unit CFM = (ft^3) / min;

	static constexpr Quantity convert(const Quantity& start, const Unit& result)
	{
		if(start.unit().base_units() != result.base_units()) return Unit::error();

		if(start.unit().base_units() == K.base_units())
		{
			Quantity temp;

			/**/ if(start.unit() == Temperature::degC ) temp = ((start.magnitude() -  0.0) * 1.0 / 1.0 + 273.15) * K;
			else if(start.unit() == Temperature::degF ) temp = ((start.magnitude() - 32.0) * 5.0 / 9.0 + 273.15) * K;
			else if(start.unit() == Temperature::degR ) temp = ((start.magnitude() -  0.0) * 5.0 / 9.0 + 273.15) * K;
			else if(start.unit() == Temperature::degRe) temp = ((start.magnitude() -  0.0) * 1.0 / 0.8 + 273.15) * K;
			else if(start.unit() == kelvin            ) temp = start;

			/**/ if(result == kelvin            ) return temp;
			else if(result == Temperature::degF ) return ((temp.magnitude() - 273.15) * 9.0 / 5.0 + 32.0) * result;
			else if(result == Temperature::degR ) return ((temp.magnitude() - 273.15) * 9.0 / 5.0 +  0.0) * result;
			else if(result == Temperature::degRe) return ((temp.magnitude() - 273.15) * 0.8 / 1.0 +  0.0) * result;
			else if(result == Temperature::degC ) return ((temp.magnitude() - 273.15) * 1.0 / 1.0 +  0.0) * result;

			return Unit::error();
		}

		return start.magnitude() * ((double)start.unit().multiplier() / (double)result.multiplier()) * result;
	}
}
