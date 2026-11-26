#include "wwind.h"

namespace clfe
{

	static constexpr LRESULT Win_Blank_Return = 0;

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

		if (uMsg == WM_SETTEXT)
		{

			if (IsWindowUnicode(hwnd))
			{
				window->record_new_name(reinterpret_cast<const wchar_t*>(lParam));
			}
			else
			{
				window->record_new_name(reinterpret_cast<const char*>(lParam));
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		if (uMsg == WM_KEYDOWN)
		{
			/*
			window->getInput()->trigKeyDown(KeyTables::translateKey<WindowsKeys>(wParam));
			*/
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		if (uMsg == WM_KEYUP)
		{
			/*
			window->getInput()->trigKeyUp(KeyTables::translateKey<WindowsKeys>(wParam));
			*/
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		if (uMsg == WM_CLOSE)
		{
			// According to microsoft, the only thing DefWindowProc() does for WM_CLOSE is call DestroyWindow()
			// In other words, we can reliably replace it's functionality with our own code
			//return DefWindowProc(hwnd, uMsg, wParam, lParam);
			
			window->request_close();
			return Win_Blank_Return;
		}

		if (uMsg == WM_MOVE)
		{
			//CLFE_LOG("moved");
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}