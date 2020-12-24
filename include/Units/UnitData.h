#pragma once

#include <cstdint>

#include "gcem.hpp"

namespace Units
{
#if defined(__GNUC__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wconversion"
#endif

	#pragma pack(push)
	#pragma pack(1)
	class UnitData
	{
	private:
		signed int m_Meter : 4;
		signed int m_Kilogram : 3;
		signed int m_Second : 4;
		signed int m_Ampere : 3;
		signed int m_Kelvin : 4;
		signed int m_Mole : 2;
		signed int m_Radians : 3;
		signed int m_Candela : 2;
		signed int m_Currency : 2;
		signed int m_Count : 2;
		bool e_flag : 1;
		bool i_flag : 1;
		bool eq_flag : 1;

		constexpr bool isRootHz() const { return *this == UnitData(0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); }

		constexpr bool isHz() const
		{
			return m_Meter    == 0
				&& m_Kilogram == 0
				&& m_Second   <  0
				&& m_Ampere   == 0
				&& m_Kelvin   == 0
				&& m_Radians  == 0
				&& m_Mole     == 0
				&& m_Candela  == 0
				&& m_Currency == 0
				&& m_Count    == 0
				&& e_flag     == 0
				&& i_flag     == 0
				&& eq_flag    == 0;
		}

		constexpr bool hasValidRoot(int power) const
		{
			return m_Meter    % power == 0
				&& m_Kilogram % power == 0
				&& m_Second   % power == 0
				&& m_Ampere   % power == 0
				&& m_Kelvin   % power == 0
				&& m_Radians  % power == 0
				&& m_Mole             == 0
				&& m_Candela          == 0
				&& m_Currency         == 0
				&& m_Count            == 0
				&& e_flag             == 0
				&& eq_flag            == 0;
		}

		constexpr UnitData(int8_t m, int8_t kg, int8_t s, int8_t A, int8_t K, int8_t mol, int8_t rad, int8_t Cd, int8_t c, int8_t cnt, bool eflag, bool iflag, bool eqflag)
			: m_Meter(m), m_Kilogram(kg), m_Second(s), m_Ampere(A), m_Kelvin(K), m_Mole(mol), m_Radians(rad),
			m_Candela(Cd), m_Currency(c), m_Count(cnt), e_flag(eflag), i_flag(iflag), eq_flag(eqflag) {}

	public:
		constexpr UnitData()
			: m_Meter(0), m_Kilogram(0), m_Second(0), m_Ampere(0), m_Kelvin(0), m_Mole(0), m_Radians(0),
			m_Candela(0), m_Currency(0), m_Count(0), e_flag(0), i_flag(0), eq_flag(0) {}

		static constexpr UnitData eq(uint8_t num)
		{
			if(num > 0b0001'1111) return UnitData::error();

			UnitData ret;
			ret.m_Count   = (num & 0b0000'0011) >> 0;
			ret.m_Radians = (num & 0b0001'1100) >> 2;
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
			return
				static_cast<BaseUnitType>(
					  ((m_Meter    & 0x0F) << 28)
					| ((m_Kilogram & 0x07) << 25)
					| ((m_Second   & 0x0F) << 21)
					| ((m_Ampere   & 0x07) << 18)
					| ((m_Kelvin   & 0x0F) << 14)
					| ((m_Mole     & 0x03) << 12)
					| ((m_Radians  & 0x07) <<  9)
					| ((m_Candela  & 0x03) <<  7)
					| ((m_Currency & 0x03) <<  5)
					| ((m_Count    & 0x03) <<  3)
					| (( e_flag    & 0x01) <<  2)
					| (( i_flag    & 0x01) <<  1)
					| ((eq_flag    & 0x01) <<  0));
		}

		constexpr bool operator!=(const UnitData& other) const { return !(*this == other); }

		constexpr bool operator==(const UnitData& other) const
		{
			return base_unit() == other.base_unit() || (e_flag    == true && other.e_flag == true);
		}

		constexpr int unit_count() const
		{
			 return
			 	((m_Meter    != 0) ? 1 : 0) + ((m_Second  != 0) ? 1 : 0) +
				((m_Kilogram != 0) ? 1 : 0) + ((m_Ampere  != 0) ? 1 : 0) +
				((m_Candela  != 0) ? 1 : 0) + ((m_Kelvin  != 0) ? 1 : 0) +
				((m_Mole     != 0) ? 1 : 0) + ((m_Radians != 0) ? 1 : 0) +
				((m_Currency != 0) ? 1 : 0) + ((m_Count   != 0) ? 1 : 0);
		}

		constexpr int degree() const
		{
			return
				m_Meter + m_Kilogram + m_Second + m_Ampere + m_Kelvin +
				m_Mole + m_Radians + m_Candela + m_Currency + m_Count;
		}

		constexpr UnitData operator^(int exp) const
		{
			UnitData ret(*this);
			ret.m_Meter    *= exp;
			ret.m_Kilogram *= exp;
			ret.m_Second   *= (ret.isRootHz() ? (exp / 2) : exp);
			ret.m_Ampere   *= exp;
			ret.m_Kelvin   *= exp;
			ret.m_Mole     *= exp;
			ret.m_Radians  *= exp;
			ret.m_Candela  *= exp;
			ret.m_Currency *= exp;
			ret.m_Count    *= exp;
			ret.i_flag     &= ((exp % 2 == 0) ? 0u : 1u);
			return ret;
		}

		constexpr UnitData operator*(const UnitData& rhs) const
		{
			UnitData ret(*this);
			ret.m_Meter    += rhs.m_Meter;
			ret.m_Kilogram += rhs.m_Kilogram;
			ret.m_Second   += (ret.isRootHz() && rhs.isRootHz() ? 0 : rhs.m_Second);
			ret.m_Ampere   += rhs.m_Ampere;
			ret.m_Kelvin   += rhs.m_Kelvin;
			ret.m_Mole     += rhs.m_Mole;
			ret.m_Radians  += rhs.m_Radians;
			ret.m_Candela  += rhs.m_Candela;
			ret.m_Currency += rhs.m_Currency;
			ret.m_Count    += rhs.m_Count;
			ret.i_flag     ^= rhs.i_flag;
			ret.e_flag     |= rhs.e_flag;
			ret.eq_flag    |= rhs.eq_flag;
			return ret;
		}

		constexpr UnitData operator/(const UnitData& rhs) const
		{
			UnitData ret(*this);
			ret.m_Meter    -= rhs.m_Meter;
			ret.m_Kilogram -= rhs.m_Kilogram;
			ret.m_Second   -= (ret.isHz() && rhs.isRootHz() ? 0 : rhs.m_Second);
			ret.m_Ampere   -= rhs.m_Ampere;
			ret.m_Kelvin   -= rhs.m_Kelvin;
			ret.m_Mole     -= rhs.m_Mole;
			ret.m_Radians  -= rhs.m_Radians;
			ret.m_Candela  -= rhs.m_Candela;
			ret.m_Currency -= rhs.m_Currency;
			ret.m_Count    -= rhs.m_Count;
			ret.i_flag     ^= rhs.i_flag;
			ret.e_flag     |= rhs.e_flag;
			ret.eq_flag    ^= rhs.eq_flag;
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

			m_Meter    /= power;
			m_Kilogram /= power;
			m_Second   /= power;
			m_Ampere   /= power;
			m_Kelvin   /= power;
			m_Radians  /= power;
			i_flag     = 0;
			eq_flag    = 0;
		}
	};
	#pragma pack(pop)

#if defined(__GNUC__)
	#pragma GCC diagnostic pop
#endif
}
