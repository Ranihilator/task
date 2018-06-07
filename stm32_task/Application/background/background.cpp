/*!
\file
\brief Фоновые процессы

*/

#include "background.hpp"
#include "stm32f3xx_hal.h"

extern std::stack <std::vector<uint8_t>> queue_cmd;						/// Очередь комманд
extern TIM_HandleTypeDef htim3;											/// Таймер АЦП и ЦАП
extern uint8_t Read_Voltage;											/// Флаг о необходимости оцифровать коды АЦП
extern uint32_t ADC_Buffer[1000];										/// Буфер АЦП кодов

float Voltage;															/// Напряжение на АЦП
float Temperature;														/// Температура аналогового датчика

namespace BACKGROUND_PROCESS
{

/*!
\file
\brief Изменения частоты дискретизации АЦП И ЦАП

*/
bool Sample_Rate(uint16_t frequency)
{
	const uint16_t min = 100;
	const uint16_t max = 1000;

	if (frequency <= min)
		frequency = min;

	if (frequency >= max)
		frequency = max;

	auto unscale = [](float data, float x_max, float x_min, float y_max, float y_min)
	{
		float A = (y_max - y_min) / (x_max - x_min);
		float B = (y_min * x_max - y_max * x_min) / (x_max - x_min);
		float res = A * data + B;

		return res;
	};

	float per = unscale (frequency, 1000, 100, 999, 9999);

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 48;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = per;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
		return false;

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
		return false;

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
		return false;

	if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK)
		return false;

	return true;
}

/*!
\file
\brief поток фоновых процессов
\param[in] argument аргументы

*/
void Task(void const *argument)
{
	while(1)
	{

		if (Read_Voltage)
		{
			float ADC = ADC_Buffer[0];
			for (uint32_t i = 1; i < 1000; i++)
			{
				ADC = (ADC + ADC_Buffer[i]) / 2;
			}

			Voltage = ADC * 0.000732421875;
			Temperature = (1.43-Voltage)/0.0043+25.0;

			Read_Voltage = 0;
		}

		std::vector<uint8_t> task;

        xSemaphoreTake(CMD_SemaphoresHandle, portMAX_DELAY);

        if (!queue_cmd.empty())
        {
        	task = queue_cmd.top();
        	queue_cmd.pop();
        }

        xSemaphoreGive(CMD_SemaphoresHandle);

        if (!task.empty())
        {
        	switch (static_cast<CMD>(task[0]))
        	{
				case CMD::CMD_LED_ON:
				{
					HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
					break;
				}
				case CMD::CMD_LED_OFF:
				{
					HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
					break;
				}
				case CMD::CMD_GET_ADC_AVG_VOLTAGE:
				{
					break;
				}
				case CMD::CMD_SET_ADC_SAMPLE_RATE:
				{
					if (task.size() == 3)
					{
						uint16_t value;

						value = task[1]<<8;
						value |= task[2];

						Sample_Rate(value);
					}
					break;
				}

				default:
				{}
        	}
        	task.clear();
        }

        osDelay(1);
	}
}

}
