#include "libS8.h"
#include <stdio.h>

int test_device(int icdev)
{
	int st;//the state of each operation
	unsigned char rdata[1024];
	unsigned char wdata[1024];
	int rwlen = 200;
	int i;

	for(i=0; i< rwlen; i++) wdata[i] = 1+i;

	st = fw_swr_eeprom(icdev, 0, rwlen, wdata);
	if(st)
	{
		printf("fw_swr_eeprom error:0x%x\n", st);
		goto DO_EXIT;
	}

	st =fw_srd_eeprom(icdev, 0, rwlen, rdata);
	if(st)
	{
		printf("fw_srd_eep error:0x%x\n",st);
		goto DO_EXIT;
	}
	printf("fw_srd_eep ok\n");

	for(i=0; i<rwlen; i++)
		printf("%02X ", rdata[i]);
	printf("\n");
	

	//st = fw_lcd_dispclear(icdev);
	//if(st)printf("fw_lcd_dispclear error:0x%x\n",st);

	//st = fw_lcd_dispstr(icdev, L"字符串测试123ab完毕", 1);
	//if(st)printf("fw_lcd_dispstr error:0x%x\n",st);
DO_EXIT:
	return st;
}
