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
extern osSemaphoreId ANS_SemaphoresHandle;

using scenario = void (*)(std::string *argument);

