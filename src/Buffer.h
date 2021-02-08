#pragma once

#include <cstdint>
#include <string>
#include <istream>

namespace Units
{
	class Buffer
	{
	private:
		std::u16string str;
		size_t ptr;
		size_t stack;

		static std::u16string to_utf16(const std::string& str);
		static std::u16string to_utf16(const std::u32string& str);
		static std::string    to_utf8 (const std::u16string& str);

		static bool isSpace(char16_t ch);

	public:
		/** @brief Constructor. Initializes a buffer from a UTF-8 string */
		Buffer(const std::string& string);

		/** @brief Constructor. Initializes a buffer from a UTF-16 string */
		Buffer(const std::u16string& string);

		/** @brief Constructor. Initializes a buffer from a UTF-32 string */
		Buffer(const std::u32string& string);

		/** @brief Constructor. Initializes a buffer from an input stream */
		Buffer(std::istream& is);

		/** @brief Destructor. */
		~Buffer() = default;

		/** @brief Constant to represent end-of-file */
		static constexpr const char16_t EOF_MARK = std::char_traits<char16_t>::eof();

		/** @brief Returns current character. */
		char16_t current() const;

		/** @brief Returns next character. */
		char16_t ahead() const;

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
		char16_t advance(bool skipws = false);

		/** @brief Accepts an optional character.
		 *
		 * If the given character was found, then @cpp true @ce is returned and
		 * the buffer advances one character. Otherwise, @cpp false @ce is
		 * returned and no advancement occurs.
		 */
		bool accept(char16_t chr);
	};
}
