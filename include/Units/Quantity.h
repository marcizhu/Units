#pragma once

#include <cmath>
#include <cstdint>
#include <functional> // for std::hash
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

		constexpr static double pow(double n, int8_t exp) { return exp == 0 ? 1.0 : (exp < 0 ? (1.0 / pow(n, -exp)) : (n * pow(n, exp - 1))); }

	public:
		constexpr Quantity() : mag(1.0), extra_(0) {}
		constexpr Quantity(double mag) : mag(mag), extra_(0) {}
		constexpr Quantity(Unit u) : mag(1.0), unit_(u), extra_(0) {}
		constexpr Quantity(double mag, Unit u) : mag(mag), unit_(u), extra_(0) {}
		constexpr Quantity(double mag, Unit u, uint32_t c) : mag(mag), unit_(u), extra_(c) {}

		constexpr double magnitude() const { return mag; }
		constexpr Unit unit() const { return unit_; }
		constexpr uint32_t extra() const { return extra_; }

		constexpr void extra(uint32_t val) { extra_ = val; }

		// quan * quan
		constexpr Quantity operator^(int8_t exp) const { return Quantity(pow(mag, exp), unit_ ^ exp); }
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

		constexpr bool operator==(const Quantity& other) const { return mag == other.mag && unit_ == other.unit_ && extra_ == other.extra_; }
		constexpr bool operator!=(const Quantity& other) const { return !(*this == other); }

		explicit constexpr operator int() const { return (int)mag; }
		explicit constexpr operator double() const { return mag; }

		void root(int8_t power) { mag = std::pow(mag, 1.0 / (double)power); unit_.root(power); }
		constexpr void pow(int8_t power) { mag = pow(mag, power); unit_ ^= power; }
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

namespace std
{
	template<>
	struct hash<Units::Quantity>
	{
		size_t operator()(Units::Quantity x) const noexcept
		{
			return hash<Units::Unit>()(x.unit()) ^ hash<double>()(x.magnitude());
		}
	};

	template<>
	struct not_equal_to<Units::Quantity>
	{
		size_t operator()(Units::Quantity a, Units::Quantity b) const noexcept
		{
			return !(a == b);
		}
	};

	inline Units::Quantity sqrt(Units::Quantity x) noexcept { x.root(2); return x; }
	inline Units::Quantity cbrt(Units::Quantity x) noexcept { x.root(3); return x; }
	inline Units::Quantity pow (Units::Quantity x, int8_t exp) noexcept { return x^exp; }

	inline Units::Quantity pow (Units::Quantity x, Units::Quantity y) noexcept { return pow (x,     (int8_t)y.magnitude()); }
	inline Units::Quantity fmod(Units::Quantity x, Units::Quantity y) noexcept { return fmod(x.magnitude(), y.magnitude()); }

	inline bool isinf   (Units::Quantity x) noexcept { return std::isinf(x.magnitude()); }
	inline bool isnan   (Units::Quantity x) noexcept { return std::isnan(x.magnitude()); }
	inline bool isnormal(Units::Quantity x) noexcept { return std::isnormal(x.magnitude()); }
	inline bool isfinite(Units::Quantity x) noexcept { return std::isfinite(x.magnitude()); }

	inline Units::Quantity abs  (Units::Quantity x) noexcept { return Units::Quantity(std::abs  (x.magnitude()), x.unit()); }
	inline Units::Quantity ceil (Units::Quantity x) noexcept { return Units::Quantity(std::ceil (x.magnitude()), x.unit()); }
	inline Units::Quantity floor(Units::Quantity x) noexcept { return Units::Quantity(std::floor(x.magnitude()), x.unit()); }
	inline Units::Quantity round(Units::Quantity x) noexcept { return Units::Quantity(std::round(x.magnitude()), x.unit()); }
	inline Units::Quantity trunc(Units::Quantity x) noexcept { return Units::Quantity(std::trunc(x.magnitude()), x.unit()); }

	inline Units::Quantity exp  (Units::Quantity x) noexcept { return Units::Quantity(std::exp  (x.magnitude())); }
	inline Units::Quantity sin  (Units::Quantity x) noexcept { return Units::Quantity(std::sin  (x.magnitude())); }
	inline Units::Quantity cos  (Units::Quantity x) noexcept { return Units::Quantity(std::cos  (x.magnitude())); }
	inline Units::Quantity tan  (Units::Quantity x) noexcept { return Units::Quantity(std::tan  (x.magnitude())); }
	inline Units::Quantity asin (Units::Quantity x) noexcept { return Units::Quantity(std::asin (x.magnitude())); }
	inline Units::Quantity acos (Units::Quantity x) noexcept { return Units::Quantity(std::acos (x.magnitude())); }
	inline Units::Quantity atan (Units::Quantity x) noexcept { return Units::Quantity(std::atan (x.magnitude())); }
	inline Units::Quantity sinh (Units::Quantity x) noexcept { return Units::Quantity(std::sinh (x.magnitude())); }
	inline Units::Quantity cosh (Units::Quantity x) noexcept { return Units::Quantity(std::cosh (x.magnitude())); }
	inline Units::Quantity tanh (Units::Quantity x) noexcept { return Units::Quantity(std::tanh (x.magnitude())); }
//	inline Units::Quantity log  (Units::Quantity x) noexcept { return Units::Quantity(std::log  (x.magnitude()), x.unit()); }
//	inline Units::Quantity log10(Units::Quantity x) noexcept { return Units::Quantity(std::log10(x.magnitude()), x.unit()); }
}
