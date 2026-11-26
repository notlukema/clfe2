#define _CLFE_CLWIND_NO_AUTO_INCLUDE
#include "windows.h"

namespace clfe
{

	window_settings WindowHints = window_settings::DefaultSettings;

	void window_hint_enable(wset_t hints)
	{
		WindowHints.add(hints);
	}

	void window_hint_disable(wset_t hints)
	{
		WindowHints.remove(hints);
	}

	window_settings extract_window_hints()
	{
		window_settings settings = WindowHints;
		WindowHints = window_settings::DefaultSettings;
		return settings;
	}

	// Defaults

	int nextx = 300, nexty = 200;

	void filter_window_defaults(int& x, int& y, int& width, int& height)
	{
		if (x < 0)
		{
			x = nextx;
			nextx += 20;
		}
		if (y < 0)
		{
			y = nexty;
			nexty += 20;
		}
		if (width < 0)
		{
			width = 800;
		}
		if (height < 0)
		{
			height = 600;
		}
	}

}