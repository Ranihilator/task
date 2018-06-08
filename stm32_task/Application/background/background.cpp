/*!
\file
\brief Фоновые процессы

*/

#include "background.hpp"
#include "stm32f3xx_hal.h"

#include <sstream>
#include <functional>
#include <unordered_map>

extern std::stack <std::string> queue_cmd;								/// Очередь комманд

extern TIM_HandleTypeDef htim3;											/// Таймер АЦП и ЦАП
extern uint8_t Read_Voltage;											/// Флаг о необходимости оцифровать коды АЦП
extern uint32_t ADC_Buffer[1000];										/// Буфер АЦП кодов

float Voltage;															/// Напряжение на АЦП

namespace BACKGROUND_PROCESS
{

namespace SCENARIO
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


	void LED_ON(std::string *argument)
	{
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
	}

	void LED_OFF(std::string *argument)
	{
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
	}

	void SET_ADC_SAMPLE_RATE(std::string *argument)
	{
		if (argument == nullptr)
			return;

		uint16_t value = stoi(*argument);;

		Sample_Rate(value);
	}

}

std::unordered_map <std::string, scenario> command_list =
{
		{"LED_ON", &SCENARIO::LED_ON},
		{"LED_OFF", &SCENARIO::LED_OFF},
		{"SET_ADC_SAMPLE_RATE", &SCENARIO::SET_ADC_SAMPLE_RATE}
};

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

			Read_Voltage = 0;
		}

		std::string task;

        xSemaphoreTake(CMD_SemaphoresHandle, portMAX_DELAY);

        if (!queue_cmd.empty())
        {
        	task.swap(queue_cmd.top());
        	queue_cmd.pop();
        }

        xSemaphoreGive(CMD_SemaphoresHandle);

        if (!task.empty())
        {
            std::string command;
            std::string argument;

            auto find_del = task.find(" ");

            if (find_del != std::string::npos)
            {
            	command = task.substr(0, find_del);
            	argument = task.substr(find_del);
            }
            else
            	command = std::move(task);

            auto find = command_list.find(command);

            if (find != command_list.end())
            	find->second(&argument);
        }

        osDelay(1);
	}
}

}
