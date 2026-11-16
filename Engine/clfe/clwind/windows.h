#ifndef CLFE_CLWIND_WINDOWS_H
#define CLFE_CLWIND_WINDOWS_H

#include "wind.h"

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

#define WINDOW_DEFAULT -1

namespace clfe
{

	constexpr int WindowDefault = WINDOW_DEFAULT;

	inline clwindow* create_window(int x, int y, int width, int height, const char* name)
	{
#if defined(_OS_WINDOWS)
		return new clwwindow(x, y, width, height, name);
#elif defined(_OS_MAC)
		return nullptr;
#elif defined(_OS_LINUX)
		return nullptr;
#else
		return nullptr;
#endif
	}

	//

	inline clwindow* create_window(int width, int height, const char* name)
	{
		return create_window(WindowDefault, WindowDefault, width, height, name);
	}

	inline clwindow* create_window(const char* name)
	{
		return create_window(WindowDefault, WindowDefault, WindowDefault, WindowDefault, name);
	}

}

#endif