#include "wwind.h"

#include "clfe/clutil/cstringutils.h"

#include <Windows.h>
#include <cstdlib>

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

	clwwindow::clwwindow(int x, int y, int width, int height, requirestr<wchar_t> name, clwclass* wclass) : hdc_(NULL)
	{
		// Handle defaults
		if (x < 0) {
			x = CW_USEDEFAULT;
		}
		if (y < 0) {
			y = CW_USEDEFAULT;
		}
		if (width < 0) {
			width = CW_USEDEFAULT;
		}
		if (height < 0) {
			height = CW_USEDEFAULT;
		}

		wclass_ = wclass;
		name_ = name.emit_copy();

		hwnd_ = CreateWindowExW(
			NULL,
			MAKEINTATOM(wclass_->atom()),
			name_,
			WS_OVERLAPPEDWINDOW,

			x, y, width, height,

			NULL,
			NULL,
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

		ShowWindow(hwnd_, SW_SHOWNORMAL);
	}

	clwwindow::~clwwindow()
	{
		ReleaseDC(hwnd_, hdc_);
		DestroyWindow(hwnd_);
		free(name_);
	}

}