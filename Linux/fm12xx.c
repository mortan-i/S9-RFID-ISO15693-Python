#include "libS8.h"
#include "_fm1208.h"
#include <stdio.h>
#include <string.h>

int fm12xx_test(int icdev)
{
int status,i;//the state of each operation
unsigned long sn;
unsigned int rlen;
unsigned char cmd_1[17]={0x00,0x84,0x00,0x00,0x08};//the buffer to write a block
unsigned char rdata[1024];//the buffer read from a block
unsigned char showData[34]={0};//hex type data
unsigned char	tt= 7,fg= 56;
        int pval[1];
        char pChVal[2];
        char pRBuffer[1024];
      	short lenToRW;
      	char pWriteBuffer[1024];

        char pShowBuf[1024];
        
        char pExKey []={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//外部认证密钥
		char pFileProKey[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};//文件保护密钥
		char pPurchaseKey[]={0x20,0x28,0x9d,0x08,0x52,0xc9,0x61,0x60,0x5b,0x92,0xb6,0x07,0xca,0xa3,0xcc,0xd9};//消费密钥
		char pCreditKey[] ={0xda,0x40,0x4f,0x59,0xe9,0xf7,0x30,0x05,0xa8,0xb9,0x79,0x35,0x73,0xa8,0xbd,0x92};//圈存密钥
		char pPin[] = {0x11,0x22,0x33,0x44,0x55,0x66};
		char pTerminal[] = {0x00,0x00,0x00,0x00,0x00,0x01};//6字节（固定）的终端机编号
		char pDirName []= {'a',' ','T','e','s','t',' ','D','i','r'};

	lenToRW = 0x54;//strlen(pWriteBuffer);//max len is 57(0x39),why???
	for(i=0; i< lenToRW; i++) pWriteBuffer[i] = i+3;

//device reset
status = fw_reset(icdev,10);
if(status)
{
	printf("ERROR(%d): Device reset failed.\n",status);
	goto EXIT;
}
printf("Device reset OK.\n");

//find card
status = fw_card(icdev,1,&sn);
if(status )
{
	printf("ERROR(%d):Find No card.\n",status);
	goto EXIT;
}
printf("Find Card: %u.\n",sn);

//card reset
status = fw_pro_reset(icdev,(unsigned char*)&rlen,rdata);
if(status)
{
	printf("ERROR(%d): Card reset failed.\n",status);
	goto EXIT;
} 
printf("Reset info: ");
for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
printf("\n");

//command test
memset(rdata,0,sizeof(rdata));

status = fw_pro_commandlink(icdev,5,cmd_1,&rlen,rdata,tt,fg);
if(status)
{
	printf("ERROR(%d): Command failed.\n",status);
	goto EXIT;
}
printf("Returned Info: ");
for(i=0; i<rlen; i++) printf("%02X",rdata[i]);
printf("\n");

			//选择主应用
            status = FWCosSelecteApp(icdev);
            if (status != 0) {
                printf("FWCosSelecteApp error!\n");
                fw_exit((int)icdev);//断开连接
                goto EXIT;
            } else {
                printf("FWCosSelecteApp ok!\n");
            }
            
			//建立一个密钥文件，用于存放各种密钥
            status = FWCosCreateKeyFile(icdev, 
            	(short)0x0000,//所在目录文件标识,主应用为0
            	(short)0x0001,//密钥文件标识符
            	(short)0x0040,//密钥文件的长度
            	0);//在密钥中安装密钥的权限,为0表示可以任意安装密钥
            if (status != 0) {
                printf("FWCosCreateKeyFile error!\n");
                printf("%d",status);
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosCreateKeyFile ok!\n");
            }
            
           	//安装外部认证密钥
            status = FWCosAddKey(icdev, 
            	(char)2,//外部认证密钥类型
            	pExKey,//密钥值
            	16);//密钥文件长度
            if (status != 0) {
                printf("FWCosAddKey[ExKey] error!\n");
                printf("%d",status);
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosAddKey[ExKey] ok!\n");
            }
            
           	//安装文件保护密钥
            status = FWCosAddKey(icdev, 
            	(char)1,//文件保护密钥类型
            	pFileProKey,//密钥值
            	16);//密钥文件长度
            if (status != 0) {
                printf("FWCosAddKey[FileProKey] error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//验证外部认证密钥
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosAddKey[FileProKey] ok!\n");
            }
            
           	//安装口令
            status = FWCosAddKey(icdev, 
            	(char)3,//口令密钥类型
            	pPin,//口令值
            	6);//口令长度
            if (status != 0) {
                printf("FWCosAddKey[Pin] error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//验证外部认证密钥
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosAddKey[Pin] ok!\n");
            }
            
           	//建立一个二进制一般文件
            status = FWCosCreateBinaryFile(icdev, 
            	(short)0x0000,//当前所在目录标识
            	(short)0x0002,//要建的文件标识
            	(short)0x0200,//文件长度
            	(char)1,//数据加密类型：0-明文方式,1-明文+MAC校验，2-密文+MAC校验
            	0,//读不需密码
            	1,//更新需要口令验证 (1级)
            	0);//删除不需密钥(此参数一般无效)
            if (status != 0) {
                printf("FWCosCreateBinaryFile error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosCreateBinaryFile ok!\n");
            }
            

           	//验证口令
            status = FWCosVerifyKey(icdev, 
            	pPin,//口令
            	6,//口令长度
            	(char)3);//口令类型
            if (status != 0) {
                printf("FWCosVerifyKey error!\n");
                printf("%X\n",status);
                FWCosSelecteApp(icdev);
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosVerifyKey ok!\n");
            }
            
           	//写(更新)二进制一般文件
            status = FWCosUpdateBinaryFile(icdev, 
            	(short)0x0002,//文件标识
            	(short)0x00,//开始偏移地址
            	pWriteBuffer,//数据值
            	(short)lenToRW,//数据长度
            	(char)1,//数据加密类型：0-明文方式,1-明文+MAC校验，2-密文+MAC校验
            	pFileProKey,//文件保护密钥
            	16);//密钥长度
            if (status != 0) {
                printf("FWCosUpdateBinaryFile error!\n");
                printf("%X\n",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosUpdateBinaryFile ok!\n");
            }
            
           	//读二进制一般文件
            status = FWCosReadBinaryFile(icdev, 
            	(short)0x0002,//文件标识
            	pRBuffer,
            	(short)0x00,//开始偏移地址
            	(short)lenToRW,//数据长度
            	(char)1,//数据加密类型：0-明文方式,1-明文+MAC校验，2-密文+MAC校验
            	pFileProKey,//文件保护密钥
            	16);//密钥长度
            if (status != 0) {
                printf("FWCosReadBinaryFile error!\n");
                printf("%X\n",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosReadBinaryFile ok!\n");
                
               // printf("%s\n",pRBuffer);
		for(i=0; i<lenToRW; i++) printf("%02X",pRBuffer[i]);
		printf("\n");
            }
            
            //***********************************************************************///
            //      值操作 
            //**************************************************************************//
			//创建金融目录
            status = FWCosCreateADF(icdev,
            	(short)0xDF01,//文件标识
            	(long)0,//在该目录下建立文件的权限，不需验证密钥
            	(long)0,//在该目录下删除文件的权限，不需验证密钥
            	pDirName,//名称
            	(char)10);//长度
            if (status != 0) {
                printf("FWCosCreateADF error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("\rFWCosCreateADF ok!\n");
            }
            
           	//安装外部认证密钥
            status = FWCosAddKey(icdev, 
            	(char)2,//外部认证密钥类型
            	pExKey,//密钥值
            	16);//密钥文件长度
            if (status != 0) {
                printf("FWCosAddKey[ExKey] error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosAddKey[ExKey] ok!\n");
            }
            
           	//安装口令
            status = FWCosAddKey(icdev, 
            	(char)3,//口令密钥类型
            	pPin,//口令值
            	6);//口令长度
            if (status != 0) {
                printf("FWCosAddKey[Pin] error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosAddKey[Pin] ok!\n");
            }
            
           	//安装消费密钥
            status = FWCosAddKey(icdev, 
            	(char)7,//消费密钥类型
            	pPurchaseKey,//密钥值
            	16);//密钥长度
            if (status != 0) {
                printf("FWCosAddKey[Purchase] error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证 
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosAddKey[Purchase] ok!\n");
            }
            
           	//安装圈存密钥
            status = FWCosAddKey(icdev, 
            	(char)5,//圈存密钥类型
            	pCreditKey,//密钥值
            	16);//密钥长度
            if (status != 0) {
                printf("FWCosAddKey[Credit] error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosAddKey[Credit] ok!\n");
            }
            
           	//验证口令
            status = FWCosVerifyKey(icdev, 
            	pPin,//口令
            	6,//口令长度
            	(char)3);//口令类型
            if (status != 0) {
                printf("FWCosVerifyKey error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosVerifyKey ok!\n");
            }
            
           	//圈存（存款）
            status = FWCosCredit(icdev,
            	(char)0x00,//圈存密钥标识，这里要设为0
            	100000,//金额
            	pTerminal,//终端号
            	pCreditKey,//圈存密钥
            	(long)16);//密钥长度
            if (status != 0) {
                printf("FWCosCredit error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosCredit ok!\n");
            }
            
           	//消费
            status = FWCosPurchase(icdev,
            	(char)0x01,//消费密钥标识，这里要设为1
            	50,//金额
            	pTerminal,//终端号
            	pPurchaseKey,//消费密钥
            	(long)16);//密钥长度
            if (status != 0) {
                printf("FWCosPurchase error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosPurchase ok!\n");
            }
            
           	//查询当前余额
            status = FWCosGetBalance(icdev,
            	pval);//密钥长度
            if (status != 0) {
                printf("FWCosGetBalance error!\n");
                printf("%d",status);
                FWCosSelecteApp(icdev);
                FWCosVerifyKey(icdev, pExKey,16,(char)2);//外部认证
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接
                goto EXIT;

            } else {
                printf("FWCosGetBalance ok!\n");
                printf("balance:%u\n", pval[0]);
            }
            
            //选择主应用
            FWCosSelecteApp(icdev);
            
            //验证外部认证密钥
            status = FWCosVerifyKey(icdev, 
            	pExKey,//外部认证密钥
            	16,//密钥文件长度
            	(char)2);
            if (status != 0) {
                printf("FWCosVerifyKey error!\n");
                printf("%d",status);
                FWCosDeleteFileSys(icdev);//测试结束前删除这个应用
                fw_exit((int)icdev);//断开连接

            } else {
                printf("FWCosVerifyKey ok!\n");
            }

            
            //测试结束前删除这个应用
            status = FWCosDeleteFileSys(icdev);
            if (status != 0) {
                printf("FWCosDeleteFileSys error!\n");
                printf("%d",status);
                fw_exit((int)icdev);//断开连接
 
            } else {
                printf("FWCosDeleteFileSys ok!\n");
            }

            fw_exit((int)icdev);//断开连接
			

EXIT:

return status;
}
