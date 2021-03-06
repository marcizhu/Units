#include <cmath>
#include "Units/Quantity.h"

namespace Units
{
	double Quantity::cround(double val)
	{
		static const double max_precision = std::pow(10.0, std::numeric_limits<double>::digits10);
		return std::round(val * max_precision) / max_precision;
	}

	Quantity Quantity::convert(const Quantity& start, const Unit& result)
	{
		if(start.m_Unit.base_units() != result.base_units()) return Quantity(std::numeric_limits<double>::quiet_NaN(), Unit::error());

		return Quantity(start.m_Magnitude * ((double)start.m_Unit.multiplier() / (double)result.multiplier()), result);
	}

	Quantity Quantity::operator+() const { return Quantity(+m_Magnitude, m_Unit); }
	Quantity Quantity::operator-() const { return Quantity(-m_Magnitude, m_Unit); }

	Quantity Quantity::operator^(const int       exp) const { return Quantity(std::pow(m_Magnitude, static_cast<double>(exp)), m_Unit ^ exp); }
	Quantity Quantity::operator+(const Quantity& rhs) const { return Quantity(m_Magnitude + rhs.m_Magnitude, m_Unit + rhs.m_Unit); }
	Quantity Quantity::operator-(const Quantity& rhs) const { return Quantity(m_Magnitude - rhs.m_Magnitude, m_Unit - rhs.m_Unit); }
	Quantity Quantity::operator*(const Quantity& rhs) const { return Quantity(m_Magnitude * rhs.m_Magnitude, m_Unit * rhs.m_Unit); }
	Quantity Quantity::operator/(const Quantity& rhs) const { return Quantity(m_Magnitude / rhs.m_Magnitude, m_Unit / rhs.m_Unit); }

	Quantity& Quantity::operator^=(const int       exp) { return *this = *this ^ exp; }
	Quantity& Quantity::operator+=(const Quantity& rhs) { return *this = *this + rhs; }
	Quantity& Quantity::operator-=(const Quantity& rhs) { return *this = *this - rhs; }
	Quantity& Quantity::operator*=(const Quantity& rhs) { return *this = *this * rhs; }
	Quantity& Quantity::operator/=(const Quantity& rhs) { return *this = *this / rhs; }

	bool Quantity::operator> (const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) >  cround(other.m_Magnitude) : cround(m_Magnitude)  > cround(convert(other, m_Unit).m_Magnitude)); }
	bool Quantity::operator< (const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) <  cround(other.m_Magnitude) : cround(m_Magnitude)  < cround(convert(other, m_Unit).m_Magnitude)); }
	bool Quantity::operator>=(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) >= cround(other.m_Magnitude) : cround(m_Magnitude) >= cround(convert(other, m_Unit).m_Magnitude)); }
	bool Quantity::operator<=(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) <= cround(other.m_Magnitude) : cround(m_Magnitude) <= cround(convert(other, m_Unit).m_Magnitude)); }
	bool Quantity::operator==(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) == cround(other.m_Magnitude) : cround(m_Magnitude) == cround(convert(other, m_Unit).m_Magnitude)); }
	bool Quantity::operator!=(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) != cround(other.m_Magnitude) : cround(m_Magnitude) != cround(convert(other, m_Unit).m_Magnitude)); }

	void Quantity::root(int power) { m_Magnitude = std::pow(m_Magnitude, 1.0 / static_cast<double>(power)); m_Unit.root(power); }
	void Quantity::pow (int power) { m_Magnitude = std::pow(m_Magnitude,       static_cast<double>(power)); m_Unit.pow (power); }

	Quantity operator+(double lhs, const Quantity& rhs) { return Quantity(lhs) + rhs; }
	Quantity operator-(double lhs, const Quantity& rhs) { return Quantity(lhs) - rhs; }
	Quantity operator*(double lhs, const Quantity& rhs) { return Quantity(lhs) * rhs; }
	Quantity operator/(double lhs, const Quantity& rhs) { return Quantity(lhs) / rhs; }

	Quantity operator*(const Unit& lhs, double rhs) { return Quantity(lhs) * Quantity(rhs); }
	Quantity operator/(const Unit& lhs, double rhs) { return Quantity(lhs) / Quantity(rhs); }
}
