#include "wsettings.h"

namespace clfe
{

	window_settings::window_settings() : settings(DefaultSettings)
	{}

	window_settings::window_settings(wset_t bools) : settings(bools)
	{}

	window_settings::window_settings(const window_settings& other) : settings(other.get())
	{}

	window_settings& window_settings::operator=(const window_settings& other)
	{
		settings = other.get();
		return *this;
	}

	//

	window_settings& window_settings::add(wset_t bools)
	{
		settings |= bools;
		return *this;
	}

	window_settings& window_settings::remove(wset_t bools)
	{
		settings &= ~bools;
		return *this;
	}

}