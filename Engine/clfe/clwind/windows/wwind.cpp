#include "wwind.h"

#include "clfe/clutil/cstringutils.h"

#include <Windows.h>
#include <cstdlib> // free()

namespace clfe
{

	HINSTANCE WinHInstance = NULL;

	HINSTANCE win_hinstance()
	{
		if (WinHInstance == NULL)
		{
			WinHInstance = GetModuleHandle(NULL);
		}
		return WinHInstance;
	}

	//

	clwclass* clwwindow::defclass = nullptr;

	clwclass* clwwindow::get_defclass()
	{
		if (defclass == nullptr)
		{
			defclass = new clwclass("Default", defproc);
		}
		return defclass;
	}

	//

	bool clwwindow::init()
	{
		return clwwindow::get_defclass() != nullptr;
	}

	void clwwindow::step()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	static step_handle handle = step_handle(clwwindow::init, clwwindow::step, clwwindow::term);

	//

	clwwindow::clwwindow(int x, int y, int width, int height, requirestr<wchar_t> name, window_settings settings, clwclass* wclass) : hdc_(NULL)
	{
		wclass_ = wclass;
		wname_ = name.emit_copy();
		name_ = tostrnarrow(wname_);

		DWORD exstyle = NULL;
		DWORD style = WS_POPUP | WS_BORDER;
		wset_t set = settings.get();

		if ((set & clfe::WS_RESIZABLE) > 0)
		{
			style |= WS_THICKFRAME;
		}
		if ((set & clfe::WS_START_VISIBLE) > 0)
		{
			style |= WS_VISIBLE;
		}
		if ((set & clfe::WS_DECORATED) > 0)
		{
			style |= WS_CAPTION;
		}
		if ((set & clfe::WS_MINIMIZABLE) > 0)
		{
			style |= WS_MINIMIZEBOX;
		}
		if ((set & clfe::WS_MAXIMIZABLE) > 0)
		{
			style |= WS_MAXIMIZEBOX;
		}
		if ((set & clfe::WS_CLOSEABLE) > 0)
		{
			style |= WS_SYSMENU;
		}
		if ((set & clfe::WS_FLOATING) > 0)
		{
			exstyle |= WS_EX_TOPMOST;
		}
		if ((set & clfe::WS_TRANSPARENT) > 0)
		{
			exstyle |= WS_EX_TRANSPARENT;
		}

		exstyle |= ((set & clfe::WS_NO_TASKBAR) > 0) ? WS_EX_TOOLWINDOW : WS_EX_APPWINDOW;

		hwnd_ = CreateWindowExW(
			exstyle,
			MAKEINTATOM(wclass_->atom()),
			wname_,
			style,

			x, y, width, height,

			NULL, // Menus aren't very cross-platform because they are either different (mac global menu) or don't exist (linux)
			NULL, // Child windows are also not very cross-platform (maybe I will add platform-specific functionalities later)
			win_hinstance(),
			this
		);

		if (hwnd_ == NULL)
		{
			// Something
			return;
		}

		hdc_ = GetDC(hwnd_);

		if (hdc_ == NULL)
		{
			// Something
		}
	}

	clwwindow::~clwwindow()
	{
		if (!closed_)
		{
			win_inner_destroy();
		}
		free(wname_);
	}

	// Created for the sake of not having to call virtual functions in the destructor
	// (Even though it should be fine to call it from the class it is defined in)
	void clwwindow::win_inner_destroy()
	{
		ReleaseDC(hwnd_, hdc_);
		DestroyWindow(hwnd_);
	}

	void clwwindow::virt_inner_destroy()
	{
		win_inner_destroy();
	}

	void clwwindow::record_new_name(const char* name)
	{
		free(wname_);
		free(name_);
		wname_ = tostrwide(name);
		name_ = copystr(name);
	}

	void clwwindow::record_new_name(const wchar_t* name)
	{
		free(wname_);
		free(name_);
		wname_ = copystr(name);
		name_ = tostrnarrow(name);
	}

	//

	int clwwindow::x() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.left;
	}

	int clwwindow::y() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.top;
	}

	clmvec<2, int> clwwindow::pos() const
	{

		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return clmvec<2, int>(rect.left, rect.top);
	}

	int clwwindow::width() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.right - rect.left;
	}

	int clwwindow::height() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.bottom - rect.top;
	}

	clmvec<2, int> clwwindow::size() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return clmvec<2, int>(rect.right - rect.left, rect.bottom - rect.top);
	}

	int clwwindow::cx() const
	{
		POINT p = { 0, 0 };
		ClientToScreen(hwnd_, &p);
		return p.x;
	}

	int clwwindow::cy() const
	{
		POINT p = { 0, 0 };
		ClientToScreen(hwnd_, &p);
		return p.y;
	}

	clmvec<2, int> clwwindow::cpos() const
	{
		POINT p = { 0, 0 };
		ClientToScreen(hwnd_, &p);
		return clmvec<2, int>(p.x, p.y);
	}

	int clwwindow::cwidth() const
	{
		RECT rect;
		GetClientRect(hwnd_, &rect);
		return rect.right;
	}

	int clwwindow::cheight() const
	{
		RECT rect;
		GetClientRect(hwnd_, &rect);
		return rect.bottom;
	}

	clmvec<2, int> clwwindow::csize() const
	{
		RECT rect;
		GetClientRect(hwnd_, &rect);
		return clmvec<2, int>(rect.right, rect.bottom);
	}
	
	//

	void clwwindow::x(int x)
	{
		SetWindowPos(hwnd_, NULL, x, y(), NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::y(int y)
	{
		SetWindowPos(hwnd_, NULL, x(), y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::pos(int x, int y)
	{
		SetWindowPos(hwnd_, NULL, x, y, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::pos(const clmvec<2, int>& pos)
	{
		SetWindowPos(hwnd_, NULL, pos.get(0), pos.get(1), NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::width(int width)
	{
		SetWindowPos(hwnd_, NULL, NULL, NULL, width, height(), SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::height(int height)
	{
		SetWindowPos(hwnd_, NULL, NULL, NULL, width(), height, SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::size(int width, int height)
	{
		SetWindowPos(hwnd_, NULL, NULL, NULL, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::size(const clmvec<2, int>& size)
	{
		SetWindowPos(hwnd_, NULL, NULL, NULL, size.get(0), size.get(1), SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::cx(int cx)
	{
		RECT rect = { cx, 0, 0, 0 };
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, rect.left, y(), NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::cy(int cy)
	{
		RECT rect = { 0, cy, 0, 0};
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, x(), rect.top, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::cpos(int cx, int cy)
	{
		RECT rect = { cx, cy, 0, 0 };
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, rect.left, rect.top, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::cpos(const clmvec<2, int>& cpos)
	{
		RECT rect = { cpos.get(0), cpos.get(1), 0, 0};
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, rect.left, rect.top, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
	}

	void clwwindow::cwidth(int cwidth)
	{
		RECT rect = { 0, 0, cwidth, 0 };
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, NULL, NULL, rect.right - rect.left, height(), SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::cheight(int cheight)
	{
		RECT rect = { 0, 0, 0, cheight };
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, NULL, NULL, width(), rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::csize(int cwidth, int cheight)
	{
		RECT rect = { 0, 0, cwidth, cheight };
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, NULL, NULL, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::csize(const clmvec<2, int>& csize)
	{
		RECT rect = { 0, 0, csize.get(0), csize.get(1) };
		DWORD style = (DWORD)GetWindowLongPtr(hwnd_, GWL_STYLE);
		DWORD exstyle = (DWORD)GetWindowLongPtr(hwnd_, GWL_EXSTYLE);
		AdjustWindowRectEx(&rect, style, FALSE, exstyle);
		SetWindowPos(hwnd_, NULL, NULL, NULL, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	}

	void clwwindow::name(const char* name)
	{
		wchar_t* wname = tostrwide(name);
		SetWindowTextW(hwnd_, wname);
		free(wname);
	}

	void clwwindow::name(const wchar_t* name)
	{
		SetWindowTextW(hwnd_, name);
	}

	//

	void clwwindow::focus()
	{
		SetForegroundWindow(hwnd_);
	}

}