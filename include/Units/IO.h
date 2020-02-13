#pragma once

#include <cmath>
#include <array>
#include <ostream>
#include <string>
#include <unordered_map>

#include "Units.h"

namespace Units
{
	/**
	 * @brief Converts a quantity to a string using scientific format
	 *
	 * Converts the given quantity to scientific notation, for example:
	 * 6.674⋅10⁻¹¹ m³ kg⁻¹ s⁻²
	 */
	std::string to_string_scientific(Quantity q);

	/**
	 * @brief Convert a unit to a string
	 *
	 * Converts a unit to a string.
	 * If the unit cannot be recognized, returns it using base SI units
	 * (for example, Cd kg² m⁻¹)
	 */
	std::string to_string(Unit u);

	/**
	 * @brief Convert a quantity to a string
	 *
	 * Converts a quantity to a string, formatting it in the most apropriate
	 * way.
	 */
	std::string to_string(Quantity q);

	/**
	 * @brief Convert a string to a unit
	 *
	 * Converts the given string to a unit.
	 *
	 * @param unit The string to be converted
	 * @param un   The unit where the result will be stored
	 *
	 * @returns `true` on success, `false` on failure.
	 */
	bool from_string(const std::string& unit, Unit& un);

	/**
	 * @brief Convert a string to a quantity
	 *
	 * Converts the given string to a quantity.
	 *
	 * @param unit The string to be converted
	 * @param q    The quantity where the result will be stored
	 *
	 * @returns `true` on success, `false` on failure.
	 */
	bool from_string(const std::string& unit, Quantity& q);
}

inline std::ostream& operator<<(std::ostream& os, const Units::Quantity& q) { return os << Units::to_string(q); }
inline std::ostream& operator<<(std::ostream& os, const Units::Unit& u)     { return os << Units::to_string(u); }

inline std::istream& operator>>(std::istream& is, Units::Quantity& u) { (void)u; return is; }
inline std::istream& operator>>(std::istream& is, Units::Unit& u)     { (void)u; return is; }
