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

extern osSemaphoreId CMD_SemaphoresHandle;

enum class CMD
{
	CMD_NULL				= 0x00,
	CMD_LED_ON				= 0x01,
	CMD_LED_OFF				= 0x02,
	CMD_GET_ADC_AVG_VOLTAGE = 0x03,
	CMD_SET_ADC_SAMPLE_RATE = 0x04,

	CMD_NACK				= 0xFF
};

enum class ACK
{
	ACK_OK					= 0x00,
	ACK_BUSY				= 0x01,

	NACK					= 0xFF
};
