#include <stdio.h>

#include "main.h"
#include "driver_usart.h"
#include "driver_spi.h"
#include "driver_key.h"
#include "driver_timer.h"
#include "driver_gpio.h"
#include "UserConfig.h"
#include "sx126x.h"

uint8_t DataLen = 0;
uint8_t pdata = 0;
uint8_t rxbuff[SIZE_DATA] = {0};

void UartTimeroutStart(void)
{

  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);      
  HAL_TIM_Base_Start_IT(&htim3);

}
void UartTimeroutStop(void)
{
//    __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);      
    HAL_TIM_Base_Stop_IT(&htim3);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    __disable_irq();  // Disable interrupts to protect the critical section
    UartTimeroutStop(); // Stop the timeout timer upon receiving a new byte
    
    // Store the received byte into the buffer and increment the data length counter
    rxbuff[DataLen++] = pdata;
    // Check if the buffer is full
    if(DataLen == SIZE_DATA)
    {
        // If the buffer is full, enqueue the data
        queueEnqueue(pUart1RxQueue, &rxbuff, DataLen);
        // Clear the buffer
        memset(rxbuff,0,SIZE_DATA);
        // Reset the data length counter
        DataLen = 0;
    }
    // Restart the timeout timer for the next byte
    UartTimeroutStart();
    // Re-enable UART reception in interrupt mode for the next byte
    HAL_UART_Receive_IT(&husart,&pdata, sizeof(pdata));

    __enable_irq();  // Re-enable interrupts
}


/**
  * @brief  Timer period elapsed callback. This function is called when the timer interrupt occurs.
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains the configuration information for the specified TIM.
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{

    // Check if the interrupt is from TIM3, which is used for UART reception timeout
    if(htim->Instance == TIM3)
    {
        // Check if any data has been received before the timeout
        if(0 != DataLen )
        {
            // If data exists, it signifies the end of a data frame. Enqueue the received data.
            queueEnqueue(pUart1RxQueue, &rxbuff, DataLen);
            // Clear the buffer
            memset(rxbuff,0,SIZE_DATA);
            // Reset the data length counter
            DataLen = 0;
        }
    }
   // Stop the timeout timer
   UartTimeroutStop();
}





/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{    
    // Initialize the HAL Library; this is the first step in any HAL-based program.
    HAL_Init();

    /*
     * Configure the system clock (AHB/APB clocks).
     * Uses the external high-speed oscillator (HSE at 8MHz) and PLL to set the system clock to 72MHz.
    */
    SystemClock_Config();

    //Initialize the UART reception queue
    UartRxQueue.front = 0;
    UartRxQueue.tail = 0;
    UartRxQueue.count = 0;
    pUart1RxQueue = (pQueue)&UartRxQueue;
  
    // 初始化USART1，设置波特率为115200 bps
    UsartInit(9600); 
    
    // 初始化定时器
    TimerInit();    
    TIM3_Init();
    // 初始化SPI
    SPI_Init();
    gpio_init();
  
    //Lora初始化
    LoraInit();
    DIO1_Init();
    printf("**********************************************\n\r");
    printf("-->Power On\n\r");
		printf("-->V1.2.35\n\r");
    printf("-->DX SX1262(LLCC68) TEST :%d %d\n\r",TEST,LORA_FRE);
    printf("**********************************************\n\r");
    ms_timer_delay(1000);    

    IrqFired = false;
    radioFlag = 0x00;
    
#if TEST
        sx126x_set_tx_cw(NULL);
#endif
    for(;;)
    {   
	    Data_Processing();
        DX_Lora_RadioIrqProcess();
    }
}

/*
 *  函数名：void Error_Handler(void)
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
*  函数作用：程序错误处理函数，此处暂时设为死循环，不做任何动作
*/
void Error_Handler(void)
{
    while(1)
    {
        printf("%s, %d\n", __FUNCTION__, __LINE__); 
    }
}
