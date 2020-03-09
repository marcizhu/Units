#pragma once

#include "sprout/cmath.hpp"

namespace Units
{
	namespace Math
	{
		/** @brief Calculate absolute value of X */
		template<typename T> constexpr static T abs(const T& x) { return sprout::abs(x); }

		/** @brief Calculate e^X */
		template<typename T> constexpr T exp(const T& x) { return sprout::exp(x); }

		/** @brief Calculate log(X), aka natural log of X */
		template<typename T> constexpr T log(const T& x) { return sprout::log(x); }

		/** @brief Calculate X^Y */
		template<typename T> constexpr T pow(const T& x, const T& y) { return sprout::pow(x, y); }

		/** @brief Calculate square root of X, aka X^(1/2) */
		template<typename T> constexpr T sqrt(const T& x) { return sprout::sqrt(x); }

		/** @brief Classify the value x */
		template<typename T> constexpr int fpclassify(const T& x) { return sprout::fpclassify(x); }

		inline constexpr double cround(const double& val) { return sprout::round(val * 1.0e15) / 1.0e15; }
		inline constexpr float cround(const float& val) { return sprout::round(val * 1.0e15f) / 1.0e15f; }
	}
}
