* ��������Keil uVision5
* ������Ϣ��
	Core: ��SDK��ȡ�ĺ����ļ��������޸ģ�
	Driver: �û���д�����������ļ���
	LR_driver��lora(LLCC68,SX1262����)��Ƶ�����ļ�����ǰΪSemtech��������
	Main: �������ļ����������ļ���
	Project: �����ļ�������Ŀ��������ļ���
	queue:���ļ�Ϊ����spi�ӿڣ����·�������ü��ɵ��ã�demo����UART�����ݴ���
	SDK: CMSIS��HAL�⣬ֻ�����õ��Ŀ⣬�������������Ҫ�����Ӧ�⣻

	Readme.txt: ����˵���ļ���

* ����˵����
	��ǰ�ļ�Ϊ�򵥵�(LLCC68,SX1262����) demoʹ�ð�������¼����ʹ�ã�Ŀǰʹ�õĿ���ICΪ STM32F103C8T6
	
* ע�⣺
	������ʾ��ֻ����˴����õ���STM32 HAL�⣬�û�������������蹦��ʱ����Ҫ�����Ӧ��HAL�����ʹ�ù���ģ�壨��������HAL�⣩
	������ʾ��ֻ�ṩ����(LLCC68,SX1262����) Lora��Ƶģ���������һ�����������޷��������еĹ��ܶ�ʵ�֣�����ʵ����Ҫ�Լ����
	������ʾ��Ϊ�˷�����ֲ�����ļ���LR_driver�����ļ�δ�����κ��޸ģ������������ļ����readme�޸�����������º���
	The HAL (Hardware Abstraction Layer) is a collection of functions the user shall implement to write platform-dependant calls to the host. The list of functions is the following:
	- sx126x_hal_reset
	- sx126x_hal_wakeup
	- sx126x_hal_write
	- sx126x_hal_read