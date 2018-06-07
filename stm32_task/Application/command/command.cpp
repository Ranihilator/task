#include "command.hpp"

std::stack <std::vector<uint8_t>> queue_cmd;

namespace COMMAND_PROCESS
{

Parser<256> queue(queue_cmd);

bool ready = false;
void Task(void const *argument)
{
	auto huart = &huart1;

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

void Command(UART_HandleTypeDef *huart)
{
	HAL_UART_DMAStop(huart);

	queue.resize(queue.capacity() - huart->hdmarx->Instance->CNDTR);
	ready = true;

	CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
}

void Answear(UART_HandleTypeDef *huart)
{
	HAL_UART_DMAStop(huart);

	queue.clear();
}

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


