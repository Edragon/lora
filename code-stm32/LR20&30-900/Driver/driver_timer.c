#include "main.h"
#include "driver_timer.h"

/*
 * ����ȫ�ֱ���
*/
TIM_HandleTypeDef htim;
TIM_HandleTypeDef htim3;

/*
 *  ��������void TimerInit(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ����ʱ����ʹ��ʱ��Ƶ��Ϊ4MHz
*/
void TimerInit(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
  
    htim.Instance               = TIM2;
    htim.Init.Prescaler         = 72-1;                             // HCLK = 72MHz, 72MHz/72 = 1MHz
    htim.Init.Period            = 0;                                // ��ÿ1us�������һ��
    htim.Init.CounterMode       = TIM_COUNTERMODE_UP;               // ���ϼ��������������е����ã�
                                                                    // ÿ1MHz��1us�����ϼ���1�Σ�������4�λ�������ʱ���жϻ��������¼�
    htim.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           // ��ʱ��ʱ�Ӳ���HCLK��Ƶ
    htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;   // ������װ�ػ���װ��
    
    // ��ʼ������Ĳ���
    if (HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;    // ѡ���ڲ�ʱ����Ϊ��ʱ��ʱ��Դ
    if (HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;           // ��������λ�����������¼�
    sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;  // ����ģʽ��ʹ��
    if (HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/*
 *  ��������void us_timer_delay(uint16_t t)
 *  ���������t-��ʱʱ��us
 *  �����������
 *  ����ֵ����
 *  �������ã���ʱ��ʵ�ֵ���ʱ��������ʱʱ��Ϊt us��Ϊ������ʱ�䣬������ʹ�üĴ����������û��ɶ����ֲ�鿴ÿ���Ĵ���ÿһλ������
*/
void us_timer_delay(uint16_t t)
{
    uint16_t counter = 0;
	__HAL_TIM_SET_AUTORELOAD(&htim, t);		
	__HAL_TIM_SET_COUNTER(&htim, counter);
	HAL_TIM_Base_Start(&htim);
	while(counter != t)
	{
		counter = __HAL_TIM_GET_COUNTER(&htim);
	}
	HAL_TIM_Base_Stop(&htim);
}



void ms_timer_delay(uint16_t t)
{
    do{
        us_timer_delay(1000);
    }while (t--);
}




 
/* TIM3 init function */
void TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
 
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 3600;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 5 * 20;//5 = 2.5ms
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
 
}
 

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{

    if(htim->Instance==TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
    }
    
    if(htim->Instance==TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM3_IRQn, 2, 1);
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }
    
}


