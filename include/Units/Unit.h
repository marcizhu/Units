#pragma once

#include <cstdint>
#include <limits>

#include "UnitData.h"
#include "gcem.hpp"

namespace Units
{
	class Unit
	{
	private:
		float m_Multiplier;
		UnitData m_Data;

		static constexpr float max_precision = gcem::pow(10.0f, std::numeric_limits<float>::digits10);
		static constexpr float cround(float val) { return gcem::round(val * max_precision) / max_precision; }

		static constexpr bool isError(const UnitData& data) { return data == UnitData::error(); }
		static constexpr bool isSame(float a, float b) { return cround(a) == cround(b); }

		constexpr Unit(float multiplier, const UnitData& dim)
			: m_Multiplier(multiplier), m_Data(dim) {}

	public:
		constexpr Unit()
			: m_Multiplier(1.0f), m_Data() {}

		constexpr Unit(double multiplier, const Unit& other)
			: m_Multiplier((float)multiplier * other.m_Multiplier), m_Data(other.m_Data) {}

		constexpr UnitData::BaseUnitType base_units() const { return m_Data.base_unit(); }
		constexpr float multiplier() const { return cround(m_Multiplier); }

		constexpr int degree() const { return m_Data.degree(); }
		constexpr int unit_count() const { return m_Data.unit_count(); }

		static constexpr Unit eq(uint8_t num) { return Unit(1.0f, UnitData::eq(num)); }

		static constexpr Unit error() { return Unit(1.0f, UnitData::error()); }
		static constexpr Unit iflag() { return Unit(1.0f, UnitData::iflag()); }

		static constexpr Unit meter   () { return Unit(1.0f, UnitData::meter()); }
		static constexpr Unit kilogram() { return Unit(1.0f, UnitData::kilogram()); }
		static constexpr Unit second  () { return Unit(1.0f, UnitData::second()); }
		static constexpr Unit ampere  () { return Unit(1.0f, UnitData::ampere()); }
		static constexpr Unit kelvin  () { return Unit(1.0f, UnitData::kelvin()); }
		static constexpr Unit radian  () { return Unit(1.0f, UnitData::radians()); }
		static constexpr Unit mole    () { return Unit(1.0f, UnitData::mole()); }
		static constexpr Unit candela () { return Unit(1.0f, UnitData::candela()); }
		static constexpr Unit currency() { return Unit(1.0f, UnitData::currency()); }
		static constexpr Unit count   () { return Unit(1.0f, UnitData::count()); }

		constexpr Unit operator^(const int   exp) const { return Unit(gcem::pow(m_Multiplier, static_cast<float>(exp)), m_Data^exp); }
		constexpr Unit operator+(const Unit& rhs) const { return (*this == rhs ? *this : Unit::error()); }
		constexpr Unit operator-(const Unit& rhs) const { return (*this == rhs ? *this : Unit::error()); }
		constexpr Unit operator*(const Unit& rhs) const { return Unit(m_Multiplier * rhs.m_Multiplier, m_Data * rhs.m_Data); }
		constexpr Unit operator/(const Unit& rhs) const { return Unit(m_Multiplier / rhs.m_Multiplier, m_Data / rhs.m_Data); }

		constexpr Unit& operator^=(const int   exp) { return *this = *this ^ exp; }
		constexpr Unit& operator+=(const Unit& rhs) { return *this = *this + rhs; }
		constexpr Unit& operator-=(const Unit& rhs) { return *this = *this - rhs; }
		constexpr Unit& operator*=(const Unit& rhs) { return *this = *this * rhs; }
		constexpr Unit& operator/=(const Unit& rhs) { return *this = *this / rhs; }

		constexpr bool operator==(Unit other) const { return ( isError(m_Data) &&  isError(other.m_Data)) || (m_Data == other.m_Data &&  isSame(m_Multiplier, other.m_Multiplier)); }
		constexpr bool operator!=(Unit other) const { return (!isError(m_Data) || !isError(other.m_Data)) && (m_Data != other.m_Data || !isSame(m_Multiplier, other.m_Multiplier)); }

		constexpr void root(int power) { m_Multiplier = gcem::pow(m_Multiplier, 1.0f / static_cast<float>(power)); m_Data.root(power); }
		constexpr void pow (int power) { m_Multiplier = gcem::pow(m_Multiplier,        static_cast<float>(power)); m_Data.pow (power); }
	};
}
