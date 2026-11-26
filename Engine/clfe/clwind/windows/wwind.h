#ifndef CLFE_CLWIND_WINDOWS_WWIND_H
#define CLFE_CLWIND_WINDOWS_WWIND_H

#include "../wind.h"
#include "../wsettings.h"
#include "clfe/clmath/vec.h"

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

	protected:
		HWND hwnd_;
		HDC hdc_;
		clwclass* wclass_;
		wchar_t* wname_;

		void win_inner_destroy();
		virtual void virt_inner_destroy();

		void record_new_name(const char* name);
		void record_new_name(const wchar_t* name);

	public:
		clwwindow(int x, int y, int width, int height, requirestr<wchar_t> name, window_settings settings, clwclass* wclass);

		inline clwwindow(int x, int y, int width, int height, const char* name, window_settings settings) : clwwindow(x, y, width, height, name, settings, get_defclass())
		{}

		inline clwwindow(int x, int y, int width, int height, const wchar_t* name, window_settings settings) : clwwindow(x, y, width, height, name, settings, get_defclass())
		{}

		virtual ~clwwindow();

		inline HWND hwnd() const
		{
			return hwnd_;
		}

		inline HDC hdc() const
		{
			return hdc_;
		}
		
		// Add wchar_t name modifier

		virtual int x() const;
		virtual int y() const;
		virtual clmvec<2, int> pos() const;
		virtual int width() const;
		virtual int height() const;
		virtual clmvec<2, int> size() const;

		virtual int cx() const;
		virtual int cy() const;
		virtual clmvec<2, int> cpos() const;
		virtual int cwidth() const;
		virtual int cheight() const;
		virtual clmvec<2, int> csize() const;

		inline wchar_t* wname() const
		{
			return wname_;
		}

		virtual void x(int x);
		virtual void y(int y);
		virtual void pos(int x, int y);
		virtual void pos(const clmvec<2, int>& pos);
		virtual void width(int width);
		virtual void height(int height);
		virtual void size(int width, int height);
		virtual void size(const clmvec<2, int>& size);

		virtual void cx(int cx);
		virtual void cy(int cy);
		virtual void cpos(int cx, int cy);
		virtual void cpos(const clmvec<2, int>& cpos);
		virtual void cwidth(int cwidth);
		virtual void cheight(int cheight);
		virtual void csize(int cwidth, int cheight);
		virtual void csize(const clmvec<2, int>& csize);

		virtual void name(const char* name);
		virtual void name(const wchar_t* name);

		//

		virtual void focus();

	};

}

#endif