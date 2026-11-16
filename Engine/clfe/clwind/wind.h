#ifndef CLFE_CLWIND_WIND_H
#define CLFE_CLWIND_WIND_H

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

	protected:
		int x, y, width, height;
		const char* name;
		
		clwindow();
		~clwindow();

	public:


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