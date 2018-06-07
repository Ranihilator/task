/*!
\file
\brief Заголовок C++ переходника

*/

#pragma once

#include <cstdint>

#include "defines.h"

#include "background/background.hpp"
#include "command/command.hpp"
#include "parser.hpp"

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "usart.h"

extern osSemaphoreId CMD_SemaphoresHandle;			/// Элемент синхронизации

/*!
\brief список комманд
*/
enum class CMD
{
	CMD_NULL				= 0x00,					/// Пустая команда (ничего не делать)
	CMD_LED_ON				= 0x01,					/// Включить светодиод
	CMD_LED_OFF				= 0x02,					/// Выключить светодиод
	CMD_GET_ADC_AVG_VOLTAGE = 0x03,					/// Получить усредненное напряжение
	CMD_SET_ADC_SAMPLE_RATE = 0x04,					/// Установить частоту дискретизации АЦП и ЦАП

	CMD_NACK				= 0xFF					/// Неиспользуемая комманда
};
