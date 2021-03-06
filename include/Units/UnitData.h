#pragma once

#include <cstdint>

namespace Units
{
#if defined(__GNUC__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wconversion"
#endif

	class UnitData
	{
	private:
		struct Data
		{
			signed int meter : 4;
			signed int kilogram : 3;
			signed int second : 4;
			signed int ampere : 3;
			signed int kelvin : 4;
			signed int mole : 2;
			signed int radians : 3;
			signed int candela : 2;
			signed int currency : 2;
			signed int count : 2;
			bool e_flag : 1;
			bool i_flag : 1;
			bool eq_flag : 1;

			constexpr Data(int8_t m, int8_t kg, int8_t s, int8_t A, int8_t K, int8_t mol, int8_t rad, int8_t Cd, int8_t c, int8_t cnt, bool eflag, bool iflag, bool eqflag)
				: meter(m), kilogram(kg), second(s), ampere(A), kelvin(K), mole(mol), radians(rad),
				  candela(Cd), currency(c), count(cnt), e_flag(eflag), i_flag(iflag), eq_flag(eqflag) {}
		};

		union
		{
			Data m_Data;
			uint32_t m_Packed;
		};

		static_assert(sizeof(Data) == sizeof(uint32_t), "Size mismatch");

		bool isRootHz() const;
		bool isHz() const;
		bool hasValidRoot(int power) const;

		constexpr UnitData(int8_t m, int8_t kg, int8_t s, int8_t A, int8_t K, int8_t mol, int8_t rad, int8_t Cd, int8_t c, int8_t cnt, bool eflag, bool iflag, bool eqflag)
			: m_Data(m, kg, s, A, K, mol, rad, Cd, c, cnt, eflag, iflag, eqflag) {}

	public:
		/** @brief Default constructor. Initializes an empty UnitData */
		constexpr UnitData()
			: m_Data(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false) {}

		/** @brief Equation constructor. Initializes an equation UnitData. Used for dB, dBW, etc... */
		static constexpr UnitData eq(uint8_t num)
		{
			if(num > 0b0001'1111) return UnitData::error();

			UnitData ret;
			ret.m_Data.count   = (num & 0b0000'0011) >> 0;
			ret.m_Data.radians = (num & 0b0001'1100) >> 2;
			ret.m_Data.eq_flag = true;
			return ret;
		}

		/** @brief Returns the unit data that represents a meter */
		static constexpr UnitData meter   () { return UnitData(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a kilogram */
		static constexpr UnitData kilogram() { return UnitData(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a second */
		static constexpr UnitData second  () { return UnitData(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents an ampere */
		static constexpr UnitData ampere  () { return UnitData(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a kelvin */
		static constexpr UnitData kelvin  () { return UnitData(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a mole */
		static constexpr UnitData mole    () { return UnitData(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a radian */
		static constexpr UnitData radians () { return UnitData(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a candela */
		static constexpr UnitData candela () { return UnitData(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a currency */
		static constexpr UnitData currency() { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0); }
		/** @brief Returns the unit data that represents a count */
		static constexpr UnitData count   () { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0); }
		/** @brief Returns the unit data that represents an error unit */
		static constexpr UnitData error   () { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0); }
		/** @brief Returns the unit data that represents the imaginary flag */
		static constexpr UnitData iflag   () { return UnitData(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0); }

		/** @brief Alias for the base unit type */
		using BaseUnitType = decltype(m_Packed);

		/** @brief Get the unit data representation as integer type */
		BaseUnitType base_unit() const;

		/** @brief Equality comparison operator */
		bool operator==(const UnitData& other) const;
		/** @brief Inequality comparison operator */
		bool operator!=(const UnitData& other) const;

		/**
		 * @brief Get amount of units
		 *
		 * Returns the number of base SI units that form this unit. For example,
		 * a unit that represents "kg" would return 1, but a unit that represents
		 * "V" (volt) would return 4 (1 V = 1 (kg * m^2) / (A * s^3))
		 */
		int unit_count() const;

		/**
		 * @brief Get the sum of the exponents of all base units
		 *
		 * Returns the sum of the exponents of this unit represented in base SI
		 * units. For example, a unit of "m" would return 1, but "m^2" would
		 * return 2.
		 */
		int degree() const;

		/** @brief Exponent operator. Returns this unit raised to the nth power */
		UnitData operator^(int n) const;
		/** @brief Product operator */
		UnitData operator*(const UnitData& rhs) const;
		/** @brief Division operator */
		UnitData operator/(const UnitData& rhs) const;

		/** @brief Power function. Performs the nth power on this unit */
		void pow(int n);
		/** @brief Root function. Performs the nth root on this unit */
		void root(int n);
	};

#if defined(__GNUC__)
	#pragma GCC diagnostic pop
#endif
}
