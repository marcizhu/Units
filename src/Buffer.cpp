#include "Buffer.h"

namespace Units
{
	Buffer::Buffer(const std::string& string)
		: str(string), ptr(0), stack(0) {}

	Buffer::Buffer(std::istream& is)
		: ptr(0), stack(0)
	{
		std::getline(is, str);
	}

	char Buffer::current() { return  ptr      < str.size() ? str[ptr    ] : EOF_MARK; }
	char Buffer::ahead  () { return (ptr + 1) < str.size() ? str[ptr + 1] : EOF_MARK; }

	void Buffer::push() { stack = ptr; }
	void Buffer::pop () { ptr = stack; }

	int Buffer::parseInt()
	{
		try
		{
			size_t idx;
			int ret = stoi(str.substr(ptr), &idx);
			return ptr += idx, ret;
		} catch(...) {
			return 0;
		}
	}

	double Buffer::parseDouble()
	{
		try
		{
			size_t idx;
			double ret = stod(str.substr(ptr), &idx);
			return ptr += idx, ret;
		} catch(...) {
			return 0.0;
		}
	}

	char Buffer::advance(bool skipws)
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

	bool Buffer::accept(char chr)
	{
		if(chr != current()) return false;

		advance();
		return true;
	}
}
