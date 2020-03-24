#pragma once

#include <functional> // for std::hash
#include <stdexcept>

#include "sprout/cmath.hpp"

namespace Units
{
	#pragma pack(push)
	#pragma pack(4)
	class Unit
	{
	private:
		double multiplier;
		struct Dimensions
		{
			signed int meter : 4;
			signed int kilogram : 3;
			signed int second : 4;
			signed int ampere : 3;
			signed int kelvin : 4;
			signed int mole : 2;
			signed int radians : 3;
			signed int candela : 2;
			signed int currency : 2;
			signed int count : 2;
			bool e_flag : 1;
			bool i_flag : 1;
			bool eq_flag : 1;

			constexpr Dimensions(int8_t _1, int8_t _2, int8_t _3, int8_t _4, int8_t _5, int8_t _6, int8_t _7, int8_t _8, int8_t _9, int8_t _10, bool e_flag, bool iflag, bool eqflag)
				: meter(_1), kilogram(_2), second(_3), ampere(_4), kelvin(_5), mole(_6), radians(_7), candela(_8), currency(_9), count(_10), e_flag(e_flag), i_flag(iflag), eq_flag(eqflag) {}

			constexpr bool operator!=(Dimensions other) const { return !(*this == other); }
			constexpr bool operator==(Dimensions other) const
			{
				return meter    == other.meter
					&& kilogram == other.kilogram
					&& second   == other.second
					&& ampere   == other.ampere
					&& kelvin   == other.kelvin
					&& mole     == other.mole
					&& radians  == other.radians
					&& candela  == other.candela
					&& currency == other.currency
					&& count    == other.count
					&& e_flag   == other.e_flag
					&& i_flag   == other.i_flag
					&& eq_flag  == other.eq_flag;
			}

			constexpr int unit_count() const
			{
				 return
				 	((meter    != 0) ? 1 : 0) + ((second  != 0) ? 1 : 0) +
					((kilogram != 0) ? 1 : 0) + ((ampere  != 0) ? 1 : 0) +
					((candela  != 0) ? 1 : 0) + ((kelvin  != 0) ? 1 : 0) +
					((mole     != 0) ? 1 : 0) + ((radians != 0) ? 1 : 0) +
					((currency != 0) ? 1 : 0) + ((count   != 0) ? 1 : 0);
			}

			constexpr int degree() const
			{
				return
					meter + kilogram + second + ampere + kelvin +
					mole + radians + candela + currency + count;
			}
		} dim;

		constexpr static bool compare_round_equals(double val1, double val2)
		{
			auto v1 = val1 - val2;
			if (v1 == 0.0 || sprout::fpclassify(v1) == FP_SUBNORMAL || sprout::abs(v1) < 1e-15) {
				return true;
			}

			return false;
		}

		constexpr void check_unit(const Unit& other) const { if(*this != other) throw std::logic_error("Incompatible units!"); }

		constexpr bool isRootHz() const
		{
			return dim == Dimensions(0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
		}

		constexpr bool isHz() const
		{
			return dim.meter    == 0
				&& dim.kilogram == 0
				&& dim.second   <  0
				&& dim.ampere   == 0
				&& dim.kelvin   == 0
				&& dim.radians  == 0
				&& dim.mole     == 0
				&& dim.candela  == 0
				&& dim.currency == 0
				&& dim.count    == 0
				&& dim.e_flag   == 0
				&& dim.i_flag   == 0
				&& dim.eq_flag  == 0;
		}

		constexpr bool hasValidRoot(int power) const
		{
			return dim.meter    % power == 0
				&& dim.kilogram % power == 0
				&& dim.second   % power == 0
				&& dim.ampere   % power == 0
				&& dim.kelvin   % power == 0
				&& dim.radians  % power == 0
				&& dim.mole             == 0
				&& dim.candela          == 0
				&& dim.currency         == 0
				&& dim.count            == 0
				&& dim.e_flag           == 0
				&& dim.eq_flag          == 0;
		}

	public:
		constexpr explicit Unit(uint8_t num)
			: multiplier(1.0), dim(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
		{
			if(num > 0b0001'1111) *this = Unit(nullptr);

			dim.count   = (num & 0b0000'0011) >> 0;
			dim.radians = (num & 0b0001'1100) >> 2;
		}

		constexpr explicit Unit()                               : multiplier(1.0), dim(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
		constexpr explicit Unit(std::nullptr_t)                 : multiplier(1.0), dim(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0) {}
		constexpr          Unit(double mult, const Unit& other) : multiplier(mult * other.multiplier), dim(other.dim) {}

		constexpr Unit(int8_t _1, int8_t _2, int8_t _3, int8_t _4, int8_t _5, int8_t _6, int8_t _7, int8_t _8, int8_t _9, int8_t _10, bool iflag = false)
			: multiplier(1.0), dim(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, 0, iflag, 0) {}

		constexpr uint32_t base_units() const { return *(const uint32_t*)&dim; }

		constexpr double unit_multiplier() const { return multiplier; }

		constexpr int meter   () const { return dim.meter;    }
		constexpr int kg      () const { return dim.kilogram; }
		constexpr int second  () const { return dim.second;   }
		constexpr int ampere  () const { return dim.ampere;   }
		constexpr int kelvin  () const { return dim.kelvin;   }
		constexpr int radian  () const { return dim.radians;  }
		constexpr int mole    () const { return dim.mole;     }
		constexpr int candela () const { return dim.candela;  }
		constexpr int currency() const { return dim.currency; }
		constexpr int count   () const { return dim.count;    }
		constexpr bool iflag  () const { return dim.i_flag;   }
		constexpr bool eflag  () const { return dim.e_flag;   }

		constexpr Unit operator^(int exp) const
		{
			Unit ret(*this);
			ret.multiplier    = sprout::pow(ret.multiplier, (double)exp);
			ret.dim.meter    *= exp;
			ret.dim.kilogram *= exp;
			ret.dim.second   *= (ret.isRootHz() ? (exp / 2) : exp);
			ret.dim.ampere   *= exp;
			ret.dim.kelvin   *= exp;
			ret.dim.mole     *= exp;
			ret.dim.radians  *= exp;
			ret.dim.candela  *= exp;
			ret.dim.currency *= exp;
			ret.dim.count    *= exp;
			ret.dim.i_flag   *= ((exp % 2 == 0) ? 0u : 1u);
			ret.dim.e_flag    = 0;
			return ret;
		}

		constexpr Unit operator+(const Unit& rhs) const { check_unit(rhs); return *this; }
		constexpr Unit operator-(const Unit& rhs) const { check_unit(rhs); return *this; }

		constexpr Unit operator*(const Unit& rhs) const
		{
			Unit ret(*this);
			ret.multiplier   *= rhs.multiplier;
			ret.dim.meter    += rhs.dim.meter;
			ret.dim.kilogram += rhs.dim.kilogram;
			ret.dim.second   += (ret.isRootHz() && rhs.isRootHz() ? 0 : rhs.dim.second);
			ret.dim.ampere   += rhs.dim.ampere;
			ret.dim.kelvin   += rhs.dim.kelvin;
			ret.dim.mole     += rhs.dim.mole;
			ret.dim.radians  += rhs.dim.radians;
			ret.dim.candela  += rhs.dim.candela;
			ret.dim.currency += rhs.dim.currency;
			ret.dim.count    += rhs.dim.count;
			ret.dim.i_flag   ^= rhs.dim.i_flag;
			ret.dim.e_flag   |= rhs.dim.e_flag;
			ret.dim.eq_flag  |= rhs.dim.eq_flag;
			return ret;
		}

		constexpr Unit operator/(const Unit& rhs) const
		{
			Unit ret(*this);
			ret.multiplier   /= rhs.multiplier;
			ret.dim.meter    -= rhs.dim.meter;
			ret.dim.kilogram -= rhs.dim.kilogram;
			ret.dim.second   -= (ret.isHz() && rhs.isRootHz() ? 0 : rhs.dim.second);
			ret.dim.ampere   -= rhs.dim.ampere;
			ret.dim.kelvin   -= rhs.dim.kelvin;
			ret.dim.mole     -= rhs.dim.mole;
			ret.dim.radians  -= rhs.dim.radians;
			ret.dim.candela  -= rhs.dim.candela;
			ret.dim.currency -= rhs.dim.currency;
			ret.dim.count    -= rhs.dim.count;
			ret.dim.i_flag   ^= rhs.dim.i_flag;
			ret.dim.e_flag   |= rhs.dim.e_flag;
			ret.dim.eq_flag  ^= rhs.dim.eq_flag;
			return ret;
		}

		constexpr Unit& operator^=(int  exp) { *this = *this ^ exp; return *this; }
		constexpr Unit& operator+=(Unit rhs) { *this = *this + rhs; return *this; }
		constexpr Unit& operator-=(Unit rhs) { *this = *this - rhs; return *this; }
		constexpr Unit& operator*=(Unit rhs) { *this = *this * rhs; return *this; }
		constexpr Unit& operator/=(Unit rhs) { *this = *this / rhs; return *this; }

		constexpr bool operator!=(Unit other) const { return dim != other.dim || !compare_round_equals(multiplier, other.multiplier); }
		constexpr bool operator==(Unit other) const { return dim == other.dim &&  compare_round_equals(multiplier, other.multiplier); }

		constexpr void pow (int power) { *this ^= power; }
		constexpr void root(int power)
		{
			if(!hasValidRoot(power))
			{
				// Test for root 2 of Hz
				if(isHz())
				{
					dim.i_flag = 1;
					return;
				}

				*this = Unit(nullptr);
				return;
			}

			multiplier    = sprout::pow(multiplier, 1.0 / (double)power);
			dim.meter    /= power;
			dim.kilogram /= power;
			dim.second   /= power;
			dim.ampere   /= power;
			dim.kelvin   /= power;
			dim.radians  /= power;
			dim.i_flag    = 0;
			dim.eq_flag   = 0;
		}

		constexpr int degree() const { return dim.degree(); }
		constexpr int unit_count() const { return dim.unit_count(); }
	};
	#pragma pack(pop)
}

static_assert(sizeof(Units::Unit) == 12, "Invalid size of Unit");
