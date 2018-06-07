/*!
\file
\brief Заголовок парсера протокола

*/

#pragma once

#include <cstdint>

#include <stack>
#include <vector>
#include <array>
#include <algorithm>

namespace COMMAND_PROCESS
{

enum class ACK
{
	ACK_OK					= 0x00,
	ACK_BUSY				= 0x01,

	NACK					= 0xFF
};

template <uint32_t BUFFER_SIZE, uint32_t QUEUE_SIZE>
class Parser
{

public:
	Parser(std::stack <std::vector<uint8_t>> &_frame):
		frame(_frame), pos(0)
	{}

	bool work()
	{
		this->frame.push(std::vector<uint8_t>());
		bool is_busy = false;

		for (uint32_t i = 0; i < pos; ++i)
		{
			if (this->buffer[i] == 0x00)
			{
				if (i + 1 == pos)
				{
					if (this->frame.size() < QUEUE_SIZE)
						this->frame.push(std::vector<uint8_t>());
					else
					{
						is_busy = true;
						break;
					}
				}

				continue;
			}
			else
				this->frame.top().emplace_back(this->buffer[i]);
		}

		if (!is_busy)
		{
			this->buffer[0] = static_cast<uint8_t>(ACK::ACK_OK);
			pos = 1;
		}
		else
		{
			this->buffer[0] = static_cast<uint8_t>(ACK::ACK_BUSY);
			pos = 1;
		}

		return true;
	}

	void resize(uint32_t _size)
	{
		if (_size < this->buffer.size())
			pos = _size;
	}

	uint8_t *data()
	{
		return static_cast<uint8_t*>(this->buffer.data());
	}

	const uint32_t size() const
	{
		return this->pos;
	}

	const uint32_t capacity() const
	{
		return this->buffer.size();
	}

	void clear()
	{
		this->pos = 0;
	}

private:
	std::array <uint8_t, BUFFER_SIZE> buffer;

	std::stack <std::vector<uint8_t>> &frame;
	uint32_t pos;
};

}
