/*!
\file
\brief Обработчик сообщений

*/

#include "command.hpp"
#include <unordered_map>

std::stack <std::string> queue_cmd;											/// Очередь комманд
extern float Voltage;														/// Напряжение на АЦП

namespace COMMAND_PROCESS
{

Parser<RECEIVE_BUFFER_SIZE, COMMAND_QUEUE_SIZE> queue(queue_cmd);			/// Парсер сообщений
bool ready = false;															/// Готовность отправить ответ

/*!
\brief Поток обработчика сообщений
\param[in] argument аргументы
*/
void Task(void const *argument)
{
	auto huart = &huart1;
    queue.Set_Value("GET_ADC_AVG_VOLTAGE", &Voltage);

	while(1)
	{
   		if (!ready)
   		{
   			if (HAL_UART_Receive_DMA(huart, queue.data(), queue.capacity()) == HAL_OK)
   				SET_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
   		}
   		else
   		{
   	        xSemaphoreTake(CMD_SemaphoresHandle, portMAX_DELAY);

   			if (queue.work())
   			{
  				if (HAL_UART_Transmit_DMA(huart, queue.data(), queue.size()) != HAL_OK)
   					queue.clear();
   			}
   	        xSemaphoreGive(CMD_SemaphoresHandle);
    		ready = false;
    	}


		osDelay(1);
	}
}

/*!
\brief Callback приема байтов
\param[in] huart дескриптор usart
*/
void Command(UART_HandleTypeDef *huart)
{
	HAL_UART_DMAStop(huart);

	queue.resize(queue.capacity() - huart->hdmarx->Instance->CNDTR);
	ready = true;

	CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
}

/*!
\brief Callback отправки байтов
\param[in] huart дескриптор usart
*/
void Answear(UART_HandleTypeDef *huart)
{
	HAL_UART_DMAStop(huart);

	queue.clear();
}

/*!
\brief Callback сбоя usart
\param[in] huart дескриптор usart
*/
void Error(UART_HandleTypeDef *huart)
{
	if (huart->Instance->ISR & UART_FLAG_PE)
		queue.clear(); //parity error

	if (huart->Instance->ISR & UART_FLAG_FE)
		queue.clear(); //framing error

	if (huart->Instance->ISR & UART_FLAG_ORE)
		queue.clear(); //overrun error

	if (huart->Instance->ISR & UART_FLAG_NE)
		queue.clear(); //noise error

}

}


