#pragma once

#include "UnitData.h"

namespace Units
{
	class Unit
	{
	private:
		float m_Multiplier;
		UnitData m_Data;

		/** @brief Round a number to the maximum precision of a float */
		static float cround(float val);

		constexpr Unit(float multiplier, const UnitData& dim)
			: m_Multiplier(multiplier), m_Data(dim) {}

	public:
		/** @brief Constructor. Creates an empty unit */
		constexpr Unit()
			: m_Multiplier(1.0f), m_Data() {}

		/** @brief Constructor. Creates a unit from another one */
		constexpr Unit(double multiplier, const Unit& other)
			: m_Multiplier((float)multiplier * other.m_Multiplier), m_Data(other.m_Data) {}

		/** @brief Get base units of this unit */
		UnitData::BaseUnitType base_units() const;

		/** @brief Get multiplier of this unit */
		float multiplier() const;

		/** @brief Get degree of this unit */
		int degree() const;

		/** @brief Get the number of base SI units that form this unit */
		int unit_count() const;

		/** @brief Constructor. Initializes an equation unit */
		static constexpr Unit eq(uint8_t num) { return Unit(1.0f, UnitData::eq(num)); }

		/** @brief Returns a representation of an invalid unit */
		static constexpr Unit error() { return Unit(1.0f, UnitData::error()); }
		/** @brief Returns a unit that represents the imaginary flag */
		static constexpr Unit iflag() { return Unit(1.0f, UnitData::iflag()); }
		/** @brief Returns a unit that represents a meter */
		static constexpr Unit meter() { return Unit(1.0f, UnitData::meter()); }
		/** @brief Returns a unit that represents a kilogram */
		static constexpr Unit kilogram() { return Unit(1.0f, UnitData::kilogram()); }
		/** @brief Returns a unit that represents a second */
		static constexpr Unit second() { return Unit(1.0f, UnitData::second()); }
		/** @brief Returns a unit that represents an ampere */
		static constexpr Unit ampere() { return Unit(1.0f, UnitData::ampere()); }
		/** @brief Returns a unit that represents a kelvin */
		static constexpr Unit kelvin() { return Unit(1.0f, UnitData::kelvin()); }
		/** @brief Returns a unit that represents a radian */
		static constexpr Unit radian() { return Unit(1.0f, UnitData::radians()); }
		/** @brief Returns a unit that represents a mole */
		static constexpr Unit mole() { return Unit(1.0f, UnitData::mole()); }
		/** @brief Returns a unit that represents a candela */
		static constexpr Unit candela () { return Unit(1.0f, UnitData::candela()); }
		/** @brief Returns a unit that represents a unit of currency */
		static constexpr Unit currency() { return Unit(1.0f, UnitData::currency()); }
		/** @brief Returns a unit that represents a unit of count */
		static constexpr Unit count() { return Unit(1.0f, UnitData::count()); }

		/** @brief Exponent operator. Calculates the unit to the given power */
		Unit operator^(const int exp) const;
		/** @brief Add operator */
		Unit operator+(const Unit& rhs) const;
		/** @brief Subtract operator */
		Unit operator-(const Unit& rhs) const;
		/** @brief Product operator */
		Unit operator*(const Unit& rhs) const;
		/** @brief Division operator */
		Unit operator/(const Unit& rhs) const;

		/** @brief Exponent operator */
		Unit& operator^=(const int exp);
		/** @brief Add operator */
		Unit& operator+=(const Unit& rhs);
		/** @brief Subtract operator */
		Unit& operator-=(const Unit& rhs);
		/** @brief Product operator */
		Unit& operator*=(const Unit& rhs);
		/** @brief Division operator */
		Unit& operator/=(const Unit& rhs);

		/**
		 * @brief Equality comparison operator.
		 *
		 * Returns `true` if both units are either the same or both are error.
		 * Returns `false` otherwise.
		 */
		bool operator==(Unit other) const;

		/**
		 * @brief Inequality comparison operator.
		 *
		 * Returns `false` if both units are either the same or both are error.
		 * Returns `true` otherwise.
		 */
		bool operator!=(Unit other) const;

		/** @brief Performs nth root of this unit */
		void root(int n);

		/** @brief Performs nth power of this unit */
		void pow (int n);
	};
}
