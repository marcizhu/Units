#include <cmath>
#include <limits>

#include "Units/Unit.h"

namespace Units
{
	float Unit::cround(float val)
	{
		static const float max_precision = (float)std::pow(10.0f, std::numeric_limits<float>::digits10);
		return std::round(val * max_precision) / max_precision;
	}

	UnitData::BaseUnitType Unit::base_units() const
	{
		return m_Data.base_unit();
	}

	float Unit::multiplier() const
	{
		return cround(m_Multiplier);
	}

	int Unit::degree() const
	{
		return m_Data.degree();
	}

	int Unit::unit_count() const
	{
		return m_Data.unit_count();
	}

	Unit Unit::operator^(const int exp) const
	{
		return Unit(std::pow(m_Multiplier, static_cast<float>(exp)), m_Data^exp);
	}

	Unit Unit::operator+(const Unit& rhs) const
	{
		return (*this == rhs ? *this : Unit::error());
	}

	Unit Unit::operator-(const Unit& rhs) const
	{
		return (*this == rhs ? *this : Unit::error());
	}

	Unit Unit::operator*(const Unit& rhs) const
	{
		return Unit(m_Multiplier * rhs.m_Multiplier, m_Data * rhs.m_Data);
	}

	Unit Unit::operator/(const Unit& rhs) const
	{
		return Unit(m_Multiplier / rhs.m_Multiplier, m_Data / rhs.m_Data);
	}

	Unit& Unit::operator^=(const int   exp) { return *this = *this ^ exp; }
	Unit& Unit::operator+=(const Unit& rhs) { return *this = *this + rhs; }
	Unit& Unit::operator-=(const Unit& rhs) { return *this = *this - rhs; }
	Unit& Unit::operator*=(const Unit& rhs) { return *this = *this * rhs; }
	Unit& Unit::operator/=(const Unit& rhs) { return *this = *this / rhs; }

	bool Unit::operator==(Unit other) const
	{
		if(m_Data == UnitData::error())
			return other.m_Data == UnitData::error();

		return m_Data == other.m_Data && cround(m_Multiplier) == cround(other.m_Multiplier);
	}

	bool Unit::operator!=(Unit other) const
	{
		return !(*this == other);
	}

	void Unit::root(int n)
	{
		m_Multiplier = std::pow(m_Multiplier, 1.0f / static_cast<float>(n));
		m_Data.root(n);
	}

	void Unit::pow(int n)
	{
		m_Multiplier = std::pow(m_Multiplier, static_cast<float>(n));
		m_Data.pow(n);
	}
}
