
extern "C"
{
#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

extern void uart_div_modify(int,int);

}

uint8 kuk[] = {'A'};
void helloTask(void *pvParameters)
{
	printf("Hello\n");	
	
	struct station_config * config = (struct station_config *)zalloc(sizeof(struct station_config)); 	
	
	strcpy((char *)config->ssid, "dlink");	
	strcpy((char *)config->password, "tannetorpet107");		
	
	wifi_station_set_config(config);
	free(config);
	wifi_station_connect();
	
	while(1);
}

/*
 * This is entry point for user code
 */
extern "C"
{
	void ICACHE_FLASH_ATTR user_init(void)
	{

		portBASE_TYPE ret;
		
		// unsure what the default bit rate is, so set to a known value
		uart_div_modify(0, UART_CLK_FREQ / 115200);
		wifi_set_opmode(STATION_MODE);	
		
		xTaskHandle t;
		ret = xTaskCreate(helloTask, (const signed char *)"rx", 256, NULL, 2, &t);
		printf("xTaskCreate returns %d handle is %d\n", ret, t);
	}
}
