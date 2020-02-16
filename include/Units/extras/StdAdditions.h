#pragma once

#include <functional> // for std::hash
#include <limits>

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

	inline Units::Quantity pow  (Units::Quantity x, Units::Quantity y) noexcept { return pow  (x,     (int8_t)y.getMagnitude()); }
	inline Units::Quantity fmod (Units::Quantity x, Units::Quantity y) noexcept { return fmod (x.getMagnitude(), y.getMagnitude()); }
	inline Units::Quantity atan2(Units::Quantity x, Units::Quantity y) noexcept { return atan2(x.getMagnitude(), y.getMagnitude()); }

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
	inline Units::Quantity log  (Units::Quantity x) noexcept { return Units::Quantity(std::log  (x.getMagnitude()), x.getUnit()); }
	inline Units::Quantity log10(Units::Quantity x) noexcept { return Units::Quantity(std::log10(x.getMagnitude()), x.getUnit()); }

	template<>
	class numeric_limits<Units::Quantity>
	{
	public:
		static constexpr bool has_denorm_loss   = numeric_limits<double>::has_denorm_loss;
		static constexpr bool has_infinity      = numeric_limits<double>::has_infinity;
		static constexpr bool has_quiet_NaN     = numeric_limits<double>::has_quiet_NaN;
		static constexpr bool has_signaling_NaN = numeric_limits<double>::has_signaling_NaN;
		static constexpr bool is_bounded        = numeric_limits<double>::is_bounded;
		static constexpr bool is_exact          = numeric_limits<double>::is_exact;
		static constexpr bool is_iec559         = numeric_limits<double>::is_iec559;
		static constexpr bool is_integer        = numeric_limits<double>::is_integer;
		static constexpr bool is_modulo         = numeric_limits<double>::is_modulo;
		static constexpr bool is_signed         = numeric_limits<double>::is_signed;
		static constexpr bool is_specialized    = true;

		static constexpr float_denorm_style has_denorm = numeric_limits<double>::has_denorm;
		static constexpr float_round_style round_style = numeric_limits<double>::round_style;

		static constexpr bool traps           = numeric_limits<double>::traps           || numeric_limits<float>::traps;
		static constexpr bool tinyness_before = numeric_limits<double>::tinyness_before || numeric_limits<float>::traps;

		static constexpr int digits         = numeric_limits<double>::digits;
		static constexpr int digits10       = numeric_limits<double>::digits10;
		static constexpr int max_digits10   = numeric_limits<double>::max_digits10;
		static constexpr int max_exponent   = numeric_limits<double>::max_exponent;
		static constexpr int max_exponent10 = numeric_limits<double>::max_exponent10;
		static constexpr int min_exponent   = numeric_limits<double>::min_exponent;
		static constexpr int min_exponent10 = numeric_limits<double>::min_exponent10;
		static constexpr int radix          = numeric_limits<double>::radix;

		static constexpr Units::Quantity denorm_min()    { return Units::Quantity(numeric_limits<double>::denorm_min()); }
		static constexpr Units::Quantity epsilon()       { return Units::Quantity(numeric_limits<double>::epsilon()); }
		static constexpr Units::Quantity infinity()      { return Units::Quantity(numeric_limits<double>::infinity()); }
		static constexpr Units::Quantity lowest()        { return Units::Quantity(numeric_limits<double>::lowest()); }
		static constexpr Units::Quantity max()           { return Units::Quantity(numeric_limits<double>::max()); }
		static constexpr Units::Quantity min()           { return Units::Quantity(numeric_limits<double>::min()); }
		static constexpr Units::Quantity quiet_NaN()     { return Units::Quantity(numeric_limits<double>::quiet_NaN()); }
		static constexpr Units::Quantity round_error()   { return Units::Quantity(numeric_limits<double>::round_error()); }
		static constexpr Units::Quantity signaling_NaN() { return Units::Quantity(numeric_limits<double>::signaling_NaN()); }
	};
}
