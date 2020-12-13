#pragma once

#include <cstdint>
#include <limits>

#include "Unit.h"
#include "gcem.hpp"

namespace Units
{
	class Quantity
	{
	private:
		double m_Magnitude;
		Unit m_Unit;

		static constexpr double max_precision = gcem::pow(10.0, std::numeric_limits<double>::digits10);
		static constexpr double cround(double val) { return gcem::round(val * max_precision) / max_precision; }

		static constexpr Quantity convert(const Quantity& start, const Unit& result)
		{
			if(start.m_Unit.base_units() != result.base_units()) return Quantity(std::numeric_limits<double>::quiet_NaN(), Unit::error());

			return Quantity(start.m_Magnitude * ((double)start.m_Unit.multiplier() / (double)result.multiplier()), result);
		}

	public:
		constexpr Quantity(Unit u = Unit())             : m_Magnitude(1.0), m_Unit(u) {}
		constexpr Quantity(double mag, Unit u = Unit()) : m_Magnitude(mag), m_Unit(u) {}

		constexpr double magnitude() const { return m_Magnitude; }
		constexpr Unit unit() const { return m_Unit; }

		explicit operator double() const { return m_Magnitude; }
		explicit operator Unit() const { return m_Unit; }

		constexpr Quantity operator+() const { return Quantity(+m_Magnitude, m_Unit); }
		constexpr Quantity operator-() const { return Quantity(-m_Magnitude, m_Unit); }

		constexpr Quantity operator^(const int       exp) const { return Quantity(gcem::pow(m_Magnitude, static_cast<double>(exp)), m_Unit ^ exp); }
		constexpr Quantity operator+(const Quantity& rhs) const { return Quantity(m_Magnitude + rhs.m_Magnitude, m_Unit + rhs.m_Unit); }
		constexpr Quantity operator-(const Quantity& rhs) const { return Quantity(m_Magnitude - rhs.m_Magnitude, m_Unit - rhs.m_Unit); }
		constexpr Quantity operator*(const Quantity& rhs) const { return Quantity(m_Magnitude * rhs.m_Magnitude, m_Unit * rhs.m_Unit); }
		constexpr Quantity operator/(const Quantity& rhs) const { return Quantity(m_Magnitude / rhs.m_Magnitude, m_Unit / rhs.m_Unit); }

		constexpr Quantity& operator^=(const int       exp) { return *this = *this ^ exp; }
		constexpr Quantity& operator+=(const Quantity& rhs) { return *this = *this + rhs; }
		constexpr Quantity& operator-=(const Quantity& rhs) { return *this = *this - rhs; }
		constexpr Quantity& operator*=(const Quantity& rhs) { return *this = *this * rhs; }
		constexpr Quantity& operator/=(const Quantity& rhs) { return *this = *this / rhs; }

		constexpr bool operator> (const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) >  cround(other.m_Magnitude) : cround(m_Magnitude)  > cround(convert(other, m_Unit).m_Magnitude)); }
		constexpr bool operator< (const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) <  cround(other.m_Magnitude) : cround(m_Magnitude)  < cround(convert(other, m_Unit).m_Magnitude)); }
		constexpr bool operator>=(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) >= cround(other.m_Magnitude) : cround(m_Magnitude) >= cround(convert(other, m_Unit).m_Magnitude)); }
		constexpr bool operator<=(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) <= cround(other.m_Magnitude) : cround(m_Magnitude) <= cround(convert(other, m_Unit).m_Magnitude)); }
		constexpr bool operator==(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) == cround(other.m_Magnitude) : cround(m_Magnitude) == cround(convert(other, m_Unit).m_Magnitude)); }
		constexpr bool operator!=(const Quantity& other) const { return (m_Unit == other.m_Unit ? cround(m_Magnitude) != cround(other.m_Magnitude) : cround(m_Magnitude) != cround(convert(other, m_Unit).m_Magnitude)); }

		constexpr void root(int power) { m_Magnitude = gcem::pow(m_Magnitude, 1.0 / static_cast<double>(power)); m_Unit.root(power); }
		constexpr void pow (int power) { m_Magnitude = gcem::pow(m_Magnitude,       static_cast<double>(power)); m_Unit.pow (power); }
	};

	constexpr Quantity operator+(double lhs, const Quantity& rhs) { return Quantity(lhs) + rhs; }
	constexpr Quantity operator-(double lhs, const Quantity& rhs) { return Quantity(lhs) - rhs; }
	constexpr Quantity operator*(double lhs, const Quantity& rhs) { return Quantity(lhs) * rhs; }
	constexpr Quantity operator/(double lhs, const Quantity& rhs) { return Quantity(lhs) / rhs; }

	constexpr Quantity operator*(const Unit& lhs, double rhs) { return Quantity(lhs) * Quantity(rhs); }
	constexpr Quantity operator/(const Unit& lhs, double rhs) { return Quantity(lhs) / Quantity(rhs); }

	template<typename T>
	using IsDoubleConvertible = typename std::enable_if<std::is_convertible<T, double>::value>::type;

	template<typename T, IsDoubleConvertible<T>> constexpr bool operator> (const Quantity& lhs, const T& rhs) { return lhs >  Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> constexpr bool operator< (const Quantity& lhs, const T& rhs) { return lhs <  Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> constexpr bool operator>=(const Quantity& lhs, const T& rhs) { return lhs >= Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> constexpr bool operator<=(const Quantity& lhs, const T& rhs) { return lhs <= Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> constexpr bool operator==(const Quantity& lhs, const T& rhs) { return lhs == Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> constexpr bool operator!=(const Quantity& lhs, const T& rhs) { return lhs != Quantity(rhs); }

	template<typename T> constexpr bool operator> (const T& lhs, const Quantity& rhs) { return Quantity(lhs) >  rhs; }
	template<typename T> constexpr bool operator< (const T& lhs, const Quantity& rhs) { return Quantity(lhs) <  rhs; }
	template<typename T> constexpr bool operator>=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) >= rhs; }
	template<typename T> constexpr bool operator<=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) <= rhs; }
	template<typename T> constexpr bool operator==(const T& lhs, const Quantity& rhs) { return Quantity(lhs) == rhs; }
	template<typename T> constexpr bool operator!=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) != rhs; }
}
