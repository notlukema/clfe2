#ifndef CLFE_CLWIND_WINDOWS_H
#define CLFE_CLWIND_WINDOWS_H

#include "wind.h"
#include "wsettings.h"
#include "clfe/clmath/vec.h"

#if !defined(_CLFE_CLWIND_NO_AUTO_INCLUDE)

#include "clfe/features.h"

#if defined(_OS_WINDOWS)
#include "windows/wwind.h"
#elif defined(_OS_MAC)
// n
#elif defined(_OS_LINUX)
// n
#else
// n
#endif

#endif

#define WINDOW_DEFAULT -1

namespace clfe
{

	constexpr int WindowDefault = WINDOW_DEFAULT;

	//

	void window_hint_enable(wset_t hints);
	void window_hint_disable(wset_t hints);

	inline void window_hint(wset_t hints, bool value)
	{
		if (value)
		{
			window_hint_enable(hints);
		}
		else
		{
			window_hint_disable(hints);
		}
	}

	inline void window_hint(wset_t hints)
	{
		window_hint_enable(hints);
	}

	inline void window_hint_visible()
	{
		window_hint_enable(WS_START_VISIBLE);
	}

	window_settings extract_window_hints();

	//

	void filter_window_defaults(int& x, int& y, int& width, int& height);

	inline clwindow* create_window(int x, int y, int width, int height, const char* name, window_settings settings)
	{
		filter_window_defaults(x, y, width, height);
#if !defined(_CLFE_CLWIND_NO_AUTO_INCLUDE)
#if defined(_OS_WINDOWS)
		return new clwwindow(x, y, width, height, name, settings);
#elif defined(_OS_MAC)
		return nullptr;
#elif defined(_OS_LINUX)
		return nullptr;
#else
		return nullptr;
#endif
#endif
	}

	// Crazy amount of variations

	inline clwindow* create_window(clmvec<2, int> pos, clmvec<2, int> size, const char* name, window_settings settings)
	{
		return create_window(pos.get(0), pos.get(1), size.get(0), size.get(1), name, settings);
	}

	inline clwindow* create_window(int x, int y, clmvec<2, int> size, const char* name, window_settings settings)
	{
		return create_window(x, y, size.get(0), size.get(1), name, settings);
	}

	inline clwindow* create_window(clmvec<2, int> pos, int width, int height, const char* name, window_settings settings)
	{
		return create_window(pos.get(0), pos.get(1), width, height, name, settings);
	}

	inline clwindow* create_window(int width, int height, const char* name, window_settings settings)
	{
		return create_window(WindowDefault, WindowDefault, width, height, name, settings);
	}

	inline clwindow* create_window(clmvec<2, int> size, const char* name, window_settings settings)
	{
		return create_window(WindowDefault, WindowDefault, size.get(0), size.get(1), name, settings);
	}

	inline clwindow* create_window(const char* name, window_settings settings)
	{
		return create_window(WindowDefault, WindowDefault, WindowDefault, WindowDefault, name, settings);
	}

	// Extract settings

	inline clwindow* create_window(int x, int y, int width, int height, const char* name)
	{
		return create_window(x, y, width, height, name, extract_window_hints());
	}

	inline clwindow* create_window(clmvec<2, int> pos, clmvec<2, int> size, const char* name)
	{
		return create_window(pos.get(0), pos.get(1), size.get(0), size.get(1), name, extract_window_hints());
	}

	inline clwindow* create_window(int x, int y, clmvec<2, int> size, const char* name)
	{
		return create_window(x, y, size.get(0), size.get(1), name, extract_window_hints());
	}

	inline clwindow* create_window(clmvec<2, int> pos, int width, int height, const char* name)
	{
		return create_window(pos.get(0), pos.get(1), width, height, name, extract_window_hints());
	}

	inline clwindow* create_window(int width, int height, const char* name)
	{
		return create_window(WindowDefault, WindowDefault, width, height, name, extract_window_hints());
	}

	inline clwindow* create_window(clmvec<2, int> size, const char* name)
	{
		return create_window(WindowDefault, WindowDefault, size.get(0), size.get(1), name, extract_window_hints());
	}

	inline clwindow* create_window(const char* name)
	{
		return create_window(WindowDefault, WindowDefault, WindowDefault, WindowDefault, name, extract_window_hints());
	}

}

#endif