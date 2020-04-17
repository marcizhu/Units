#pragma once

#include <cstdint>
#include <string>

namespace Units
{
	class StringBuffer
	{
	private:
		const std::string& str;
		size_t ptr;

	public:
		StringBuffer(const std::string& string) : str(string), ptr(0) {}
		~StringBuffer() = default;

		constexpr static const char EOF_MARK = (char)0xFF;

		/** @brief Returns current character. */
		char current() { return  ptr      < str.size() ? str[ptr    ] : EOF_MARK; }
		/** @brief Returns next character. */
		char ahead  () { return (ptr + 1) < str.size() ? str[ptr + 1] : EOF_MARK; }

		/** @brief Advances to the next character. Returns current char. */
		char advance(bool skipws = false)
		{
			if(current() == EOF_MARK) return EOF_MARK;

			++ptr;

			if(skipws)
			{
				while(current() == ' ')
					++ptr;
			}

			return current();
		}

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
