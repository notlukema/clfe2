#ifndef CLFE_CLUTIL_BIT_STREAM_H
#define CLFE_CLUTIL_BIT_STREAM_H

// Relatively crude bit reader/writer for i/o streams

#include <istream>
#include <ostream>
#include <cstdint>

namespace clfe
{

	using byte_t = uint8_t;
	using rcount_t = uint64_t;

	struct bit_pointer
	{

		byte_t last_byte;
		uint8_t bit;
		bool read_all;
		bool error;

		inline bit_pointer() : last_byte(0), bit(0), read_all(false), error(false)
		{}

		inline void reset()
		{
			last_byte = 0;
			bit = 0;
			read_all = false;
			error = false;
		}

	};

	constexpr byte_t bit_mask[8] =
	{
		1,
		3,
		7,
		15,
		31,
		63,
		127,
		255
	};

	// Reads file one byte at a time
	template<typename T>
	inline T read_bits(std::istream& input, bit_pointer& p, rcount_t count)
	{
		if (count > sizeof(T) * 8)
		{
			count = sizeof(T) * 8;
		}
		if (p.read_all || p.error)
		{
			return 0;
		}

		T out = 0;
		rcount_t base = count;
		while (count > 0)
		{
			if (p.bit == 0)
			{
				input.read(reinterpret_cast<char*>(&p.last_byte), 1);
				if (input.fail())
				{
					p.read_all = true;
					p.error = true;
				}
				else if (input.eof())
				{
					p.read_all = true;
				}
				if (input.gcount() == 0)
				{
					break;
				}
			}

			uint8_t read_count = 8 - p.bit;
			if (read_count > count)
			{
				read_count = static_cast<uint8_t>(count);
			}

			out |= (p.last_byte & bit_mask[read_count - 1]) << (base - count);

			count -= read_count;
			p.bit += read_count;

			if (p.bit == 8)
			{
				p.bit = 0;
			}
			else
			{
				p.last_byte >>= read_count;
			}
		}

		return out;
	}

	inline void skip_bits(std::istream& input, bit_pointer& p, rcount_t count)
	{
		if (p.read_all || p.error)
		{
			return;
		}

		count += p.bit;
		rcount_t skip_bytes = count / 8;
		if (p.bit > 0)
		{
			skip_bytes--;
		}

		if (skip_bytes > 0)
		{
			input.ignore(static_cast<std::streamsize>(skip_bytes));
			if (input.fail())
			{
				p.read_all = true;
				p.error = true;
				return;
			}
			else if (input.eof())
			{
				p.read_all = true;
				return;
			}
		}

		p.bit = count % 8;

		if (p.bit > 0)
		{
			input.read(reinterpret_cast<char*>(&p.last_byte), 1);
			if (input.fail())
			{
				p.read_all = true;
				p.error = true;
			}
			else if (input.eof())
			{
				p.read_all = true;
			}
		}
	}

	template <typename T>
	inline T read_bytes(std::istream& input, bit_pointer& p, rcount_t count)
	{
		return read_bits<T>(input, p, count * 8);
	}

	inline void skip_bytes(std::istream& input, bit_pointer& p, rcount_t count)
	{
		skip_bits(input, p, count * 8);
	}

	// Write
	// Note: writing by bit can be finicky as of right now

	template <typename T>
	inline bool write_bits(std::ostream& output, bit_pointer& p, T value, rcount_t count)
	{
		if (count > sizeof(T) * 8)
		{
			count = sizeof(T) * 8;
		}
		if (p.read_all || p.error)
		{
			return false;
		}

		rcount_t base = count;
		while (count > 0)
		{
			if (p.bit == 0)
			{
				p.last_byte = 0;
			}

			uint8_t write_count = 8 - p.bit;
			if (write_count > count)
			{
				write_count = static_cast<uint8_t>(count);
			}

			// Large type & small type = potential errors (technically works but doesn't feel right)
			p.last_byte |= ((value >> (base - count)) & bit_mask[write_count - 1]) << p.bit;

			count -= write_count;
			p.bit += write_count;

			if (p.bit == 8)
			{
				output.write(reinterpret_cast<char*>(&p.last_byte), 1);
				if (output.fail())
				{
					p.read_all = true;
					p.error = true;
					return false;
				}
				p.bit = 0;
			}
		}
		return true;
	}

	// Note: writing by bit can be finicky as of right now
	inline bool write_close(std::ostream& output, bit_pointer& p)
	{
		if (p.read_all || p.error)
		{
			return false;
		}

		if (p.bit > 0)
		{
			output.write(reinterpret_cast<char*>(&p.last_byte), 1);
			if (output.fail())
			{
				p.read_all = true;
				p.error = true;
				return false;
			}
			p.bit = 0;
		}

		p.read_all = true;

		return true;
	}

	/* I'm not making this since it requires zero chunks and I don't want this header to be too bloated
	inline bool fill_empty_bits(std::ostream& output, bit_pointer& p, rcount_t count)
	{
		if (p.read_all || p.error)
		{
			return false;
		}

		count += p.bit;
		rcount_t empty_bytes = count / 8;
		if (p.bit > 0)
		{
			if (empty_bytes == 0)
			{
				p.bit = static_cast<uint8_t>(count);
				return true;
			}

			empty_bytes--;

			output.write(reinterpret_cast<char*>(&p.last_byte), 1);
			if (output.fail())
			{
				p.read_all = true;
				p.error = true;
				return false;
			}
		}

		p.bit = count % 8;

		if (empty_bytes > 0)
		{
			output.write(reinterpret_cast<char*>(&p.last_byte), empty_bytes);
			if (output.fail())
			{
				p.read_all = true;
				p.error = true;
				return false;
			}
		}

		return true;
	}
	*/

}

#endif // CLFE_CLUTIL_BIT_STREAM_H