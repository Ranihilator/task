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


/*!
\brief Класс парсер

\details
\tparam BUFFER_SIZE размер приемного буфера
\tparam QUEUE_SIZE размер очереди сообщений
*/
template <uint32_t BUFFER_SIZE, uint32_t QUEUE_SIZE>
class Parser
{

public:
	Parser(std::stack <std::string> &_frame):
		frame(_frame), pos(0)
	{}

	/*!
	\brief Тело парсера

	\details Вызывается после завершения приема данных, парсер анализирует посылку и формирует ответ в рабочем буфере.

	Если принимаемая команда совпала со списком \see Parser::ans_value ответ будет содержать переменную
	*/
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

	/*!
	\brief Изменить размер позиции в буфере
	*/
	void resize(uint32_t _size)
	{
		if (_size < this->buffer.size())
			pos = _size;
	}

	/*!
	\brief Голый указатель на буфер парсера
	\return указатель на данные
	*/
	uint8_t *data()
	{
		return static_cast<uint8_t*>(this->buffer.data());
	}

	/*!
	\brief Текущая позиция в буфере (размер реальных рабочих данных)
	\return размер
	*/
	const uint32_t size() const
	{
		return this->pos;
	}

	/*!
	\brief Емкость буфера, размер
	\return размер
	*/
	const uint32_t capacity() const
	{
		return this->buffer.size();
	}

	/*!
	\brief Очистить буфер
	*/
	void clear()
	{
		this->pos = 0;
	}

	/*!
	\brief Установить пару команду и указатель на переменную для ответной отправки
	\param[in] str - строковое представление команды
	\param[in] value - указатель на передаваемую переменную
	*/
	void Set_Value(std::string str, float *value)
	{
		ans_value[str] = value;
	}

private:
	std::array <uint8_t, BUFFER_SIZE> buffer;					///< Рабочий буфер парсера

	std::stack <std::string> &frame;							///< Сылка на очередь сообщений
	std::unordered_map <std::string, float*> ans_value;			///< Описание отвечаемых команд (переменные)

	uint32_t pos;												///< позиция рабочих байтов буфера парсера
};

}
