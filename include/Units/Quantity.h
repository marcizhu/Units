#pragma once

#include <cmath>
#include <cstdint>
#include <stdexcept>

#include "Unit.h"
#include "sprout/cmath.hpp"

namespace Units
{
	class Quantity
	{
	private:
		double magnitude;
		Unit unit;

		static constexpr double cround(const double& val) { return sprout::round(val * 1.0e16) / 1.0e16; }

	public:
		constexpr Quantity(Unit u = Unit())             : magnitude(1.0), unit(u) {}
		constexpr Quantity(double mag, Unit u = Unit()) : magnitude(mag), unit(u) {}

		constexpr double getMagnitude() const { return cround(magnitude); }
		constexpr Unit getUnit() const { return unit; }

		// quan * quan
		constexpr Quantity operator^(int exp) const { return Quantity(sprout::pow(magnitude, (double)exp), unit ^ exp); }
		constexpr Quantity operator+(const Quantity& rhs) const { return Quantity(magnitude + rhs.magnitude, unit + rhs.unit); }
		constexpr Quantity operator-(const Quantity& rhs) const { return Quantity(magnitude - rhs.magnitude, unit - rhs.unit); }
		constexpr Quantity operator*(const Quantity& rhs) const { return Quantity(magnitude * rhs.magnitude, unit * rhs.unit); }
		constexpr Quantity operator/(const Quantity& rhs) const { return Quantity(magnitude / rhs.magnitude, unit / rhs.unit); }

		constexpr Quantity& operator^=(int exp)             { *this = *this ^ exp; return *this; }
		constexpr Quantity& operator+=(const Quantity& rhs) { *this = *this + rhs; return *this; }
		constexpr Quantity& operator-=(const Quantity& rhs) { *this = *this - rhs; return *this; }
		constexpr Quantity& operator*=(const Quantity& rhs) { *this = *this * rhs; return *this; }
		constexpr Quantity& operator/=(const Quantity& rhs) { *this = *this / rhs; return *this; }

		constexpr Quantity operator+() const { return Quantity(+magnitude, unit); }
		constexpr Quantity operator-() const { return Quantity(-magnitude, unit); }

		constexpr bool operator> (const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude >  other.magnitude; }
		constexpr bool operator< (const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude <  other.magnitude; }
		constexpr bool operator>=(const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude >= other.magnitude; }
		constexpr bool operator<=(const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude <= other.magnitude; }

		/** @brief Inequality comparison operator */
		constexpr bool operator!=(const Quantity& other) const { return unit != other.unit || cround(magnitude) != cround(other.magnitude); }
		/** @brief Equality comparison operator */
		constexpr bool operator==(const Quantity& other) const { return unit == other.unit && cround(magnitude) == cround(other.magnitude); }

		constexpr void root(int power) { magnitude = sprout::pow(magnitude, 1.0 / (double)power); unit.root(power); }
		constexpr void pow (int power) { magnitude = sprout::pow(magnitude,       (double)power); unit.pow (power); }
	};

	// real * quan
	constexpr Quantity operator+(double lhs, const Quantity& rhs) { return Quantity(lhs) + rhs; }
	constexpr Quantity operator-(double lhs, const Quantity& rhs) { return Quantity(lhs) - rhs; }
	constexpr Quantity operator*(double lhs, const Quantity& rhs) { return Quantity(lhs) * rhs; }
	constexpr Quantity operator/(double lhs, const Quantity& rhs) { return Quantity(lhs) / rhs; }

	// unit * real
	constexpr Quantity operator*(const Unit& lhs, double rhs) { return Quantity(lhs) * Quantity(rhs); }
	constexpr Quantity operator/(const Unit& lhs, double rhs) { return Quantity(lhs) / Quantity(rhs); }

	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator> (const Quantity& lhs, const T& rhs) { return lhs >  Quantity(rhs); }
	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator< (const Quantity& lhs, const T& rhs) { return lhs <  Quantity(rhs); }
	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator>=(const Quantity& lhs, const T& rhs) { return lhs >= Quantity(rhs); }
	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator<=(const Quantity& lhs, const T& rhs) { return lhs <= Quantity(rhs); }

	template<typename T> constexpr bool operator> (const T& lhs, const Quantity& rhs) { return Quantity(lhs) >  rhs; }
	template<typename T> constexpr bool operator< (const T& lhs, const Quantity& rhs) { return Quantity(lhs) <  rhs; }
	template<typename T> constexpr bool operator>=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) >= rhs; }
	template<typename T> constexpr bool operator<=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) <= rhs; }
}

static_assert(sizeof(Units::Quantity) == 16, "Invalid size of Quantity");
