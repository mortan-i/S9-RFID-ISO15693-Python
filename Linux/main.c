#include "libS8.h"
#include <stdio.h>

int main(int argc,char* argv[])
{
	int icdev,st,number;
	char szVer[128];
	int iNode = 0;
	char szNode[128];

	//usb port ...
	
	do
	{
		sprintf(szNode, "/dev/usb/hiddev%d", iNode);
		iNode++;
		if((icdev=fw_init_ex(2,szNode,115200))== -1)
		{
			printf("fw_init_ex ERR %d\n",icdev);
			return 0;
		}
		else
		{
			st = fw_getver(icdev, szVer);
			if(st ==0)
			{
				break;
			}
			else
			{ 
				printf("%s init error\n",szNode);
			}
		}
	}while(icdev != -1);

	
	////serila port ...
	/*
	do
	{
		sprintf(szNode, "/dev/ttyS%d", iNode);
		iNode++;
		if((icdev=fw_init_ex(1,szNode,115200))== -1)
		{
			printf("fw_init_ex ERR %d\n",icdev);
			return 0;
		}
		else
		{
			st = fw_getver(icdev, szVer);
			if(st ==0)
			{
				break;
			}
			else
			{ 
				printf("%s init error\n",szNode);
			}
		}
	}while(icdev != -1);
	*/

	printf("%s init ok\n",szNode);
       
       fw_beep(icdev,10);
         
       printf("1---Device\n");
       printf("2---MifareOne \n");
	printf("3---Mifare Card Loop Find \n");
	printf("4---Contactless-CPU \n");
	printf("5---FM12XX(1208/1216) \n");
	printf("6---Contact-CPU card \n");
	printf("7---PSAM1 \n");
	printf("8---PSAM2 \n");
	printf("9---Utralight_C \n");
	printf("10--ICODE2 \n");
	printf("0---Quit   \n");

        scanf("%d",&number);

	switch(number)
	{
	
	case 1:
		st = test_device(icdev);
		break;	
	case 2:
		st = test_m1(icdev);
		break;	
	case 3:
		st = autoTest_m1(icdev);
		break;
	case 4:
		st = contactLess_cpu_test(icdev);
		break;	
	case 5:
		st = fm12xx_test(icdev);
		break;	
	case 6:
		st = contact_cpu_test(icdev);
		break;	
	case 7:
		st = psam1_test(icdev);
		break;
	
	case 8:
		st = psam2_test(icdev);
		break;
	case 9:
		st = ultralight_c_test(icdev);
		break;
	case 10:
		st = icode2_test(icdev);
		break;
        default:
		break;
	}

       fw_exit(icdev);
       return 0; 
}
