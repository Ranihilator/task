#pragma once

#include "application.hpp"

#include "usart.h"

namespace COMMAND_PROCESS
{

void Task(void const *argument);
void Command(UART_HandleTypeDef *huart);
void Answear(UART_HandleTypeDef *huart);
void Error(UART_HandleTypeDef *huart);

}
