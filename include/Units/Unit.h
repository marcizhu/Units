#pragma once

#include <stdexcept>
#include <functional> // for std::hash

namespace Units
{
	class Unit
	{
	private:
		signed int meter_ : 4;
		signed int kilogram_ : 3;
		signed int second_ : 4;
		signed int ampere_ : 3;
		signed int kelvin_ : 4;
		signed int mole_ : 2;
		signed int radians_ : 3;
		signed int candela_ : 2;
		signed int currency_ : 2;
		signed int count_ : 2;
		bool e_flag : 1;
		bool i_flag : 1;
		bool eq_flag : 1;

		constexpr void check_unit(const Unit& other) const { if(*this != other) throw std::logic_error("Incompatible units!"); }

		constexpr bool isHz() const
		{
			return meter_    == 0
				&& kilogram_ == 0
				&& second_   <  0
				&& ampere_   == 0
				&& kelvin_   == 0
				&& radians_  == 0
				&& mole_     == 0
				&& candela_  == 0
				&& currency_ == 0
				&& count_    == 0
				&& e_flag    == 0
				&& i_flag    == 0
				&& eq_flag   == 0;
		}

		constexpr bool isRootHz() const
		{
			return meter_    == 0
				&& kilogram_ == 0
				&& second_   == -1
				&& ampere_   == 0
				&& kelvin_   == 0
				&& radians_  == 0
				&& mole_     == 0
				&& candela_  == 0
				&& currency_ == 0
				&& count_    == 0
				&& e_flag    == 0
				&& i_flag    == 1
				&& eq_flag   == 0;
		}

		constexpr bool hasValidRoot(int power) const
		{
			return meter_    % power == 0
				&& kilogram_ % power == 0
				&& second_   % power == 0
				&& ampere_   % power == 0
				&& kelvin_   % power == 0
				&& radians_  % power == 0
				&& mole_             == 0
				&& candela_          == 0
				&& currency_         == 0
				&& count_            == 0
				&& e_flag            == 0
				&& eq_flag           == 0;
		}

	public:
		constexpr explicit Unit() : meter_(0), kilogram_(0), second_(0), ampere_(0), kelvin_(0), mole_(0), radians_(0), candela_(0), currency_(0), count_(0), e_flag(0), i_flag(0), eq_flag(0) {}
		constexpr explicit Unit(std::nullptr_t) : meter_(0), kilogram_(0), second_(0), ampere_(0), kelvin_(0), mole_(0), radians_(0), candela_(0), currency_(0), count_(0), e_flag(1), i_flag(0), eq_flag(0) {}

		constexpr Unit(int8_t _1, int8_t _2, int8_t _3, int8_t _4, int8_t _5, int8_t _6, int8_t _7, int8_t _8, int8_t _9, int8_t _10, bool iflag = false, bool eqflag = false)
			: meter_(_1), kilogram_(_2), second_(_3), ampere_(_4), kelvin_(_5), mole_(_6), radians_(_7), candela_(_8), currency_(_9), count_(_10), e_flag(0), i_flag(iflag), eq_flag(eqflag) {}

		// Get the meter power
		constexpr int meter() const { return meter_; }
		// Get the kilogram power
		constexpr int kg() const { return kilogram_; }
		// Get the second power
		constexpr int second() const { return second_; }
		// Get the ampere power
		constexpr int ampere() const { return ampere_; }
		// Get the Kelvin power
		constexpr int kelvin() const { return kelvin_; }
		// Get the radian power
		constexpr int radian() const { return radians_; }
		// Get the mole power
		constexpr int mole() const { return mole_; }
		// Get the candela power
		constexpr int candela() const { return candela_; }
		// Get the currency power
		constexpr int currency() const { return currency_; }
		// Get the count power
		constexpr int count() const { return count_; }
		// Imaginary flag
		constexpr bool iflag() const { return i_flag; }
		// Error flag
		constexpr bool eflag() const { return e_flag; }

		constexpr Unit operator^(int8_t exp) const
		{
			Unit ret(*this);
			ret.meter_    *= exp;
			ret.kilogram_ *= exp;
			ret.second_   *= (ret.isRootHz() ? (exp / 2) : exp);
			ret.ampere_   *= exp;
			ret.kelvin_   *= exp;
			ret.mole_     *= exp;
			ret.radians_  *= exp;
			ret.candela_  *= exp;
			ret.currency_ *= exp;
			ret.count_    *= exp;
			ret.i_flag    *= ((exp % 2 == 0) ? 0u : 1u);
			ret.e_flag     = 0;
			return ret;
		}

		constexpr Unit operator+(const Unit& rhs) const { check_unit(rhs); return *this; }
		constexpr Unit operator-(const Unit& rhs) const { check_unit(rhs); return *this; }

		constexpr Unit operator*(const Unit& rhs) const
		{
			Unit ret(*this);
			ret.meter_    += rhs.meter_;
			ret.kilogram_ += rhs.kilogram_;
			ret.second_   += (ret.isRootHz() && rhs.isRootHz() ? 0 : rhs.second_);
			ret.ampere_   += rhs.ampere_;
			ret.kelvin_   += rhs.kelvin_;
			ret.mole_     += rhs.mole_;
			ret.radians_  += rhs.radians_;
			ret.candela_  += rhs.candela_;
			ret.currency_ += rhs.currency_;
			ret.count_    += rhs.count_;
			ret.i_flag    ^= rhs.i_flag;
			ret.e_flag    |= rhs.e_flag;
			ret.eq_flag   |= rhs.eq_flag;
			return ret;
		}

		constexpr Unit operator/(const Unit& rhs) const
		{
			Unit ret(*this);
			ret.meter_    -= rhs.meter_;
			ret.kilogram_ -= rhs.kilogram_;
			ret.second_   -= (ret.isHz() && rhs.isRootHz() ? 0 : rhs.second_);
			ret.ampere_   -= rhs.ampere_;
			ret.kelvin_   -= rhs.kelvin_;
			ret.mole_     -= rhs.mole_;
			ret.radians_  -= rhs.radians_;
			ret.candela_  -= rhs.candela_;
			ret.i_flag    ^= rhs.i_flag;
			ret.e_flag    |= rhs.e_flag;
			ret.eq_flag   |= rhs.eq_flag;
			return ret;
		}

		constexpr Unit& operator^=(int8_t exp)    { *this = *this ^ exp; return *this; }
		constexpr Unit& operator+=(Unit rhs) { *this = *this + rhs; return *this; }
		constexpr Unit& operator-=(Unit rhs) { *this = *this - rhs; return *this; }
		constexpr Unit& operator*=(Unit rhs) { *this = *this * rhs; return *this; }
		constexpr Unit& operator/=(Unit rhs) { *this = *this / rhs; return *this; }

		constexpr bool operator!=(Unit other) const { return !(*this == other); }
		constexpr bool operator==(Unit other) const
		{
			return meter_    == other.meter_
				&& kilogram_ == other.kilogram_
				&& second_   == other.second_
				&& ampere_   == other.ampere_
				&& kelvin_   == other.kelvin_
				&& mole_     == other.mole_
				&& radians_  == other.radians_
				&& candela_  == other.candela_
				&& currency_ == other.currency_
				&& count_    == other.count_
				&& e_flag    == other.e_flag
				&& i_flag    == other.i_flag
				&& eq_flag   == other.eq_flag;
		}

		constexpr void root(int power)
		{
			if(!hasValidRoot(power))
			{
				// Test for root 2 of Hz
				if(isHz())
				{
					i_flag = 1;
					return;
				}

				*this = Unit(nullptr);
				return;
			}

			meter_    /= power;
			kilogram_ /= power;
			second_   /= power;
			ampere_   /= power;
			kelvin_   /= power;
			radians_  /= power;
			i_flag = 0;
			eq_flag = 0;
		}
	};
}

static_assert(sizeof(Units::Unit) == 4, "Invalid size of Unit");

namespace std
{
	template<>
	struct hash<Units::Unit>
	{
		size_t operator()(Units::Unit x) const noexcept
		{
			return hash<uint32_t>()(*reinterpret_cast<const uint32_t*>(&x));
		}
	};

	inline Units::Unit sqrt(Units::Unit x) noexcept { x.root(2); return x; }
	inline Units::Unit cbrt(Units::Unit x) noexcept { x.root(3); return x; }
	inline Units::Unit pow (Units::Unit x, int8_t exp) noexcept { return x^exp; }
}
