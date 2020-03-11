#pragma once

namespace Units
{
	class Buffer
	{
	public:
		virtual ~Buffer() = default;

		constexpr static const char EOF_MARK = (char)0xFF;

		/** @brief Accepts an optional character. Returns `true` if char was found. */
		virtual bool accept(char chr) = 0;

		/** @brief Returns current character. */
		virtual char current() = 0;

		/** @brief Returns next character. */
		virtual char ahead() = 0;

		/** @brief Advances to the next character. Returns current char. */
		virtual char advance(bool skipws = false) = 0;

		/** @brief Expects a character. Returns `false` if expected character was not found. */
		virtual bool expect(char chr) = 0;

		virtual void push() = 0;
		virtual void pop() = 0;
	};
}
