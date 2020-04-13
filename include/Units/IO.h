#pragma once

#include <ostream>
#include <string>

#include "Units.h"

namespace Units
{
	/**
	 * @brief Converts a quantity to a string using scientific format
	 *
	 * Converts the given quantity to scientific notation, for example:
	 * 6.674⋅10⁻¹¹ m³ kg⁻¹ s⁻²
	 */
	std::string to_string_scientific(const Quantity& q);

	/**
	 * @brief Convert a unit to a string
	 *
	 * Converts a unit to a string.
	 * If the unit cannot be recognized, returns it using base SI units
	 * (for example, Cd kg² m⁻¹)
	 */
	std::string to_string(const Unit& unit);

	/**
	 * @brief Convert a quantity to a string
	 *
	 * Converts a quantity to a string, formatting it in the most apropriate
	 * way.
	 */
	std::string to_string(const Quantity& quant);

	/**
	 * @brief Convert a string to a unit
	 *
	 * Converts the given string to a unit.
	 *
	 * @param str  The string to be converted
	 * @param unit The unit where the result will be stored
	 *
	 * @returns `true` on success, `false` on failure.
	 */
	bool from_string(const std::string& str, Unit& unit);

	/**
	 * @brief Convert a string to a quantity
	 *
	 * Converts the given string to a quantity.
	 *
	 * @param str   The string to be converted
	 * @param quant The quantity where the result will be stored
	 *
	 * @returns `true` on success, `false` on failure.
	 */
	bool from_string(const std::string& str, Quantity& quant);

	/**
	 * @brief Convert a string to a quantity
	 *
	 * Converts the contents of the buffer to a quantity.
	 *
	 * @param is   The input stream
	 * @param unit The unit where the result will be stored
	 *
	 * @returns `true` on success, `false` on failure.
	 */
	bool from_buffer(std::istream& is, Unit& unit);

	/**
	 * @brief Convert a string to a quantity
	 *
	 * Converts the contents of the buffer to a quantity.
	 *
	 * @param is    The input stream
	 * @param quant The quantity where the result will be stored
	 *
	 * @returns `true` on success, `false` on failure.
	 */
	bool from_buffer(std::istream& is, Quantity& quant);
}

inline std::ostream& operator<<(std::ostream& os, const Units::Quantity& q) { return os << Units::to_string(q); }
inline std::ostream& operator<<(std::ostream& os, const Units::Unit& u)     { return os << Units::to_string(u); }

inline std::istream& operator>>(std::istream& is, Units::Quantity& q) { from_buffer(is, q); return is; }
inline std::istream& operator>>(std::istream& is, Units::Unit& u)     { from_buffer(is, u); return is; }
