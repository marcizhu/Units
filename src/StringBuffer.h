#pragma once

#include <cstdint>

#include "Buffer.h"

namespace Units
{
	class StringBuffer : public Buffer
	{
	private:
		const std::string& str;
		size_t ptr;

	public:
		StringBuffer(const std::string& s) : str(s), ptr(0) {}
		~StringBuffer() = default;

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
	};
}
