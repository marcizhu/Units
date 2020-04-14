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
		float multiplier;
		UnitData data;

		static constexpr float max_precision = gcem::pow(10.0, std::numeric_limits<float>::digits10);
		static constexpr float cround(float val) { return gcem::round(val * max_precision) / max_precision; }

		static constexpr bool isError(const UnitData& data) { return data == UnitData::error(); }
		static constexpr bool isSame(float a, float b) { return cround(a) == cround(b); }

		constexpr Unit(float mult, const UnitData& dim) : multiplier(mult), data(dim) {}

	public:
		constexpr Unit()                               : multiplier(1.0), data() {}
		constexpr Unit(double mult, const Unit& other) : multiplier((float)mult * other.multiplier), data(other.data) {}

		constexpr uint32_t base_units() const { return *(const uint32_t*)&data; }
		constexpr float unit_multiplier() const { return cround(multiplier); }

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

		constexpr Unit operator^(int exp) const { return Unit(gcem::pow(multiplier, static_cast<float>(exp)), data^exp); }

		constexpr Unit operator+(const Unit& rhs) const { return (*this == rhs ? *this : Unit::error()); }
		constexpr Unit operator-(const Unit& rhs) const { return (*this == rhs ? *this : Unit::error()); }
		constexpr Unit operator*(const Unit& rhs) const { return Unit(multiplier * rhs.multiplier, data * rhs.data); }
		constexpr Unit operator/(const Unit& rhs) const { return Unit(multiplier / rhs.multiplier, data / rhs.data); }

		constexpr Unit& operator^=(int  exp) { *this = *this ^ exp; return *this; }
		constexpr Unit& operator+=(Unit rhs) { *this = *this + rhs; return *this; }
		constexpr Unit& operator-=(Unit rhs) { *this = *this - rhs; return *this; }
		constexpr Unit& operator*=(Unit rhs) { *this = *this * rhs; return *this; }
		constexpr Unit& operator/=(Unit rhs) { *this = *this / rhs; return *this; }

		constexpr bool operator!=(Unit other) const { return (!isError(data) || !isError(other.data)) && (data != other.data || !isSame(multiplier, other.multiplier)); }
		constexpr bool operator==(Unit other) const { return ( isError(data) &&  isError(other.data)) || (data == other.data &&  isSame(multiplier, other.multiplier)); }

		constexpr void root(int power) { multiplier = gcem::pow(multiplier, 1.0f / static_cast<float>(power)); data.root(power); }
		constexpr void pow (int power) { multiplier = gcem::pow(multiplier,        static_cast<float>(power)); data.pow (power); }

		constexpr int degree() const { return data.degree(); }
		constexpr int unit_count() const { return data.unit_count(); }
	};
}
