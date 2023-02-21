#include "libS8.h"
#include <stdio.h>

int autoTest_m1(int icdev)
{
int st;//the state of each operation
unsigned long snr;//card serial number
unsigned char cardSt = 1;
unsigned long counter =0;

while(1)
{
	//find card
	st=fw_card(icdev,1,&snr);//find card with mode multi card
	if(st ==0)
	{ 
		cardSt = 1;
		printf("Find Card[%d]: %u\n",counter++, (unsigned int)snr);
	}
	else
	{
		if(cardSt == 1)
		{
			cardSt = 0;
			printf("NO card, put card on the reader...\n");
		}
	}
}

return st;
}


