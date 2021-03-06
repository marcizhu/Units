#include "Units/UnitData.h"

namespace Units
{
	bool UnitData::isRootHz() const
	{
		return *this == UnitData(0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
	}

	bool UnitData::isHz() const
	{
		return m_Data.meter    == 0
			&& m_Data.kilogram == 0
			&& m_Data.second   <  0
			&& m_Data.ampere   == 0
			&& m_Data.kelvin   == 0
			&& m_Data.radians  == 0
			&& m_Data.mole     == 0
			&& m_Data.candela  == 0
			&& m_Data.currency == 0
			&& m_Data.count    == 0
			&& m_Data.e_flag   == 0
			&& m_Data.i_flag   == 0
			&& m_Data.eq_flag  == 0;
	}

	bool UnitData::hasValidRoot(int power) const
	{
		return m_Data.meter    % power == 0
			&& m_Data.kilogram % power == 0
			&& m_Data.second   % power == 0
			&& m_Data.ampere   % power == 0
			&& m_Data.kelvin   % power == 0
			&& m_Data.radians  % power == 0
			&& m_Data.mole             == 0
			&& m_Data.candela          == 0
			&& m_Data.currency         == 0
			&& m_Data.count            == 0
			&& m_Data.e_flag           == 0
			&& m_Data.eq_flag          == 0;
	}

	UnitData::BaseUnitType UnitData::base_unit() const
	{
		return static_cast<BaseUnitType>(
			  ((m_Data.meter    & 0x0F) << 28)
			| ((m_Data.kilogram & 0x07) << 25)
			| ((m_Data.second   & 0x0F) << 21)
			| ((m_Data.ampere   & 0x07) << 18)
			| ((m_Data.kelvin   & 0x0F) << 14)
			| ((m_Data.mole     & 0x03) << 12)
			| ((m_Data.radians  & 0x07) <<  9)
			| ((m_Data.candela  & 0x03) <<  7)
			| ((m_Data.currency & 0x03) <<  5)
			| ((m_Data.count    & 0x03) <<  3)
			| ((m_Data.e_flag   & 0x01) <<  2)
			| ((m_Data.i_flag   & 0x01) <<  1)
			| ((m_Data.eq_flag  & 0x01) <<  0));
	}

	bool UnitData::operator==(const UnitData& other) const
	{
		return
			(m_Data.e_flag  == true && other.m_Data.e_flag == true)
			|| ((m_Data.meter    == other.m_Data.meter   )
				&& (m_Data.kilogram == other.m_Data.kilogram)
				&& (m_Data.candela  == other.m_Data.candela )
				&& (m_Data.mole     == other.m_Data.mole    )
				&& (m_Data.currency == other.m_Data.currency)
				&& (m_Data.second   == other.m_Data.second  )
				&& (m_Data.ampere   == other.m_Data.ampere  )
				&& (m_Data.kelvin   == other.m_Data.kelvin  )
				&& (m_Data.radians  == other.m_Data.radians )
				&& (m_Data.count    == other.m_Data.count   ));
	}

	bool UnitData::operator!=(const UnitData& other) const
	{
		return !(*this == other);
	}

	int UnitData::unit_count() const
	{
		 return
		 	(m_Data.meter    != 0) + (m_Data.second  != 0) +
			(m_Data.kilogram != 0) + (m_Data.ampere  != 0) +
			(m_Data.candela  != 0) + (m_Data.kelvin  != 0) +
			(m_Data.mole     != 0) + (m_Data.radians != 0) +
			(m_Data.currency != 0) + (m_Data.count   != 0);
	}

	int UnitData::degree() const
	{
		return
			m_Data.meter + m_Data.kilogram + m_Data.second + m_Data.ampere + m_Data.kelvin +
			m_Data.mole + m_Data.radians + m_Data.candela + m_Data.currency + m_Data.count;
	}

	UnitData UnitData::operator^(int exp) const
	{
		UnitData ret(*this);
		ret.m_Data.meter    *= exp;
		ret.m_Data.kilogram *= exp;
		ret.m_Data.second   *= (ret.isRootHz() ? (exp / 2) : exp);
		ret.m_Data.ampere   *= exp;
		ret.m_Data.kelvin   *= exp;
		ret.m_Data.mole     *= exp;
		ret.m_Data.radians  *= exp;
		ret.m_Data.candela  *= exp;
		ret.m_Data.currency *= exp;
		ret.m_Data.count    *= exp;
		ret.m_Data.i_flag   &= ((exp % 2 == 0) ? 0u : 1u);
		return ret;
	}

	UnitData UnitData::operator*(const UnitData& rhs) const
	{
		UnitData ret(*this);
		ret.m_Data.meter    += rhs.m_Data.meter;
		ret.m_Data.kilogram += rhs.m_Data.kilogram;
		ret.m_Data.second   += (ret.isRootHz() && rhs.isRootHz() ? 0 : rhs.m_Data.second);
		ret.m_Data.ampere   += rhs.m_Data.ampere;
		ret.m_Data.kelvin   += rhs.m_Data.kelvin;
		ret.m_Data.mole     += rhs.m_Data.mole;
		ret.m_Data.radians  += rhs.m_Data.radians;
		ret.m_Data.candela  += rhs.m_Data.candela;
		ret.m_Data.currency += rhs.m_Data.currency;
		ret.m_Data.count    += rhs.m_Data.count;
		ret.m_Data.i_flag   ^= rhs.m_Data.i_flag;
		ret.m_Data.e_flag   |= rhs.m_Data.e_flag;
		ret.m_Data.eq_flag  |= rhs.m_Data.eq_flag;
		return ret;
	}

	UnitData UnitData::operator/(const UnitData& rhs) const
	{
		UnitData ret(*this);
		ret.m_Data.meter    -= rhs.m_Data.meter;
		ret.m_Data.kilogram -= rhs.m_Data.kilogram;
		ret.m_Data.second   -= (ret.isHz() && rhs.isRootHz() ? 0 : rhs.m_Data.second);
		ret.m_Data.ampere   -= rhs.m_Data.ampere;
		ret.m_Data.kelvin   -= rhs.m_Data.kelvin;
		ret.m_Data.mole     -= rhs.m_Data.mole;
		ret.m_Data.radians  -= rhs.m_Data.radians;
		ret.m_Data.candela  -= rhs.m_Data.candela;
		ret.m_Data.currency -= rhs.m_Data.currency;
		ret.m_Data.count    -= rhs.m_Data.count;
		ret.m_Data.i_flag   ^= rhs.m_Data.i_flag;
		ret.m_Data.e_flag   |= rhs.m_Data.e_flag;
		ret.m_Data.eq_flag  ^= rhs.m_Data.eq_flag;
		return ret;
	}

	void UnitData::pow(int power)
	{
		*this = *this ^ power;
	}

	void UnitData::root(int power)
	{
		if(!hasValidRoot(power))
		{
			// Test for root 2 of Hz
			if(isHz())
			{
				m_Data.i_flag = 1;
				return;
			}

			*this = UnitData::error();
			return;
		}

		m_Data.meter    /= power;
		m_Data.kilogram /= power;
		m_Data.second   /= power;
		m_Data.ampere   /= power;
		m_Data.kelvin   /= power;
		m_Data.radians  /= power;
		m_Data.i_flag    = 0;
		m_Data.eq_flag   = 0;
	}
}
