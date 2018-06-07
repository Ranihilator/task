/*!
\file
\brief C++ переходник

*/

#include "application.hpp"

void (*Application_Background)(void const *argument) = &BACKGROUND_PROCESS::Task;
void (*Application_Command)(void const *argument) = &COMMAND_PROCESS::Task;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
		COMMAND_PROCESS::Answear(huart);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
		COMMAND_PROCESS::Command(huart);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
		COMMAND_PROCESS::Error(huart);
}
