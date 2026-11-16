#include "wwind.h"

namespace clfe
{

	static constexpr LRESULT WinBlankReturn = 0;

	LRESULT CALLBACK clwwindow::defproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		clwwindow* window = nullptr;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
			window = (clwwindow*)createStruct->lpCreateParams;

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		}
		else
		{
			window = (clwwindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (window == nullptr)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		if (uMsg == WM_KEYDOWN)
		{
			/*
			window->getInput()->trigKeyDown(KeyTables::translateKey<WindowsKeys>(wParam));
			*/
			return WinBlankReturn;
		}
		if (uMsg == WM_KEYUP)
		{
			/*
			window->getInput()->trigKeyUp(KeyTables::translateKey<WindowsKeys>(wParam));
			*/
			return WinBlankReturn;
		}

		if (uMsg == WM_CLOSE)
		{
			/*
			window->destroy();
			*/
			return WinBlankReturn;
		}

		if (uMsg == WM_MOVE)
		{
			//CLFE_LOG("moved");
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}