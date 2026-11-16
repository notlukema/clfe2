#ifndef CLFE_CLUTIL_CSTRINGUTILS_H
#define CLFE_CLUTIL_CSTRINGUTILS_H

#include <type_traits>
#include <cstdlib>

namespace clfe
{

	// Generic utils
	// All functions return a fresh copy of the string allocated on dynamic memory
	// Uses malloc(), so remember to use free() instead of delete

	char* tostrnarrow(const wchar_t* str);
	wchar_t* tostrwide(const char* str);

	char* concatstr(const char* str1, const char* str2);
	wchar_t* concatstr(const wchar_t* str1, const wchar_t* str2);

	size_t str_len(const char* str);
	size_t str_len(const wchar_t* str);

	char* copystr(const char* str);
	wchar_t* copystr(const wchar_t* str);

	char* cutstr(const char* str, size_t a, size_t b);
	wchar_t* cutstr(const wchar_t* str, size_t a, size_t b);

	inline char* tostrnarrow(const char* str)
	{
		return copystr(str);
	}

	inline wchar_t* tostrwide(const wchar_t* str)
	{
		return copystr(str);
	}

	template <typename T>
	concept util_compat_string = std::is_same_v<T, char> || std::is_same_v<T, wchar_t>;

	template <typename To, typename From>
		requires util_compat_string<To> && util_compat_string<From>
	To* tostr(const From* str)
	{
		if constexpr (std::is_same_v<To, char>)
		{
			if constexpr (std::is_same_v<From, char>)
			{
				return copystr(str);
			}
			return tostrnarrow(str);
		}
		if constexpr (std::is_same_v<To, wchar_t>)
		{
			if constexpr (std::is_same_v<From, wchar_t>)
			{
				return copystr(str);
			}
			return tostrwide(str);
		}
		return nullptr;
	}

	// Special utils

	template <typename T>
		requires util_compat_string<T>
	struct requirestr
	{
	private:
		T* required_str;
		bool should_free;

	public:
		requirestr(const T* str) : should_free(false)
		{
			required_str = const_cast<T*>(str);
		}

		requirestr(const char* str) requires (!std::is_same_v<T, char>) : should_free(true)
		{
			required_str = tostr<T>(str);
		}

		requirestr(const wchar_t* str) requires (!std::is_same_v<T, wchar_t>) : should_free(true)
		{
			required_str = tostr<T>(str);
		}

		~requirestr()
		{
			if (should_free && required_str != nullptr)
			{
				free(required_str);
			}
		}

		inline const T* get() const
		{
			return required_str;
		}

		inline operator const T* () const
		{
			return required_str;
		}

		T* emit_copy()
		{
			if (should_free)
			{
				should_free = false;
				return required_str;
			}

			return copystr(required_str);
		}

	};

}

#endif // CLFE_CLUTIL_CSTRINGUTILS_H