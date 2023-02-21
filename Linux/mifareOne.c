#include "libS8.h"
#include <stdio.h>

int test_m1(int icdev)
{
int st;//the state of each operation
unsigned long snr;//card serial number
unsigned long value;
unsigned char keybuf[7]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char wdata[17]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0xaa,0xbb,0xcc,0xdd,0xee,0xff};//the buffer to write a block
unsigned char rdata[17];//the buffer read from a block
unsigned char showData[34]={0};//hex type data
unsigned char sec=3;//sector to operation
unsigned char block=12;//the block to write/read

//load key 
st=fw_load_key(icdev,0,sec,keybuf);//load keyA 
if(st)
{
 printf("Load Key Error!%d\n",st);
 goto EXIT;
}
printf("Load Key ok!\n");

//find card
st=fw_card(icdev,1,&snr);//find card with mode multi card
if(st)
{
 printf("Find Card Error!%d\n",st);
 goto EXIT;
}
printf("Hava Card!\n");
printf("The Card Serial Number is: %u\n",(unsigned int)snr);


//authenication 
st=fw_authentication(icdev,0,sec);
if(st)
{
 printf("Authenicate Error!%d\n",st);
 goto EXIT;
}
printf("Authenicate ok!\n");

/// write block
st=fw_write(icdev,block,wdata);
if(st)
{
 printf("Write Block Data Error!%d\n",st);
 goto EXIT;
}
printf("Write Data To Block Ok!\n");

//Read block data
st=fw_read(icdev,block,rdata);
if(st)
{
 printf("Read Block Data Error!%d\n",st);
 goto EXIT;
}
hex_a(showData,rdata,32);
printf("Read Block %d Ok!The Data Is:%s\n",block,showData);

///////////////////////////
// Value operation
//////////////////////////
//Init value

st=fw_initval(icdev,block,1000);//init value 1000
if(st)
{
 printf("Initial Block %d With Value 1000 Error!%d \n",block,st);
 goto EXIT;
}
printf("Initial Block %d With Value 1000 Ok!\n",block);

//st=fw_card(icdev,1,&snr);
//st=fw_authentication(icdev,0,sec);

//increment value
st=fw_increment(icdev,block,200)||fw_transfer(icdev,block);//call transfer after increment
if(st)
{
 printf("Increment Value 200 Error!%d\n",st);
 goto EXIT;
}
printf("Increment Value 200 Ok!\n");

//decrement value
st=fw_decrement(icdev,block,100)||fw_transfer(icdev,block);//call transfer after decrement
if(st)
{
 printf("Decrement Value Error!%d\n",st);
 goto EXIT;
}

printf("Decrement Value 100 OK!\n");

//read value
st=fw_readval(icdev,block,&value);
if(st)
{
 printf("Read Value Error!%d\n",st);
 goto EXIT;
}
printf("Read Value Ok!\n");
printf("The Value Of Block %d is:%u\n",block,(unsigned int)value);

/////////////////////////////
// Change key
////////////////////////////
unsigned char newkeya[7]={0x11,0x22,0x33,0x44,0x55,0x66};
unsigned char ctrl[5]={0xff,0x07,0x80,0x69};
unsigned char keyb[7]={0xff,0xff,0xff,0xff,0xff,0xff};
st=fw_changeb3(icdev,sec,newkeya,ctrl,0,keyb);
if(st)
{
 printf("Change Key Error!%d\n",st);
 goto EXIT;
}
printf("Key Be Changed To 112233445566 OK \n");

//change key back to ffffffffffff
st=fw_load_key(icdev,0,sec,newkeya);//load key with 112233445566
if(st)
{
  printf("load key 112233445566 Error!%d\n",st);
  goto EXIT;
}
st=fw_authentication(icdev,0,sec);
if(st)
{
 printf("Authenticate sector %d Error!%d\n",sec,st);
 goto EXIT;
}
st=fw_changeb3(icdev,sec,keybuf,ctrl,0,keyb);
if(st)
{
 printf("Key Be Changed Back To ffffffffffff Error!%d\n",st);
 goto EXIT;
}
printf("Key Be Changed Back To ffffffffffff OK!\n");

EXIT:

return st;
}
