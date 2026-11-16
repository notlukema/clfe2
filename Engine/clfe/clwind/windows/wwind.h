#ifndef CLFE_CLWIND_WINDOWS_WWIND_H
#define CLFE_CLWIND_WINDOWS_WWIND_H

#include "../wind.h"

#include "clfe/clutil/cstringutils.h"

#include <Windows.h>

namespace clfe
{

	HINSTANCE win_hinstance();

	class clwclass
	{
	private:
		ATOM atom_;
		wchar_t* name_;

	public:
		clwclass(requirestr<wchar_t> name, WNDPROC wndproc);
		~clwclass();

		inline ATOM atom() const
		{
			return atom_;
		}

		inline const wchar_t* name() const
		{
			return name_;
		}

	};

	class clwwindow : public clwindow
	{
	protected:
		static LRESULT CALLBACK defproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static clwclass* defclass;

	public:
		static clwclass* get_defclass();
		static bool init();
		static void step();
		static void term();

	private:
		HWND hwnd_;
		HDC hdc_;
		clwclass* wclass_;
		wchar_t* name_;

	public:
		clwwindow(int x, int y, int width, int height, requirestr<wchar_t> name, clwclass* wclass);

		inline clwwindow(int x, int y, int width, int height, const char* name) : clwwindow(x, y, width, height, name, get_defclass())
		{}

		inline clwwindow(int x, int y, int width, int height, const wchar_t* name) : clwwindow(x, y, width, height, name, get_defclass())
		{}

		~clwwindow();

	};

}

#endif