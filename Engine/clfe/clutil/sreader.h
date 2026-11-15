#ifndef CLFE_CLUTIL_SREADER_H
#define CLFE_CLUTIL_SREADER_H

#include <istream>
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
	T read_bits(std::istream& input, bit_pointer& p, rcount_t count)
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
		count += p.bit;
		rcount_t read_bytes = count / 8;
		if (p.bit > 0)
		{
			read_bytes--;
		}

		input.ignore(static_cast<std::streamsize>(read_bytes));
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
	T read_bytes(std::istream& input, bit_pointer& p, rcount_t count)
	{
		return read_bits(input, p, count * 8);
	}

	inline void skip_bytes(std::istream& input, bit_pointer& p, rcount_t count)
	{
		skip_bits(input, p, count * 8);
	}

	// Add more later (full file byte, string, maybe file property reading)
	// Also make an swriter.h

}

#endif