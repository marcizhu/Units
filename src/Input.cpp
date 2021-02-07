#include <cctype>
#include <istream>
#include <unordered_map>

#include "Units/Units.h"
#include "Units/IO.h"
#include "Units/extras/StdAdditions.h"

#include "Buffer.h"

namespace Units
{
	/*
	Syntax (EBNF)

             expression = value term ;
                   term = factor { ( " " | "." | "*" | "/" ) , factor } ;
                 factor = prefixed_unit , [power]
                        | "(" , expression , ")" ;
          prefixed_unit = [prefix] , unit ;
                  value = floating_point_number ;
                  power = "^" , signed_number ;
                 prefix = "y".."Y" ;
                   unit = ( "m" | "kg" | "s" | "A" | "K" | "mol" | "cd"... )

		Examples
			1 m, 1 m^2, 1 m/s, 1 m/s^2, 1 (4 cm^2), 33 Hz, 33 s^-1, 45 m / (10 s), 2 N*s
	*/

	template<typename Buffer> Quantity parseExpression(Buffer& buff);
	template<typename Buffer> Quantity parseTerm(Buffer& buff);
	template<typename Buffer> Quantity parseFactor(Buffer& buff);
	template<typename Buffer> Quantity parseUnit(Buffer& buff);
	template<typename Buffer> double parsePrefix(Buffer& buff);

	std::unordered_map<std::u16string, Unit> units
	{
		// Special
		{ u"none" , none },
		{ u"%"    , percent },
		{ u"error", error   },
		{ u"iflag", iflag   },

		{ u""   , none },
		{ u"m"  , m    },
		{ u"kg" , kg   },
		{ u"s"  , s    },
		{ u"A"  , A    },
		{ u"K"  , K    },
		{ u"mol", mol  },
		{ u"rad", rad  },
		{ u"Cd" , Cd   },

		{ u"sr"  , sr            },
		{ u"Hz"  , Hz            },
		{ u"N"   , N             },
		{ u"Pa"  , Pa            },
		{ u"J"   , J             },
		{ u"W"   , W             },
		{ u"C"   , C             },
		{ u"V"   , V             },
		{ u"F"   , F             },
		{ u"\u2126", ohm         },
		{ u"S"   , S             },
		{ u"Wb"  , Wb            },
		{ u"T"   , T             },
		{ u"H"   , H             },
		{ u"lm"  , lm            },
		{ u"lx"  , lx            },
		{ u"Bq"  , Bq            },
		{ u"Gy"  , Gy            },
		{ u"Sv"  , Sv            },
		{ u"kat" , kat           },
		{ u"$"   , currency      },
		{ u"item", count         },
		{ u"\u221aHz", std::sqrt(Hz) },

		{ u"Np" , Log::neper },
		{ u"B"  , Log::B     },
		{ u"BA" , Log::BA    },
		{ u"dB" , Log::dB    },
		{ u"dBA", Log::dBA   },
		{ u"dBc", Log::dBc   },

		{ u"BV"       , Log::BV     },
		{ u"BmV"      , Log::BmV    },
		{ u"B\u00B5V", Log::BuV    },
		{ u"B10nV"    , Log::B10nV  },
		{ u"BW"       , Log::BW     },
		{ u"Bk"       , Log::Bk     },
		{ u"dBV"      , Log::dBV    },
		{ u"dBmV"     , Log::dBmV   },
		{ u"dBuV"     , Log::dBuV   },
		{ u"dB10nV"   , Log::dB10nV },
		{ u"dBW"      , Log::dBW    },
		{ u"dBk"      , Log::dBk    },
		{ u"dBm"      , Log::dBm    },

		{ u"h",  Time::hour  },
		{ u"Eh", Energy::hartree },
		{ u"mi", i::mile }
	};

	bool isLetter(Buffer& buff)
	{
		return (buff.current() >= 'a' && buff.current() <= 'z')
			|| (buff.current() >= 'A' && buff.current() <= 'Z');
	}

	template<typename Buffer>
	Quantity parseExpression(Buffer& buff)
	{
		if(std::isspace(buff.current())) buff.advance(true);

		double quant = buff.parseDouble();
		Quantity term = parseTerm(buff);
		return quant * term;
	}

	template<typename Buffer>
	Quantity parseTerm(Buffer& buff)
	{
		if(std::isspace(buff.current())) buff.advance(true);
		Quantity factor = parseFactor(buff);

		while( buff.current() == ' '
			|| buff.current() == '*'
			|| buff.current() == '.'
			|| buff.current() == '/'
			|| buff.current() == '(')
		{
			switch(buff.current())
			{
				case ' ':
				case '*':
				case '.':
				case '(':
					if(buff.advance(true) != '(' && !isLetter(buff)) continue;
					factor *= parseFactor(buff);
					break;

				case '/':
					if(buff.advance(true) != '(' && !isLetter(buff)) continue;
					factor /= parseFactor(buff);
					break;
			}
		}

		return factor;
	}

	template<typename Buffer>
	Quantity parseFactor(Buffer& buff)
	{
		if(buff.accept('('))
		{
			Quantity expr = parseExpression(buff);
			if(!buff.accept(')')) return Unit::error();

			return expr.magnitude() == 0.0 ? 1.0 * expr.unit() : expr;
		}

		buff.push();
		Quantity unit = parseUnit(buff);

		if(unit == Unit::error())
		{
			buff.pop();
			return parsePrefix(buff) * parseUnit(buff);
		}

		return unit;
	}

	template<typename Buffer>
	Quantity parseUnit(Buffer& buff)
	{
		Quantity ret = Unit::error();
		std::u16string unitName;

		while(isLetter(buff)
			|| buff.current() == '$'
			|| buff.current() == '%'
			|| buff.current() == u'\u221A'  // Square root symbol
			|| buff.current() == u'\u2126') // Ohm symbol
		{
			unitName += buff.current();
			buff.advance();
		}

		// Exception: kg is the only SI unit with prefix
		if(unitName == u"g") return g;

		auto it = units.find(unitName);
		if(it != units.end()) ret = 1.0 * it->second;

		if(ret != Unit::error() && buff.accept('^'))
			ret ^= buff.parseInt();

		return ret;
	}

	template<typename Buffer>
	double parsePrefix(Buffer& buff)
	{
		switch(buff.current())
		{
			case 'Y': buff.advance(); return yotta;
			case 'Z': buff.advance(); return zetta;
			case 'E': buff.advance(); return exa;
			case 'P': buff.advance(); return peta;
			case 'T': buff.advance(); return tera;
			case 'G': buff.advance(); return giga;
			case 'M': buff.advance(); return mega;
			case 'k': buff.advance(); return kilo;
			case 'h': buff.advance(); return hecto;
			case 'c': buff.advance(); return centi;
			case 'm': buff.advance(); return milli;
			case 'u': buff.advance(); return micro;
			case 'n': buff.advance(); return nano;
			case 'p': buff.advance(); return pico;
			case 'f': buff.advance(); return femto;
			case 'a': buff.advance(); return atto;
			case 'z': buff.advance(); return zepto;
			case 'y': buff.advance(); return yocto;
		}

		/**/ if(buff.accept(u'\u00B5')) return micro;
		else if(buff.accept('d')) return buff.accept('a') ? deca : deci;

		return 1.0;
	}

	template<typename InputType>
	Unit to_unit_template(InputType& str)
	{
		Buffer buff(str);
		return parseTerm(buff).unit();
	}

	template<typename InputType>
	Quantity to_quantity_template(InputType& str)
	{
		Buffer buff(str);
		return parseExpression(buff);
	}

	Unit to_unit(const std::string& str)    { return to_unit_template(str); }
	Unit to_unit(const std::u16string& str) { return to_unit_template(str); }
	Unit to_unit(const std::u32string& str) { return to_unit_template(str); }
	Unit to_unit(std::istream& is)          { return to_unit_template(is); }

	Quantity to_quantity(const std::string& str)    { return to_quantity_template(str); }
	Quantity to_quantity(const std::u16string& str) { return to_quantity_template(str); }
	Quantity to_quantity(const std::u32string& str) { return to_quantity_template(str); }
	Quantity to_quantity(std::istream& is)          { return to_quantity_template(is); }
}
