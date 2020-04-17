#pragma once

#include <istream>
#include <cstdint>

namespace Units
{
	class StreamBuffer
	{
	private:
		std::istream& is;
		char curr_char;

	public:
		StreamBuffer(std::istream& stream) : is(stream), curr_char(0) { curr_char = (char)is.get(); }
		~StreamBuffer() = default;

		constexpr static const char EOF_MARK = (char)0xFF;

		/** @brief Returns current character. */
		char current() { return curr_char; }

		/** @brief Returns next character. */
		char ahead  () { char c = (char)is.peek(); return c != EOF ? c : EOF_MARK; }

		/** @brief Advances to the next character. Returns current char. */
		char advance(bool skipws = false)
		{
			if(current() == EOF_MARK) return EOF_MARK;

			curr_char = (char)is.get();

			if(skipws)
			{
				while(curr_char == ' ')
					curr_char = (char)is.get();
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
