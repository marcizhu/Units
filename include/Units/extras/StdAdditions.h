#pragma once

#include <functional> // for std::hash

#include "../Units.h"

// std namespace additions for units
namespace std
{
	template<>
	struct hash<Units::Unit>
	{
		size_t operator()(Units::Unit x) const noexcept
		{
			return hash<uint32_t>()(*reinterpret_cast<const uint32_t*>(&x));
		}
	};

	inline constexpr Units::Unit sqrt(Units::Unit x) noexcept { x.root(2); return x; }
	inline constexpr Units::Unit cbrt(Units::Unit x) noexcept { x.root(3); return x; }
	inline constexpr Units::Unit pow (Units::Unit x, int8_t exp) noexcept { return x^exp; }
}

// std namespace additions for quantities
namespace std
{
	template<>
	struct hash<Units::Quantity>
	{
		size_t operator()(Units::Quantity x) const noexcept
		{
			return hash<Units::Unit>()(x.getUnit()) ^ hash<double>()(x.getMagnitude());
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

	inline Units::Quantity pow (Units::Quantity x, Units::Quantity y) noexcept { return pow (x,     (int8_t)y.getMagnitude()); }
	inline Units::Quantity fmod(Units::Quantity x, Units::Quantity y) noexcept { return fmod(x.getMagnitude(), y.getMagnitude()); }

	inline bool isinf   (Units::Quantity x) noexcept { return std::isinf   (x.getMagnitude()); }
	inline bool isnan   (Units::Quantity x) noexcept { return std::isnan   (x.getMagnitude()); }
	inline bool isnormal(Units::Quantity x) noexcept { return std::isnormal(x.getMagnitude()); }
	inline bool isfinite(Units::Quantity x) noexcept { return std::isfinite(x.getMagnitude()); }

	inline Units::Quantity abs  (Units::Quantity x) noexcept { return Units::Quantity(std::abs  (x.getMagnitude()), x.getUnit(), x.getUncertainty()); }
	inline Units::Quantity fabs (Units::Quantity x) noexcept { return Units::Quantity(std::fabs (x.getMagnitude()), x.getUnit(), x.getUncertainty()); }
	inline Units::Quantity ceil (Units::Quantity x) noexcept { return Units::Quantity(std::ceil (x.getMagnitude()), x.getUnit(), x.getUncertainty()); }
	inline Units::Quantity floor(Units::Quantity x) noexcept { return Units::Quantity(std::floor(x.getMagnitude()), x.getUnit(), x.getUncertainty()); }
	inline Units::Quantity round(Units::Quantity x) noexcept { return Units::Quantity(std::round(x.getMagnitude()), x.getUnit(), x.getUncertainty()); }
	inline Units::Quantity trunc(Units::Quantity x) noexcept { return Units::Quantity(std::trunc(x.getMagnitude()), x.getUnit(), x.getUncertainty()); }

	inline Units::Quantity exp  (Units::Quantity x) noexcept { return Units::Quantity(std::exp  (x.getMagnitude())); }
	inline Units::Quantity sin  (Units::Quantity x) noexcept { return Units::Quantity(std::sin  (x.getMagnitude())); }
	inline Units::Quantity cos  (Units::Quantity x) noexcept { return Units::Quantity(std::cos  (x.getMagnitude())); }
	inline Units::Quantity tan  (Units::Quantity x) noexcept { return Units::Quantity(std::tan  (x.getMagnitude())); }
	inline Units::Quantity asin (Units::Quantity x) noexcept { return Units::Quantity(std::asin (x.getMagnitude()), Units::radian); }
	inline Units::Quantity acos (Units::Quantity x) noexcept { return Units::Quantity(std::acos (x.getMagnitude()), Units::radian); }
	inline Units::Quantity atan (Units::Quantity x) noexcept { return Units::Quantity(std::atan (x.getMagnitude()), Units::radian); }
	inline Units::Quantity sinh (Units::Quantity x) noexcept { return Units::Quantity(std::sinh (x.getMagnitude())); }
	inline Units::Quantity cosh (Units::Quantity x) noexcept { return Units::Quantity(std::cosh (x.getMagnitude())); }
	inline Units::Quantity tanh (Units::Quantity x) noexcept { return Units::Quantity(std::tanh (x.getMagnitude())); }
//	inline Units::Quantity log  (Units::Quantity x) noexcept { return Units::Quantity(std::log  (x.getMagnitude()), x.unit()); }
//	inline Units::Quantity log10(Units::Quantity x) noexcept { return Units::Quantity(std::log10(x.getMagnitude()), x.unit()); }
}
