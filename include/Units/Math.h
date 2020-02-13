#pragma once

#include <type_traits>
#include <stdexcept>
#include <limits>

namespace Units
{
	namespace Math
	{
		/** @brief Calculate absolute value of X */
		template<typename T>
		constexpr static T abs(const T& x) { return x < T(0) ? -x : x; }

		template<typename FloatingPoint>
		constexpr FloatingPoint exp(
			const FloatingPoint& x,
			typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type* = nullptr);

		namespace details
		{
			/** @brief Calculate X^2 */
			template<typename T>
			constexpr static T pow2(const T& x) { return x * x; }

			template<typename T, typename IntType>
			constexpr static T pow_n_impl(const T& x, IntType n)
			{
				return n == 1 ? x
					: n % 2 ? x * pow2(pow_n_impl(x, n / 2))
					: pow2(pow_n_impl(x, n / 2));
			}

			/**
			 * @brief Test whether values are within machine epsilon
			 *
			 * Used for algorithm termination
			 */
			template<typename T>
			constexpr bool feq(const T& x, const T& y)
			{
				return abs(x - y) <= std::numeric_limits<T>::epsilon();
			}

			template <typename T>
			constexpr T exp(const T& x, const T& sum, const T& n, int i, const T& t)
			{
				return feq(sum, sum + t/n) ?
					sum :
					exp(x, sum + t/n, n * i, i+1, t * x);
			}

			template<typename T>
			constexpr T log_iter(const T& x, const T& y)
			{
				return y + T{2} * (x - Math::exp(y)) / (x + Math::exp(y));
			}

			template<typename T>
			constexpr T log(const T& x, const T& y)
			{
				return feq(y, log_iter(x, y)) ? y : log(x, log_iter(x, y));
			}

			/** @brief Number e */
			constexpr long double e()
			{
				return 2.71828182845904523536l;
			}

			// For numerical stability, constrain the domain to be x > 0.25 && x < 1024
			// - multiply/divide as necessary. To achieve the desired recursion depth
			// constraint, we need to account for the max double. So we'll divide by
			// e^5. If you want to compute a compile-time log of huge or tiny long
			// doubles, YMMV.

			// if x <= 1, we will multiply by e^5 repeatedly until x > 1
			template <typename T>
			constexpr T logGT(const T& x)
			{
				return x > T(0.25) ? log(x, T(0)) :
					logGT<T>(x * T(e() * e() * e() * e() * e())) - T(5);
			}

			// if x >= 2e10, we will divide by e^5 repeatedly until x < 2e10
			template <typename T>
			constexpr T logLT(const T& x)
			{
				return x < T(1024) ? log(x, T(0)) :
					logLT<T>(x / T(e() * e() * e() * e() * e())) + T(5);
			}
		}

		/** @brief Calculate X^n */
		template<typename T, typename IntType>
		constexpr static T pow_n(
			const T& x,
			IntType n,
			typename std::enable_if<std::is_integral<IntType>::value>::type* = nullptr)
		{
			return n == 0 ? T(1)
				 : n >  0 ? details::pow_n_impl(x, n)
				 : T(1) / details::pow_n_impl(x, -n);
		}

		/** @brief Calculate e^X */
		template<typename FloatingPoint>
		constexpr FloatingPoint exp(
			const FloatingPoint& x,
			typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type*)
		{
			return details::exp(x, FloatingPoint(1), FloatingPoint(1), 2, x);
		}

		/** @brief Calculate log(X), aka natural log of X */
		template <typename FloatingPoint>
		constexpr FloatingPoint log(
			const FloatingPoint& x,
			typename std::enable_if<std::is_floating_point<FloatingPoint>::value>::type* = nullptr)
		{
			return x < 0 ? throw std::domain_error("log") :
				x >= FloatingPoint(1024) ?
					details::logLT(x) :
					details::logGT(x);
		}

		/** @brief Calculate square root of X^Y */
		template<typename T>
		constexpr static T pow(const T& x, const T& y)
		{
			return x == T(0) ? T(0) : exp(y * log(x));
		}

		/** @brief Calculate square root of X, aka X^(1/2) */
		template<typename T>
		constexpr static T sqrt(const T& x)
		{
			return x < T(0) ? throw std::domain_error("sqrt") : pow(x, T(0.5));
		}
	}
}
