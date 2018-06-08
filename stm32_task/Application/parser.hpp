/*!
\file
\brief Заголовок парсера протокола

*/

#pragma once

#include <cstdint>

#include <stack>
#include <string>
#include <array>
#include <algorithm>
#include <unordered_map>

namespace COMMAND_PROCESS
{

const std::string MS_OK = "OK";
const std::string MS_BUSY = "BUSY";


template <uint32_t BUFFER_SIZE, uint32_t QUEUE_SIZE>
class Parser
{

public:
	Parser(std::stack <std::string> &_frame):
		frame(_frame), pos(0)
	{}

	bool work()
	{
		if (pos == 0)
			return false;

		bool is_busy = false;
		bool is_new_message = false;

		for (uint32_t i = 0; i < pos; ++i)
		{
			if (this->buffer[i] != 0x00)
			{
				if (!is_new_message)
				{
					if (this->frame.size() < QUEUE_SIZE)
						this->frame.push(std::string());
					else
					{
						is_busy = true;
						break;
					}
				}

				is_new_message = true;
				this->frame.top().push_back(this->buffer[i]);
			}
			else
				is_new_message = false;


		}

		if (is_new_message)
			this->frame.pop();

		pos = 0;

		if (!is_busy)
		{
			std::copy(MS_OK.begin(), MS_OK.end(), this->buffer.begin());
			this->pos = MS_OK.size();

			if (!this->frame.empty())
			{
				auto find = ans_value.find(this->frame.top());

	            if (find != ans_value.end())
	            {
	        		this->buffer[this->pos++] = ' ';

	        		std::string str = std::to_string( *find->second);

	        		for (auto &data : str)
	        			this->buffer[this->pos++] = data;

	        		this->buffer[this->pos++] = ' ';
	        		this->buffer[this->pos++] = 'V';

	            }
			}

		}
		else
		{
			std::copy(MS_BUSY.begin(), MS_BUSY.end(), this->buffer.begin());
			this->pos = MS_BUSY.size();
		}
		this->buffer[this->pos++] = 0x00;

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

	void Set_Value(std::string str, float *value)
	{
		ans_value[str] = value;
	}

private:
	std::array <uint8_t, BUFFER_SIZE> buffer;

	std::stack <std::string> &frame;
	std::unordered_map <std::string, float*> ans_value;

	uint32_t pos;
};

}
