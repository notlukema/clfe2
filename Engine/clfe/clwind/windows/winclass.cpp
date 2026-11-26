#include "wwind.h"

#include "clfe/clutil/cstringutils.h"

#include <Windows.h>
#include <cstdlib>
#include <vector>

namespace clfe
{

	static std::vector<clwclass*> Classes;

	static void remove_class(clwclass* wclass)
	{
		auto it = Classes.begin();
		while (it != Classes.end())
		{
			if (*it == wclass)
			{
				it = Classes.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	//

	clwclass::clwclass(requirestr<wchar_t> name, WNDPROC wndproc)
	{
		name_ = name.emit_copy();

		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC; // Private DC
		wc.lpfnWndProc = wndproc;
		wc.hInstance = win_hinstance();
		wc.lpszClassName = name_;

		atom_ = RegisterClassEx(&wc);
		if (atom_ == NULL)
		{
			// Something
		}

		Classes.push_back(this);
	}

	clwclass::~clwclass()
	{
		UnregisterClassW(MAKEINTATOM(atom_), win_hinstance());
		free(name_);
		remove_class(this);
	}

	//

	void clwwindow::term()
	{
		while (Classes.size() > 0)
		{
			delete Classes.front();
		}
	}

}