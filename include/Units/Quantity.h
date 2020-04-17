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
		double magnitude;
		Unit unit;

		static constexpr double max_precision = gcem::pow(10.0, std::numeric_limits<double>::digits10);
		static constexpr double cround(double val) { return gcem::round(val * max_precision) / max_precision; }

		static constexpr Quantity convert(const Quantity& start, const Unit& result)
		{
			if(start.getUnit().base_units() != result.base_units()) return Quantity(std::numeric_limits<double>::quiet_NaN(), Unit::error());

			return Quantity(start.getMagnitude() * ((double)start.getUnit().unit_multiplier() / (double)result.unit_multiplier()), result);
		}

	public:
		constexpr Quantity(Unit u = Unit())             : magnitude(1.0), unit(u) {}
		constexpr Quantity(double mag, Unit u = Unit()) : magnitude(mag), unit(u) {}

		constexpr double getMagnitude() const { return magnitude; }
		constexpr Unit getUnit() const { return unit; }

		explicit operator double() const { return magnitude; }
		explicit operator Unit() const { return unit; }

		constexpr Quantity operator+() const { return Quantity(+magnitude, unit); }
		constexpr Quantity operator-() const { return Quantity(-magnitude, unit); }

		constexpr Quantity operator^(int exp) const { return Quantity(gcem::pow(magnitude, static_cast<double>(exp)), unit ^ exp); }
		constexpr Quantity operator+(const Quantity& rhs) const { return Quantity(magnitude + rhs.magnitude, unit + rhs.unit); }
		constexpr Quantity operator-(const Quantity& rhs) const { return Quantity(magnitude - rhs.magnitude, unit - rhs.unit); }
		constexpr Quantity operator*(const Quantity& rhs) const { return Quantity(magnitude * rhs.magnitude, unit * rhs.unit); }
		constexpr Quantity operator/(const Quantity& rhs) const { return Quantity(magnitude / rhs.magnitude, unit / rhs.unit); }

		constexpr Quantity& operator^=(int exp)             { return *this = *this ^ exp; }
		constexpr Quantity& operator+=(const Quantity& rhs) { return *this = *this + rhs; }
		constexpr Quantity& operator-=(const Quantity& rhs) { return *this = *this - rhs; }
		constexpr Quantity& operator*=(const Quantity& rhs) { return *this = *this * rhs; }
		constexpr Quantity& operator/=(const Quantity& rhs) { return *this = *this / rhs; }

		constexpr bool operator> (const Quantity& other) const { return (unit == other.unit ? cround(magnitude) >  cround(other.magnitude) : cround(magnitude)  > cround(convert(other, unit).magnitude)); }
		constexpr bool operator< (const Quantity& other) const { return (unit == other.unit ? cround(magnitude) <  cround(other.magnitude) : cround(magnitude)  < cround(convert(other, unit).magnitude)); }
		constexpr bool operator>=(const Quantity& other) const { return (unit == other.unit ? cround(magnitude) >= cround(other.magnitude) : cround(magnitude) >= cround(convert(other, unit).magnitude)); }
		constexpr bool operator<=(const Quantity& other) const { return (unit == other.unit ? cround(magnitude) <= cround(other.magnitude) : cround(magnitude) <= cround(convert(other, unit).magnitude)); }
		constexpr bool operator==(const Quantity& other) const { return (unit == other.unit ? cround(magnitude) == cround(other.magnitude) : cround(magnitude) == cround(convert(other, unit).magnitude)); }
		constexpr bool operator!=(const Quantity& other) const { return (unit != other.unit ? cround(magnitude) != cround(other.magnitude) : cround(magnitude) != cround(convert(other, unit).magnitude)); }

		constexpr void root(int power) { magnitude = gcem::pow(magnitude, 1.0 / static_cast<double>(power)); unit.root(power); }
		constexpr void pow (int power) { magnitude = gcem::pow(magnitude,       static_cast<double>(power)); unit.pow (power); }
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
