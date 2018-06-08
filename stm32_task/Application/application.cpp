/*!
\file
\brief C++ переходник

*/

#include "application.hpp"

void (*Application_Background)(void const *argument) = &BACKGROUND_PROCESS::Task;		///< Фоновый процесс
void (*Application_Command)(void const *argument) = &COMMAND_PROCESS::Task;				///< Процесс обработчик пакетов

/*!
\brief Callback передачи USART пакетов
\details переход в C++
*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
		COMMAND_PROCESS::Answear(huart);
}

/*!
\brief Callback приема USART пакетов
\details переход в C++
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
		COMMAND_PROCESS::Command(huart);
}

/*!
\brief Callback ошибки USART пакетов
\details переход в C++
*/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
		COMMAND_PROCESS::Error(huart);
}
