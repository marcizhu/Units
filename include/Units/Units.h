#pragma once

#include "Units/Unit.h"
#include "Units/Quantity.h"

#if defined(__GNUC__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wunused-const-variable"
#endif

namespace Units
{
	// The standard SI prefixes
	const double yotta = 1e+24;
	const double zetta = 1e+21;
	const double exa   = 1e+18;
	const double peta  = 1e+15;
	const double tera  = 1e+12;
	const double giga  = 1e+9;
	const double mega  = 1e+6;
	const double kilo  = 1e+3;
	const double hecto = 1e+2;
	const double deca  = 1e+1;
	const double deci  = 1e-1;
	const double centi = 1e-2;
	const double milli = 1e-3;
	const double micro = 1e-6;
	const double nano  = 1e-9;
	const double pico  = 1e-12;
	const double femto = 1e-15;
	const double atto  = 1e-18;
	const double zepto = 1e-21;
	const double yocto = 1e-24;

	// Binary prefixes, pending adoption
	const double kibi = 1024;
	const double mebi = 1024 * kibi;
	const double gibi = 1024 * mebi;
	const double tebi = 1024 * gibi;
	const double pebi = 1024 * tebi;
	const double exbi = 1024 * pebi;
	const double zebi = 1024 * exbi;
	const double yobi = 1024 * zebi;

	// Handy values
	namespace Constants
	{
		const double pi  = 3.14159265358979323846264338327950288;
		const double tau = 6.28318530717958647692528676655900576;
	}

	const Unit one;
	const Unit error   = Unit::error();
	const Unit none    = one;

	// The base SI units
	const Unit meter    = Unit::meter();
	const Unit kilogram = Unit::kilogram();
	const Unit second   = Unit::second();
	const Unit ampere   = Unit::ampere();
	const Unit kelvin   = Unit::kelvin();
	const Unit mole     = Unit::mole();
	const Unit radian   = Unit::radian();
	const Unit candela  = Unit::candela();
	const Unit currency = Unit::currency();
	const Unit count    = Unit::count();

	const Unit m   = meter;
	const Unit kg  = kilogram;
	const Unit s   = second;
	const Unit A   = ampere;
	const Unit K   = kelvin;
	const Unit mol = mole;
	const Unit rad = radian;
	const Unit Cd  = candela;

	/** @brief i flag, imaginary flag */
	const Unit iflag = Unit::iflag();

	// Derived SI units
	const Unit steradian      = radian * radian;
	const Unit hertz          = second^-1;
	const Unit newton         = kilogram * meter / (second^2);
	const Unit pascal         = newton / (meter^2);
	const Unit joule          = newton * meter;
	const Unit watt           = joule / second;
	const Unit coulomb        = ampere * second;
	const Unit volt           = watt / ampere;
	const Unit farad          = coulomb / volt;
	const Unit ohm            = volt / ampere;
	const Unit siemens        = ampere / volt;
	const Unit weber          = volt * second;
	const Unit tesla          = weber / (meter^2);
	const Unit henry          = weber / ampere;
	const Unit degree_celsius = kelvin;
	const Unit lumen          = candela * steradian;
	const Unit lux            = lumen / (meter^-2);
	const Unit becquerel      = count / second;
	const Unit gray           = joule / kilogram;
	const Unit sievert        = joule / kilogram;
	const Unit katal          = mol / second;

	const Unit sr  = steradian;
	const Unit Hz  = hertz;
	const Unit N   = newton;
	const Unit Pa  = pascal;
	const Unit J   = joule;
	const Unit W   = watt;
	const Unit C   = coulomb;
	const Unit V   = volt;
	const Unit F   = farad;
	const Unit S   = siemens;
	const Unit Wb  = weber;
	const Unit T   = tesla;
	const Unit H   = henry;
	const Unit lm  = lumen;
	const Unit lx  = lux;
	const Unit Bq  = becquerel;
	const Unit Gy  = gray;
	const Unit Sv  = sievert;
	const Unit kat = katal;

	// Not approved for use alone (needed for use with prefixes)
	const Unit     liter = Unit(0.001, m^3);
	const Quantity gram  = 0.001 * kg;

	// Alternate (non-US) spellings:
	const Unit metre = meter;
	const Unit litre = liter;
	const double deka = deca;

	// Short unit names
	// Distance units
	const Quantity cm = centi * m;
	const Quantity km = kilo  * m;
	const Quantity mm = milli * m;
	const Quantity nm = nano  * m;

	// Volume units
	const Unit L      = liter;
	const Quantity mL = milli * L;

	// Mass units
	const Quantity g     = gram;
	const Quantity mg    = milli  *  g;
	const Quantity tonne = 1000.0 * kg;
	const Quantity t     = tonne;

	// Atomic mass units
	const Unit Da = Unit(1.66053906660e-27, kg);
	const Unit u  = Da;

	/** @brief Units from the CGS system */
	namespace CGS
	{
		/** @brief Speed of light in cm/s */
		const double c_const    = 29979245800.0;
		const Unit erg          = Unit(1e-7, J);
		const Unit dyn          = Unit(1e-5, N);
		const Unit barye        = Unit(0.1, Pa);
		const Unit gal          = Unit(0.01, m / (s^2));
		const Unit poise        = Unit(0.1, Pa * s);
		const Unit stokes       = Unit(1e-4, (m^2) / s);
		const Unit kayser       = Unit(100.0, one / m);
		const Unit oersted      = Unit(1000.0 / 4.0 / Constants::pi, A / m);
		const Unit gauss        = Unit(1e-4, T);
		const Unit debye        = Unit(1.0 / (c_const * 1e20), C * m);
		const Unit maxwell      = Unit(1e-8, Wb);
		const Unit biot         = Unit(10.0, A);
		const Unit gilbert      = Unit(0.01, oersted * m);
		const Unit stilb        = Unit(10000.0, Cd / (m^2));
		const Unit lambert      = Unit(10000.0 / Constants::pi, Cd / (m^2));
		const Unit phot         = Unit(10000, lx);
		const Unit curie        = Unit(3.7e10, Bq);
		const Unit roentgen     = Unit(2.58e-4, C / kg);
		const Unit REM          = Unit(0.01, Sv);
		const Unit RAD          = Unit(100000, erg / kg);
		const Unit emu          = Unit(0.001, A * m * m);
		const Unit langley      = Unit(41840.0, J / (m^2));
		const Unit unitpole     = Unit(1.256637061436e-7, Wb);
		const Unit statC_charge = Unit(10.0 / c_const, C);
		const Unit statC_flux   = Unit(10.0 / (4.0 * Constants::pi * c_const), V * m);

		const Quantity abOhm    = 1e-9 * ohm;
		const Quantity abFarad  = 1e09 * F;
		const Quantity abHenry  = 1e-9 * H;
		const Quantity abVolt   = 1e-8 * V;

		/** @brief statvolt, electric potential. 1 erg / statC */
		const Quantity statV     = c_const * abVolt;
		const Quantity statT     = c_const * 1e-4 * T;
		const Quantity statHenry = c_const * c_const * abHenry;
		const Quantity statOhm   = c_const * c_const * abOhm;
		const Quantity statFarad = (1.0 / (c_const * c_const)) * abFarad;
	}

	/** @brief meter-gram-force system of units (aka gravitational metric system) */
	namespace GM
	{
		const Unit pond     = Unit(980.665, CGS::dyn);
		const Unit hyl      = Unit(9.80665, kg);
		const Unit at       = Unit(98066.5, Pa); // technical atmosfere
		const Unit poncelet = Unit(980.665, W);
		const Unit PS       = Unit(735.49875, W); // metric horsepower
	}

	/** @brief Meter tonne second system of units */
	namespace MTS
	{
		/** @brief Sthène. 1 t * m/s = 1000 N */
		const Unit sthene  = Unit(1000.0, N); // sn
		/** @brief Pièze, 1 t/m * s^2 = 1000 Pa */
		const Unit pieze   = Unit(1000.0, Pa); // pz
		/** @brief Thermie, energy required to raise temperature of 1 t of H2O by 1ºC */
		const Unit thermie = Unit(4.1868 * mega, J); // th
	}

	/** @brief Units of time */
	namespace Time
	{
		/** @brief Minute */
		const Unit min  = Unit(60.0, s);
		/** @brief Hour */
		const Unit hour = Unit(3600, s);
		/** @brief Day */
		const Unit day  = Unit(24, hour);
		/** @brief Week */
		const Unit week = Unit(7, day);
		/** @brief Median calendar year */
		const Unit yr   = Unit(8760.0, hour);

		/** @brief Julian year */
		const Unit aj   = Unit(365.25, day);
		/** @brief Standard year */
		const Unit year = aj;

		/** @brief Fortnight (two weeks) */
		const Quantity fortnight = 14 * day;
		/** @brief Sidereal day */
		const Quantity sday = 365.24 / 366.24 * day;
		/** @brief Sidereal year */
		const Quantity syr  = 365.256363004 * day;
		/** @brief Mean tropical year */
		const Quantity at   = 365.24219 * day;
		/** @brief Gregorian year */
		const Quantity ag   = 365.2425 * day;
		/** @brief Synodal month */
		const Quantity mos  = 29.53059 * day;
		/** @brief Mean Julian month */
		const Quantity moj  = 1.0 / 12.0 * aj;
		/** @brief mean Gregorian month */
		const Quantity mog  = 1.0 / 12.0 * ag;
	}

	const Unit h   = Time::hour;
	const Unit min = Time::min;

	/** @brief International units */
	namespace i
	{
		const Unit grain = Unit(64.79891 * micro, kg);

		const Unit inch   = Unit(0.0254, m);
		const Unit foot   = Unit(0.3048, m);
		const Unit yard   = Unit(0.9144, m);
		const Unit mile   = Unit(1609.344, m);
		const Unit league = Unit(3.0, mile);

		const Unit cord       = Unit(128.0, foot^3);
		const Unit board_foot = Unit(144.0, inch^3);
		const Unit mil        = Unit(milli, inch);
		const Unit circ_mil   = Unit(Constants::pi / 4.0, mil^2);

		const Quantity point = (0.127 / 360.0) * m;
		const Quantity pica  = (0.127 / 30.0) * m;
		const Quantity hand  = 4.0 * inch;
	}

	const Unit in   = i::inch;
	const Unit ft   = i::foot;
	const Unit yd   = i::yard;
	const Unit mile = i::mile;

	/** @brief Avoirdupois units, common international standard */
	namespace av
	{
		const Unit dram              = Unit(0.0017718451953125, kg);
		const Unit ounce             = Unit(16.0, dram);
		const Unit pound             = Unit(0.45359237, kg);
		const Unit hundredweight     = Unit(100.0, pound);
		const Unit longhundredweight = Unit(112.0, pound);
		const Unit ton               = Unit(2000.0, pound);
		const Unit longton           = Unit(2240.0, pound);
		const Unit stone             = Unit(14.0, pound);
		const Unit poundal           = Unit(0.138254954376, N);
		const Unit lbf               = Unit(4.4482216152605, N);
		const Unit ozf               = Unit(1.0 / 16.0, lbf);
		const Unit slug              = lbf * (s^2) / ft;
	}

	const Unit lb  = av::pound;
	const Unit ton = av::ton;
	const Unit oz  = av::ounce;
	const Unit lbf = av::lbf;

	/** @brief Troy units */
	namespace Troy
	{
		const Unit pennyweight = Unit(24.0, i::grain);
		const Unit oz          = Unit(0.0311034768, kg);
		const Unit pound       = Unit(12.0, oz);
	}

	/** @brief Units used in the United States */
	namespace US
	{
		const Unit foot    = Unit(1200.0 / 3937.0, m);
		const Unit inch    = Unit(1.0 / 12.0, foot);
		const Unit mil     = Unit(0.001, inch);
		const Unit yard    = Unit(3.0, foot);
		const Unit rod     = Unit(16.5, foot);
		const Unit chain   = Unit(4.0, rod);
		const Unit link    = Unit(0.01, chain);
		const Unit furlong = Unit(10.0, chain);
		const Unit mile    = Unit(8.0, furlong);
		const Unit league  = Unit(3.0, mile);

		// Area
		const Unit acre      = Unit(43560.0, foot^2);
		const Unit homestead = Unit(160.0, acre);
		const Unit section   = Unit(640.0, acre);
		const Unit township  = Unit(36.0, section);

		// Volume
		const Unit minim    = Unit(61.611519921875 * micro, L);
		const Unit dram     = Unit(60.0, minim);
		const Unit floz     = Unit(29.5735295625e-6, m^3);
		const Unit tbsp     = Unit(0.5, floz);
		const Unit tsp      = Unit(1.0 / 6.0, floz);
		const Unit pinch    = Unit(0.125, tsp);
		const Unit dash     = Unit(0.5, pinch);
		const Unit shot     = Unit(3.0, tbsp);
		const Unit gill     = Unit(4.0, floz);
		const Unit cup      = Unit(8.0, floz);
		const Unit pint     = Unit(2.0, cup);
		const Unit quart    = Unit(2.0, pint);
		const Unit cord     = Unit(128.0, ft^3);
		const Unit gallon   = Unit(3.785411784, L);
		const Unit flbarrel = Unit(31.5, gallon);
		const Unit barrel   = Unit(42.0, gallon);
		const Unit hogshead = Unit(63.0, gallon);
		const Unit fifth    = Unit(0.2,  gallon);

		namespace Engineers
		{
			const Unit chain = Unit(100.0, foot);
			const Unit link  = Unit(0.01, chain);
		}

		/** @brief US customary dry measurements */
		namespace Dry
		{
			const Unit pint   = Unit(0.5506104713575, L);
			const Unit quart  = Unit(2.0, pint);
			const Unit gallon = Unit(4.0, quart);
			const Unit peck   = Unit(2.0, gallon);
			const Unit bushel = Unit(35.23907016688, L);
			const Unit barrel = Unit(7056.0, in^3);
			const Unit sack   = Unit(3.0, bushel);
			const Unit strike = Unit(2.0, bushel);
		}

		namespace Grain
		{
			const Unit bushel_corn   = Unit(56.0, av::pound);
			const Unit bushel_wheat  = Unit(60.0, av::pound);
			const Unit bushel_barley = Unit(48.0, av::pound);
			const Unit bushel_oats   = Unit(32.0, av::pound);
		}
	}

	const Unit acre = US::acre;
	const Unit gal  = US::gallon;

	/** @brief FDA-specific volume units in metric */
	namespace Metric
	{
		const Unit tbsp        = Unit(0.015, L);
		const Unit tsp         = Unit(0.005, L);
		const Unit floz        = Unit(0.030, L);
		const Unit cup         = Unit(0.250, L);
		const Unit cup_uslegal = Unit(0.240, L);
		const Unit carat       = Unit(0.0002, kg);
	}

	/** @brief Some Canada specific variants on the us units */
	namespace Canada
	{
		const Unit tbsp     = Unit(0.015, L);
		const Unit tsp      = Unit(0.005, L);
		const Unit cup      = Unit(0.250, L);
		const Unit cup_trad = Unit(0.2273045, L);

		namespace Grain
		{
			const Unit bushel_oats = Unit(34.0, av::pound);
		}
	}

	/** @brief Some Australia specific variants on the us units */
	namespace Australia
	{
		const Unit tbsp = Unit(0.020, L);
		const Unit tsp  = Unit(0.005, L);
		const Unit cup  = Unit(0.250, L);
	}

	/** @brief Imperial system units (British) */
	namespace Imperial
	{
		const Unit inch = Unit(0.02539998, m);
		const Unit foot = Unit(12.0, inch);

		const Unit thou          = Unit(0.0000254, m);
		const Unit barleycorn    = Unit(1.0 / 3.0, inch);
		const Unit rod           = Unit(16.5, foot);
		const Unit chain         = Unit(4.0, rod);
		const Unit link          = Unit(0.01, chain);
		const Unit pace          = Unit(2.5, foot);
		const Unit yard          = Unit(3.0, foot);
		const Unit furlong       = Unit(201.168, m);
		const Unit league        = Unit(4828.032, m);
		const Unit mile          = Unit(5280.0, foot);
		const Unit nautical_mile = Unit(6080, foot);
		const Unit knot          = nautical_mile / h;
		const Unit acre          = Unit(4840.0, yard^2);

		// Area
		const Unit perch = Unit(25.29285264, m^2);
		const Unit rood  = Unit(1011.7141056, m^2);

		// Volume
		const Unit gallon = Unit(4.54609, L);
		const Unit quart  = Unit(0.25, gallon);
		const Unit pint   = Unit(0.5, quart);
		const Unit gill   = Unit(0.25, pint);
		const Unit cup    = Unit(0.5, pint);
		const Unit floz   = Unit(0.1, cup);
		const Unit tbsp   = Unit(0.5, floz);
		const Unit tsp    = Unit(1.0 / 3.0, tbsp);

		const Unit barrel = Unit(36.0, gallon);
		const Unit peck   = Unit(2.0, gallon);
		const Unit bushel = Unit(4.0, peck);
		const Unit dram   = Unit(1.0 / 8.0, floz);
		const Unit minim  = Unit(1.0 / 60.0, dram);

		// Weight
		const Unit drachm        = Unit(0.0017718451953125, kg);
		const Unit stone         = Unit(6.35029318, kg);
		const Unit hundredweight = Unit(112.0,  av::pound);
		const Unit ton           = Unit(2240.0, av::pound);
		const Unit slug          = Unit(14.59390294, kg);
	}

	namespace Apothecaries
	{
		const Unit floz         = Imperial::floz;
		const Unit minim        = Unit(59.1938802083333333333 * micro, L);
		const Unit scruple      = Unit(20.0, i::grain);
		const Unit drachm       = Unit(3.0, scruple);
		const Unit ounce        = Unit(8.0, drachm);
		const Unit pound        = Unit(12.0, ounce);
		const Unit pint         = Imperial::pint;
		const Unit gallon       = Imperial::gallon;
		const Unit metric_ounce = Unit(0.028, kg);
	}

	/** @brief Nautical units */
	namespace Nautical
	{
		const Unit fathom = Unit(2.0, yd);
		const Unit cable  = Unit(120, fathom);
		const Unit mile   = Unit(1852.0, m);
		const Unit knot   = mile / h;
		const Unit league = Unit(3.0, mile);
	}

	/** @brief Some historical Japanese units */
	namespace Japan
	{
		const Unit shaku = Unit(10.0 / 33.0, m);
		const Unit sun   = Unit(0.1, shaku);
		const Unit ken   = Unit(1.0 + 9.0 / 11.0, m);
		const Unit tsubo = Unit(100.0 / 30.25, m^2);
		const Unit sho   = Unit(2401.0 / 1331.0, L);
		const Unit kan   = Unit(15.0 / 4.0, kg);
		const Unit go    = Unit(2401.0 / 13310, L);
		const Unit cup   = Unit(0.2, L);
	}

	/** @brief Some historical chinese units */
	namespace Chinese
	{
		const Unit jin   = Unit(0.5, kg);
		const Unit liang = Unit(0.0001, kg);
		const Unit qian  = Unit(0.00001, kg);

		const Unit li    = Unit(500.0, m);
		const Unit cun   = Unit(10.0 / 300.0, m);
		const Unit chi   = Unit(10.0, cun);
		const Unit zhang = Unit(10.0, chi);
	}

	/** @brief Typographic units for typesetting or printing */
	namespace Typographic
	{
		namespace American
		{
			const Unit line  = Unit(1.0 / 12.0, in);
			const Unit point = Unit(1.0 / 6.0, line);
			const Unit pica  = Unit(12.0, point);
			const Unit twip  = Unit(1.0 / 20.0, point);
		}

		namespace Printers
		{
			const Unit point = Unit(0.013837, in);
			const Unit pica  = Unit(12.0, point);
		}

		namespace French
		{
			const Unit point  = Unit(15.625 / 41559.0, m);
			const Unit ligne  = Unit(6.0, point);
			const Unit pouce  = Unit(12.0, ligne);
			const Unit didot  = point;
			const Unit cicero = Unit(12.0, didot);
			const Unit pied   = Unit(12.0, pouce);
			const Unit toise  = Unit(6.0, pied);
		}

		namespace Metric
		{
			const Unit point = Unit(375.0 * micro, m);
			const Unit quart = Unit(0.25 * milli, m);
		}
	}

	/** @brief Units related to distance */
	namespace Distance
	{
		/** @brief Smoot, or Oliver Smoot's height as of October 1958 (see https://en.wikipedia.org/wiki/Smoot) */
		const Quantity smoot     = 67.0 * in;
		/** @brief Cubit */
		const Quantity cubit     = 18.0 * in;
		/** @brief Long cubit */
		const Quantity longcubit = 21.0 * in;

		/** @brief Light-year */
		const Unit ly        = Unit(9.4607304725808e15, m);
		/** @brief Astronomical unit */
		const Unit au        = Unit(149597870700.0, m);
		/** @brief Astronomical unit (old definition) */
		const Unit au_old    = Unit(149597900000.0, m);
		/** @brief Angstrom, 10^-10 m (100 pm) */
		const Unit angstrom  = Unit(1e-10, m);
		/** @brief Parsec, as defined by the International Astronomical Union */
		const Unit parsec    = Unit(3.08567758149136727891e16, m);

		/** @brief Arpent (US) */
		const Unit arpent_us = Unit(58.47131, m);
		/** @brief Arpent (FR) */
		const Unit arpent_fr = Unit(71.46466, m);
		/** @brief The X unit */
		const Unit xu        = Unit(1.0021e-13, m);
	}

	/** @brief Units related to compass directions */
	namespace Direction
	{
		/** @brief North */
		const Quantity north =  1.0 * iflag;
		/** @brief South */
		const Quantity south = -1.0 * iflag;
		/** @brief East */
		const Quantity east  =  1.0;
		/** @brief West */
		const Quantity west  = -1.0;

		/** @brief North, short name */
		const Quantity N = north;
		/** @brief South, short name */
		const Quantity S = south;
		/** @brief East, short name */
		const Quantity E = east;
		/** @brief West, short name */
		const Quantity W = west;
	}

	/** @brief Additional Area units */
	namespace Area
	{
		/** @brief Are. 100 m^2 */
		const Unit are     = Unit(100.0, m^2);
		/** @brief Hectare. 10^4 m^2 */
		const Unit hectare = Unit(100.0, are);
		/** @brief Barn. 10^−28 m^2 (or 100 fm^2) */
		const Unit barn    = Unit(1e-28, m^2);
		/** @brief Arpent. 0.84628 acres (or ≈3424.8 m^2) */
		const Unit arpent  = Unit(0.84628, acre);
	}

	/** @brief Additional mass units */
	namespace Mass
	{
		/** @brief Quintal. 100 kg */
		const Quantity quintal   = 100.0 * kg;
		/** @brief Assay ton. 26.1666... g */
		const Unit ton_assay     = Unit((29.0 + 1.0 / 6.0) * milli, kg);
		/** @brief Assay long ton. 32.3333... g */
		const Unit longton_assay = Unit((32.0 + 2.0 / 3.0) * milli, kg);
	}

	/** @brief Some extra volume units */
	namespace Volume
	{
		/** @brief Stere. 1 m^3 */
		const Unit stere     = m^3;
		/** @brief Acre-foot. Defined as an area of an acre with a depth of 1 foot */
		const Unit acre_foot = acre * US::foot;
		/** @brief Drum. Volume of a cylindrical container with 55 US gal of capacity */
		const Unit drum      = Unit(55.0, US::gallon);
	}

	/** @brief Angle measurement units */
	namespace Angle
	{
		/** @brief Degree */
		const Unit deg    = Unit(Constants::pi  / 180.0, rad);
		/** @brief Gradian */
		const Unit grad   = Unit(Constants::pi  / 200.0, rad);
		/** @brief Binary radian */
		const Unit brad   = Unit(Constants::tau / 256.0, rad);

		/** @brief Gon */
		const Unit gon    = Unit(9.0 / 10.0, deg);
		/** @brief Arc minute */
		const Unit arcmin = Unit(1.0 / 60.0, deg);
		/** @brief Arc second */
		const Unit arcsec = Unit(1.0 / 60.0, arcmin);
	}

	/** @brief Units related to temperature */
	namespace Temperature
	{
		/** @brief Degree Celsius */
		const Unit celsius    = Unit(1.0, K);
		/** @brief Degree Fahrenheit */
		const Unit fahrenheit = Unit(5.0 / 9.0, celsius);
		/** @brief Degree Réaumur */
		const Unit reaumur    = Unit(5.0 / 4.0, celsius);
		/** @brief Degree Rankine */
		const Unit rankine    = Unit(5.0 / 9.0, K);

		/** @brief Degree Celsius, short name */
		const Unit degC  = celsius;
		/** @brief Degree Fahrenheit, short name */
		const Unit degF  = fahrenheit;
		/** @brief Degree Réaumur, short name */
		const Unit degRe = reaumur;
		/** @brief Degree Rankine, short name */
		const Unit degR  = rankine;
	}

	/** @brief Units related to pressure */
	namespace Pressure
	{
		/** @brief Bar, 100,000 Pascals */
		const Unit bar   = Unit(1.0e5, Pa);
		/** @brief PSI, Pound per square inch */
		const Unit psi   = Unit(6894.757293168, Pa);
		/** @brief Inches of mercury at 15.5°C or 60°F */
		const Unit inHg  = Unit(3376.849669, Pa);
		/** @brief Millimeters of mercury at 15.5°C or 60°F */
		const Unit mmHg  = Unit(133.322387415, Pa);
		/** @brief Torr */
		const Unit torr  = Unit(101325.0 / 760.0, Pa);
		/** @brief Inches of water at 15.5°C or 60°F */
		const Unit inH2O = Unit(248.843004, Pa);
		/** @brief Millimeters of water at 15.5°C or 60°F */
		const Unit mmH2O = Unit(1.0 / 25.4, inH2O);
		/** @brief Atmosphere */
		const Unit atm   = Unit(101325.0, Pa);
		/** @brief Technical atmosphere. Same as gravitational metric system */
		const Unit att   = GM::at;
	}

	/** @brief Power units */
	namespace Power
	{
		/** @brief Electric horsepower */
		const Unit hpE = Unit(746.0, W);
		/** @brief Mechanical horsepower */
		const Unit hpI = Unit(745.69987158227022, W);
		/** @brief Boiler horsepower */
		const Unit hpS = Unit(9812.5, W);
		/** @brief Metric horsepower */
		const Unit hpM = Unit(735.49875, W);

		/** @brief Volt-Ampere */
		const Unit VA  = V * A;
		/** @brief Volt-Ampere reactive */
		const Unit VAR = V * A * iflag;
	}

	/** @brief Horsepower */
	const Unit hp = Power::hpI;

	/** @brief Energy units */
	namespace Energy
	{
		/** @brief Watt-hour */
		const Unit Wh  = W * h;
		/** @brief ElectronVolt */
		const Unit eV  = Unit(1.602176634e-19, J);

		/** @brief Calorie at 4°C */
		const Unit cal_4    = Unit(4.20400, J);
		/** @brief Calorie at 15°C */
		const Unit cal_15   = Unit(4.18580, J);
		/** @brief Calorie at 20°C */
		const Unit cal_20   = Unit(4.18190, J);
		/** @brief Mean calorie */
		const Unit cal_mean = Unit(4.19002, J);
		/** @brief International table calorie */
		const Unit cal_it   = Unit(4.18680, J);
		/** @brief Thermochemical calorie */
		const Unit cal_th   = Unit(4.18400, J);
		/** @brief Thermochemical kilocalorie */
		const Quantity kcal = kilo * cal_th;

		/** @brief Thermochemical BTU (British Thermal Unit) */
		const Unit btu_th   = Unit(1054.350, J);
		/** @brief BTU (British Thermal Unit) at 39°F (3.9°C) */
		const Unit btu_39   = Unit(1059.67, J);
		/** @brief BTU (British Thermal Unit) at 59°F (15°C) */
		const Unit btu_59   = Unit(1054.80, J);
		/** @brief BTU (British Thermal Unit) at 60°F (15.6°C) */
		const Unit btu_60   = Unit(1054.68, J);
		/** @brief Mean BTU (British Thermal Unit) */
		const Unit btu_mean = Unit(1055.87, J);
		/** @brief International Table BTU (British Thermal Unit) */
		const Unit btu_it   = Unit(1055.05585, J);
		/** @brief International standard ISO 31-4 for BTU */
		const Unit btu_iso  = Unit(1055.06, J);
		/** @brief Quad, one quadrillion (10^15) BTUs */
		const Unit quad     = Unit(1055.05585262e15, J);
		/** @brief Ton of cooling, aka 12.000 BTU/h (3.52 kW) */
		const Quantity tonc = 12000.0 * btu_th / h;

		/** @brief Therm, 100,000 BTUs (US definition) */
		const Unit therm_us = Unit(100000.0, btu_59);
		/** @brief Therm, 100,000 BTUs (UK definition) */
		const Unit therm_br = Unit(105505585.257, J);
		/** @brief Therm, 100,000 ISO BTUs */
		const Unit therm_ec = Unit(100000, btu_iso);
		/** @brief Energy efficiency ratio */
		const Unit EER      = btu_th / (W * h);
		/** @brief Specific gravity */
		const Unit SG       = lb / (ft^3);

		/** @brief Ton of TNT (trinitrotoluene, or 2,4,6-trinitrotoluene) */
		const Unit ton_tnt = Unit(4.184 * giga, J);
 		/** @brief BOE, Barrel of Oil Equivalent */
 		const Unit boe     = Unit(5.8e6, btu_59);
 		/** @brief FOEB, Fuel of Oil Equivalent Barrel */
 		const Unit foeb    = Unit(6.05e6, btu_59);
 		/** @brief Hartree, an atomic unit of energy */
 		const Unit hartree = Unit(4.3597441775e-18, J);
 		/** @brief Ton-Hour. Unit of refrigeration equal to 12000 BTU */
 		const Unit tonhour = Unit(3516.8528421, Wh);
	}

	const Unit btu = Energy::btu_it;
	const Unit cal = Energy::cal_th;

	/** @brief Units used in the textile industry */
	namespace Textile
	{
		/** @brief Tex, grams per 1000 meters of yarn */
		const Unit tex    = Unit(1e-6, kg / m);
		/** @brief Tex, grams per 9000 meters of yarn */
		const Unit denier = Unit(1.0 / 9.0, tex);
		const Unit span   = Unit(0.2286, m);
		const Unit finger = Unit(0.1143, m);
		const Unit nail   = Unit(0.5, finger);
	}

	/** @brief Units used in clinical medicine */
	namespace Clinical
	{
		/** @brief Peripheral vascular resistance unit */
		const Unit pru           = Unit(milli, Pressure::mmHg * s / L);
		/** @brief Hybrid resistance units, or Wood units */
		const Unit woodu         = Pressure::mmHg * min / L;
		/** @brief Diopter */
		const Unit diopter       = m^-1;
		/** @brief Prism diopter */
		const Unit prism_diopter = Unit::eq(20);
		/** @brief Mesh size, aka number of holes per inch */
		const Unit mesh          = in^-1;
		/** @brief Charrière, French catheter scale */
		const Unit charriere     = Unit(1.0 * milli / 3.0, m);
		/** @brief Drop */
		const Unit drop          = Unit(0.05 * milli, L);
		/** @brief Metabolic equivalent of task */
		const Unit met           = Unit(3.5 * milli, L / min / kg);
	}

	// Log-based units
	namespace Log
	{
		/** @brief Neper */
		const Unit neper  = Unit::eq(0);

		/** @brief Bel */
		const Unit bel  = Unit::eq(1);
		/** @brief Bel. A-weighted */
		const Unit belA = Unit::eq(2);

		/** @brief Decibel */
		const Unit dB  = Unit::eq(3);
		/** @brief Decibel. A-weighted */
		const Unit dBA = Unit::eq(4);
		/** @brief Decibel. Ratio relative to carrier wave */
		const Unit dBc = Unit::eq(5);

		/** @brief Natural logarithm */
		const Unit log         = neper;
		/** @brief Base 2 logarithm */
		const Unit log2        = Unit::eq(6);
		/** @brief Base 10 logarithm */
		const Unit log10       = Unit::eq(7);
		/** @brief Negative base 10 logarithm */
		const Unit neglog10    = Unit::eq(8);

		/** @brief Short form for Bels */
		const Unit B = bel;
		/** @brief Short form for Bels, A-weighted */
		const Unit BA = belA;

		/** @brief Sound pressure level for Bels */
		const Unit B_SPL  = Unit(2e-5, Pa * B);
		/** @brief Sound pressure level for decibels */
		const Unit dB_SPL = Unit(2e-5, Pa * dB);
		/** @brief Voltage relative to 1 volt RMS, regardless of impedance */
		const Unit BV     = B * V;
		/** @brief Voltage relative to 1 millivolt RMS across 75-ohm impedance */
		const Unit BmV    = Unit(1e-3, B * V);
		/** @brief Voltage relative to 0.7746 volts RMS (1 mW across 600-ohm resistor) */
 		const Unit Bu     = Unit(0.7746, B * V);
		/** @brief Voltage relative to 1 microvolt RMS. */
		const Unit BuV    = Unit(1e-6, B * V);
		/** @brief Voltage relative to 10 nanovolt RMS. */
		const Unit B10nV  = Unit(10.0 * nano, B * V);
		/** @brief Power relative to 1 Watt. */
		const Unit BW     = B * W;
		/** @brief Power relative to 1 kiloWatt. */
		const Unit Bk     = Unit(kilo, B * W);
		/** @brief Voltage relative to 1 volt RMS, regardless of impedance */
		const Unit dBV    = dB * V;
		/** @brief Voltage relative to 1 millivolt RMS across 75-ohm impedance */
		const Unit dBmV   = Unit(1e-3, dB * V);
		/** @brief Voltage relative to 0.7746 volts RMS (1 mW across 600-ohm resistor) */
 		const Unit dBu    = Unit(0.7746, dB * V);
		/** @brief Voltage relative to 1 microvolt RMS. */
		const Unit dBuV   = Unit(1e-6, dB * V);
		/** @brief Voltage relative to 10 nanovolt RMS. */
		const Unit dB10nV = Unit(10.0 * nano, dB * V);
		/** @brief Power relative to 1 Watt. */
		const Unit dBW    = dB * W;
		/** @brief Power relative to 1 kiloWatt. */
		const Unit dBk    = Unit(kilo, dB * W);
		/** @brief Power relative to 1 milliWatt across 50-ohm impedance */
		const Unit dBm    = Unit(milli, dB * W);
	}

	/** @brief Units used in chemical and biological laboratories */
	namespace Laboratory
	{
		const Quantity enzyme_unit = 1.0 * micro * mol / min;

		/** @brief Svedberg, 10^-13 s */
		const Unit svedberg = Unit(1e-13, s);
		/** @brief Plaque-forming unit */
		const Unit PFU      = Unit(1.0, count);
		/** @brief pH, unit for acidity */
		const Unit pH       = mol / L * Log::neglog10;
		/** @brief Molarity, mol / L (aka concentration per unit volume) */
		const Unit molarity = mol / L;
		/** @brief Molality, mol / kg (aka concentration per unit mass) */
		const Unit molality = mol / kg;
	}

	/** @brief Units related to quantities of data */
	namespace Data
	{
		/** @brief Bit */
		const Unit bit    = Unit(1, count);
		/** @brief Nibble, 4 bits */
		const Unit nibble = Unit(4, bit);
		/** @brief Byte, 8 bits */
		const Unit byte   = Unit(8, bit);
	}

	/** @brief Units related to computation */
	namespace Computation
	{
		/** @brief Floating-point operation */
		const Unit FLOP  = Unit(1.0, count);
		/** @brief Floating-point operation per second */
		const Unit FLOPS = FLOP / s;
		/** @brief Million instructions per second */
		const Unit MIPS  = Unit(1.0e6, count / s);
	}

	/** @brief percent, 1 in one hundred */
	const Unit percent   = Unit(1e-2, count);
	/** @brief per mille, 1 in one thousand */
	const Unit per_mille = Unit(1e-3, count);
	/** @brief Basis points, 1 in ten thousand */
	const Unit bp        = Unit(1e-4, count);
	/** @brief ppm, parts per million */
	const Unit ppm       = Unit(1e-6, count);
	/** @brief ppb, parts per billion */
	const Unit ppb       = Unit(1e-9, count);

	/** @brief RPM, revolutions per minute */
	const Unit rpm = Unit(2.0 * Constants::pi / 60.0, rad / s);
	/** @brief CFM, cubic feet per minute */
	const Unit CFM = (ft^3) / min;

	inline Quantity convert(const Quantity& start, const Unit& result)
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


#if defined(__GNUC__)
	#pragma GCC diagnostic pop
#endif
