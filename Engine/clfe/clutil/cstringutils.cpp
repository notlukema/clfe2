#include "cstringutils.h"

#include <cstdlib>
#include <malloc.h>
//#include <corecrt.h> // Already included by cstdlib
#include <string.h>
#include <wchar.h>

namespace clfe
{

	char* tostrnarrow(const wchar_t* wstr)
	{
		size_t required_size;
		wcstombs_s(&required_size, NULL, 0, wstr, _TRUNCATE);

		char* buffer = (char*)malloc(required_size * sizeof(char));
		wcstombs_s(nullptr, buffer, required_size, wstr, _TRUNCATE);

		return buffer;
	}

	wchar_t* tostrwide(const char* str)
	{
		size_t required_size;
		mbstowcs_s(&required_size, NULL, 0, str, _TRUNCATE);

		wchar_t* buffer = (wchar_t*)malloc(required_size * sizeof(wchar_t));
		if (buffer == nullptr)
		{
			return nullptr;
		}

		mbstowcs_s(nullptr, buffer, required_size, str, _TRUNCATE);

		return buffer;
	}

	char* concatstr(const char* str1, const char* str2)
	{
		size_t len1 = strlen(str1);
		size_t len2 = strlen(str2);

		char* buffer = (char*)malloc((len1 + len2 + 1) * sizeof(char));
		if (buffer == nullptr)
		{
			return nullptr;
		}

		strcpy_s(buffer, len1 + 1, str1);
		strcat_s(buffer, len1 + len2 + 1, str2);

		return buffer;
	}

	wchar_t* concatstr(const wchar_t* str1, const wchar_t* str2)
	{
		size_t len1 = wcslen(str1);
		size_t len2 = wcslen(str2);

		wchar_t* buffer = (wchar_t*)malloc((len1 + len2 + 1) * sizeof(wchar_t));
		if (buffer == nullptr)
		{
			return nullptr;
		}

		wcscpy_s(buffer, len1 + 1, str1);
		wcscat_s(buffer, len1 + len2 + 1, str2);

		return buffer;
	}

	size_t str_len(const char* str)
	{
		return strlen(str);
	}

	size_t str_len(const wchar_t* str)
	{
		return wcslen(str);
	}

	char* copystr(const char* str)
	{
		size_t len = strlen(str) + 1;

		char* buffer = (char*)malloc(len * sizeof(char));
		if (buffer == nullptr)
		{
			return nullptr;
		}

		strcpy_s(buffer, len, str);

		return buffer;
	}

	wchar_t* copystr(const wchar_t* str)
	{
		size_t len = wcslen(str) + 1;

		wchar_t* buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
		if (buffer == nullptr)
		{
			return nullptr;
		}

		wcscpy_s(buffer, len, str);

		return buffer;
	}

	char* cutstr(const char* str, size_t a, size_t b)
	{
		if (a < 0 || b < 0)
		{
			return nullptr;
		}
		if (b < a)
		{
			return cutstr(str, b, a);
		}

		size_t len = strlen(str);
		if (a > len || b > len)
		{
			return nullptr;
		}

		size_t newlen = b - a + 1;

		char* buffer = (char*)malloc(newlen * sizeof(char));
		if (buffer == nullptr)
		{
			return nullptr;
		}

		strncpy_s(buffer, newlen, str + a, newlen - 1);

		return buffer;
	}

	wchar_t* cutstr(const wchar_t* str, size_t a, size_t b)
	{
		if (a < 0 || b < 0)
		{
			return nullptr;
		}
		if (b < a)
		{
			return cutstr(str, b, a);
		}

		size_t len = wcslen(str);
		if (a > len || b > len)
		{
			return nullptr;
		}

		size_t newlen = b - a + 1;

		wchar_t* buffer = (wchar_t*)malloc(newlen * sizeof(wchar_t));
		if (buffer == nullptr)
		{
			return nullptr;
		}

		wcsncpy_s(buffer, newlen, str + a, newlen - 1);

		return buffer;
	}

}