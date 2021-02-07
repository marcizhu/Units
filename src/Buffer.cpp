#include <codecvt>
#include <locale>
#include <cstdlib>

#include "Buffer.h"

namespace Units
{
	Buffer::Buffer(const std::string& string)
		: str(to_utf16(string)), ptr(0), stack(0) {}

	Buffer::Buffer(const std::u16string& string)
		: str(string), ptr(0), stack(0) {}

	Buffer::Buffer(const std::u32string& string)
		: str(to_utf16(string)), ptr(0), stack(0) {}

	Buffer::Buffer(std::istream& is)
		: ptr(0), stack(0)
	{
		std::string temp;
		std::getline(is, temp);
		str = to_utf16(temp);
	}

	std::string Buffer::to_utf8(const std::u16string& s)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
		return conv.to_bytes(s);
	}

	std::u16string Buffer::to_utf16(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
		return conv.from_bytes(str);
	}

	std::u16string Buffer::to_utf16(const std::u32string& str)
	{
		std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv;
		std::string bytes = conv.to_bytes(str);
		return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
	}

	char16_t Buffer::current() { return  ptr      < str.size() ? str[ptr    ] : EOF_MARK; }
	char16_t Buffer::ahead  () { return (ptr + 1) < str.size() ? str[ptr + 1] : EOF_MARK; }

	void Buffer::push() { stack = ptr; }
	void Buffer::pop () { ptr = stack; }

	int Buffer::parseInt()
	{
		std::string utf8 = to_utf8(str.substr(ptr));

		const char* begin = utf8.data() + ptr;
		char* end = nullptr;

		long ret = strtol(begin, &end, 10);
		ptr += (size_t)(end - begin);
		return static_cast<int>(ret);
	}

	double Buffer::parseDouble()
	{
		std::string utf8 = to_utf8(str.substr(ptr));

		const char* begin = utf8.data() + ptr;
		char* end = nullptr;

		double ret = strtod(begin, &end);
		ptr += (size_t)(end - begin);
		return ret;
	}

	char16_t Buffer::advance(bool skipws)
	{
		if(current() == EOF_MARK) return EOF_MARK;

		++ptr;

		if(skipws)
		{
			while(std::isspace(current()))
				++ptr;
		}

		return current();
	}

	bool Buffer::accept(char16_t chr)
	{
		if(chr != current()) return false;

		advance();
		return true;
	}
}
