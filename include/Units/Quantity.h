#pragma once

#include <cmath>
#include <cstdint>
#include <stdexcept>

#include "Unit.h"

namespace Units
{
	class Quantity
	{
	private:
		double mag;
		Unit unit_;
		uint32_t extra_;

		template<typename T>
		constexpr static T pow2(T const& x) { return x * x; }

		template<typename T, typename IntType>
		constexpr static T pow_n_impl(const T& x, IntType n)
		{
			return n == 1 ? x
				: n % 2 ? x * pow2(pow_n_impl(x, n / 2))
				: pow2(pow_n_impl(x, n / 2));
		}

		template<typename T, typename IntType>
		constexpr static T pow_n(const T& x, IntType n)
		{
			return n == 0 ? T(1)
				: n > 0 ? pow_n_impl(x, n)
				: T(1) / pow_n_impl(x, -n);
		}

	public:
		constexpr Quantity() : mag(0.0), extra_(0) {}
		constexpr Quantity(double mag) : mag(mag), extra_(0) {}
		constexpr Quantity(Unit u) : mag(1.0), unit_(u), extra_(0) {}
		constexpr Quantity(double mag, Unit u) : mag(mag), unit_(u), extra_(0) {}
		constexpr Quantity(double mag, Unit u, uint32_t c) : mag(mag), unit_(u), extra_(c) {}

		constexpr double magnitude() const { return mag; }
		constexpr Unit unit() const { return unit_; }
		constexpr uint32_t extra() const { return extra_; }

		constexpr void extra(uint32_t val) { extra_ = val; }

		// quan * quan
		constexpr Quantity operator^(int8_t exp) const { return Quantity(pow_n(mag, exp), unit_ ^ exp); }
		constexpr Quantity operator+(const Quantity& rhs) const { return Quantity(mag + rhs.mag, unit_ + rhs.unit_, (extra_ != 0 ? extra_ : rhs.extra_)); }
		constexpr Quantity operator-(const Quantity& rhs) const { return Quantity(mag - rhs.mag, unit_ - rhs.unit_, (extra_ != 0 ? extra_ : rhs.extra_)); }
		constexpr Quantity operator*(const Quantity& rhs) const { return Quantity(mag * rhs.mag, unit_ * rhs.unit_, (extra_ != 0 ? extra_ : rhs.extra_)); }
		constexpr Quantity operator/(const Quantity& rhs) const { return Quantity(mag / rhs.mag, unit_ / rhs.unit_, (extra_ != 0 ? extra_ : rhs.extra_)); }

		constexpr Quantity& operator^=(int8_t exp)          { *this = *this ^ exp; return *this; }
		constexpr Quantity& operator+=(const Quantity& rhs) { *this = *this + rhs; return *this; }
		constexpr Quantity& operator-=(const Quantity& rhs) { *this = *this - rhs; return *this; }
		constexpr Quantity& operator*=(const Quantity& rhs) { *this = *this * rhs; return *this; }
		constexpr Quantity& operator/=(const Quantity& rhs) { *this = *this / rhs; return *this; }

		constexpr Quantity operator+() const { return Quantity(+mag, unit_, extra_); }
		constexpr Quantity operator-() const { return Quantity(-mag, unit_, extra_); }

		constexpr bool operator> (const Quantity& other) const { if(unit_ != other.unit_) throw std::logic_error("Invalid comparison"); return mag >  other.mag; }
		constexpr bool operator< (const Quantity& other) const { if(unit_ != other.unit_) throw std::logic_error("Invalid comparison"); return mag <  other.mag; }
		constexpr bool operator>=(const Quantity& other) const { if(unit_ != other.unit_) throw std::logic_error("Invalid comparison"); return mag >= other.mag; }
		constexpr bool operator<=(const Quantity& other) const { if(unit_ != other.unit_) throw std::logic_error("Invalid comparison"); return mag <= other.mag; }

		/** @brief Inequality comparison operator */
		constexpr bool operator!=(const Quantity& other) const { return !(*this == other); }

		/** @brief Equality comparison operator */
		constexpr bool operator==(const Quantity& other) const
		{
			if(unit_ != other.unit_) throw std::logic_error("Invalid comparison");

			return mag    == other.mag
				&& extra_ == other.extra_;
		}

		void root(int8_t power) { mag = std::pow(mag, 1.0 / (double)power); unit_.root(power); }
		constexpr void pow(int8_t power) { mag = pow_n(mag, power); unit_ ^= power; }
	};

	// real * quan
	constexpr Quantity operator+(double lhs, const Quantity& rhs) { return Quantity(lhs) + rhs; }
	constexpr Quantity operator-(double lhs, const Quantity& rhs) { return Quantity(lhs) - rhs; }
	constexpr Quantity operator*(double lhs, const Quantity& rhs) { return Quantity(lhs) * rhs; }
	constexpr Quantity operator/(double lhs, const Quantity& rhs) { return Quantity(lhs) / rhs; }

	// unit * real
	constexpr Quantity operator*(const Unit& lhs, double rhs) { return Quantity(lhs) * Quantity(rhs); }
	constexpr Quantity operator/(const Unit& lhs, double rhs) { return Quantity(lhs) / Quantity(rhs); }

	template<typename T> constexpr bool operator> (const Quantity& lhs, const T rhs) { return lhs >  Quantity(rhs); }
	template<typename T> constexpr bool operator< (const Quantity& lhs, const T rhs) { return lhs <  Quantity(rhs); }
	template<typename T> constexpr bool operator>=(const Quantity& lhs, const T rhs) { return lhs >= Quantity(rhs); }
	template<typename T> constexpr bool operator<=(const Quantity& lhs, const T rhs) { return lhs <= Quantity(rhs); }

	template<typename T> constexpr bool operator> (const T lhs, const Quantity& rhs) { return Quantity(lhs) >  rhs; }
	template<typename T> constexpr bool operator< (const T lhs, const Quantity& rhs) { return Quantity(lhs) <  rhs; }
	template<typename T> constexpr bool operator>=(const T lhs, const Quantity& rhs) { return Quantity(lhs) >= rhs; }
	template<typename T> constexpr bool operator<=(const T lhs, const Quantity& rhs) { return Quantity(lhs) <= rhs; }
}

static_assert(sizeof(Units::Quantity) == 16, "Invalid size of Quantity");
