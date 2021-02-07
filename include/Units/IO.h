#pragma once

#include <ostream>
#include <string>

#include "Units.h"

namespace Units
{
	/**
	 * @brief Converts a quantity to a UTF-8 string using scientific format
	 *
	 * Converts the given quantity to scientific notation, for example:
	 * 6.674⋅10⁻¹¹ m³ kg⁻¹ s⁻²
	 */
	std::string to_string_scientific(const Quantity& q);

	/**
	 * @brief Convert a unit to a UTF-8 string
	 *
	 * Converts a unit to a string.
	 * If the unit cannot be recognized, returns it using base SI units
	 * (for example, Cd kg² m⁻¹)
	 */
	std::string to_string(const Unit& unit);

	/**
	 * @brief Convert a quantity to a UTF-8 string
	 *
	 * Converts a quantity to a string, formatting it in the most apropriate
	 * way
	 */
	std::string to_string(const Quantity& quant);

	/**
	 * @brief Convert a UTF-8 string to a unit
	 *
	 * Converts the given string to a unit. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Unit to_unit(const std::string& str);

	/**
	 * @brief Convert a UTF-16 string to a unit
	 *
	 * Converts the given string to a unit. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Unit to_unit(const std::u16string& str);

	/**
	 * @brief Convert a UTF-32 string to a unit
	 *
	 * Converts the given string to a unit. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Unit to_unit(const std::u32string& str);

	/**
	 * @brief Convert buffer contents to a quantity
	 *
	 * Converts the given string to a quantity. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Unit to_unit(std::istream& is);

	/**
	 * @brief Convert a UTF-8 string to a quantity
	 *
	 * Converts the given string to a quantity. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Quantity to_quantity(const std::string& str);

	/**
	 * @brief Convert a UTF-16 string to a quantity
	 *
	 * Converts the given string to a quantity. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Quantity to_quantity(const std::u16string& str);

	/**
	 * @brief Convert a UTF-32 string to a quantity
	 *
	 * Converts the given string to a quantity. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Quantity to_quantity(const std::u32string& str);

	/**
	 * @brief Convert buffer contents to a quantity
	 *
	 * Converts the given string to a quantity. If the conversion is not successful
	 * or the given string is invalid, @cpp Units::error @ce is returned
	 */
	Quantity to_quantity(std::istream& is);
}

inline std::ostream& operator<<(std::ostream& os, const Units::Quantity& q) { return os << Units::to_string(q); }
inline std::ostream& operator<<(std::ostream& os, const Units::Unit& u)     { return os << Units::to_string(u); }

inline std::istream& operator>>(std::istream& is, Units::Quantity& q) { q = Units::to_quantity(is); return is; }
inline std::istream& operator>>(std::istream& is, Units::Unit& u)     { u = Units::to_unit    (is); return is; }
