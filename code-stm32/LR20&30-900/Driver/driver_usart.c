#include "main.h"
#include "driver_usart.h"
/*
 * ����ȫ�ֱ���
*/
UART_HandleTypeDef husart;

/*
 *  ��������void UsartInit(uint32_t baudrate)
 *  ���������baudrate-���ڲ�����
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��USART�Ĳ����ʣ��շ�ѡ����Ч����λ��
*/
void UsartInit(uint32_t baudrate)
{
    husart.Instance         = USARTx;                  // ѡ��USART1
    husart.Init.BaudRate    = baudrate;                // ���ò�����
    husart.Init.WordLength  = USART_WORDLENGTH_8B;     // ����������ЧλΪ8bit
    husart.Init.StopBits    = USART_STOPBITS_1;        // ����һλֹͣλ
    husart.Init.Parity      = USART_PARITY_NONE;       // ����У��λ
    husart.Init.Mode        = USART_MODE_TX_RX;        // ���տɷ�
    husart.Init.HwFlowCtl   = UART_HWCONTROL_NONE;
    
    // ʹ�ÿ⺯����ʼ��USART1�Ĳ���
    if (HAL_UART_Init(&husart) != HAL_OK)
    {
        Error_Handler();
    }
    
    HAL_UART_Receive_IT(&husart,&pdata, sizeof(pdata));
}

/*
 *  ��������void HAL_USART_MspInit(USART_HandleTypeDef* husart)
 *  ���������husart-USART���
 *  �����������
 *  ����ֵ����
 *  �������ã�ʹ��USART1��ʱ�ӣ�ʹ������ʱ�ӣ����������ŵĸ��ù���
*/
void HAL_UART_MspInit(UART_HandleTypeDef* husart)
{
    // ����GPIO�ṹ�����
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(husart->Instance==USARTx)
    {
        // ʹ��USART1��ʱ��
        USARTx_CLK_EN();
        
        // ʹ��USART1������������ŵ�ʱ��
        USARTx_GPIO_CLK_EN();
        
        /**USART1 GPIO Configuration   
        PA9      ------> USART1_TX
        PA10     ------> USART1_RX
        */
        GPIO_InitStruct.Pin = USARTx_TX_PIN;            // ѡ��USART1��TX����
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;         // ����Ϊ�������칦��
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;   // ���ŷ�ת���ʿ�
        HAL_GPIO_Init(USARTx_PORT, &GPIO_InitStruct);   // ��ʼ��TX����

        GPIO_InitStruct.Pin = USARTx_RX_PIN;            // ѡ��RX����
        GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;      // ����Ϊ����
        HAL_GPIO_Init(USARTx_PORT, &GPIO_InitStruct);   // ��ʼ��RX����

        /*��ռ���ȼ�0�������ȼ�1*/
        HAL_NVIC_SetPriority(USART1_IRQn ,0,1);
        HAL_NVIC_EnableIRQ(USART1_IRQn); /*ʹ��USART1�ж�ͨ��*/
        
    }
}

/*
 *  ��������void HAL_USART_MspDeInit(USART_HandleTypeDef* husart)
 *  ���������husart-USART���
 *  �����������
 *  ����ֵ����
 *  �������ã�ʧ��USART1��ʱ�ӣ�ʧ������ʱ�ӣ�����RX/TX��������ΪĬ��״̬
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* husart)
{
    if(husart->Instance==USARTx)
    {
        USARTx_CLK_DIS();

        /**USART1 GPIO Configuration    
        PA9      ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(USARTx_PORT, USARTx_TX_PIN | USARTx_RX_PIN);
    }
} 


void Usart_SendString(uint8_t *str)
{
    unsigned int k=0;
    do {
        HAL_UART_Transmit(&husart,(uint8_t *)(str + k) ,1,1000);
        k++;
    } while (*(str + k)!='\0');
}




/*****************************************************
*function:	д�ַ��ļ�����
*param1:	������ַ�
*param2:	�ļ�ָ��
*return:	����ַ���ASCII��
******************************************************/
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&husart, (uint8_t*)&ch, 1, 10);
	return ch;
}

/*****************************************************
*function:	���ַ��ļ�����
*param1:	�ļ�ָ��
*return:	��ȡ�ַ���ASCII��
******************************************************/
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&husart, (uint8_t*)&ch, 1, 10);
    return (int)ch;
}


/*
 * ������´��룬����Ҫ�ڹ��������й�ѡUse MicroLIB
*/

#pragma import(__use_no_semihosting)
 
struct __FILE
{
	int a;
};
 
FILE __stdout;
FILE __stdin;
void _sys_exit(int x)
{
	
}
