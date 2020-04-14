#pragma once

#include "Unit.h"
#include "Quantity.h"

namespace Units
{
	// The standard SI prefixes
	constexpr double yotta = 1e+24;
	constexpr double zetta = 1e+21;
	constexpr double exa   = 1e+18;
	constexpr double peta  = 1e+15;
	constexpr double tera  = 1e+12;
	constexpr double giga  = 1e+9;
	constexpr double mega  = 1e+6;
	constexpr double kilo  = 1e+3;
	constexpr double hecto = 1e+2;
	constexpr double deca  = 1e+1;
	constexpr double deci  = 1e-1;
	constexpr double centi = 1e-2;
	constexpr double milli = 1e-3;
	constexpr double micro = 1e-6;
	constexpr double nano  = 1e-9;
	constexpr double pico  = 1e-12;
	constexpr double femto = 1e-15;
	constexpr double atto  = 1e-18;
	constexpr double zepto = 1e-21;
	constexpr double yocto = 1e-24;

	// Binary prefixes, pending adoption
	constexpr double kibi = 1024;
	constexpr double mebi = 1024 * kibi;
	constexpr double gibi = 1024 * mebi;
	constexpr double tebi = 1024 * gibi;
	constexpr double pebi = 1024 * tebi;
	constexpr double exbi = 1024 * pebi;
	constexpr double zebi = 1024 * exbi;
	constexpr double yobi = 1024 * zebi;

	// Handy values
	namespace Constants
	{
		constexpr double pi  = 3.14159265358979323846264338327950288;
		constexpr double tau = 6.28318530717958647692528676655900576;
	}

	constexpr Unit one;
	constexpr Unit error   = Unit::error();
	constexpr Unit none    = one;

	// The base SI units
	constexpr Unit meter    = Unit::meter();
	constexpr Unit kilogram = Unit::kilogram();
	constexpr Unit second   = Unit::second();
	constexpr Unit ampere   = Unit::ampere();
	constexpr Unit kelvin   = Unit::kelvin();
	constexpr Unit mole     = Unit::mole();
	constexpr Unit radian   = Unit::radian();
	constexpr Unit candela  = Unit::candela();
	constexpr Unit currency = Unit::currency();
	constexpr Unit count    = Unit::count();

	constexpr Unit m   = meter;
	constexpr Unit kg  = kilogram;
	constexpr Unit s   = second;
	constexpr Unit A   = ampere;
	constexpr Unit K   = kelvin;
	constexpr Unit mol = mole;
	constexpr Unit rad = radian;
	constexpr Unit Cd  = candela;

	/** @brief i flag, imaginary flag */
	constexpr Unit iflag = Unit::iflag();

	// Derived SI units
	constexpr Unit steradian      = radian * radian;
	constexpr Unit hertz          = second^-1;
	constexpr Unit newton         = kilogram * meter / (second^2);
	constexpr Unit pascal         = newton / (meter^2);
	constexpr Unit joule          = newton * meter;
	constexpr Unit watt           = joule / second;
	constexpr Unit coulomb        = ampere * second;
	constexpr Unit volt           = watt / ampere;
	constexpr Unit farad          = coulomb / volt;
	constexpr Unit ohm            = volt / ampere;
	constexpr Unit siemens        = ampere / volt;
	constexpr Unit weber          = volt * second;
	constexpr Unit tesla          = weber / (meter^2);
	constexpr Unit henry          = weber / ampere;
	constexpr Unit degree_celsius = kelvin;
	constexpr Unit lumen          = candela * steradian;
	constexpr Unit lux            = lumen / (meter^-2);
	constexpr Unit becquerel      = count / second;
	constexpr Unit gray           = joule / kilogram;
	constexpr Unit sievert        = joule / kilogram;
	constexpr Unit katal          = mol / second;

	constexpr Unit sr  = steradian;
	constexpr Unit Hz  = hertz;
	constexpr Unit N   = newton;
	constexpr Unit Pa  = pascal;
	constexpr Unit J   = joule;
	constexpr Unit W   = watt;
	constexpr Unit C   = coulomb;
	constexpr Unit V   = volt;
	constexpr Unit F   = farad;
	constexpr Unit S   = siemens;
	constexpr Unit Wb  = weber;
	constexpr Unit T   = tesla;
	constexpr Unit H   = henry;
	constexpr Unit lm  = lumen;
	constexpr Unit lx  = lux;
	constexpr Unit Bq  = becquerel;
	constexpr Unit Gy  = gray;
	constexpr Unit Sv  = sievert;
	constexpr Unit kat = katal;

	// Not approved for use alone (needed for use with prefixes)
	constexpr Unit     liter = Unit(0.001, m^3);
	constexpr Quantity gram  = 0.001 * kg;

	// Alternate (non-US) spellings:
	constexpr Unit metre = meter;
	constexpr Unit litre = liter;
	constexpr double deka = deca;

	// Short unit names
	// Distance units
	constexpr Quantity cm = centi * m;
	constexpr Quantity km = kilo  * m;
	constexpr Quantity mm = milli * m;
	constexpr Quantity nm = nano  * m;

	// Volume units
	constexpr Unit L      = liter;
	constexpr Quantity mL = milli * L;

	// Mass units
	constexpr Quantity g     = gram;
	constexpr Quantity mg    = milli  *  g;
	constexpr Quantity tonne = 1000.0 * kg;
	constexpr Quantity t     = tonne;

	// Atomic mass units
	constexpr Unit Da = Unit(1.66053906660e-27, kg);
	constexpr Unit u  = Da;

	/** @brief Units from the CGS system */
	namespace CGS
	{
		constexpr double c_const    = 29979245800.0; // speed of light in cm/s
		constexpr Unit erg          = Unit(1e-7, J);
		constexpr Unit dyn          = Unit(1e-5, N);
		constexpr Unit barye        = Unit(0.1, Pa);
		constexpr Unit gal          = Unit(0.01, m / (s^2));
		constexpr Unit poise        = Unit(0.1, Pa * s);
		constexpr Unit stokes       = Unit(1e-4, (m^2) / s);
		constexpr Unit kayser       = Unit(100.0, one / m);
		constexpr Unit oersted      = Unit(1000.0 / 4.0 / Constants::pi, A / m);
		constexpr Unit gauss        = Unit(1e-4, T);
		constexpr Unit debye        = Unit(1.0 / (c_const * 1e20), C * m);
		constexpr Unit maxwell      = Unit(1e-8, Wb);
		constexpr Unit biot         = Unit(10.0, A);
		constexpr Unit gilbert      = Unit(0.01, oersted * m);
		constexpr Unit stilb        = Unit(10000.0, Cd / (m^2));
		constexpr Unit lambert      = Unit(10000.0 / Constants::pi, Cd / (m^2));
		constexpr Unit phot         = Unit(10000, lx);
		constexpr Unit curie        = Unit(3.7e10, Bq);
		constexpr Unit roentgen     = Unit(2.58e-4, C / kg);
		constexpr Unit REM          = Unit(0.01, Sv);
		constexpr Unit RAD          = Unit(100000, erg / kg);
		constexpr Unit emu          = Unit(0.001, A * m * m);
		constexpr Unit langley      = Unit(41840.0, J / (m^2));
		constexpr Unit unitpole     = Unit(1.256637061436e-7, Wb);
		constexpr Unit statC_charge = Unit(10.0 / c_const, C);
		constexpr Unit statC_flux   = Unit(10.0 / (4.0 * Constants::pi * c_const), V * m);

		constexpr Quantity abOhm    = 1e-9 * ohm;
		constexpr Quantity abFarad  = 1e09 * F;
		constexpr Quantity abHenry  = 1e-9 * H;
		constexpr Quantity abVolt   = 1e-8 * V;

		constexpr Quantity statV     = c_const * abVolt;
		constexpr Quantity statT     = c_const * 1e-4 * T;
		constexpr Quantity statHenry = c_const * c_const * abHenry;
		constexpr Quantity statOhm   = c_const * c_const * abOhm;
		constexpr Quantity statFarad = (1.0 / (c_const * c_const)) * abFarad;
	}

	/** @brief meter-gram-force system of units (aka gravitational metric system) */
	namespace GM
	{
		constexpr Unit pond     = Unit(980.665, CGS::dyn);
		constexpr Unit hyl      = Unit(9.80665, kg);
		constexpr Unit at       = Unit(98066.5, Pa); // technical atmosfere
		constexpr Unit poncelet = Unit(980.665, W);
		constexpr Unit PS       = Unit(735.49875, W); // metric horsepower
	}

	/** @brief Meter tonne second system of units */
	namespace MTS
	{
		constexpr Unit sthene  = Unit(1000.0, N);
		constexpr Unit pieze   = Unit(1000.0, Pa);
		constexpr Unit thermie = Unit(4.1868 * mega, J);
	}

	/** @brief Units of time */
	namespace Time
	{
		/** @brief Minute */
		constexpr Unit min  = Unit(60.0, s);
		/** @brief Hour */
		constexpr Unit hour = Unit(3600, s);
		/** @brief Day */
		constexpr Unit day  = Unit(24, hour);
		/** @brief Week */
		constexpr Unit week = Unit(7, day);
		/** @brief Median calendar year */
		constexpr Unit yr   = Unit(8760.0, hour);

		/** @brief Julian year */
		constexpr Unit aj   = Unit(365.25, day);
		/** @brief Standard year */
		constexpr Unit year = aj;

		/** @brief Fortnight (two weeks) */
		constexpr Quantity fortnight = 14 * day;
		/** @brief Sidereal day */
		constexpr Quantity sday = 365.24 / 366.24 * day;
		/** @brief Sidereal year */
		constexpr Quantity syr  = 365.256363004 * day;
		/** @brief Mean tropical year */
		constexpr Quantity at   = 365.24219 * day;
		/** @brief Gregorian year */
		constexpr Quantity ag   = 365.2425 * day;
		/** @brief Synodal month */
		constexpr Quantity mos  = 29.53059 * day;
		/** @brief Mean Julian month */
		constexpr Quantity moj  = 1.0 / 12.0 * aj;
		/** @brief mean Gregorian month */
		constexpr Quantity mog  = 1.0 / 12.0 * ag;
	}

	constexpr Unit h   = Time::hour;
	constexpr Unit min = Time::min;

	/** @brief International units */
	namespace i
	{
		constexpr Unit grain = Unit(64.79891 * micro, kg);

		constexpr Unit inch   = Unit(0.0254, m);
		constexpr Unit foot   = Unit(0.3048, m);
		constexpr Unit yard   = Unit(0.9144, m);
		constexpr Unit mile   = Unit(1609.344, m);
		constexpr Unit league = Unit(3.0, mile);

		constexpr Unit cord       = Unit(128.0, foot^3);
		constexpr Unit board_foot = Unit(144.0, inch^3);
		constexpr Unit mil        = Unit(milli, inch);
		constexpr Unit circ_mil   = Unit(Constants::pi / 4.0, mil^2);

		constexpr Quantity point = (0.127 / 360.0) * m;
		constexpr Quantity pica  = (0.127 / 30.0) * m;
		constexpr Quantity hand  = 4.0 * inch;
	}

	constexpr Unit in   = i::inch;
	constexpr Unit ft   = i::foot;
	constexpr Unit yd   = i::yard;
	constexpr Unit mile = i::mile;

	/** @brief Avoirdupois units, common international standard */
	namespace av
	{
		constexpr Unit dram              = Unit(0.0017718451953125, kg);
		constexpr Unit ounce             = Unit(16.0, dram);
		constexpr Unit pound             = Unit(0.45359237, kg);
		constexpr Unit hundredweight     = Unit(100.0, pound);
		constexpr Unit longhundredweight = Unit(112.0, pound);
		constexpr Unit ton               = Unit(2000.0, pound);
		constexpr Unit longton           = Unit(2240.0, pound);
		constexpr Unit stone             = Unit(14.0, pound);
		constexpr Unit poundal           = Unit(0.138254954376, N);
		constexpr Unit lbf               = Unit(4.4482216152605, N);
		constexpr Unit ozf               = Unit(1.0 / 16.0, lbf);
		constexpr Unit slug              = lbf * (s^2) / ft;
	}

	constexpr Unit lb  = av::pound;
	constexpr Unit ton = av::ton;
	constexpr Unit oz  = av::ounce;
	constexpr Unit lbf = av::lbf;

	/** @brief Troy units */
	namespace Troy
	{
		constexpr Unit pennyweight = Unit(24.0, i::grain);
		constexpr Unit oz          = Unit(0.0311034768, kg);
		constexpr Unit pound       = Unit(12.0, oz);
	}

	/** @brief Units used in the United States */
	namespace US
	{
		constexpr Unit foot    = Unit(1200.0 / 3937.0, m);
		constexpr Unit inch    = Unit(1.0 / 12.0, foot);
		constexpr Unit mil     = Unit(0.001, inch);
		constexpr Unit yard    = Unit(3.0, foot);
		constexpr Unit rod     = Unit(16.5, foot);
		constexpr Unit chain   = Unit(4.0, rod);
		constexpr Unit link    = Unit(0.01, chain);
		constexpr Unit furlong = Unit(10.0, chain);
		constexpr Unit mile    = Unit(8.0, furlong);
		constexpr Unit league  = Unit(3.0, mile);

		namespace Engineers
		{
			constexpr Unit chain = Unit(100.0, foot);
			constexpr Unit link  = Unit(0.01, chain);
		}

		// Area
		constexpr Unit acre      = Unit(43560.0, foot^2);
		constexpr Unit homestead = Unit(160.0, acre);
		constexpr Unit section   = Unit(640.0, acre);
		constexpr Unit township  = Unit(36.0, section);

		// Volume
		constexpr Unit minim    = Unit(61.611519921875 * micro, L);
		constexpr Unit dram     = Unit(60.0, minim);
		constexpr Unit floz     = Unit(29.5735295625e-6, m^3);
		constexpr Unit tbsp     = Unit(0.5, floz);
		constexpr Unit tsp      = Unit(1.0 / 6.0, floz);
		constexpr Unit pinch    = Unit(0.125, tsp);
		constexpr Unit dash     = Unit(0.5, pinch);
		constexpr Unit shot     = Unit(3.0, tbsp);
		constexpr Unit gill     = Unit(4.0, floz);
		constexpr Unit cup      = Unit(8.0, floz);
		constexpr Unit pint     = Unit(2.0, cup);
		constexpr Unit quart    = Unit(2.0, pint);
		constexpr Unit cord     = Unit(128.0, ft^3);
		constexpr Unit gallon   = Unit(3.785411784, L);
		constexpr Unit flbarrel = Unit(31.5, gallon);
		constexpr Unit barrel   = Unit(42.0, gallon);
		constexpr Unit hogshead = Unit(63.0, gallon);
		constexpr Unit fifth    = Unit(0.2,  gallon);

		/** @brief US customary dry measurements */
		namespace Dry
		{
			constexpr Unit pint   = Unit(0.5506104713575, L);
			constexpr Unit quart  = Unit(2.0, pint);
			constexpr Unit gallon = Unit(4.0, quart);
			constexpr Unit peck   = Unit(2.0, gallon);
			constexpr Unit bushel = Unit(35.23907016688, L);
			constexpr Unit barrel = Unit(7056.0, in^3);
			constexpr Unit sack   = Unit(3.0, bushel);
			constexpr Unit strike = Unit(2.0, bushel);
		}

		namespace Grain
		{
			constexpr Unit bushel_corn   = Unit(56.0, av::pound);
			constexpr Unit bushel_wheat  = Unit(60.0, av::pound);
			constexpr Unit bushel_barley = Unit(48.0, av::pound);
			constexpr Unit bushel_oats   = Unit(32.0, av::pound);
		}
	}

	constexpr Unit acre = US::acre;
	constexpr Unit gal  = US::gallon;

	/** @brief FDA-specific volume units in metric */
	namespace Metric
	{
		constexpr Unit tbsp        = Unit(0.015, L);
		constexpr Unit tsp         = Unit(0.005, L);
		constexpr Unit floz        = Unit(0.030, L);
		constexpr Unit cup         = Unit(0.250, L);
		constexpr Unit cup_uslegal = Unit(0.240, L);
		constexpr Unit carat       = Unit(0.0002, kg);
	}

	/** @brief Some Canada specific variants on the us units */
	namespace Canada
	{
		constexpr Unit tbsp     = Unit(0.015, L);
		constexpr Unit tsp      = Unit(0.005, L);
		constexpr Unit cup      = Unit(0.250, L);
		constexpr Unit cup_trad = Unit(0.2273045, L);

		namespace Grain
		{
			constexpr Unit bushel_oats = Unit(34.0, av::pound);
		}
	}

	/** @brief Some Australia specific variants on the us units */
	namespace Australia
	{
		constexpr Unit tbsp = Unit(0.020, L);
		constexpr Unit tsp  = Unit(0.005, L);
		constexpr Unit cup  = Unit(0.250, L);
	}

	/** @brief Imperial system units (British) */
	namespace Imp
	{
		constexpr Unit inch = Unit(0.02539998, m);
		constexpr Unit foot = Unit(12.0, inch);

		constexpr Unit thou          = Unit(0.0000254, m);
		constexpr Unit barleycorn    = Unit(1.0 / 3.0, inch);
		constexpr Unit rod           = Unit(16.5, foot);
		constexpr Unit chain         = Unit(4.0, rod);
		constexpr Unit link          = Unit(0.01, chain);
		constexpr Unit pace          = Unit(2.5, foot);
		constexpr Unit yard          = Unit(3.0, foot);
		constexpr Unit furlong       = Unit(201.168, m);
		constexpr Unit league        = Unit(4828.032, m);
		constexpr Unit mile          = Unit(5280.0, foot);
		constexpr Unit nautical_mile = Unit(6080, foot);
		constexpr Unit knot          = nautical_mile / h;
		constexpr Unit acre          = Unit(4840.0, yard^2);

		// Area
		constexpr Unit perch = Unit(25.29285264, m^2);
		constexpr Unit rood  = Unit(1011.7141056, m^2);

		// Volume
		constexpr Unit gallon = Unit(4.54609, L);
		constexpr Unit quart  = Unit(0.25, gallon);
		constexpr Unit pint   = Unit(0.5, quart);
		constexpr Unit gill   = Unit(0.25, pint);
		constexpr Unit cup    = Unit(0.5, pint);
		constexpr Unit floz   = Unit(0.1, cup);
		constexpr Unit tbsp   = Unit(0.5, floz);
		constexpr Unit tsp    = Unit(1.0 / 3.0, tbsp);

		constexpr Unit barrel = Unit(36.0, gallon);
		constexpr Unit peck   = Unit(2.0, gallon);
		constexpr Unit bushel = Unit(4.0, peck);
		constexpr Unit dram   = Unit(1.0 / 8.0, floz);
		constexpr Unit minim  = Unit(1.0 / 60.0, dram);

		// Weight
		constexpr Unit drachm        = Unit(0.0017718451953125, kg);
		constexpr Unit stone         = Unit(6.35029318, kg);
		constexpr Unit hundredweight = Unit(112.0,  av::pound);
		constexpr Unit ton           = Unit(2240.0, av::pound);
		constexpr Unit slug          = Unit(14.59390294, kg);
	}

	namespace Apothecaries
	{
		constexpr Unit floz         = Imp::floz;
		constexpr Unit minim        = Unit(59.1938802083333333333 * micro, L);
		constexpr Unit scruple      = Unit(20.0, i::grain);
		constexpr Unit drachm       = Unit(3.0, scruple);
		constexpr Unit ounce        = Unit(8.0, drachm);
		constexpr Unit pound        = Unit(12.0, ounce);
		constexpr Unit pint         = Imp::pint;
		constexpr Unit gallon       = Imp::gallon;
		constexpr Unit metric_ounce = Unit(0.028, kg);
	}

	/** @brief Nautical units */
	namespace Nautical
	{
		constexpr Unit fathom = Unit(2.0, yd);
		constexpr Unit cable  = Unit(120, fathom);
		constexpr Unit mile   = Unit(1852.0, m);
		constexpr Unit knot   = mile / h;
		constexpr Unit league = Unit(3.0, mile);
	}

	/** @brief Some historical Japanese units */
	namespace Japan
	{
		constexpr Unit shaku = Unit(10.0 / 33.0, m);
		constexpr Unit sun   = Unit(0.1, shaku);
		constexpr Unit ken   = Unit(1.0 + 9.0 / 11.0, m);
		constexpr Unit tsubo = Unit(100.0 / 30.25, m^2);
		constexpr Unit sho   = Unit(2401.0 / 1331.0, L);
		constexpr Unit kan   = Unit(15.0 / 4.0, kg);
		constexpr Unit go    = Unit(2401.0 / 13310, L);
		constexpr Unit cup   = Unit(0.2, L);
	}

	/** @brief Some historical chinese units */
	namespace Chinese
	{
		constexpr Unit jin   = Unit(0.5, kg);
		constexpr Unit liang = Unit(0.0001, kg);
		constexpr Unit qian  = Unit(0.00001, kg);

		constexpr Unit li    = Unit(500.0, m);
		constexpr Unit cun   = Unit(10.0 / 300.0, m);
		constexpr Unit chi   = Unit(10.0, cun);
		constexpr Unit zhang = Unit(10.0, chi);
	}

	/** @brief Typographic units for typesetting or printing */
	namespace Typographic
	{
		namespace American
		{
			constexpr Unit line  = Unit(1.0 / 12.0, in);
			constexpr Unit point = Unit(1.0 / 6.0, line);
			constexpr Unit pica  = Unit(12.0, point);
			constexpr Unit twip  = Unit(1.0 / 20.0, point);
		}

		namespace Printers
		{
			constexpr Unit point = Unit(0.013837, in);
			constexpr Unit pica  = Unit(12.0, point);
		}

		namespace French
		{
			constexpr Unit point  = Unit(15.625 / 41559.0, m);
			constexpr Unit ligne  = Unit(6.0, point);
			constexpr Unit pouce  = Unit(12.0, ligne);
			constexpr Unit didot  = point;
			constexpr Unit cicero = Unit(12.0, didot);
			constexpr Unit pied   = Unit(12.0, pouce);
			constexpr Unit toise  = Unit(6.0, pied);
		}

		namespace Metric
		{
			constexpr Unit point = Unit(375.0 * micro, m);
			constexpr Unit quart = Unit(0.25 * milli, m);
		}
	}

	/** @brief Units related to distance */
	namespace Distance
	{
		/** @brief Smoot, or Oliver Smoot's height as of October 1958 (see https://en.wikipedia.org/wiki/Smoot) */
		constexpr Quantity smoot     = 67.0 * in;
		/** @brief Cubit */
		constexpr Quantity cubit     = 18.0 * in;
		/** @brief Long cubit */
		constexpr Quantity longcubit = 21.0 * in;

		/** @brief Light-year */
		constexpr Unit ly        = Unit(9.4607304725808e15, m);
		/** @brief Astronomical unit */
		constexpr Unit au        = Unit(149597870700.0, m);
		/** @brief Astronomical unit (old definition) */
		constexpr Unit au_old    = Unit(149597900000.0, m);
		/** @brief Angstrom, 10^-10 m (100 pm) */
		constexpr Unit angstrom  = Unit(1e-10, m);
		/** @brief Parsec, as defined by the International Astronomical Union */
		constexpr Unit parsec    = Unit(3.08567758149136727891e16, m);

		/** @brief Arpent (US) */
		constexpr Unit arpent_us = Unit(58.47131, m);
		/** @brief Arpent (FR) */
		constexpr Unit arpent_fr = Unit(71.46466, m);
		/** @brief The X unit */
		constexpr Unit xu        = Unit(1.0021e-13, m);
	}

	/** @brief Units related to compass directions */
	namespace Direction
	{
		/** @brief North */
		constexpr Quantity north =  1.0 * iflag;
		/** @brief South */
		constexpr Quantity south = -1.0 * iflag;
		/** @brief East */
		constexpr Quantity east  =  1.0;
		/** @brief West */
		constexpr Quantity west  = -1.0;

		/** @brief North, short name */
		constexpr Quantity N = north;
		/** @brief South, short name */
		constexpr Quantity S = south;
		/** @brief East, short name */
		constexpr Quantity E = east;
		/** @brief West, short name */
		constexpr Quantity W = west;
	}

	/** @brief Additional Area units */
	namespace Area
	{
		constexpr Unit are     = Unit(100.0, m^2);
		constexpr Unit hectare = Unit(100.0, are);
		/** @brief Barn. 10^−28 m^2 (or 100 fm^2) */
		constexpr Unit barn    = Unit(1e-28, m^2);
		constexpr Unit arpent  = Unit(0.84628, acre);
	}

	/** @brief Additional mass units */
	namespace Mass
	{
		constexpr Quantity quintal   = 100.0 * kg;
		constexpr Unit ton_assay     = Unit((29.0 + 1.0 / 6.0) * milli, kg);
		constexpr Unit longton_assay = Unit((32.0 + 2.0 / 3.0) * milli, kg);
	}

	/** @brief Some extra volume units */
	namespace Volume
	{
		constexpr Unit stere     = m^3;
		constexpr Unit acre_foot = acre * US::foot;
		constexpr Unit drum      = Unit(55.0, US::gallon);
	}

	/** @brief Angle measurement units */
	namespace Angle
	{
		/** @brief Degree */
		constexpr Unit deg    = Unit(Constants::pi  / 180.0, rad);
		/** @brief Gradian */
		constexpr Unit grad   = Unit(Constants::pi  / 200.0, rad);
		/** @brief Binary radian */
		constexpr Unit brad   = Unit(Constants::tau / 256.0, rad);

		/** @brief Gon */
		constexpr Unit gon    = Unit(9.0 / 10.0, deg);
		/** @brief Arc minute */
		constexpr Unit arcmin = Unit(1.0 / 60.0, deg);
		/** @brief Arc second */
		constexpr Unit arcsec = Unit(1.0 / 60.0, arcmin);
	}

	/** @brief Units related to temperature */
	namespace Temperature
	{
		/** @brief Degree Celsius */
		constexpr Unit celsius    = Unit(1.0, K);
		/** @brief Degree Fahrenheit */
		constexpr Unit fahrenheit = Unit(5.0 / 9.0, celsius);
		/** @brief Degree Réaumur */
		constexpr Unit reaumur    = Unit(5.0 / 4.0, celsius);
		/** @brief Degree Rankine */
		constexpr Unit rankine    = Unit(5.0 / 9.0, K);

		/** @brief Degree Celsius, short name */
		constexpr Unit degC  = celsius;
		/** @brief Degree Fahrenheit, short name */
		constexpr Unit degF  = fahrenheit;
		/** @brief Degree Réaumur, short name */
		constexpr Unit degRe = reaumur;
		/** @brief Degree Rankine, short name */
		constexpr Unit degR  = rankine;
	}

	/** @brief Units related to pressure */
	namespace Pressure
	{
		/** @brief Bar, 100,000 Pascals */
		constexpr Unit bar   = Unit(1.0e5, Pa);
		/** @brief PSI, Pound per square inch */
		constexpr Unit psi   = Unit(6894.757293168, Pa);
		/** @brief Inches of mercury at 15.5°C or 60°F */
		constexpr Unit inHg  = Unit(3376.849669, Pa);
		/** @brief Millimeters of mercury at 15.5°C or 60°F */
		constexpr Unit mmHg  = Unit(133.322387415, Pa);
		/** @brief Torr */
		constexpr Unit torr  = Unit(101325.0 / 760.0, Pa);
		/** @brief Inches of water at 15.5°C or 60°F */
		constexpr Unit inH2O = Unit(248.843004, Pa);
		/** @brief Millimeters of water at 15.5°C or 60°F */
		constexpr Unit mmH2O = Unit(1.0 / 25.4, inH2O);
		/** @brief Atmosphere */
		constexpr Unit atm   = Unit(101325.0, Pa);
		/** @brief Technical atmosphere. Same as gravitational metric system */
		constexpr Unit att   = GM::at;
	}

	/** @brief Power units */
	namespace Power
	{
		/** @brief Electric horsepower */
		constexpr Unit hpE = Unit(746.0, W);
		/** @brief Mechanical horsepower */
		constexpr Unit hpI = Unit(745.69987158227022, W);
		/** @brief Boiler horsepower */
		constexpr Unit hpS = Unit(9812.5, W);
		/** @brief Metric horsepower */
		constexpr Unit hpM = Unit(735.49875, W);

		/** @brief Volt-Ampere */
		constexpr Unit VA  = V * A;
		/** @brief Volt-Ampere reactive */
		constexpr Unit VAR = V * A * iflag;
	}

	/** @brief Horsepower */
	constexpr Unit hp = Power::hpI;

	/** @brief Energy units */
	namespace Energy
	{
		/** @brief Watt-hour */
		constexpr Unit Wh  = W * h;
		/** @brief ElectronVolt */
		constexpr Unit eV  = Unit(1.602176634e-19, J);

		/** @brief Calorie at 4°C */
		constexpr Unit cal_4    = Unit(4.20400, J);
		/** @brief Calorie at 15°C */
		constexpr Unit cal_15   = Unit(4.18580, J);
		/** @brief Calorie at 20°C */
		constexpr Unit cal_20   = Unit(4.18190, J);
		/** @brief Mean calorie */
		constexpr Unit cal_mean = Unit(4.19002, J);
		/** @brief International table calorie */
		constexpr Unit cal_it   = Unit(4.18680, J);
		/** @brief Thermochemical calorie */
		constexpr Unit cal_th   = Unit(4.18400, J);
		/** @brief Thermochemical kilocalorie */
		constexpr Quantity kcal = kilo * cal_th;

		/** @brief Thermochemical BTU (British Thermal Unit) */
		constexpr Unit btu_th   = Unit(1054.350, J);
		/** @brief BTU (British Thermal Unit) at 39°F (3.9°C) */
		constexpr Unit btu_39   = Unit(1059.67, J);
		/** @brief BTU (British Thermal Unit) at 59°F (15°C) */
		constexpr Unit btu_59   = Unit(1054.80, J);
		/** @brief BTU (British Thermal Unit) at 60°F (15.6°C) */
		constexpr Unit btu_60   = Unit(1054.68, J);
		/** @brief Mean BTU (British Thermal Unit) */
		constexpr Unit btu_mean = Unit(1055.87, J);
		/** @brief International Table BTU (British Thermal Unit) */
		constexpr Unit btu_it   = Unit(1055.05585, J);
		/** @brief International standard ISO 31-4 for BTU */
		constexpr Unit btu_iso  = Unit(1055.06, J);
		/** @brief Quad, one quadrillion (10^15) BTUs */
		constexpr Unit quad     = Unit(1055.05585262e15, J);
		/** @brief Ton of cooling, aka 12.000 BTU/h (3.52 kW) */
		constexpr Quantity tonc = 12000.0 * btu_th / h;

		/** @brief Therm, 100,000 BTUs (US definition) */
		constexpr Unit therm_us = Unit(100000.0, btu_59);
		/** @brief Therm, 100,000 BTUs (UK definition) */
		constexpr Unit therm_br = Unit(105505585.257, J);
		/** @brief Therm, 100,000 ISO BTUs */
		constexpr Unit therm_ec = Unit(100000, btu_iso);
		/** @brief Energy efficiency ratio */
		constexpr Unit EER      = btu_th / (W * h);
		/** @brief Specific gravity */
		constexpr Unit SG       = lb / (ft^3);

		/** @brief Ton of TNT (trinitrotoluene, or 2,4,6-trinitrotoluene) */
		constexpr Unit ton_tnt = Unit(4.184 * giga, J);
		constexpr Unit boe     = Unit(5.8e6, btu_59);
		constexpr Unit foeb    = Unit(6.05e6, btu_59);
		constexpr Unit hartree = Unit(4.35974465054e-18, J);
		constexpr Unit tonhour = Unit(3516.8528421, Wh);
	}

	constexpr Unit btu = Energy::btu_it;
	constexpr Unit cal = Energy::cal_th;

	/** @brief Units used in the textile industry */
	namespace Textile
	{
		constexpr Unit tex    = Unit(1e-6, kg / m);
		constexpr Unit denier = Unit(1.0 / 9.0, tex);
		constexpr Unit span   = Unit(0.2286, m);
		constexpr Unit finger = Unit(0.1143, m);
		constexpr Unit nail   = Unit(0.5, finger);
	}

	/** @brief Units used in clinical medicine */
	namespace Clinical
	{
		/** @brief Peripheral vascular resistance unit */
		constexpr Unit pru           = Unit(milli, Pressure::mmHg * s / L);
		/** @brief Hybrid resistance units, or Wood units */
		constexpr Unit woodu         = Pressure::mmHg * min / L;
		/** @brief Diopter */
		constexpr Unit diopter       = m^-1;
		/** @brief Prism diopter */
		constexpr Unit prism_diopter = Unit::eq(20);
		/** @brief Mesh size, aka number of holes per inch */
		constexpr Unit mesh          = in^-1;
		/** @brief Charrière, French catheter scale */
		constexpr Unit charriere     = Unit(1.0 * milli / 3.0, m);
		/** @brief Drop */
		constexpr Unit drop          = Unit(0.05 * milli, L);
		/** @brief Metabolic equivalent of task */
		constexpr Unit met           = Unit(3.5 * milli, L / min / kg);
	}

	// Log-based units
	namespace Log
	{
		/** @brief Neper */
		constexpr Unit neper  = Unit::eq(0);
		/** @brief Neper. Power unit */
		constexpr Unit neperP = Unit::eq(1);

		/** @brief Bel */
		constexpr Unit bel  = Unit::eq(2);
		/** @brief Bel. A-weighted */
		constexpr Unit belA = Unit::eq(3);
		/** @brief Bel. Assume power always */
		constexpr Unit belP = Unit::eq(4);

		/** @brief Decibel */
		constexpr Unit dB  = Unit::eq(5);
		/** @brief Decibel. A-weighted */
		constexpr Unit dBA = Unit::eq(6);
		/** @brief Decibel. Ratio relative to carrier wave */
		constexpr Unit dBc = Unit::eq(7);
		/** @brief Decibel. Assume power always */
		constexpr Unit dBP = Unit::eq(8);

		/** @brief Natural logarithm */
		constexpr Unit log         = neper;
		/** @brief Base 2 logarithm */
		constexpr Unit log2        = Unit::eq(10);
		/** @brief Base 10 logarithm */
		constexpr Unit log10       = Unit::eq(11);
		/** @brief Negative base 10 logarithm */
		constexpr Unit neglog10    = Unit::eq(12);
		/** @brief Negative base 100 logarithm */
		constexpr Unit neglog100   = Unit::eq(13);
		/** @brief Negative base 1000 logarithm */
		constexpr Unit neglog1000  = Unit::eq(14);
		/** @brief Negative base 50000 logarithm */
		constexpr Unit neglog50000 = Unit::eq(15);

		/** @brief Short form for Bels */
		constexpr Unit B = bel;
		/** @brief Short form for Bels, A-weighted */
		constexpr Unit BA = belA;
		/** @brief Short form for Bels. Assume always power */
		constexpr Unit BP = belP;

		/** @brief Sound pressure level for Bels */
		constexpr Unit B_SPL  = Unit(2e-5, Pa * B);
		/** @brief Sound pressure level for decibels */
		constexpr Unit dBSPL  = Unit(2e-5, Pa * dB);
		/** @brief Voltage relative to 1 volt RMS, regardless of impedance */
		constexpr Unit BV     = B * V;
		/** @brief Voltage relative to 1 millivolt RMS across 75-ohm impedance */
		constexpr Unit BmV    = Unit(1e-3, B * V);
		/** @brief Voltage relative to 1 microvolt RMS. */
		constexpr Unit BuV    = Unit(1e-6, B * V);
		/** @brief Voltage relative to 10 nanovolt RMS. */
		constexpr Unit B10nV  = Unit(10.0 * nano, B * V);
		/** @brief Power relative to 1 Watt. */
		constexpr Unit BW     = B * W;
		/** @brief Power relative to 1 kiloWatt. */
		constexpr Unit Bk     = Unit(kilo, B * W);
		/** @brief Voltage relative to 1 volt RMS, regardless of impedance */
		constexpr Unit dBV    = dB * V;
		/** @brief Voltage relative to 1 millivolt RMS across 75-ohm impedance */
		constexpr Unit dBmV   = Unit(1e-3, dB * V);
		/** @brief Voltage relative to 1 microvolt RMS. */
		constexpr Unit dBuV   = Unit(1e-6, dB * V);
		/** @brief Voltage relative to 10 nanovolt RMS. */
		constexpr Unit dB10nV = Unit(10.0 * nano, dB * V);
		/** @brief Power relative to 1 Watt. */
		constexpr Unit dBW    = dB * W;
		/** @brief Power relative to 1 kiloWatt. */
		constexpr Unit dBk    = Unit(kilo, dB * W);
		/** @brief Power relative to 1 milliWatt across 50-ohm impedance */
		constexpr Unit dBm    = Unit(milli, dB * W);
	}

	/** @brief Units used in chemical and biological laboratories */
	namespace Laboratory
	{
		constexpr Quantity enzyme_unit = 1.0 * micro * mol / min;

		/** @brief Svedberg, 10^-13 s */
		constexpr Unit svedberg = Unit(1e-13, s);
		/** @brief Plaque-forming unit */
		constexpr Unit PFU      = Unit(1.0, count);
		/** @brief pH, unit for acidity */
		constexpr Unit pH       = mol / L * Log::neglog10;
		constexpr Unit molarity = mol / L;
		constexpr Unit molality = mol / kg;
	}

	/** @brief Units related to quantities of data */
	namespace Data
	{
		/** @brief Bit */
		constexpr Unit bit    = Unit(1, count);
		/** @brief Nibble, 4 bits */
		constexpr Unit nibble = Unit(4, bit);
		/** @brief Byte, 8 bits */
		constexpr Unit byte   = Unit(8, bit);
	}

	/** @brief Units related to computation */
	namespace Computation
	{
		/** @brief Floating-point operation */
		constexpr Unit FLOP  = Unit(1.0, count);
		/** @brief Floating-point operation per second */
		constexpr Unit FLOPS = FLOP / s;
		/** @brief Million instructions per second */
		constexpr Unit MIPS  = Unit(1.0e6, count / s);
	}

	/** @brief percent, 1 in one hundred */
	constexpr Unit percent   = Unit(1e-2, count);
	/** @brief per mille, 1 in one thousand */
	constexpr Unit per_mille = Unit(1e-3, count);
	/** @brief Basis points, 1 in ten thousand */
	constexpr Unit bp        = Unit(1e-4, count);
	/** @brief ppm, parts per million */
	constexpr Unit ppm       = Unit(1e-6, count);
	/** @brief ppb, parts per billion */
	constexpr Unit ppb       = Unit(1e-9, count);

	/** @brief RPM, revolutions per minute */
	constexpr Unit rpm = Unit(2.0 * Constants::pi / 60.0, rad / s);
	/** @brief CFM, cubic feet per minute */
	constexpr Unit CFM = (ft^3) / min;

	constexpr Quantity convert(const Quantity& start, const Unit& result)
	{
		if(start.getUnit().base_units() != result.base_units()) return Unit::error();

		if(start.getUnit().base_units() == K.base_units())
		{
			Quantity temp;

			/**/ if(start.getUnit() == Temperature::degC ) temp = ((start.getMagnitude() -  0.0) * 1.0 / 1.0 + 273.15) * K;
			else if(start.getUnit() == Temperature::degF ) temp = ((start.getMagnitude() - 32.0) * 5.0 / 9.0 + 273.15) * K;
			else if(start.getUnit() == Temperature::degR ) temp = ((start.getMagnitude() -  0.0) * 5.0 / 9.0 + 273.15) * K;
			else if(start.getUnit() == Temperature::degRe) temp = ((start.getMagnitude() -  0.0) * 1.0 / 0.8 + 273.15) * K;
			else if(start.getUnit() == kelvin            ) temp = start;

			/**/ if(result == kelvin            ) return temp;
			else if(result == Temperature::degF ) return ((temp.getMagnitude() - 273.15) * 9.0 / 5.0 + 32.0) * result;
			else if(result == Temperature::degR ) return ((temp.getMagnitude() - 273.15) * 9.0 / 5.0 +  0.0) * result;
			else if(result == Temperature::degRe) return ((temp.getMagnitude() - 273.15) * 0.8 / 1.0 +  0.0) * result;
			else if(result == Temperature::degC ) return ((temp.getMagnitude() - 273.15) * 1.0 / 1.0 +  0.0) * result;

			return Unit::error();
		}

		return start.getMagnitude() * ((double)start.getUnit().unit_multiplier() / (double)result.unit_multiplier()) * result;
	}
}
