#pragma once

#include <limits>
#include <type_traits>

#include "Unit.h"

namespace Units
{
	class Quantity
	{
	private:
		double m_Magnitude;
		Unit m_Unit;

		static double cround(double val);
		static Quantity convert(const Quantity& start, const Unit& result);

	public:
		constexpr Quantity(Unit u = Unit())             : m_Magnitude(1.0), m_Unit(u) {}
		constexpr Quantity(double mag, Unit u = Unit()) : m_Magnitude(mag), m_Unit(u) {}

		constexpr double magnitude() const { return m_Magnitude; }
		constexpr Unit unit() const { return m_Unit; }

		explicit operator double() const { return m_Magnitude; }
		explicit operator Unit() const { return m_Unit; }

		Quantity operator+() const;
		Quantity operator-() const;

		Quantity operator^(const int       exp) const;
		Quantity operator+(const Quantity& rhs) const;
		Quantity operator-(const Quantity& rhs) const;
		Quantity operator*(const Quantity& rhs) const;
		Quantity operator/(const Quantity& rhs) const;

		Quantity& operator^=(const int       exp);
		Quantity& operator+=(const Quantity& rhs);
		Quantity& operator-=(const Quantity& rhs);
		Quantity& operator*=(const Quantity& rhs);
		Quantity& operator/=(const Quantity& rhs);

		bool operator> (const Quantity& other) const;
		bool operator< (const Quantity& other) const;
		bool operator>=(const Quantity& other) const;
		bool operator<=(const Quantity& other) const;
		bool operator==(const Quantity& other) const;
		bool operator!=(const Quantity& other) const;

		void root(int power);
		void pow (int power);
	};

	Quantity operator+(double lhs, const Quantity& rhs);
	Quantity operator-(double lhs, const Quantity& rhs);
	Quantity operator*(double lhs, const Quantity& rhs);
	Quantity operator/(double lhs, const Quantity& rhs);

	Quantity operator*(const Unit& lhs, double rhs);
	Quantity operator/(const Unit& lhs, double rhs);

	template<typename T>
	using IsDoubleConvertible = typename std::enable_if<std::is_convertible<T, double>::value>::type;

	template<typename T, IsDoubleConvertible<T>> bool operator> (const Quantity& lhs, const T& rhs) { return lhs >  Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> bool operator< (const Quantity& lhs, const T& rhs) { return lhs <  Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> bool operator>=(const Quantity& lhs, const T& rhs) { return lhs >= Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> bool operator<=(const Quantity& lhs, const T& rhs) { return lhs <= Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> bool operator==(const Quantity& lhs, const T& rhs) { return lhs == Quantity(rhs); }
	template<typename T, IsDoubleConvertible<T>> bool operator!=(const Quantity& lhs, const T& rhs) { return lhs != Quantity(rhs); }

	template<typename T> bool operator> (const T& lhs, const Quantity& rhs) { return Quantity(lhs) >  rhs; }
	template<typename T> bool operator< (const T& lhs, const Quantity& rhs) { return Quantity(lhs) <  rhs; }
	template<typename T> bool operator>=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) >= rhs; }
	template<typename T> bool operator<=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) <= rhs; }
	template<typename T> bool operator==(const T& lhs, const Quantity& rhs) { return Quantity(lhs) == rhs; }
	template<typename T> bool operator!=(const T& lhs, const Quantity& rhs) { return Quantity(lhs) != rhs; }
}
