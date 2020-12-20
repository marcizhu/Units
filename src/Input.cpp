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

	std::unordered_map<std::string, Unit> units
	{
		// Special
		{ "none" , none },
		{ "%"    , percent },
		{ "error", error   },
		{ "iflag", iflag   },

		{ ""   , none },
		{ "m"  , m    },
		{ "kg" , kg   },
		{ "s"  , s    },
		{ "A"  , A    },
		{ "K"  , K    },
		{ "mol", mol  },
		{ "rad", rad  },
		{ "Cd" , Cd   },

		{ "sr"  , sr            },
		{ "Hz"  , Hz            },
		{ "N"   , N             },
		{ "Pa"  , Pa            },
		{ "J"   , J             },
		{ "W"   , W             },
		{ "C"   , C             },
		{ "V"   , V             },
		{ "F"   , F             },
		{ "Ω"   , ohm           },
		{ "S"   , S             },
		{ "Wb"  , Wb            },
		{ "T"   , T             },
		{ "H"   , H             },
		{ "lm"  , lm            },
		{ "lx"  , lx            },
		{ "Bq"  , Bq            },
		{ "Gy"  , Gy            },
		{ "Sv"  , Sv            },
		{ "kat" , kat           },
		{ "$"   , currency      },
		{ "item", count         },
		{ "√Hz" , std::sqrt(Hz) },

		{ "Np" , Log::neper },
		{ "B"  , Log::B     },
		{ "BA" , Log::BA    },
		{ "dB" , Log::dB    },
		{ "dBA", Log::dBA   },
		{ "dBc", Log::dBc   },

		{ "BV"        , Log::BV     },
		{ "BmV"       , Log::BmV    },
		{ u8"B\u00B5V", Log::BuV    },
		{ "B10nV"     , Log::B10nV  },
		{ "BW"        , Log::BW     },
		{ "Bk"        , Log::Bk     },
		{ "dBV"       , Log::dBV    },
		{ "dBmV"      , Log::dBmV   },
		{ "dBuV"      , Log::dBuV   },
		{ "dB10nV"    , Log::dB10nV },
		{ "dBW"       , Log::dBW    },
		{ "dBk"       , Log::dBk    },
		{ "dBm"       , Log::dBm    },

		{ "h"         , Time::hour  },
		{ "Eh", Energy::hartree },
		{ "mi", i::mile }
	};

	template<typename Buffer>
	bool isLetter(Buffer& buff)
	{
		return (buff.current() >= 'a' && buff.current() <= 'z')
			|| (buff.current() >= 'A' && buff.current() <= 'Z');
	}

	template<typename Buffer>
	bool isNumber(Buffer& buff)
	{
		return (buff.current() >= '0' && buff.current() <= '9');
	}

	template<typename Buffer>
	bool isWhitespace(Buffer& buff)
	{
		return std::isspace(buff.current());
	}

	template<typename Buffer>
	Quantity parseExpression(Buffer& buff)
	{
		if(isWhitespace(buff)) buff.advance(true);

		double quant = buff.parseDouble();
		Quantity term = parseTerm(buff);
		return quant * term;
	}

	template<typename Buffer>
	Quantity parseTerm(Buffer& buff)
	{
		if(isWhitespace(buff)) buff.advance(true);
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
			if(!buff.accept(')')) return error;

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
		Quantity ret = error;
		std::string unitName;

		// FIXME: Does NOT allow sqrt(Hz) && Ω to pass through
		while(isLetter(buff)
			|| buff.current() == '$'
			|| buff.current() == '%')
		{
			unitName += buff.current();
			buff.advance();
		}

		// Exception: kg is the only SI unit with prefix
		if(unitName == "g") return g;

		auto it = units.find(unitName);
		if(it != units.end()) ret = 1.0 * it->second;

		if(ret != error && buff.accept('^'))
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

		/**/ if(buff.accept('\xC2') && buff.accept('\xB5')) return micro;
		else if(buff.accept('d')) return buff.accept('a') ? deca : deci;

		return 1.0;
	}

	Unit to_unit(const std::string& str)
	{
		Buffer buff(str);
		return parseTerm(buff).unit();
	}

	Unit to_unit(std::istream& is)
	{
		Buffer buff(is);
		return parseTerm(buff).unit();
	}

	Quantity to_quantity(const std::string& str)
	{
		Buffer buff(str);
		return parseExpression(buff);
	}

	Quantity to_quantity(std::istream& is)
	{
		Buffer buff(is);
		return parseExpression(buff);
	}
}
