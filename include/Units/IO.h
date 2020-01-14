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
}

inline std::ostream& operator<<(std::ostream& os, Units::Quantity& q) { return os << to_string(q); }
inline std::ostream& operator<<(std::ostream& os, Units::Unit& u)     { return os << to_string(u); }
