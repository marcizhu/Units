#include <string>
#include <iostream>

#include "Units/Units.h"
#include "Units/IO.h"
#include "Units/addons/std.h"

#define EXPRTK_HEADER "../src/exprtk/exprtk.hpp"
#include "Units/addons/exprtk.h"

int main()
{
	using namespace Units;

	typedef exprtk::symbol_table<Quantity> symbol_table_t;
	typedef exprtk::expression<Quantity>     expression_t;
	typedef exprtk::parser<Quantity>             parser_t;
	typedef exprtk::parser_error::type            error_t;

	Quantity x;
	Quantity y;

	symbol_table_t symbol_table;
	symbol_table.add_variable("x", x);
	symbol_table.add_variable("y", y);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	std::string expression_str;
	std::cout << "Enter value of variable \"x\": "; std::cin >> x;
	std::cout << "Enter value of variable \"y\": "; std::cin >> y;
	std::cout << "Enter expression to be evaluated: ";
	std::getline(std::cin, expression_str);

	parser_t parser;
	if(!parser.compile(expression_str, expression))
	{
		std::cout << parser.error() << ". Expression: " << expression_str << std::endl;

		for(std::size_t i = 0; i < parser.error_count(); ++i)
		{
			error_t err = parser.get_error(i);
			std::cout << exprtk::parser_error::to_str(err.mode) << ": " << err.diagnostic << ". Expression: " << expression_str << std::endl;
		}
	}

	Quantity ans = expression.value();
	std::cout << "Answer: " << ans << std::endl;
}
