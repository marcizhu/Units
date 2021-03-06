#pragma once

/*
 * This module adds compatibility with the library ExprTK by Arash Partow (http://www.partow.net/programming/exprtk/index.html)
 * Thus, with this file is possible to run arbitrary operations on quantities using mathematical expressions
 *
 * NOTE: This file should be included *after* exprtk.hpp.
 */

#include <functional>
#include "../Units.h"

namespace exprtk { namespace details { inline bool is_true(Units::Quantity v) { return std::not_equal_to<double>()(0.0,v.magnitude()); } }}

#ifdef EXPRTK_HEADER
#	include EXPRTK_HEADER
#else
#	include "exprtk.hpp"
#endif

namespace exprtk { namespace details { namespace numeric { namespace details {

	template<> inline Units::Quantity shr_impl   (const Units::Quantity v0, const Units::Quantity v1, real_type_tag) { return Units::Quantity(shr_impl   <double>(v0.magnitude(), v1.magnitude(), real_type_tag())); }
	template<> inline Units::Quantity shl_impl   (const Units::Quantity v0, const Units::Quantity v1, real_type_tag) { return Units::Quantity(shl_impl   <double>(v0.magnitude(), v1.magnitude(), real_type_tag())); }
	template<> inline Units::Quantity roundn_impl(const Units::Quantity v0, const Units::Quantity v1, real_type_tag) { return Units::Quantity(roundn_impl<double>(v0.magnitude(), v1.magnitude(), real_type_tag())); }
	template<> inline Units::Quantity root_impl  (const Units::Quantity v0, const Units::Quantity v1, real_type_tag) { return Units::Quantity(root_impl  <double>(v0.magnitude(), v1.magnitude(), real_type_tag())); }

	template<> inline Units::Quantity erf_impl  (const Units::Quantity v, real_type_tag) { return Units::Quantity(erf_impl  <double>(v.magnitude(), real_type_tag()), v.unit()); }
	template<> inline Units::Quantity erfc_impl (const Units::Quantity v, real_type_tag) { return Units::Quantity(erfc_impl <double>(v.magnitude(), real_type_tag()), v.unit()); }
	template<> inline Units::Quantity frac_impl (const Units::Quantity v, real_type_tag) { return Units::Quantity(frac_impl <double>(v.magnitude(), real_type_tag()), v.unit()); }
	template<> inline Units::Quantity trunc_impl(const Units::Quantity v, real_type_tag) { return Units::Quantity(trunc_impl<double>(v.magnitude(), real_type_tag()), v.unit()); }

	template<> inline int           to_int32_impl(const Units::Quantity v, real_type_tag) { return static_cast<int          >(v.magnitude()); }
	template<> inline long long int to_int64_impl(const Units::Quantity v, real_type_tag) { return static_cast<long long int>(v.magnitude()); }

	template<> struct number_type<Units::Quantity>
	{ typedef real_type_tag type; number_type() {} };

}}}}
