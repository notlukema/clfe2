#ifndef CLFE_CLWIND_WSETTINGS_H
#define CLFE_CLWIND_WSETTINGS_H

#include <cstdint>

namespace clfe
{

	using wset_t = uint64_t;
	using wdset_t = uint64_t;

	template <typename T>
	constexpr T bit_at(uint8_t at)
	{
		return (T)(1) << at;
	}

	//

	constexpr wset_t WS_RESIZABLE = bit_at<wset_t>(0);
	constexpr wset_t WS_START_VISIBLE = bit_at<wset_t>(1);
	constexpr wset_t WS_DECORATED = bit_at<wset_t>(2);
	constexpr wset_t WS_MINIMIZABLE = bit_at<wset_t>(3);
	constexpr wset_t WS_MAXIMIZABLE = bit_at<wset_t>(4);
	constexpr wset_t WS_CLOSEABLE = bit_at<wset_t>(5);
	constexpr wset_t WS_FOCUSED = bit_at<wset_t>(6);
	constexpr wset_t WS_FLOATING = bit_at<wset_t>(7);
	constexpr wset_t WS_MAXIMIZED = bit_at<wset_t>(8);
	constexpr wset_t WS_TRANSPARENT = bit_at<wset_t>(9);
	constexpr wset_t WS_NO_TASKBAR = bit_at<wset_t>(10); // Do note that this may invoke style changes

	constexpr wdset_t WDS_COLOR_BITS = bit_at<wdset_t>(0);
	constexpr wdset_t WDS_RED_BITS = bit_at<wdset_t>(1); // May not work on certain platforms
	constexpr wdset_t WDS_GREEN_BITS = bit_at<wdset_t>(2); // May not work on certain platforms
	constexpr wdset_t WDS_BLUE_BITS = bit_at<wdset_t>(3); // May not work on certain platforms
	constexpr wdset_t WDS_ALPHA_BITS = bit_at<wdset_t>(4); // May not work on certain platforms
	constexpr wdset_t WDS_REFRESH_RATE = bit_at<wdset_t>(5);

	// More to come

	//

	struct window_settings
	{
	public:
		static constexpr wset_t DefaultSettings = (WS_RESIZABLE | WS_DECORATED | WS_MINIMIZABLE | WS_MAXIMIZABLE | WS_CLOSEABLE);

	private:
		wset_t settings;
		// Any non-boolean settings?

	public:
		window_settings();
		window_settings(wset_t bools);

		// For the sake of not wanting to use defaults
		window_settings(const window_settings& other);
		window_settings& operator=(const window_settings& other);

		inline wset_t get() const
		{
			return settings;
		}

		window_settings& add(wset_t bools);
		window_settings& remove(wset_t bools);

		//

		inline window_settings operator|(wset_t bools)
		{
			return window_settings(*this).add(bools);
		}

		inline window_settings operator|(const window_settings& bools)
		{
			return operator|(bools.get());
		}

		// Deactivates the given settings
		inline window_settings operator&(wset_t bools)
		{
			return window_settings(*this).remove(bools);
		}

		// Deactivates the given settings
		inline window_settings operator&(const window_settings& bools)
		{
			return operator&(bools.get());
		}

		//

		inline window_settings& operator|=(wset_t bools)
		{
			return add(bools);
		}

		inline window_settings& operator|=(const window_settings& bools)
		{
			return operator|=(bools.get());
		}

		// Deactivates the given settings
		inline window_settings& operator&=(wset_t bools)
		{
			return remove(bools);
		}

		// Deactivates the given settings
		inline window_settings& operator&=(const window_settings& bools)
		{
			return operator&=(bools.get());
		}

	};

	inline window_settings create_window_settings(wset_t bools = window_settings::DefaultSettings)
	{
		return window_settings(bools);
	}

}

#endif // CLFE_CLWIND_WSETTINGS_H