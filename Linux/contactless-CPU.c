#include "libS8.h"
#include <stdio.h>
#include <string.h>

int contactLess_cpu_test(int icdev)
{
int st,i;//the state of each operation
unsigned long sn;
unsigned int rlen;
unsigned char cmd_1[17]={0x00,0x84,0x00,0x00,0x08};//the buffer to write a block
unsigned char rdata[1024];//the buffer read from a block
unsigned char showData[34]={0};//hex type data
unsigned char	tt= 7,fg= 255;//56;
unsigned char buf_cmd_src1[]={0x00,0xA4,0x04,0x00,0x08,0xA0,0x00,0x00,0x03,0x33,0x01,0x01,0x01};
unsigned char buf_cmd_src2[]={0x80,0xA8,0x00,0x00,0x23,0x83,0x21,0x36,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00
,0x00,0x01,0x01,0x56,0x00,0x00,0x00,0x00,0x00,0x01,0x56,0x14,0x12,0x31,0x01,0x11,0x22,0x33,0x55};
unsigned int cmdLen;




//device reset
st = fw_reset(icdev,10);
if(st)
{
	printf("ERROR(%d): Device reset failed.\n",st);
	goto EXIT;
}
printf("Device reset OK.\n");

//find card
st = fw_card(icdev,1,&sn);
if(st )
{
	printf("ERROR(%d):Find No card.\n",st);
	goto EXIT;
}
printf("Find Card: %u.\n",sn);

//card reset
st = fw_pro_reset(icdev,(unsigned char*)&rlen,rdata);
if(st)
{
	printf("ERROR(%d): Card reset failed.\n",st);
	goto EXIT;
} 
printf("Reset info: ");
for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
printf("\n");

//command test
memset(rdata,0,sizeof(rdata));
cmdLen = sizeof(buf_cmd_src1);
printf("sent data: ");
for(i=0; i<cmdLen; i++) printf("%02X",buf_cmd_src1[i]);
printf("\n");

st = fw_pro_commandlink(icdev,cmdLen,buf_cmd_src1,&rlen,rdata,tt,fg);
if(st)
{
	printf("ERROR(%d): Command failed.\n",st);
	goto EXIT;
}
printf("Returned Info: ");
for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
printf("\n");

memset(rdata,0,sizeof(rdata));
cmdLen = sizeof(buf_cmd_src2);
printf("sent data: ");
for(i=0; i<cmdLen; i++) printf("%02X",buf_cmd_src2[i]);
printf("\n");

st = fw_pro_commandlink(icdev,cmdLen,buf_cmd_src2,&rlen,rdata,tt,fg);
if(st)
{
	printf("ERROR(%d): Command failed.\n",st);
	goto EXIT;
}
printf("Returned Info: ");
for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
printf("\n");
			

EXIT:

return st;
}
