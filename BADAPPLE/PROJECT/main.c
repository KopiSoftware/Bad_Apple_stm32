#include "OLED_I2C.h"
#include "delay.h"
#include "stm32f10x.h"
#include "ff.h"  
#include "exfuns.h" 
#include "sdio_sdcard.h"  
#include "usart.h" 
#include "sys.h"
#include "stm32f10x_sdio.h"
#include "misc.h"

FIL fil;
FRESULT res;
UINT bww;
int xin,yin=6;
unsigned char bmp[84*6];


int main(void)
{
	
	delay_init(72);
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	I2C_Configuration();
	OLED_Init();
	
//--------------------------------------SD initialize
	while(SD_Init())
	{
	printf("SD Card Error!\n");					
	printf("Please Check!\n");
	delay_ms(1000);
	}
//--------------------------------------mount SD 	
	exfuns_init();						 
	f_mount(fs[0],"0:",1); 		
	res=f_open (&fil,"0:/Bad_Apple.bin", FA_READ);		
	OLED_Fill(0x00);//全屏灭
	//f_read (&fil, bmp,128*8,&bww);
	
	
	while(1){
			f_read (&fil, bmp,84*yin,&bww);
			OLED_DrawBMP(21,0,105,yin,(unsigned char *)bmp);
	}
	
}
