#include "wind.h"

#include <vector>

namespace clfe
{

	static std::vector<step_handle*> Handles;
	static std::vector<clwindow*> Windows;

	step_handle::step_handle(bool (*init)(), void (*step)(), void (*term)()) : init(init), step(step), term(term)
	{
		Handles.push_back(this);
	}

	bool clwindow::init()
	{
		for (step_handle* handle : Handles)
		{
			if (handle->init != nullptr)
			{
				if (!handle->init())
				{
					return false;
				}
			}
		}
		return true;
	}

	void clwindow::step()
	{
		for (step_handle* handle : Handles)
		{
			if (handle->step != nullptr)
			{
				handle->step();
			}
		}
	}

	void clwindow::term()
	{
		while (Windows.size() > 0)
		{
			delete Windows.front();
		}

		for (step_handle* handle : Handles)
		{
			if (handle->term != nullptr)
			{
				handle->term();
			}
		}
	}

	static void remove_window(clwindow* window)
	{
		auto it = Windows.begin();
		while (it != Windows.end())
		{
			if (*it == window)
			{
				Windows.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	//

	clwindow::clwindow() : x(0), y(0), width(0), height(0), name(nullptr)
	{
		Windows.push_back(this);
	}

	clwindow::~clwindow()
	{
		remove_window(this);
	}

}