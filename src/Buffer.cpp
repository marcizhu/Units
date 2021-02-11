#include <codecvt>
#include <locale>
#include <cstdlib>

#include "Buffer.h"

namespace Units
{
	Buffer::Buffer(const std::string& str)
		: str(to_utf16(str)), ptr(0), stack(0) {}

	Buffer::Buffer(const std::u16string& str)
		: str(str), ptr(0), stack(0) {}

	Buffer::Buffer(const std::u32string& str)
		: str(to_utf16(str)), ptr(0), stack(0) {}

	Buffer::Buffer(std::istream& is)
		: ptr(0), stack(0)
	{
		std::string temp;
		std::getline(is, temp);
		str = to_utf16(temp);
	}

	std::string Buffer::to_utf8(const std::u16string& s)
	{
		try {
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
			return conv.to_bytes(s);
		} catch(...) {
			return std::string();
		}
	}

	std::u16string Buffer::to_utf16(const std::string& str)
	{
		try {
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
			return conv.from_bytes(str);
		} catch(...) {
			return std::u16string();
		}
	}

	std::u16string Buffer::to_utf16(const std::u32string& str)
	{
		try {
			std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv;
			std::string bytes = conv.to_bytes(str);
			return std::u16string(reinterpret_cast<const char16_t*>(bytes.c_str()), bytes.length() / sizeof(char16_t));
		} catch(...) {
			return std::u16string();
		}
	}

	bool Buffer::isSpace(char16_t ch)
	{
		return ch == ' '  || ch == '\t'
			|| ch == '\n' || ch == '\v'
			|| ch == '\f' || ch == '\r';
	}

	char16_t Buffer::current() const { return  ptr      < str.size() ? str[ptr    ] : EOF_MARK; }
	char16_t Buffer::ahead  () const { return (ptr + 1) < str.size() ? str[ptr + 1] : EOF_MARK; }

	void Buffer::push() { stack = ptr; }
	void Buffer::pop () { ptr = stack; }

	double Buffer::parseDouble()
	{
		std::string utf8 = to_utf8(str.substr(ptr));

		const char* begin = utf8.c_str();
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
			while(isSpace(current()))
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
