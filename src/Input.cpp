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

	Quantity parseExpression(Buffer& buff);
	Quantity parseTerm(Buffer& buff);
	Quantity parseFactor(Buffer& buff);
	Quantity parseUnit(Buffer& buff);
	double parsePrefix(Buffer& buff);

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
		{ u"B\u00B5V" , Log::BuV    },
		{ u"B\u03BCV" , Log::BuV    },
		{ u"BuV"      , Log::BuV    },
		{ u"B10nV"    , Log::B10nV  },
		{ u"BW"       , Log::BW     },
		{ u"Bk"       , Log::Bk     },
		{ u"dBV"      , Log::dBV    },
		{ u"dBmV"     , Log::dBmV   },
		{ u"dB\u00B5V", Log::dBuV   },
		{ u"dB\u03BCV", Log::dBuV   },
		{ u"dBuV"     , Log::dBuV   },
		{ u"dB10nV"   , Log::dB10nV },
		{ u"dBW"      , Log::dBW    },
		{ u"dBk"      , Log::dBk    },
		{ u"dBm"      , Log::dBm    },

		{ u"h",  Time::hour  },
		{ u"Eh", Energy::hartree },
		{ u"mi", i::mile }
	};

	bool isLetter(const Buffer& buff)
	{
		return (buff.current() >= 'a' && buff.current() <= 'z')
			|| (buff.current() >= 'A' && buff.current() <= 'Z');
	}

	bool isSpace(const Buffer& buff)
	{
		return buff.current() == ' '  || buff.current() == '\t'
			|| buff.current() == '\n' || buff.current() == '\v'
			|| buff.current() == '\f' || buff.current() == '\r';
	}

	bool isSuperscript(const Buffer& buff)
	{
		return buff.current() == u'\u2070' // 0
			|| buff.current() == u'\u00B9' // 1
			|| (buff.current() >= u'\u00B2' && buff.current() <= u'\u00B3')  // 2 through 3
			|| (buff.current() >= u'\u2074' && buff.current() <= u'\u2079'); // 4 through 9
	}

	int superscript2int(const Buffer& buff)
	{
		/**/ if(buff.current() == u'\u2070') return 0;
		else if(buff.current() == u'\u00B9') return 1;
		else if(buff.current() >= u'\u00B2' && buff.current() <= u'\u00B3') return buff.current() - u'\u00B0';
		else if(buff.current() >= u'\u2074' && buff.current() <= u'\u2079') return buff.current() - u'\u2070';

		return 0;
	}

	int parseInt(Buffer& buff)
	{
		if(isSpace(buff)) buff.advance(true);

		int ret = 0;
		bool neg = false;

		/**/ if(buff.accept(u'-')) neg = true;
		else if(buff.accept(u'+')) neg = false;

		while(buff.current() >= u'0' && buff.current() <= u'9')
		{
			ret = 10 * ret + (buff.current() - '0');
			buff.advance();
		}

		return neg ? -ret : ret;
	}

	int parseExponent(Buffer& buff)
	{
		// TODO: This accepts combinations of superscript and non-superscript numbers
		if(isSpace(buff)) buff.advance(true);

		int ret = 0;
		bool neg = false;

		/**/ if(buff.accept(u'-') || buff.accept(u'\u207B')) neg = true;
		else if(buff.accept(u'+') || buff.accept(u'\u207A')) neg = false;

		while((buff.current() >= u'0' && buff.current() <= u'9') || isSuperscript(buff))
		{
			if(isSuperscript(buff))
				ret = 10 * ret + superscript2int(buff);
			else
				ret = 10 * ret + (buff.current() - '0');

			buff.advance();
		}

		return neg ? -ret : ret;
	}

	double parseDouble(Buffer& buff)
	{
		int integral = parseInt(buff);
		int decimal = 0;
		int exponent = 0;

		if(buff.accept(u'.'))
		{
			if(buff.accept(u'-') || buff.accept(u'+'))
				return std::numeric_limits<double>::quiet_NaN();

			decimal = parseInt(buff);
		}

		if(buff.accept(u'e') || buff.accept(u'E'))
			exponent = parseInt(buff);

		return decimal
			? (integral + ((double)decimal / (double)std::pow(10.0, std::floor(std::log10(decimal)) + 1))) * std::pow(10.0, exponent)
			: (integral * std::pow(10.0, exponent));
	}

	Quantity parseExpression(Buffer& buff)
	{
		if(isSpace(buff)) buff.advance(true);

		double quant = parseDouble(buff);
		Quantity term = parseTerm(buff);
		return quant * term;
	}

	Quantity parseTerm(Buffer& buff)
	{
		if(isSpace(buff)) buff.advance(true);

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

	Quantity parseUnit(Buffer& buff)
	{
		Quantity ret = Unit::error();
		std::u16string unitName;

		while(isLetter(buff)
			|| buff.current() == '$'
			|| buff.current() == '%'
			|| buff.current() == u'\u221A'  // Square root symbol
			|| buff.current() == u'\u2126'  // Ohm symbol
			|| buff.current() == u'\u00B5'  // Micro symbol
			|| buff.current() == u'\u03BC') // Greek mu symbol
		{
			unitName += buff.current();
			buff.advance();
		}

		// Exception: kg is the only SI unit with prefix
		if(unitName == u"g") return g;

		auto it = units.find(unitName);
		if(it != units.end()) ret = Quantity(1.0, it->second);

		if(ret != Unit::error() &&
			(buff.accept('^')
				|| buff.current() == u'\u207A' // Superscript +
				|| buff.current() == u'\u207B' // Superscript -
				|| isSuperscript(buff))) // Superscript number
		{
			ret ^= parseExponent(buff);
		}

		return ret;
	}

	double parsePrefix(Buffer& buff)
	{
		switch(buff.current())
		{
			case u'Y': buff.advance(); return yotta;
			case u'Z': buff.advance(); return zetta;
			case u'E': buff.advance(); return exa;
			case u'P': buff.advance(); return peta;
			case u'T': buff.advance(); return tera;
			case u'G': buff.advance(); return giga;
			case u'M': buff.advance(); return mega;
			case u'k': buff.advance(); return kilo;
			case u'h': buff.advance(); return hecto;
			case u'c': buff.advance(); return centi;
			case u'm': buff.advance(); return milli;
			case u'n': buff.advance(); return nano;
			case u'p': buff.advance(); return pico;
			case u'f': buff.advance(); return femto;
			case u'a': buff.advance(); return atto;
			case u'z': buff.advance(); return zepto;
			case u'y': buff.advance(); return yocto;

			// Special cases
			case u'u':
			case u'\u00B5':
			case u'\u03BC':
				buff.advance();
				return micro;
		}

		if(buff.accept(u'd'))
			return buff.accept(u'a') ? deca : deci;

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
