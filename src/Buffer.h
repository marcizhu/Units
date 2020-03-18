#pragma once

#include <string>

namespace Units
{
	class Buffer
	{
	public:
		virtual ~Buffer() = default;

		constexpr static const char EOF_MARK = (char)0xFF;

		/** @brief Returns current character. */
		virtual char current() = 0;

		/** @brief Returns next character. */
		virtual char ahead() = 0;

		/** @brief Advances to the next character. Returns current char. */
		virtual char advance(bool skipws = false) = 0;

		/** @brief Expects a character. Returns `false` if expected character was not found. */
		bool expect(char chr)
		{
			if(chr != current())
			{
				throw std::runtime_error(
					"quantity: expecting '" + std::string(1, static_cast<char>(chr)) + "'");
				return false;
			}

			advance();
			return true;
		}

		/** @brief Accepts an optional character. Returns `true` if char was found. */
		bool accept(char chr)
		{
			if(chr != current()) return false;

			advance();
			return true;
		}
	};
}
