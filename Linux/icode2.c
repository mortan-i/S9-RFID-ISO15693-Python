#include "libS8.h"
#include <stdio.h>
#include <string.h>

int icode2_test(int icdev)
{
	int st;
	unsigned char rlen[17]={0};
	unsigned char rbuffer[256];
	unsigned char szCardSn[512] ={0};
	unsigned char UID[16];
	unsigned char m_StaAddr = 12;
	unsigned char m_Blockno = 1;
	unsigned char tmp[256];
	int i;

	fw_config_card(icdev, 0x31);

	st= fw_inventory(icdev,0x36,0,0,rlen,rbuffer);        //find single card
	if(st) 
	{
		printf("Find single card ERROR!\n");
		return 0;
	}

	hex_a(szCardSn, &rbuffer[0], 2* rlen[0]);

	printf("Find card %s \n", (char *)szCardSn);

	memcpy(UID,(char*)&rbuffer[0], 8);


	st=fw_select_uid(icdev,0x22,&UID[0]);
	if(st)
	{
		printf("fw_select_uid ERROR!\n");
		return 0;
	}

    	st=fw_reset_to_ready(icdev,0x22,&UID[0]);
    	if(st)
	{
		printf("fw_reset_to_ready ERROR!\n");
		return 0;
	}

 
	st = fw_get_securityinfo(icdev,0x22,0x04,0x02, &UID[0],rlen,rbuffer);
	if(st)
	{
		printf("fw_get_securityinfo ERROR!\n");
		return 0;
	}

	st=fw_readblock(icdev,0x22,m_StaAddr,m_Blockno,&UID[0],rlen,rbuffer);  //read block data
	if(st)
	{
		printf("Read data ERROR! \n");
		return 0;
	}
	
	for(i=0;i<m_Blockno;i++)
	{
		sprintf((char *)tmp,"BlockAddr:[%2d] Data:[%02X %02X %02X %02X]",m_StaAddr+i,rbuffer[i*4],rbuffer[i*4+1],rbuffer[i*4+2],rbuffer[i*4+3]);
		printf("%s\n", (const char *)tmp);
	}


	return 0;
}






