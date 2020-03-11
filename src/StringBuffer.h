#pragma once

#include <string>
#include <cstdint>

#include "Buffer.h"

namespace Units
{
	class StringBuffer : public Buffer
	{
	private:
		const std::string& str;
		size_t ptr;
		size_t ptr_old;

	public:
		StringBuffer(const std::string& s) : str(s), ptr(0), ptr_old(0) {}
		~StringBuffer() = default;

		bool accept(char chr) override
		{
			if(chr != current()) return false;

			advance();
			return true;
		}

		char current() override { return  ptr      < str.size() ? str[ptr    ] : EOF_MARK; }
		char ahead  () override { return (ptr + 1) < str.size() ? str[ptr + 1] : EOF_MARK; }

		char advance(bool skipws = false) override
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

		bool expect(char chr) override
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

		void push() override { ptr_old = ptr; }
		void pop () override { ptr = ptr_old; }
	};
}
