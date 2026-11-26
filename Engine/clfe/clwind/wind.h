#ifndef CLFE_CLWIND_WIND_H
#define CLFE_CLWIND_WIND_H

#include "wsettings.h"
#include "clfe/clmath/vec.h"

// Base class for windowing

namespace clfe
{

	struct step_handle
	{

		bool (*init)();
		void (*step)(), (*term)();

		step_handle(bool (*init)(), void (*step)(), void (*term)());

	};

	class clwindow
	{
	public:
		static bool init();
		static void step();
		static void term();

		struct callback_set
		{
			 
		};

	protected:
		char* name_;
		bool closed_, close_requested_;
		
		clwindow();

		virtual void virt_inner_destroy() = 0;

	public:
		virtual ~clwindow();
		void destroy();

		inline bool closed() const
		{
			return closed_;
		}

		inline bool close_requested() const
		{
			return close_requested_;
		}

		void request_close();
		void suppress_close_request();

		inline operator bool() const
		{
			return !closed_;
		}

		inline bool operator!() const
		{
			return closed_;
		}

		// Parameters

		//virtual bool set(wset_t setting, bool value) = 0;
		//virtual bool get(wset_t setting) = 0;

		virtual int x() const = 0;
		virtual int y() const = 0;
		virtual clmvec<2, int> pos() const = 0;
		virtual int width() const = 0;
		virtual int height() const = 0;
		virtual clmvec<2, int> size() const = 0;

		virtual int cx() const = 0;
		virtual int cy() const = 0;
		virtual clmvec<2, int> cpos() const = 0;
		virtual int cwidth() const = 0;
		virtual int cheight() const = 0;
		virtual clmvec<2, int> csize() const = 0;

		inline const char* name() const
		{
			return name_;
		}

		virtual void x(int x) = 0;
		virtual void y(int y) = 0;
		virtual void pos(int x, int y) = 0;
		virtual void pos(const clmvec<2, int>& pos) = 0;
		virtual void width(int width) = 0;
		virtual void height(int height) = 0;
		virtual void size(int width, int height) = 0;
		virtual void size(const clmvec<2, int>& size) = 0;

		virtual void cx(int cx) = 0;
		virtual void cy(int cy) = 0;
		virtual void cpos(int cx, int cy) = 0;
		virtual void cpos(const clmvec<2, int>& cpos) = 0;
		virtual void cwidth(int cwidth) = 0;
		virtual void cheight(int cheight) = 0;
		virtual void csize(int cwidth, int cheight) = 0;
		virtual void csize(const clmvec<2, int>& csize) = 0;

		virtual void name(const char* name) = 0;

		//

		virtual void focus() = 0;

	};

	inline bool clwinit()
	{
		return clwindow::init();
	}

	inline void clwstep()
	{
		clwindow::step();
	}

	inline void clwterm()
	{
		clwindow::term();
	}

}

#endif