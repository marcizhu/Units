#pragma once

#include <cstdint>
#include <string>
#include <istream>

namespace Units
{
	class Buffer
	{
	private:
		std::string str;
		size_t ptr;
		size_t stack;

	public:
		/** @brief Constructor. Initializes a buffer from a string */
		Buffer(const std::string& string);

		/** @brief Constructor. Initializes a buffer from an input stream */
		Buffer(std::istream& is);

		/** @brief Destructor. */
		~Buffer() = default;

		/** @brief Constant to represent end-of-file */
		static constexpr const char EOF_MARK = (char)0xFF;

		/** @brief Returns current character. */
		char current();

		/** @brief Returns next character. */
		char ahead();

		/**
		 * @brief Push the current pointer to the stack
		 *
		 * It is only safe to call @ref push() once. Calling it multiple times
		 * will only store the current pointer when the last call to @ref push()
		 * happened.
		 */
		void push();

		/**
		 * @brief Pop the current pointer from the stack
		 *
		 * It is safe to call @ref pop() before calling @ref push(). It is also
		 * safe to call pop() multiple times. In the first case, the current
		 * pointer will be set to the beggining of the string. In the second
		 * case, in each call to @ref pop(), the current pointer will be set to
		 * the value previously set by calling @ref push() or set to the beggining
		 * of the string if no previous calls to @ref push() were made.
		 */
		void pop();

		/** @brief Parse int at current location */
		int parseInt();

		/** @brief Parse double at current location */
		double parseDouble();

		/**
		 * @brief Advances to the next character, optionally skipping whitespaces
		 *
		 * @param skipws  Whether to skip whitespaces or not
		 *
		 * @returns the character at the current location (before advancing)
		 */
		char advance(bool skipws = false);

		/** @brief Accepts an optional character.
		 *
		 * If the given character was found, then @cpp true @ce is returned and
		 * the buffer advances one character. Otherwise, @cpp false @ce is
		 * returned and no advancement occurs.
		 */
		bool accept(char chr);
	};
}
