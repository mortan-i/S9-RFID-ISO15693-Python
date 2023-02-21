#include "libS8.h"
#include <stdio.h>
#include <string.h>

int psam1_test(int icdev)
{
int st,i;//the state of each operation
unsigned long sn;
unsigned char rlen;
unsigned char cmd_1[]={0x00,0x84,0x00,0x00,0x08};//the buffer to write a block
unsigned char rdata[1024];//the buffer read from a block
unsigned char showData[34]={0};//hex type data
unsigned char cmdLen;


//set card sheet
st = fw_setcpu(icdev, 0x0D); //0x0d -> SAM1
if(st != 0)
{
	printf("ERROR(%02x): slect cpu card sheet failed.\n", st);
	goto EXIT;
}

//card reset
st = fw_cpureset(icdev,&rlen,rdata);
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
cmdLen = sizeof(cmd_1);
printf("sent data: ");
for(i=0; i<cmdLen; i++) printf("%02X",cmd_1[i]);
printf("\n");

st = fw_cpuapdu(icdev,cmdLen,cmd_1,&rlen,rdata);
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
