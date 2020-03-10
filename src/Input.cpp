#include "Units/Units.h"
#include "Units/IO.h"
#include "Units/extras/StdAdditions.h"

namespace Units
{
	// 15 km^2/s^2

	class Buffer
	{
	protected:
		constexpr static const char EOF_MARK = (char)0xFF;

	public:
		/** @brief Accepts an optional character. Returns `true` if char was found. */
		virtual bool accept(char chr) = 0;

		/** @brief Returns current character. */
		virtual char current() = 0;

		/** @brief Returns next character. */
		virtual char ahead() = 0;

		/** @brief Advances to the next character. Returns current char. */
		virtual char advance(bool skipws = false) = 0;

		/** @brief Expects a character. Returns `false` if expected character was not found. */
		virtual bool expect(char chr) = 0;

		virtual void push() = 0;
		virtual void pop() = 0;
	};

	class StringBuffer : public Buffer
	{
	private:
		const std::string& str;
		size_t ptr;
		size_t ptr_old;

	public:
		StringBuffer(const std::string& s) : str(s), ptr(0), ptr_old(0) {}
		~StringBuffer() = default;

		bool accept(char chr) override
		{
			if(chr != current()) return false;

			advance();
			return true;
		}

		char current() override { return  ptr      < str.size() ? str[ptr    ] : EOF_MARK; }
		char ahead  () override { return (ptr + 1) < str.size() ? str[ptr + 1] : EOF_MARK; }

		char advance(bool skipws = false) override
		{
			if(current() == EOF_MARK) return EOF_MARK;

			++ptr;

			if(skipws)
			{
				while(current() == ' ')
					++ptr;
			}

			return current();
		}

		bool expect(char chr) override
		{
			if(chr != current())
			{
				throw std::runtime_error(
					"quantity: expecting '" + std::string(1, static_cast<char>(chr)) + "'");
				return false;
			}

			advance();
			return true;
		}

		void push() override { ptr_old = ptr; }
		void pop () override { ptr = ptr_old; }
	};

	/*
	Syntax (EBNF)

			 expression = [value] term ;
                   term = factor { ( " " | "." | "*" | "/" ) , factor } ;
                 factor = prefixed-unit , [power]
                        | "(" , expression , ")" ;
          prefixed-unit = [prefix] , unit ;
                  value = floating_point_number ;
                  power = "^" , signed_number ;
                 prefix = "y".."Y" ;
                   unit = ( "m" | "kg" | "s" | "A" | "K" | "mol" | "cd"... )

		Examples
			1 m, 1 m^2, 1 m/s, 1 m/s^2, 1 (4 cm)^2, 33 Hz, 33 s^-1, 45 m / (10 s)
	*/

	std::unordered_map<std::string, Unit> units
	{
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
		{ "√Hz" , std::sqrt(Hz) }
	};

	bool isLetter(Buffer* buff)
	{
		return (buff->current() >= 'a' && buff->current() <= 'z')
			|| (buff->current() >= 'A' && buff->current() <= 'Z');
	}

	bool isNumber(Buffer* buff)
	{
		return (buff->current() >= '0' && buff->current() <= '9');
	}

	bool isWhitespace(Buffer* buff)
	{
		return std::isspace(buff->current());
	}

	Quantity parseExpression(Buffer* buff);
	Quantity parseTerm(Buffer* buff);
	Quantity parseFactor(Buffer* buff);

	Unit parseUnit(Buffer* buff);

	double parsePrefix(Buffer* buff);
	double parseValue(Buffer* buff);
	int parsePower(Buffer* buff);
	int parseInt(Buffer* buff);

	Quantity parseExpression(Buffer* buff)
	{
		double quantity = parseValue(buff);
		return quantity * parseTerm (buff);
	}

	Quantity parseTerm(Buffer* buff)
	{
		if(isWhitespace(buff)) buff->advance(true);
		Quantity factor = parseFactor(buff);

		while(buff->current() == ' '
			|| buff->current() == '*'
			|| buff->current() == '.'
			|| buff->current() == '/')
		{
			switch(buff->current())
			{
				case ' ':
				case '*':
				case '.':
					buff->advance(true);
					if(!isLetter(buff) && buff->current() != '(') continue;
					factor *= parseFactor(buff);
					break;

				case '/':
					buff->advance(true);
					if(!isLetter(buff) && buff->current() != '(') continue;
					factor /= parseFactor(buff);
					break;
			}
		}

		return factor;
	}

	Quantity parseFactor(Buffer* buff)
	{
		if(buff->accept('('))
		{
			Quantity expr = parseExpression(buff);
			buff->expect(')');

			return expr;
		}

		buff->push();
		Unit unit = parseUnit(buff);

		if(unit.eflag())
		{
			buff->pop();
			return parsePrefix(buff) * parseUnit(buff);
		}

		return 1.0 * unit;
	}

	Unit parseUnit(Buffer* buff)
	{
		Unit ret = error;
		std::string unitName;

		while(isLetter(buff) || buff->current() == '$')
		{
			unitName += buff->current();
			buff->advance();
		}

		auto it = units.find(unitName);
		if(it != units.end() && !unitName.empty()) ret = it->second;

		if(ret != error && buff->accept('^'))
		{
			ret ^= (int8_t)parseInt(buff);
		}

		return ret;
	}

	double parsePrefix(Buffer* buff)
	{
		switch(buff->current())
		{
			case 'Y': buff->advance(); return yotta;
			case 'Z': buff->advance(); return zetta;
			case 'E': buff->advance(); return exa;
			case 'P': buff->advance(); return peta;
			case 'T': buff->advance(); return tera;
			case 'G': buff->advance(); return giga;
			case 'M': buff->advance(); return mega;
			case 'k': buff->advance(); return kilo;
			case 'h': buff->advance(); return hecto;
			case 'c': buff->advance(); return centi;
			case 'm': buff->advance(); return milli;
			case 'u': buff->advance(); return micro;
			case 'n': buff->advance(); return nano;
			case 'p': buff->advance(); return pico;
			case 'f': buff->advance(); return femto;
			case 'a': buff->advance(); return atto;
			case 'z': buff->advance(); return zepto;
			case 'y': buff->advance(); return yocto;

			case 'd':
				buff->advance();
				return buff->accept('a') ? deca : deci;
		}

		return 1.0;
	}

	double parseValue(Buffer* buff)
	{
		std::string s;

		while(isNumber(buff)
			|| buff->current() == '-'
			|| buff->current() == '+'
			|| buff->current() == 'e'
			|| buff->current() == 'E'
			|| buff->current() == '.')
		{
			s += buff->current();
			buff->advance();
		}

		return std::atof(s.c_str());
	}

	int parseInt(Buffer* buff)
	{
		int total = 0;
		bool neg  = false;

		/**/ if(buff->accept('+')) neg = false;
		else if(buff->accept('-')) neg = true;

		while(isNumber(buff))
		{
			total = 10 * total + buff->current();
			buff->advance();
		}

		return neg ? -total : total;
	}

	bool from_string(const std::string& str, Unit& unit)
	{
		Buffer* buff = new StringBuffer(str);
		unit = parseExpression(buff).getUnit();
		return true;
	}

	bool from_string(const std::string& str, Quantity& quant)
	{
		Buffer* buff = new StringBuffer(str);
		quant = parseExpression(buff);
		return true;
	}
}
