#pragma once

#include <cstdint>

#include <stack>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>

namespace COMMAND_PROCESS
{

template <uint32_t BUFFER_SIZE>
class Parser
{

public:
	Parser(std::stack <std::vector<uint8_t>> &_frame):
		pos(0), frame(_frame)
	{}

	bool work()
	{
		this->frame.push(std::vector<uint8_t>());

		//for (auto it = this->buffer.begin(); it != this->buffer.end(); ++it)
		for (auto i = 0; i < pos; ++i)
		{
			if (this->buffer[i] == 0x00)
			{
				if (i + 1 == pos)
					this->frame.push(std::vector<uint8_t>());

				continue;
			}
			else
				this->frame.top().emplace_back(this->buffer[i]);
		}

		pos = 0;
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
