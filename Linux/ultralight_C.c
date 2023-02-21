#include "libS8.h"
#include <stdio.h>
#include <string.h>

int ultralight_c_test(int icdev)
{
	int status,i;//the state of each operation
	unsigned long sn, snr2;
	unsigned char rlen;
	unsigned char ucKey[]={0x49,0x45,0x4D,0x4B,0x41,0x45,0x52,0x42,0x21,0x4E,0x41,0x43,0x55,0x4F,0x59,0x46};//the buffer to write a block
	unsigned char rdata[128];//the buffer read from a block
	unsigned char showData[34]={0};//hex type data
       char pWriteBuffer[1024];
      	short lenToRW;
	int page = 8;

	for(i=0; i< 4; i++) pWriteBuffer[i] = i+3;

	//find card
	status = fw_card(icdev,1,&sn);
	if(status )
	{
		printf("ERROR(%d):Find No card.\n",status);
		goto EXIT;
	}
	printf("Find Card: %u.\n",sn);


	status = fw_anticoll2(icdev, 0, &snr2);
	if(status)
	{
		printf("Find Invalid Card.\n");
		goto EXIT;
	}

	status = fw_select2(icdev, snr2);
	if(status)
	{
		printf("Select card error.\n");
		goto EXIT;
	}

	status = fw_ultralt_C_authen(icdev,ucKey);
	if(status)
	{
		printf("Authen Key error\n");
		goto EXIT;
	}
	else
	{
		printf("Authen Key OK\n");
	}
	
	//write
	status = fw_write_ultralt(icdev, page, pWriteBuffer);
	if(status)
	{
		printf("Write Data Error\n");
		goto EXIT;
	}
	else
		printf("Write Data OK.\n");


	//read
	status = fw_read_ultralt(icdev, page, rdata);
	if(status)
	{
		printf("Read Error\n");
		goto EXIT;
	}

	printf("Read OK\n");

	hex_a(showData, rdata, 8);

	printf("data: %s\n", showData);
	

EXIT:
	return status;
}
