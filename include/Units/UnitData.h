#pragma once

#include <cstdint>

#include "gcem.hpp"

namespace Units
{
	#pragma pack(push)
	#pragma pack(1)
	class UnitData
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

		constexpr bool isRootHz() const { return *this == UnitData(0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); }

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

		constexpr UnitData(int8_t _1, int8_t _2, int8_t _3, int8_t _4, int8_t _5, int8_t _6, int8_t _7, int8_t _8, int8_t _9, int8_t _10, bool eflag, bool iflag, bool eqflag)
			: meter_(_1), kilogram_(_2), second_(_3), ampere_(_4), kelvin_(_5), mole_(_6), radians_(_7), candela_(_8), currency_(_9), count_(_10), e_flag(eflag), i_flag(iflag), eq_flag(eqflag) {}

	public:
		constexpr UnitData()
			: meter_(0), kilogram_(0), second_(0), ampere_(0), kelvin_(0), mole_(0), radians_(0), candela_(0), currency_(0), count_(0), e_flag(0), i_flag(0), eq_flag(0) {}

		static constexpr UnitData eq(uint8_t num)
		{
			if(num > 0b0001'1111) return UnitData::error();

			UnitData ret;
			ret.count_   = (num & 0b0000'0011) >> 0;
			ret.radians_ = (num & 0b0001'1100) >> 2;
			ret.eq_flag  = true;
			return ret;
		}

		static constexpr UnitData meter   () { return UnitData(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		static constexpr UnitData kilogram() { return UnitData(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		static constexpr UnitData second  () { return UnitData(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		static constexpr UnitData ampere  () { return UnitData(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		static constexpr UnitData kelvin  () { return UnitData(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); }
		static constexpr UnitData mole    () { return UnitData(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); }
		static constexpr UnitData radians () { return UnitData(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0); }
		static constexpr UnitData candela () { return UnitData(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0); }
		static constexpr UnitData currency() { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); }
		static constexpr UnitData count   () { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); }
		static constexpr UnitData error   () { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0); }
		static constexpr UnitData iflag   () { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); }

		using BaseUnitType = uint32_t;

		constexpr BaseUnitType base_unit() const
		{
			return static_cast<BaseUnitType>(
				((meter_    & 0x0F) << 28) |
				((kilogram_ & 0x07) << 25) |
				((second_   & 0x0F) << 21) |
				((ampere_   & 0x07) << 18) |
				((kelvin_   & 0x0F) << 14) |
				((mole_     & 0x03) << 12) |
				((radians_  & 0x07) <<  9) |
				((candela_  & 0x03) <<  7) |
				((currency_ & 0x03) <<  5) |
				((count_    & 0x03) <<  3) |
				(( e_flag   & 0x01) <<  2) |
				(( i_flag   & 0x01) <<  1) |
				((eq_flag   & 0x01) <<  0));
		}

		constexpr bool operator!=(const UnitData& other) const { return !(*this == other); }
		constexpr bool operator==(const UnitData& other) const
		{
			return (meter_   == other.meter_
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
				&& eq_flag   == other.eq_flag)
				|| (e_flag   == true && other.e_flag == true);
		}

		constexpr int unit_count() const
		{
			 return
			 	((meter_    != 0) ? 1 : 0) + ((second_  != 0) ? 1 : 0) +
				((kilogram_ != 0) ? 1 : 0) + ((ampere_  != 0) ? 1 : 0) +
				((candela_  != 0) ? 1 : 0) + ((kelvin_  != 0) ? 1 : 0) +
				((mole_     != 0) ? 1 : 0) + ((radians_ != 0) ? 1 : 0) +
				((currency_ != 0) ? 1 : 0) + ((count_   != 0) ? 1 : 0);
		}

		constexpr int degree() const
		{
			return
				meter_ + kilogram_ + second_ + ampere_ + kelvin_ +
				mole_ + radians_ + candela_ + currency_ + count_;
		}

		constexpr UnitData operator^(int exp) const
		{
			UnitData ret(*this);
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
			return ret;
		}

		constexpr UnitData operator*(const UnitData& rhs) const
		{
			UnitData ret(*this);
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

		constexpr UnitData operator/(const UnitData& rhs) const
		{
			UnitData ret(*this);
			ret.meter_    -= rhs.meter_;
			ret.kilogram_ -= rhs.kilogram_;
			ret.second_   -= (ret.isHz() && rhs.isRootHz() ? 0 : rhs.second_);
			ret.ampere_   -= rhs.ampere_;
			ret.kelvin_   -= rhs.kelvin_;
			ret.mole_     -= rhs.mole_;
			ret.radians_  -= rhs.radians_;
			ret.candela_  -= rhs.candela_;
			ret.currency_ -= rhs.currency_;
			ret.count_    -= rhs.count_;
			ret.i_flag    ^= rhs.i_flag;
			ret.e_flag    |= rhs.e_flag;
			ret.eq_flag   ^= rhs.eq_flag;
			return ret;
		}

		constexpr void pow (int power) { *this = *this ^ power; }
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

				*this = UnitData::error();
				return;
			}

			meter_    /= power;
			kilogram_ /= power;
			second_   /= power;
			ampere_   /= power;
			kelvin_   /= power;
			radians_  /= power;
			i_flag     = 0;
			eq_flag    = 0;
		}
	};
	#pragma pack(pop)
}
