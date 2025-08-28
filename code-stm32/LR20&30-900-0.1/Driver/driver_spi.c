#include "main.h"
#include "driver_spi.h"

/*
 * ����ȫ�ֱ���
*/
SPI_HandleTypeDef hspi;

/*
 *  ��������void SPI_Init(void)
 *  ���������
 *  �����������
 *  ����ֵ����
 *  �������ã���ʼ��SPI
*/
void SPI_Init(void)
{
  hspi.Instance               = SPIx;
  hspi.Init.Mode              = SPI_MODE_MASTER;	        // ����SPIģʽ(����ģʽ)
  hspi.Init.Direction         = SPI_DIRECTION_2LINES;       // ����SPI������ʽ(ȫ˫��)
  
  hspi.Init.DataSize          = SPI_DATASIZE_8BIT;          // �������ݸ�ʽ(8bit����)
  
  hspi.Init.CLKPolarity       = SPI_POLARITY_LOW;           // ����ʱ�Ӽ���(CPOL=0)
  
  hspi.Init.CLKPhase          = SPI_PHASE_1EDGE;            // ����ʱ����λ(CPHA=0)
  
  hspi.Init.NSS               = SPI_NSS_SOFT;	            // ����Ƭѡ��ʽ(���Ƭѡ,�Զ���GPIO)
  hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;   // ����SPIʱ�Ӳ����ʷ�Ƶ(16��Ƶ,SPI1:72/16=4.5MHz)
  hspi.Init.FirstBit          = SPI_FIRSTBIT_MSB;           // ���ô�С��ģʽ(MSB,��λ��ǰ)
  hspi.Init.TIMode            = SPI_TIMODE_DISABLE;         // ����֡��ʽ(�ر�TIģʽ)
  hspi.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE; // ����CRCУ��(�ر�CRCУ��)
  hspi.Init.CRCPolynomial     = 7;                          // ����CRCУ�����ʽ(��Χ:1~65535)

  if(HAL_SPI_Init(&hspi) != HAL_OK)
  {
      Error_Handler();
  }      
  
  __HAL_SPI_ENABLE(&hspi); 
}


/*
 *  ��������void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
 *  ���������hspi-SPI���
 *  �����������
 *  ����ֵ����
 *  �������ã�ʹ��SPI��ʱ�ӣ�ʹ������ʱ�ӣ����������ŵĸ��ù���
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    if(hspi->Instance==SPIx)
    {
        // SPI�������ʱ��ʹ��
		ICM_CS_GPIO_CLK_ENABLE();
		SPIx_SCK_GPIO_CLK_ENABLE(); 
		SPIx_MISO_GPIO_CLK_ENABLE();
		SPIx_MOSI_GPIO_CLK_ENABLE();
		
		SPIx_CLK_ENABLE(); // SPIʱ��ʹ��

		
        // SPI���Ƭѡ�������
		GPIO_InitStruct.Pin       = ICM_CS_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;      
		HAL_GPIO_Init(ICM_CS_GPIO_PORT, &GPIO_InitStruct);
		ICM_CS(1);      // CS��ʼ����


        //SCL
        GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH; 
		HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

        //MISO
	    GPIO_InitStruct.Pin       = SPIx_MISO_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH; 
		HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

        //MOSI
		GPIO_InitStruct.Pin       = SPIx_MOSI_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH; 
		HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);  
	}
}

/*
 *  ��������void SPI_WriteBytes(uint8_t *pdata, uint16_t sz)
 *  ���������pdata -> Ҫд������ָ��; sz->Ҫд���ֽڸ���
 *  �����������
 *  ����ֵ����
 *  �������ã�SPI����һ���ֽ�
*/
void SPI_WriteBytes(uint8_t *pdata, uint16_t sz)
{
    HAL_SPI_Transmit(&hspi, pdata, sz, 20);
}

/*
 *  ��������uint8_t SPI_RWOneByte(uint8_t pdata)
 *  ���������pdata -> Ҫд������
 *  ���������
 *  ����ֵ������������
 *  �������ã�SPI��дһ���ֽ�
*/
uint8_t SPI_RWOneByte(uint8_t pdata)
{
    uint8_t temp = 0;
    
    HAL_SPI_TransmitReceive(&hspi, &pdata, &temp, 1, 20);
    
    return temp;
}

/*
 *  ��������void SPI_ReadBytes(uint8_t *pdata, uint16_t sz)
 *  ���������pdata -> Ҫ��������ָ��; sz -> Ҫ�������ݸ���
 *  ���������
 *  ����ֵ��
 *  �������ã�SPI��N���ֽ�
*/
void SPI_ReadBytes(uint8_t *pdata, uint16_t sz)
{
    HAL_SPI_Receive(&hspi, pdata, sz, 20);
}
