#ifndef __DRIVER_SPI_H
#define __DRIVER_SPI_H

#include "stm32f1xx_hal.h"
#include "driver_timer.h"
#include "UserConfig.h"



/************************* SPI Ӳ����ض��� *************************/
#define SPIx                             SPI1
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 
#define ICM_CS_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE() 

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()


#define ICM_CS_PIN                       LCC68_NSS_PIN               
#define ICM_CS_GPIO_PORT                 LCC68_NSS_PORT  

#define SPIx_SCK_PIN                     LCC68_SCK_PIN
#define SPIx_SCK_GPIO_PORT               LCC68_SCK_PORT

#define SPIx_MISO_PIN                    LCC68_MISO_PIN
#define SPIx_MISO_GPIO_PORT              LCC68_MISO_PORT

#define SPIx_MOSI_PIN                    LCC68_MOSI_PIN
#define SPIx_MOSI_GPIO_PORT              LCC68_MOSI_PORT 




                                  
#define ICM_CS(level)                    {HAL_GPIO_WritePin(ICM_CS_GPIO_PORT, ICM_CS_PIN, level?GPIO_PIN_SET:GPIO_PIN_RESET);us_timer_delay(10);}
/************************* SPI Ӳ����ض������ *************************/
/*
 *  ��������void SPI_Init(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��SPI
*/
extern void SPI_Init(void);

/*
 *  ��������uint8_t SPI_RWOneByte(uint8_t pdata)
 *  ���������pdata -> Ҫд������
 *  ���������
 *  ����ֵ������������
 *  �������ã�SPI��дһ���ֽ�
*/
extern uint8_t SPI_RWOneByte(uint8_t pdata);

/*
 *  ��������void SPI_WriteBytes(uint8_t *pdata, uint16_t sz)
 *  ���������pdata -> Ҫд������ָ��; sz->Ҫд���ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã�SPI����һ���ֽ�
*/
extern void SPI_WriteBytes(uint8_t *pdata, uint16_t sz);

/*
 *  ��������void SPI_ReadBytes(uint8_t *pdata, uint16_t sz)
 *  ���������pdata -> Ҫ��������ָ��; sz -> Ҫ�������ݸ���
 *  ���������
 *  ����ֵ��
 *  �������ã�SPI��N���ֽ�
*/
extern void SPI_ReadBytes(uint8_t *pdata, uint16_t sz);



extern SPI_HandleTypeDef hspi;


#endif  //__DRIVER_SPI_H
