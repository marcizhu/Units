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
	constexpr double deka  = 1e+1;
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

	constexpr Quantity one;
	constexpr Quantity percent = 0.01 * one;
	constexpr Unit     error   = Unit(nullptr);

	// The base SI units
	constexpr Unit meter   (1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	constexpr Unit kilogram(0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	constexpr Unit second  (0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
	constexpr Unit ampere  (0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
	constexpr Unit kelvin  (0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
	constexpr Unit mole    (0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
	constexpr Unit radian  (0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
	constexpr Unit candela (0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
	constexpr Unit currency(0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
	constexpr Unit count   (0, 0, 0, 0, 0, 0, 0, 0, 0, 1);

	constexpr Unit iflag   (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1); // i flag

	constexpr Unit m   = meter;
	constexpr Unit kg  = kilogram;
	constexpr Unit s   = second;
	constexpr Unit A   = ampere;
	constexpr Unit K   = kelvin;
	constexpr Unit mol = mole;
	constexpr Unit rad = radian;
	constexpr Unit Cd  = candela;

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
	constexpr Quantity liter = 0.001 * (m^3);
	constexpr Quantity gram  = 0.001 * kg;

	// Alternate (non-US) spellings:
	constexpr Quantity metre = meter;
	constexpr Quantity litre = liter;
	constexpr double   deca  = deka;

	// Short unit names
	// Distance units
	constexpr Quantity cm = centi * m;
	constexpr Quantity km = kilo  * m;
	constexpr Quantity mm = milli * m;
	constexpr Quantity nm = nano  * m;

	// Volume units
	constexpr Quantity L  = liter;
	constexpr Quantity mL = milli * L;

	// mass units
	constexpr Quantity g  = gram;
	constexpr Quantity mg = milli * g;

	// Units from the cgs system
	namespace cgs
	{
		constexpr double c_const        = 29979245800.0; // speed of light in cm/s
		constexpr Quantity erg          = 1e-7 * J;
		constexpr Quantity dyn          = 1e-5 * N;
		constexpr Quantity barye        = 0.1 * Pa;
		constexpr Quantity gal          = cm / (s^2);
		constexpr Quantity poise        = 0.1 * Pa * s;
		constexpr Quantity stokes       = 1e-4 * (m^2) / s;
		constexpr Quantity kayser       = one / cm;
		constexpr Quantity oersted      = 1000.0 / 4.0 / Constants::pi * A / m;
		constexpr Quantity gauss        = 1e-4 * T;
		constexpr Quantity debye        = 1.0 / (c_const * 1e20) * C * m;
		constexpr Quantity maxwell      = 1e-8 * Wb;
		constexpr Quantity biot         = 10.0 * A;
		constexpr Quantity gilbert      = oersted * cm;
		constexpr Quantity stilb        = 1.0 * Cd / (cm^2);
		constexpr Quantity lambert      = 1.0 / Constants::pi * Cd / (cm^2);
		constexpr Quantity phot         = 10000 * lx;
		constexpr Quantity curie        = 3.7e10 * Bq;
		constexpr Quantity roentgen     = 2.58e-4 * C / kg;
		constexpr Quantity REM          = 0.01 * Sv;
		constexpr Quantity RAD          = 100 * erg / g;
		constexpr Quantity emu          = 0.001 * A * m * m;
		constexpr Quantity langley      = 41840.0 * J / (m^2);
		constexpr Quantity unitpole     = 1.256637061436e-7 * Wb;
		constexpr Quantity statC_charge = 10.0 / c_const * C;
		constexpr Quantity statC_flux   = 10.0 / (4.0 * Constants::pi * c_const) * V * m;
		constexpr Quantity abOhm        = 1e-9 * ohm;
		constexpr Quantity abFarad      = 1e9 * F;
		constexpr Quantity abHenry      = 1e-9 * H;
		constexpr Quantity abVolt       = 1e-8 * V;
		constexpr Quantity statV        = c_const * abVolt;
		constexpr Quantity statT        = c_const * 1e-4 * T;
		constexpr Quantity statHenry    = c_const * c_const * abHenry;
		constexpr Quantity statOhm      = c_const * c_const * abOhm;
		constexpr Quantity statFarad    = 1.0 / (c_const * c_const) * abFarad;
	}

	// meter-gram-force system of units
	namespace gm
	{
		constexpr Quantity pond     = 980.665 * cgs::dyn;
		constexpr Quantity hyl      = 9.80665 * kg;
		constexpr Quantity at       = 98066.5 * Pa; // technical atmosfere
		constexpr Quantity poncelet = 980.665 * W;
		constexpr Quantity PS       = 735.49875 * W; // metric horsepower
	}

	// Meter tonne second system of units
	namespace MTS
	{
		constexpr Quantity sthene  = 1000.0 * N;
		constexpr Quantity pieze   = 1000.0 * Pa;
		constexpr Quantity thermie = 4.186 * mega * J;
	}

	// Units of time
	namespace time
	{
		constexpr Quantity min  = 60.0 * s;
		constexpr Quantity hour = 3600 * s;
		constexpr Quantity day  = 24 * hour;
		constexpr Quantity week = 7 * day;
		constexpr Quantity yr   = 8760.0 * hour; // median calendar year;
		constexpr Quantity fortnight = 14 * day;

		constexpr Quantity sday = 365.24 / 366.24 * day; // sidereal day
		constexpr Quantity syr  = 365.256363004 * day; // sidereal year
		constexpr Quantity at   = 365.24219 * day; // mean tropical year
		constexpr Quantity aj   = 365.25 * day; // julian year
		constexpr Quantity ag   = 365.2425 * day; // gregorian year
		constexpr Quantity year = aj; // standard year
		constexpr Quantity mos  = 29.53059 * day; // synodal month
		constexpr Quantity moj  = 1.0 / 12.0 * aj; // mean julian month
		constexpr Quantity mog  = 1.0 / 12.0 * ag; // mean gregorian month
	}

	constexpr Quantity h   = time::hour;
	constexpr Quantity min = time::min;

	// International units
	namespace i
	{
		constexpr Quantity grain = 64.79891 * mg;

		constexpr Quantity point = 127.0 / 360.0 * mm;
		constexpr Quantity pica  = 127.0 / 30.0 * mm;
		constexpr Quantity inch  = 0.0254 * m;
		constexpr Quantity foot  = 0.3048 * m;

		constexpr Quantity yard   = 0.9144 * m;
		constexpr Quantity mile   = 1609.344 * m;
		constexpr Quantity league = 3.0 * mile;
		constexpr Quantity hand   = 4.0 * inch;

		constexpr Quantity cord       = 128.0 * (foot^3);
		constexpr Quantity board_foot = 144.0 * (inch^3);
		constexpr Quantity mil        = milli * inch;
		constexpr Quantity circ_mil   = Constants::pi / 4.0 * (mil^2);
	}

	constexpr Quantity in   = i::inch;
	constexpr Quantity ft   = i::foot;
	constexpr Quantity yd   = i::yard;
	constexpr Quantity mile = i::mile;

	// Avoirdupois units, common international standard
	namespace av
	{
		constexpr Quantity dram              = 1.7718451953125 * g;
		constexpr Quantity ounce             = 16.0 * dram;
		constexpr Quantity pound             = 453.59237 * g;
		constexpr Quantity hundredweight     = 100.0 * pound;
		constexpr Quantity longhundredweight = 112.0 * pound;
		constexpr Quantity ton               = 2000.0 * pound;
		constexpr Quantity longton           = 2240.0 * pound;
		constexpr Quantity stone             = 14.0 * pound;
		constexpr Quantity poundal           = 0.138254954376 * N;
		constexpr Quantity lbf               = 4.4482216152605 * N;
		constexpr Quantity ozf               = 1.0 / 16.0 * lbf;
		constexpr Quantity slug              = lbf * (s^2) / ft;
	}

	constexpr Quantity lb  = av::pound;
	constexpr Quantity ton = av::ton;
	constexpr Quantity oz  = av::ounce;
	constexpr Quantity lbf = av::lbf;

	// troy units
	namespace Troy
	{
		constexpr Quantity pennyweight = 24.0 * i::grain;
		constexpr Quantity oz          = 31.1034768 * g;
		constexpr Quantity pound       = 12.0 * oz;
	}

	namespace US
	{
		constexpr Quantity foot    = 1200.0 / 3937.0 * m;
		constexpr Quantity inch    = 1.0 / 12.0 * foot;
		constexpr Quantity mil     = 0.001 * inch;
		constexpr Quantity yard    = 3.0 * foot;
		constexpr Quantity rod     = 16.5 * foot;
		constexpr Quantity chain   = 4.0 * rod;
		constexpr Quantity link    = 0.01 * chain;
		constexpr Quantity furlong = 10.0 * chain;
		constexpr Quantity mile    = 8.0 * furlong;
		constexpr Quantity league  = 3.0 * mile;

		namespace Engineers
		{
			constexpr Quantity chain = 100.0 * foot;
			constexpr Quantity link  = 0.01 * chain;
		}

		// area
		constexpr Quantity acre      = 43560.0 * (foot^2);
		constexpr Quantity homestead = 160.0 * acre;
		constexpr Quantity section   = 640.0 * acre;
		constexpr Quantity township  = 36.0 * section;

		// volume
		constexpr Quantity minim    = 61.611519921875 * micro * L;
		constexpr Quantity dram     = 60.0 * minim;
		constexpr Quantity floz     = 29.5735295625e-6 * (m^3);
		constexpr Quantity tbsp     = 0.5 * floz;
		constexpr Quantity tsp      = 1.0 / 6.0 * floz;
		constexpr Quantity pinch    = 0.125 * tsp;
		constexpr Quantity dash     = 0.5 * pinch;
		constexpr Quantity shot     = 3.0 * tbsp;
		constexpr Quantity gill     = 4.0 * floz;
		constexpr Quantity cup      = 8.0 * floz;
		constexpr Quantity pint     = 2.0 * cup;
		constexpr Quantity quart    = 2.0 * pint;
		constexpr Quantity cord     = 128.0 * (ft^3);
		constexpr Quantity gallon   = 3.785411784 * L;
		constexpr Quantity flbarrel = 31.5 * gallon;
		constexpr Quantity barrel   = 42.0 * gallon;
		constexpr Quantity hogshead = 63.0 * gallon;
		constexpr Quantity fifth    = 0.2 * gallon;

		// US customary dry measurements
		namespace Dry
		{
			constexpr Quantity pint   = 0.5506104713575 * L;
			constexpr Quantity quart  = 2.0 * pint;
			constexpr Quantity gallon = 4.0 * quart;
			constexpr Quantity peck   = 2.0 * gallon;
			constexpr Quantity bushel = 35.23907016688 * L;
			constexpr Quantity barrel = 7056.0 * (in^3);
			constexpr Quantity sack   = 3.0 * bushel;
			constexpr Quantity strike = 2.0 * bushel;
		}

		namespace Grain
		{
			constexpr Quantity bushel_corn   = 56.0 * av::pound;
			constexpr Quantity bushel_wheat  = 60.0 * av::pound;
			constexpr Quantity bushel_barley = 48.0 * av::pound;
			constexpr Quantity bushel_oats   = 32.0 * av::pound;
		}

		constexpr Quantity gal = US::gallon;
	}

	// FDA specific volume units in metric
	namespace Metric
	{
		constexpr Quantity tbsp        = 15.0 * mL;
		constexpr Quantity tsp         = 5.0 * mL;
		constexpr Quantity floz        = 30.0 * mL;
		constexpr Quantity cup         = 250.0 * mL;
		constexpr Quantity cup_uslegal = 240.0 * mL;
		constexpr Quantity carat       = 0.2 * g;
	}

	// Some Canada specific variants on the us units
	namespace Canada
	{
		constexpr Quantity tbsp     = 15.0 * mL;
		constexpr Quantity tsp      = 5.0 * mL;
		constexpr Quantity cup      = 250.0 * mL;
		constexpr Quantity cup_trad = 227.3045 * mL;

		namespace Grain
		{
			constexpr Quantity bushel_oats = 34.0 * av::pound;
		}
	}

	// Some Austrailia specific variants on the us units
	namespace Australia
	{
		constexpr Quantity tbsp = 20.0 * mL;
		constexpr Quantity tsp  = 5.0 * mL;
		constexpr Quantity cup  = 250.0 * mL;
	}

	// Imperial system units (British)
	namespace Imp
	{
		constexpr Quantity inch = 2.539998 * cm;
		constexpr Quantity foot = 12.0 * inch;

		constexpr Quantity thou          = 0.0254 * mm;
		constexpr Quantity barleycorn    = 1.0 / 3.0 * inch;
		constexpr Quantity rod           = 16.5 * foot;
		constexpr Quantity chain         = 4.0 * rod;
		constexpr Quantity link          = 0.01 * chain;
		constexpr Quantity pace          = 2.5 * foot;
		constexpr Quantity yard          = 3.0 * foot;
		constexpr Quantity furlong       = 201.168 * m;
		constexpr Quantity league        = 4828.032 * m;
		constexpr Quantity mile          = 5280.0 * foot;
		constexpr Quantity nautical_mile = 6080 * foot;
		constexpr Quantity knot          = nautical_mile / h;
		constexpr Quantity acre          = 4840.0 * (yard^2);

		// area
		constexpr Quantity perch = 25.29285264 * (m^2);
		constexpr Quantity rood  = 1011.7141056 * (m^2);

		// volume
		constexpr Quantity gallon = 4546.09 * mL;
		constexpr Quantity quart  = 0.25 * gallon;
		constexpr Quantity pint   = 0.5 * quart;
		constexpr Quantity gill   = 0.25 * pint;
		constexpr Quantity cup    = 0.5 * pint;
		constexpr Quantity floz   = 0.1 * cup;
		constexpr Quantity tbsp   = 0.5 * floz;
		constexpr Quantity tsp    = 1.0 / 3.0 * tbsp;

		constexpr Quantity barrel = 36.0 * gallon;
		constexpr Quantity peck   = 2.0 * gallon;
		constexpr Quantity bushel = 4.0 * peck;
		constexpr Quantity dram   = 1.0 / 8.0 * floz;
		constexpr Quantity minim  = 1.0 / 60.0 * dram;

		// weight
		constexpr Quantity drachm        = 1.7718451953125 * g;
		constexpr Quantity stone         = 6350.29318 * g;
		constexpr Quantity hundredweight = 112.0 * av::pound;
		constexpr Quantity ton           = 2240.0 * av::pound;
		constexpr Quantity slug          = 14.59390294 * kg;
	}

	namespace Apothecaries
	{
		constexpr Quantity floz         = Imp::floz;
		constexpr Quantity minim        = 59.1938802083333333333 * micro * L;
		constexpr Quantity scruple      = 20.0 * i::grain;
		constexpr Quantity drachm       = 3.0 * scruple;
		constexpr Quantity ounce        = 8.0 * drachm;
		constexpr Quantity pound        = 12.0 * ounce;
		constexpr Quantity pint         = Imp::pint;
		constexpr Quantity gallon       = Imp::gallon;
		constexpr Quantity metric_ounce = 28.0 * g;
	}

	// Nautical units
	namespace Nautical
	{
		constexpr Quantity fathom = 2.0 * yd;
		constexpr Quantity cable  = 120 * fathom;
		constexpr Quantity mile   = 1.852 * km;
		constexpr Quantity knot   = mile / h;
		constexpr Quantity league = 3.0 * mile;
	}

	// Some historical Japanese units
	namespace Japan
	{
		constexpr Quantity shaku = 10.0 / 33.0 * m;
		constexpr Quantity sun   = 0.1 * shaku;
		constexpr Quantity ken   = (1.0 + 9.0 / 11.0) * m;
		constexpr Quantity tsubo = 100.0 / 30.25 * (m^2);
		constexpr Quantity sho   = 2401.0 / 1331.0 * L;
		constexpr Quantity kan   = 15.0 / 4.0 * kg;
		constexpr Quantity go    = 2401.0 / 13310 * L;
		constexpr Quantity cup   = 200.0 * mL;
	}

	// Some historical chinese units
	namespace Chinese
	{
		constexpr Quantity jin   = 0.5 * kg;
		constexpr Quantity liang = 0.1 * g;
		constexpr Quantity qian  = 0.01 * g;

		constexpr Quantity li    = 500 * m;
		constexpr Quantity cun   = 10.0 / 300.0 * m;
		constexpr Quantity chi   = 10.0 * cun;
		constexpr Quantity zhang = 10.0 * chi;
	}

	// Typographic units for typesetting or printing
	namespace Typographic
	{
		namespace American
		{
			constexpr Quantity line  = 1.0 / 12.0 * in;
			constexpr Quantity point = 1.0 / 6.0 * line;
			constexpr Quantity pica  = 12.0 * point;
			constexpr Quantity twip  = 1.0 / 20.0 * point;
		}

		namespace Printers
		{
			constexpr Quantity point = 0.013837 * in;
			constexpr Quantity pica  = 12.0 * point;
		}

		namespace French
		{
			constexpr Quantity point  = 15625.0 / 41559.0 * mm;
			constexpr Quantity ligne  = 6.0 * point;
			constexpr Quantity pouce  = 12.0 * ligne;
			constexpr Quantity didot  = point;
			constexpr Quantity cicero = 12.0 * didot;
			constexpr Quantity pied   = 12.0 * pouce;
			constexpr Quantity toise  = 6.0 * pied;
		}

		namespace Metric
		{
			constexpr Quantity point = 375.0 * micro * m;
			constexpr Quantity quart = 0.25 * mm;
		}
	}

	// Units related to distance
	namespace Distance
	{
		constexpr Quantity ly        = 9.4607304725808e15 * m;
		constexpr Quantity au        = 149597870700.0 * m;
		constexpr Quantity au_old    = 1.495979e11 * m;
		constexpr Quantity angstrom  = 1e-10 * m;
		constexpr Quantity parsec    = 3.085678e16 * m;
		constexpr Quantity smoot     = 67.0 * in;
		constexpr Quantity cubit     = 18.0 * in;
		constexpr Quantity longcubit = 21.0 * in;
		constexpr Quantity arpent_us = 58.47131 * m;
		constexpr Quantity arpent_fr = 71.46466 * m;
		constexpr Quantity xu        = 0.1 * pico * m;
	}

	// Units related to compass directions
	namespace Direction
	{
		// using iflag as a complex coordinate
		constexpr Quantity east  =  1.0;
		constexpr Quantity north =  1.0 * iflag;
		constexpr Quantity south = -1.0 * iflag;
		constexpr Quantity west  = -1.0;

		constexpr Quantity N = north;
		constexpr Quantity S = south;
		constexpr Quantity E = east;
		constexpr Quantity W = west;
	}

	//  Area units
	constexpr Quantity acre = US::acre;

	// Additional Area units
	namespace Area
	{
		constexpr Quantity are     = 100.0 * (m^2);
		constexpr Quantity hectare = 100.0 * are;
		constexpr Quantity barn    = 1e-28 * (m^2);
		constexpr Quantity arpent  = 0.84628 * acre;
	}

	// additional mass units
	namespace Mass
	{
		constexpr Quantity quintal       = 100.0 * kg;
		constexpr Quantity ton_assay     = (29.0 + 1. / 6.0) * g;
		constexpr Quantity longton_assay = (32.0 + 2.0 / 3.0) * g;
	}

	// some extra volume units
	namespace Volume
	{
		constexpr Quantity stere     = m^3;
		constexpr Quantity acre_foot = acre * US::foot;
		constexpr Quantity drum      = 55.0 * US::gallon;
	}

	// angle measure units
	namespace Angle
	{
		constexpr Quantity deg    = Constants::pi  / 180.0 * rad;
		constexpr Quantity grad   = Constants::pi  / 200.0 * rad;
		constexpr Quantity brad   = Constants::tau / 256.0 * rad; // binary radian
		constexpr Quantity gon    = 0.9 * deg;
		constexpr Quantity arcmin = 1.0 / 60.0 * deg;
		constexpr Quantity arcsec = 1.0 / 60.0 * arcmin;
	}

	// units related to temperature
	namespace Temperature
	{
		constexpr Quantity celsius    = 1.0 * K;
		constexpr Quantity fahrenheit = 5.0 / 9.0 * celsius;
		constexpr Quantity reaumur    = 5.0 / 4.0 * celsius;
		constexpr Quantity rankine    = 5.0 / 9.0 * K;

		constexpr Quantity degC = celsius;
		constexpr Quantity degF = fahrenheit;
		constexpr Quantity degR = rankine;
	}

	// others
	constexpr Quantity rpm = 2.0 * Constants::pi / 60.0 * rad / s;
	constexpr Quantity CFM = (ft^3) / min;

	// Units related to pressure
	namespace Pressure
	{
		constexpr Quantity bar   = 1.0e+5 * Pa;
		constexpr Quantity psi   = 6894.757293168 * Pa;
		constexpr Quantity inHg  = 3376.849669 * Pa; // at 60 degF
		constexpr Quantity mmHg  = 133.322387415 * Pa;
		constexpr Quantity torr  = 101325.0 / 760.0 * Pa; // this is really close to mmHg
		constexpr Quantity inH2O = 248.843004 * Pa; // at 60 degF
		constexpr Quantity mmH2O = 1.0 / 25.4 * inH2O; // at 60 degF
		constexpr Quantity atm   = 101325.0 * Pa;
		constexpr Quantity att   = gm::at; // technical atmosphere same as gravitational metric system
	}

	// Power units
	namespace Power
	{
		constexpr Quantity hpE = 746.0 * W; // electric horsepower
		constexpr Quantity hpI = 745.69987158227022 * W; // mechanical horsepower
		constexpr Quantity hpS = 9812.5 * W; // Boiler horsepower
		constexpr Quantity hpM = 735.49875 * W; // Boiler horsepower

		constexpr Quantity  VAR = W * iflag;
	}

	constexpr Quantity hp = Power::hpI;

	// Speed units
	constexpr Quantity mph = mile / h;
	constexpr Quantity mps = m / s;

	// Energy units
	namespace Energy
	{
		constexpr Quantity Wh  = 1.0 * W * h;
		constexpr Quantity eV  = 1.602176634e-19 * J;

		constexpr Quantity cal_4    = 4.20400 * J;
		constexpr Quantity cal_15   = 4.18580 * J; // calorie at 15 degC
		constexpr Quantity cal_20   = 4.18190 * J; // calorie at 20 degC
		constexpr Quantity cal_mean = 4.19002 * J; // mean calorie
		constexpr Quantity cal_it   = 4.18680 * J; // international table calorie
		constexpr Quantity cal_th   = 4.18400 * J; // thermochemical calorie
		constexpr Quantity kcal     = 4184.0 * J;

		constexpr Quantity btu_th   = 1054.350 * J; // thermochemical btu
		constexpr Quantity btu_39   = 1059.67 * J;
		constexpr Quantity btu_59   = 1054.80 * J;
		constexpr Quantity btu_60   = 1054.68 * J;
		constexpr Quantity btu_mean = 1055.87 * J;
		constexpr Quantity btu_it   = 1055.05585 * J; // international table btu
		constexpr Quantity btu_iso  = 1055.06 * J; // rounded btu_it
		constexpr Quantity quad     = 1055.05585262 * J;
		constexpr Quantity tonc     = 12000.0 * btu_th / h;

		constexpr Quantity therm_us = 100000.0 * btu_59;
		constexpr Quantity therm_br = 105505585.257 * J;
		constexpr Quantity therm_ec = 100000 * btu_iso;
		constexpr Quantity EER      = btu_th / W / h; // Energy efficiency ratio
		constexpr Quantity SG       = lb / (ft^3); // Specific gravity

		constexpr Quantity ton_tnt = 4.184 * giga * J;
		constexpr Quantity boe     = 5.8e6 * btu_59;
		constexpr Quantity foeb    = 6.05e6 * btu_59;
		constexpr Quantity hartree = 4.35974465054e-18 * J;
		constexpr Quantity tonhour = 3.5168528421 * kilo * Wh;
	}

	constexpr Quantity btu = Energy::btu_it;
	constexpr Quantity cal = Energy::cal_th;

	// Units used in the textile industry
	namespace Textile
	{
		constexpr Quantity tex    = g / km;
		constexpr Quantity denier = 1.0 / 9.0 * tex;
		constexpr Quantity span   = 0.2286 * m;
		constexpr Quantity finger = 0.1143 * m;
		constexpr Quantity nail   = 0.5 * finger;
	}

	// Units used in clinical medicine
	namespace Clinical
	{
		constexpr Quantity pru     = Pressure::mmHg * s / mL; // peripheral vascular resistance unit
		constexpr Quantity woodu   = Pressure::mmHg * min / L; // wood unit
		constexpr Quantity diopter = m^-1;
//		constexpr Quantity prism_diopter = ???
		constexpr Quantity mesh      = in^-1;
		constexpr Quantity charriere = 1.0 / 3.0 * mm;
		constexpr Quantity drop      = 0.05 * mL;
		constexpr Quantity met       = 3.5 * mL / min / kg; // metabolic equivalent
	}

	// Units used in chemical and biological laboratories
	namespace Laboratory
	{
		constexpr Quantity svedberg = 1e-13 * s;
		constexpr Quantity enzyme_unit = micro * mol / min;

		constexpr Quantity PFU      = 1.0 * count;
		constexpr Quantity pH       = 1.0 * mol / L; // negative log10;
		constexpr Quantity molarity = 1.0 * mol / L;
		constexpr Quantity molality = 1.0 * mol / kg;
	}

	// Weight units
	constexpr Quantity tonne = 1000.0 * kg;
	constexpr Quantity t     = tonne;
	constexpr Quantity Da    = 1.6605388628e-27 * kg;
	constexpr Quantity u     = Da;

	// Units related to quantities of data
	namespace Data
	{
		constexpr Quantity bit    = 1 * count;
		constexpr Quantity nibble = 4 * bit;
		constexpr Quantity byte   = 8 * bit;

		constexpr Quantity kB = kilo * byte;
		constexpr Quantity MB = mega * byte;
		constexpr Quantity GB = giga * byte;
		constexpr Quantity TB = tera * byte;

		constexpr Quantity KiB = kibi * byte;
		constexpr Quantity MiB = mebi * byte;
		constexpr Quantity GiB = gibi * byte;
		constexpr Quantity TiB = tebi * byte;
	}

	// Units related to computation
	namespace Computation
	{
		constexpr Quantity FLOP  = 1.0 * count;
		constexpr Quantity FLOPS = FLOP / s;
		constexpr Quantity MIPS  = (1.0e6 * count / s);
	}

	// concentrations
	constexpr Quantity ppm = 1e-6 * count;
	constexpr Quantity ppb = 1e-9 * count;

	// other special units
	namespace Special
	{
		// square root of Hertz
		constexpr Quantity sqrtHz = Hz * iflag;
		// Amplitude spectral density
		constexpr Quantity ASD = 1.0 * V / sqrtHz;
	}

	constexpr Quantity candle  = 0.981 * Cd;
	constexpr Quantity faraday = 9.648533289e4 * C;
}
