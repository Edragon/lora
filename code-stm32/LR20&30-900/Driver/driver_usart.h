#ifndef __DRIVER_USART_H
#define __DRIVER_USART_H

#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "UserConfig.h"









/*********************
 * ���ź궨��
**********************/
#define USARTx                  USART1
#define USARTx_TX_PIN           LOG_UART_TX_PIN
#define USARTx_RX_PIN           LOG_UART_RX_PIN
#define USARTx_PORT             GPIOA
#define USARTx_GPIO_CLK_EN()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_CLK_EN()         __HAL_RCC_USART1_CLK_ENABLE()
#define USARTx_CLK_DIS()        __HAL_RCC_USART1_CLK_DISABLE()

/*********************
 * �����궨��
**********************/

/*********************
 * ȫ�ֱ�������
**********************/
extern UART_HandleTypeDef husart;

/*********************
 * ���⺯��API
**********************/

/*
 *  ��������void UsartInit(uint32_t baudrate)
 *  ���������baudrate-���ڲ�����
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��USART�Ĳ����ʣ��շ�ѡ����Ч����λ��
*/
extern void UsartInit(uint32_t baudrate);

extern void Usart_SendString(uint8_t *str);



#endif

