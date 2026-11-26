#include "wind.h"

#include <vector>
#include <cstdint>
#include <cstdlib> // free()

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
		/*
		uint32_t size = static_cast<uint32_t>(Windows.size());
		clwindow** windows = new clwindow*[size];

		// Call destroy on all windows first
		for (uint32_t i = 0; i < size; ++i)
		{
			windows[i] = Windows.front();
			windows[i]->destroy();
		}

		for (uint32_t i = 0; i < size; ++i)
		{
			delete windows[i];
		}

		delete[] windows;
		*/
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
				it = Windows.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	//

	clwindow::clwindow() : name_(nullptr), closed_(false), close_requested_(false)
	{
		Windows.push_back(this);
	}

	clwindow::~clwindow()
	{
		if (!closed_)
		{
			remove_window(this);
		}
		free(name_); // This should basically always be a c string copy
	}

	void clwindow::destroy()
	{
		if (closed_)
		{
			return;
		}

		virt_inner_destroy();
		remove_window(this);
		closed_ = true;
		close_requested_ = true;
	}

	void clwindow::request_close()
	{
		if (closed_)
		{
			return;
		}

		close_requested_ = true;
		// Callback
		if (false)
		{
			destroy();
		}
	}

	void clwindow::suppress_close_request()
	{
		if (closed_)
		{
			return;
		}

		close_requested_ = false;
	}

}