#pragma once

#include <cmath>
#include <cstdint>
#include <stdexcept>

#include "Unit.h"
#include "Math.h"

namespace Units
{
	class Quantity
	{
	private:
		double magnitude;
		float uncertainty;
		Unit unit;

		static constexpr float uncert_add(const Quantity& lhs, const Quantity& rhs)
		{
			float a = lhs.uncertainty;
			float b = rhs.uncertainty;

			return Math::sqrt(a * a + b * b);
		}

		static constexpr float uncert_prod(const Quantity& lhs, const Quantity& rhs)
		{
			float a = lhs.magnitude != 0.0 ? lhs.uncertainty / static_cast<float>(lhs.magnitude) : 0.0;
			float b = rhs.magnitude != 0.0 ? rhs.uncertainty / static_cast<float>(rhs.magnitude) : 0.0;

			return (float)Math::abs(lhs.magnitude * rhs.magnitude) * Math::sqrt(a * a + b * b);
		}

		static constexpr float uncert_div(const Quantity& lhs, const Quantity& rhs)
		{
			float a = lhs.magnitude != 0.0 ? lhs.uncertainty / static_cast<float>(lhs.magnitude) : 0.0;
			float b = rhs.magnitude != 0.0 ? rhs.uncertainty / static_cast<float>(rhs.magnitude) : 0.0;

			return (float)Math::abs(lhs.magnitude / rhs.magnitude) * Math::sqrt(a * a + b * b);
		}

	public:
		constexpr Quantity(Unit u = Unit())                             : magnitude(1.0), uncertainty(0.0f), unit(u) {}
		constexpr Quantity(double mag, Unit u = Unit(), float c = 0.0f) : magnitude(mag), uncertainty(c),    unit(u) {}

		constexpr double getMagnitude() const { return magnitude; }
		constexpr float getUncertainty() const { return uncertainty; }
		constexpr Unit getUnit() const { return unit; }

		constexpr void setUncertainty(float val) { uncertainty = val; }

		// quan * quan
		constexpr Quantity operator^(int8_t exp) const { return Quantity(Math::pow_n(magnitude, exp), unit ^ exp); }
		constexpr Quantity operator+(const Quantity& rhs) const { return Quantity(magnitude + rhs.magnitude, unit + rhs.unit, uncert_add (*this, rhs)); }
		constexpr Quantity operator-(const Quantity& rhs) const { return Quantity(magnitude - rhs.magnitude, unit - rhs.unit, uncert_add (*this, rhs)); }
		constexpr Quantity operator*(const Quantity& rhs) const { return Quantity(magnitude * rhs.magnitude, unit * rhs.unit, uncert_prod(*this, rhs)); }
		constexpr Quantity operator/(const Quantity& rhs) const { return Quantity(magnitude / rhs.magnitude, unit / rhs.unit, uncert_div (*this, rhs)); }

		constexpr Quantity& operator^=(int8_t exp)          { *this = *this ^ exp; return *this; }
		constexpr Quantity& operator+=(const Quantity& rhs) { *this = *this + rhs; return *this; }
		constexpr Quantity& operator-=(const Quantity& rhs) { *this = *this - rhs; return *this; }
		constexpr Quantity& operator*=(const Quantity& rhs) { *this = *this * rhs; return *this; }
		constexpr Quantity& operator/=(const Quantity& rhs) { *this = *this / rhs; return *this; }

		constexpr Quantity operator+() const { return Quantity(+magnitude, unit, uncertainty); }
		constexpr Quantity operator-() const { return Quantity(-magnitude, unit, uncertainty); }

		constexpr bool operator> (const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude >  other.magnitude; }
		constexpr bool operator< (const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude <  other.magnitude; }
		constexpr bool operator>=(const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude >= other.magnitude; }
		constexpr bool operator<=(const Quantity& other) const { if(unit != other.unit) throw std::logic_error("Invalid comparison"); return magnitude <= other.magnitude; }

		/** @brief Inequality comparison operator */
		constexpr bool operator!=(const Quantity& other) const { return !(*this == other); }

		/** @brief Equality comparison operator */
		constexpr bool operator==(const Quantity& other) const
		{
			if(unit != other.unit) throw std::logic_error("Invalid comparison");

			return magnitude   == other.magnitude
				&& uncertainty == other.uncertainty;
		}

		constexpr void root(int8_t power) { magnitude = Math::pow(magnitude, 1.0 / (double)power); unit.root(power); }
		constexpr void pow (int8_t power) { magnitude = Math::pow(magnitude,       (double)power); unit.pow (power); }
	};

	// real * quan
	constexpr Quantity operator+(double lhs, const Quantity& rhs) { return Quantity(lhs) + rhs; }
	constexpr Quantity operator-(double lhs, const Quantity& rhs) { return Quantity(lhs) - rhs; }
	constexpr Quantity operator*(double lhs, const Quantity& rhs) { return Quantity(lhs) * rhs; }
	constexpr Quantity operator/(double lhs, const Quantity& rhs) { return Quantity(lhs) / rhs; }

	// unit * real
	constexpr Quantity operator*(const Unit& lhs, double rhs) { return Quantity(lhs) * Quantity(rhs); }
	constexpr Quantity operator/(const Unit& lhs, double rhs) { return Quantity(lhs) / Quantity(rhs); }

	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator> (const Quantity& lhs, const T rhs) { return lhs >  Quantity(rhs); }
	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator< (const Quantity& lhs, const T rhs) { return lhs <  Quantity(rhs); }
	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator>=(const Quantity& lhs, const T rhs) { return lhs >= Quantity(rhs); }
	template<typename T, typename std::enable_if< std::is_convertible<T, double>::value >::type > constexpr bool operator<=(const Quantity& lhs, const T rhs) { return lhs <= Quantity(rhs); }

	template<typename T> constexpr bool operator> (const T lhs, const Quantity& rhs) { return Quantity(lhs) >  rhs; }
	template<typename T> constexpr bool operator< (const T lhs, const Quantity& rhs) { return Quantity(lhs) <  rhs; }
	template<typename T> constexpr bool operator>=(const T lhs, const Quantity& rhs) { return Quantity(lhs) >= rhs; }
	template<typename T> constexpr bool operator<=(const T lhs, const Quantity& rhs) { return Quantity(lhs) <= rhs; }
}

static_assert(sizeof(Units::Quantity) == 16, "Invalid size of Quantity");
