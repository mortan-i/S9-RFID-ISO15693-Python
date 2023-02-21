
#ifndef __FM1208_H__
#define __FM1208_H__

#if defined(linux) || defined(__LYNX) || defined(__unix) || defined(_AIX)
#define _stdcall 
#define __stdcall
#endif

// 安全权限
#ifndef MWTOKEN_SEC
	#define	MWTOKEN_SEC
	#define	FWCOS_SEC_ALW				((unsigned long)0x00000000)	// 永远满足
	#define	FWCOS_SEC_USER				((unsigned long)0x00000001)	// 用户口令权限
	#define FWCOS_SEC_SO				((unsigned long)0x0000000A) // 管理员权限
	#define FWCOS_SEC_NEVER				((unsigned long)0x000000EF) // 永远不满足
#endif

#ifndef	MWTOKEN_ALGID
	#define	MWTOKEN_ALGID
	#define	TOKEN_ALGID_DES				((unsigned long)0x00000000)
	#define	TOKEN_ALGID_SSF				((unsigned long)0x00000001)
	#define	TOKEN_ALGID_SCB2			((unsigned long)0x00000002)
	#define	TOKEN_ALGID_SHA1			((unsigned long)0x00000030)
	#define TOKEN_ALID_ANY				((unsigned long)0xFFFFFFFF)
#endif

//密钥类型标识
#ifndef FWCOS_KEYTYPE
   #define FWCOS_KEYTYPE
   #define FW_KEYTYPE_FILEPROTECT       (0x01)//文件线路保护密钥
   #define FW_KEYTYPE_EXVERIFY          (0x02)//外部认证密钥
   #define FW_KEYTYPE_PIN               (0x03)//口令密钥
   #define FW_KEYTYPE_UNLOCK            (0x04)//解锁口令密钥
   #define FW_KEYTYPE_CREDIT			(0x05)//圈存密钥
   #define FW_KEYTYPE_DEBIT				(0x06)//圈提密钥
   #define FW_KEYTYPE_PURCHASE			(0x07)//消费密钥
   #define FW_KEYTYPE_OVERDRAWLIMIT     (0x08)//修改透支限额
   #define FW_KEYTYPE_INTERNAL			(0x09)//内部密钥
   #define FW_KEYTYPE_RELOADPIN			(0x0A)//重装口令密钥
#endif 


#define FT_READ_MSG			0x00
#define FT_WRITE_MSG		0x01
#define FT_READ_ACK			0x02

#define MAX_PACKET_SIZE_READ		(64 *1024 )

#define READ_LEN_ONETIME	(59)//add by cdt 每次最多读的字节数
#define WRITE_LEN_ONETIME	(54)//add by cdt 每次最多写的字节数
#define SIZE_ONEPAGE		(512)//528//每一页的容量
#define MAX_SIZE_FALSH		(2*1024*1024)//false的存储容量(2M)
#define MAX_LENGTH_PAGES	(MAX_SIZE_FALSH/SIZE_ONEPAGE)//可用的最大页数
#define MAX_LENGTH_AUTHEN   (32) //验证的密码的最大长度

#define OFFSET_USERPIN      (33)//用户口令所在页的偏移地址
#define OFFSET_SOPIN		(40)//管理员口令所在页的偏移地址
#define OFFSET_AUTHENKEY	(47)//认证用的密钥所在页的偏移地址
#define OFFSET_MAINTAINKEY  (97)//应用维护密钥所在页的偏移地址，每个密钥信息占51个字节，最多存放 7 个维护密钥


// Return codes
#define		F32x_SUCCESS				0x00
#define		F32x_DEVICE_NOT_FOUND		0xFF
#define		F32x_INVALID_HANDLE			0x01
#define		F32x_READ_ERROR				0x02
#define		F32x_RX_QUEUE_NOT_READY		0x03
#define		F32x_WRITE_ERROR			0x04
#define		F32x_RESET_ERROR			0x05
#define		F32x_INVALID_PARAMETER		0x06
#define		F32x_INVALID_REQUEST_LENGTH	0x07
#define		F32x_DEVICE_IO_FAILED		0x08
#define		F32x_INVALID_PAGE_ADDRESS	0x09
#define		F32x_INVALID_OFFSET_ADDRESS	0x0a

// RX Queue status flags
#define		F32x_RX_NO_OVERRUN			0x00
#define		F32x_RX_OVERRUN				0x01
#define		F32x_RX_READY				0x02

//exports functions
#ifdef __cplusplus
extern "C"{
#endif
/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	连接读写器设备，获得设备句柄
// 函数参数：
//	port:	输入参数，设备端口类型(USB或串口)
//	baud:	输入参数，连接时的波特率
// 返回：
//        成功返回绝对值大于1，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosConnect(__int16 port, int baud);



/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	释放设备句柄
// 函数参数：
//	lDevHandle:	输入参数，设备句柄
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosDisconnect(long lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	复位，并返回复位信息
// 函数参数：
//	lDevHandle:	   输入参数，设备句柄
//      pbReturnInfo:	   输出参数，存放复位信息的缓冲区
//      pulReturnInfoLen:  输出参数/输出参数，数据长度
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosReset(long lDevHandle,
                         void* pbReturnInfo,
			 unsigned long*	pulReturnInfoLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	创建主应用，空白卡需首先执行一次此函数进行初始化
// 函数参数：
//	lDevHandle:	输入参数，设备句柄
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateMainApp(long           lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	选择应用
// 函数参数：
//	lDevHandle:	输入参数，设备句柄
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosSelecteApp(long           lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	删除文件系统
// 函数参数：
//	lDevHandle:	输入参数，设备句柄
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosDeleteFileSys(
                             long           lDevHandle);



/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	在当前应用目录下建立一个子目录文件
// 函数参数：
//	lDevHandle:	输入参数，设备句柄
//	usDirFileID:	输入参数，子目录的文件标识符
//  usDirSize:		输入参数，目录的空间大小
//	ulCreateSec:	输入参数，在子目录下建立文件的权限
//	ulDeleteSec:	输入参数，删除此子目录的权限

// 返回：
//        成功返回0，否则失败
// 备注：
//	如果成功建立了目录文件，则当前目录为所建立的目录，也就是说当前目录为：
//	主控目录/应用目录/建立的目录
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateDirectory(
                             long           lDevHandle,
                             unsigned short usDirFileID,
							 unsigned short usDirSize,
                             unsigned long  ulCreateSec,
                             unsigned long  ulDeleteSec);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	在主应用目录下建立一个金融专用目录文件
// 函数参数：
//	lDevHandle:		输入参数，设备句柄
//	usDirFileID:	输入参数，子目录的文件标识符
//	ulCreateSec:	输入参数，在子目录下建立文件的权限
//	ulDeleteSec:	输入参数，删除此子目录的权限
//  pbDirName:      输入参数，此目录的名称，5~16字节
//  ucDirNameLength:输入参数，目录名称的长度(5-16)
// 返回：
//        成功返回0，否则失败
// 备注：
//       这是建立钱包应用的前提条件
/////////////////////////////////////////////////////////////////////////////////////
long _stdcall FWCosCreateADF(long   lDevHandle,
							 unsigned short usDirFileID,
							 unsigned long  ulCreateSec,
                             unsigned long  ulDeleteSec,
							 void*          pbDirName,
							 unsigned char  ucDirNameLength);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	选择应用的子目录
// 函数参数：
//	lDevHandle:	    输入参数，设备句柄
//	usDirID:		输入参数，目录标识符
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosSelectDirectory(
                             long            lDevHandle,
                             unsigned short  usDirID);
/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	在当前应用目录下或者当前应用目录的子目录下建立一个二进制文件
// 函数参数：
//	lDevHandle:	    输入参数，设备句柄
//	usDirFileID:	输入参数，子目录的文件标识符，如果此参数为0x00000000
//						则表示在当前应用目录下建立一个二进制文件
//	usFileID:		输入参数，所要建立的二进制文件标识符
//	usFileLen:		输入参数，文件长度
//  cryptyType:     输入参数，数据传输的加密方式，0：明文方式，1：明文+MAC校验方式，2：密文+MAC校验方式
//	ulReadSec:		输入参数，读取文件的权限
//	ulUpdateSec:	输入参数，更新文件的权限
//	ulDeleteSec:	输入参数，删除文件的权限
// 返回：
//        成功返回0，否则失败
// 备注：
//	
//	
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateBinaryFile(
                             long            lDevHandle,
                             unsigned short  usDirFileID,
                             unsigned short  usFileID,
                             unsigned short  usFileLen,
                             unsigned char   cryptyType,
                             unsigned long   ulReadSec,
			     unsigned long   ulUpdateSec,
			     unsigned long   ulDeleteSec);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	在当前应用目录下或者当前应用目录的子目录下建立一个定长记录文件
// 函数参数：
//	lDevHandle:		    输入参数，设备句柄
//	usDirFileID:		输入参数，子目录的文件标识符，如果此参数为0x00000000
//						则表示在当前应用目录下建立一个定长记录文件
//  ucFRecord           记录文件的类型，0->定长记录文件，1->循环记录文件，2->变长记录文件
//	usFileID:			输入参数，所要建立的定长记录文件标识符
//	bRecordNum:			输入参数，记录数目
//	bRecordLen:			输入参数，记录长度
//  cryptyType:         输入参数，数据传输的加密方式，0：明文方式，1：明文+MAC校验方式，2：密文+MAC校验方式
//	ulReadSec:			输入参数，读取记录的权限
//	ulUpdateSec:		输入参数，更新记录的权限
//	ulDeleteSec:		输入参数，删除记录的权限
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosCreateRecordFile(
									 long			lDevHandle,
									 unsigned short	usDirFileID,
									 unsigned char  ucFRecord,
									 unsigned short	usFileID,
									 unsigned char	bRecordNum,
									 unsigned short	bRecordLen,
									 unsigned char  cryptyType,
									 unsigned long	ulReadSec,
									 unsigned long	ulUpdateSec,
									 unsigned long	ulDeleteSec);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	激活当前应用目录下的子目录
// 函数参数：
//	lDevHandle:	        输入参数，设备句柄
//	usDirFileID:		输入参数，子目录的文件标识符
// 返回：
//        成功返回0，否则失败
// 备注：
//	在建立文件后，文件的安全条件并没有发挥作用，只有在激活后，文件的安全权限才有作用
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosActiveDirectory(
                             long            lDevHandle,
                             unsigned short  usDirFileID);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	读取二进制文件
// 函数参数：
//	lDevHandle:	        输入参数，设备句柄
//  usFileID:       输入参数，二进制文件的标识符
//	pbBinData:		输出参数，存放读取二进制数据的缓冲区
//	usOffset:		输入参数，读取的起始偏移量
//	usReadLen:		输入参数，读取的长度
//  cryptyType:   输入参数，数据传输的加密方式，0：明文方式，1：明文+MAC校验方式，2：密文+MAC校验方式
//  pProKey:        输入参数，加密用的线路保护密钥，当文件为加密方式是，应与添加的线路保护密钥一致
//  ulKeyLen:       输入参数, 线路保护密钥的长度
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosReadBinaryFile(
                             long           lDevHandle,
							 unsigned short usFileID,
                             void*			pbBinData,
                             unsigned short usOffset,
                             unsigned short usReadLen,
							 unsigned char			cryptyType,
							 void*          pProKey,
							 unsigned long  ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	更新记录文件
// 函数参数：
//	lDevHandle:	    输入参数，设备句柄
//  usFileID:       输入参数，二进制文件的标识符
//	usOffset:		输入参数，读取的起始偏移量
//	pbBinData:		输入参数，更新的二进制数据
//	usUpdateLen:	输入参数，更新的长度
//  cryptyType:   输入参数，数据传输的加密方式，0：明文方式，1：明文+MAC校验方式，2：密文+MAC校验方式
//  pProKey:        输入参数，加密用的线路保护密钥，当文件为加密方式是，应与添加的线路保护密钥一致
//  ulKeyLen:       输入参数, 线路保护密钥的长度
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosUpdateBinaryFile(
                             long            lDevHandle,
							 unsigned short  usFileID,
                             unsigned short  usOffset,
                             const void*     pbBinData,
                             unsigned short  usUpdateLen,
                             unsigned char            cryptyType,
							 void*           pProKey,
							 unsigned long   ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	添加记录
// 函数参数：
//	lDevHandle:	        输入参数，设备句柄
//  bRecordFileID:      输入参数，记录文件的标识符
//	pbRecData:			输出参数，要添加的记录数据
//	bAppendLen;			输入参数，要添加的记录长度
//  cryptyType:       输入参数，数据传输的加密方式，0：明文方式，1：明文+MAC校验方式，2：密文+MAC校验方式
//  pProKey:            输入参数，加密用的线路保护密钥，当文件为加密方式是，应与添加的线路保护密钥一致
//  ulKeyLen:           输入参数, 线路保护密钥的长度
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosAppendRecord(
								 long			lDevHandle,
								 unsigned char  bRecordFileID,
								 const void*		pbRecData,
								 unsigned short	bAppendLen,
								 unsigned char            cryptyType,
								 void*           pProKey,
								 unsigned long   ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	更新记录文件
// 函数参数：
//	lDevHandle:	        输入参数，设备句柄
//  ucFRecord           记录文件的类型，这里只能取两个值（0和1），0->定长记录文件，1->变长记录文件
//  bRecordFileID:      输入参数，记录文件的标识符
//	bRecordNum:			输入参数，所要更新的记录号
//	pbRecData:			输出参数，更新的记录数据
//	bUpdateLen;			输入参数，更新的记录长度
//  cryptyType:       输入参数，数据传输的加密方式，0：明文方式，1：明文+MAC校验方式，2：密文+MAC校验方式
//  pProKey:            输入参数，加密用的线路保护密钥，当文件为加密方式是，应与添加的线路保护密钥一致
//  ulKeyLen:           输入参数, 线路保护密钥的长度
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosUpdateRecord(
								 long			lDevHandle,
								 unsigned char  ucRecord,
								 unsigned char  bRecordFileID,
								 unsigned char	bRecordNum,
								 const void*		pbRecData,
								 unsigned short	bUpdateLen,
								 unsigned char            cryptyType,
								 void*           pProKey,
								 unsigned long   ulKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	认证用户密钥或者管理员密钥
// 函数参数：
//	lDevHandle:	    输入参数，设备句柄
//	pbKey:			输入参数，用户密钥，或者管理员密钥
//	ulKeyLen:		输入参数，密钥长度
//	ulKeyType:		输入参数，密钥类型 FW_KEYTYPE_EXVERIFY：外部认证密钥
//                            FW_KEYTYPE_PIN：用户口令

//
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosVerifyKey(
                             long            lDevHandle,
                             const void*     pbKey,
                             unsigned long   ulKeyLen,
                             unsigned long   ulKeyType);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	修改用户密钥或者管理员密钥
// 函数参数：
//	lDevHandle:	    输入参数，设备句柄
//	pbOldPin:		输入参数，旧密钥
//  ulOldKeyLen：   输入参数，旧密钥长度
//  pbNewKey:       输入参数，新密钥
//  ulNewKeyLen:    输入参数，新密钥长度
//	bKeyType:		输入参数，密钥类型标识，
//                       FW_KEYTYPE_FILEPROTECT : 文件线路保护密钥
//                       FW_KEYTYPE_EXVERIFY    : 外部认证密钥
//                       FW_KEYTYPE_PIN         : 口令密钥
//                       FW_KEYTYPE_UNLOCK      : 解锁口令密钥
//                       FW_KEYTYPE_PURCHASE    : 消费密钥
//                       FW_KEYTYPE_CREDIT      : 圈存密钥
// 
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosUpdateKey(
                             long            lDevHandle,
                             const void*     pbOldKey,
                             unsigned long   ulOldKeyLen,
                             const void*     pbNewKey,
                             unsigned long   ulNewKeyLen,
                             unsigned long   bKeyType);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	读取定长记录文件
// 函数参数：
//	lDevHandle:	        输入参数，设备句柄
//  ucFRecord           记录文件的类型，这里只能取两个值（0和1），0->定长记录文件，1->变长记录文件
//  bRecordFileID:      输入参数，记录文件的标识符
//	bRecordNum:			输入参数，所要读取的记录号
//	pbRecData:			输出参数，存放读取记录数据的缓冲区
//	bRecordLen;			输入参数，所要读取的记录长度
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosReadRecord(
								 long			lDevHandle,
								 unsigned char  ucFRecord,
								 unsigned char  bRecordFileID,
								 unsigned char	bRecordNum,
								 void*			pbRecData,
								 unsigned short	bRecordLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	创建密钥文件
// 函数参数：
//	lDevHandle:	        输入参数，设备句柄
//  usDirFileID         输入参数，所在目录文件的短标识符
//  usFileID:			输入参数，记录文件的标识符
//	uFileLen:			输入参数，密钥文件的长度
//	ulGenSec:			输入参数，在密钥文件中安装密钥的权限
/////////////////////////////////////////////////////////////////////////////////////

long __stdcall FWCosCreateKeyFile(
			long			lTokenHandle,
			unsigned short	usDirFileID,
			unsigned short	usFileID,
			unsigned short  uFileLen,
			unsigned long	ulGenSec);



	/////////////////////////////////////////////////////////////////////////////////////
	// 函数功能：
	//	添加密钥
	// 函数参数：
	//	lDevHandle:		输入参数，设备句柄，通过 FWCosConnect 函数获取
	//	bKeyType:			输入参数，密钥类型标识，
    //                       FW_KEYTYPE_FILEPROTECT : 文件线路保护密钥
	//                       FW_KEYTYPE_EXVERIFY    : 外部认证密钥
	//                       FW_KEYTYPE_PIN         : 口令密钥
	//                       FW_KEYTYPE_UNLOCK      : 解锁口令密钥
	//                       FW_KEYTYPE_PURCHASE    : 消费密钥
	//                       FW_KEYTYPE_CREDIT      : 圈存密钥
	//	pbKeyValue:			输入参数，密钥值
	//	ulKeyValueLen:		输入参数，密钥值的长度
	// 备注：
	//	1	在执行此函数前，请先确保当前目录在应用目录
	/////////////////////////////////////////////////////////////////////////////////////
	long __stdcall FWCosAddKey(
					long			lDevHandle,
					unsigned char	bKeyType,
					const void*		pbKeyValue,
					unsigned long	ulKeyValueLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	添加密钥增强函数
// 函数参数：
//	lDevHandle:		输入参数，设备句柄，通过 FWCosConnect 函数获取
//	bKeyType:			输入参数，密钥类型标识，
//                       FW_KEYTYPE_FILEPROTECT : 文件线路保护密钥
//                       FW_KEYTYPE_EXVERIFY    : 外部认证密钥
//                       FW_KEYTYPE_PIN         : 口令密钥
//                       FW_KEYTYPE_UNLOCK      : 解锁口令密钥
//						 FW_KEYTYPE_CREDIT      : 圈存（存钱）密钥
//                       FW_KEYTYPE_PURCHASE    : 消费密钥
//  ucKeyID:            输入参数，该密钥的标识号(ID)
//	pbKeyValue:			输入参数，密钥值
//	ulKeyValueLen:		输入参数，密钥值的长度
//  ucSecUpdate:        输入参数，更新该密钥的权限
//  ucNextSt:           输入参数，验证改密钥后的后续状态，若是外部认证密钥，须设为FWCOS_SEC_SO，若为口令密钥，须设为FWCOS_SEC_USER，其他设为 0
//	ucMaxCntError:		输入参数，最大错误次数(1-15)，该参数仅对文件线路保护密钥、外部认证密钥、口令密钥、解锁口密钥有效
//  cryptyType:         输入参数，此参数无效，可设置为0

// 备注：
//	1	在执行此函数前，请先确保当前目录在应用目录
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosAddKeyEx(
						   long			lDevHandle,
						   unsigned char	bKeyType,
						   unsigned char    ucKeyID,
						   const void*		pbKeyValue,
						   unsigned long	ulKeyValueLen,
						   unsigned char    ucSecUpdate,
						   unsigned char    ucNextSt,
						   unsigned char	ucMaxCntError,
						   unsigned char    cryptyType);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	修改用户口令
// 函数参数：
//	lDevHandle:		输入参数，设备句柄，通过 FWCosConnect 函数获取
//	pbOldPin:			输入参数，旧口令
//	ulOldPinLen:		输入参数，旧口令长度
//	pbNewPin:			输入参数，新口令
//	ulNewPinLen:		输入参数，新口令长度
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosUpdatePin(
							  long			lDevHandle,
							  const void*		pbOldPin,
							  unsigned long	ulOldPinLen,
							  const void*		pbNewPin,
							  unsigned long	ulNewPinLen);


/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
// 向一个钱包文件或存折内存款
// 函数参数：
// lDevHandle:  输入参数，读写器设备句柄
// ucKeyID:		输入参数，圈存密钥标识符
// value:		输入参数，圈存的金额
// terminalID:	输入参数，终端机编号
// pbCreditKey: 输入参数，已安装的圈存密钥
// ulCreditKeyLen:输入参数，安装的圈存密钥的长度
////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosCredit(
						   long lDevHandle,
						   unsigned char ucKeyID,//密钥标识符
						   unsigned int  value,//圈存金额(32位)
						   unsigned char* terminalID,//终端机编号（6个字节长)
						   void*     pbCreditKey,
						   unsigned long ulCreditKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
// 钱包消费
// 函数参数：
// lDevHandle:  输入参数，读写器设备句柄
// ucKeyID:		输入参数，消费密钥标识符
// value:		输入参数，消费的金额
// terminalID:	输入参数，终端机编号
// pbPurchaseKey: 输入参数，已安装的消费密钥
// ulPurchaseKeyLen:输入参数，安装的消费密钥的长度
////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosPurchase(
						   long lDevHandle,
						   unsigned char ucKeyID,//密钥标识符
						   unsigned int  value,//消费金额(32位)
						   unsigned char* terminalID,//终端机编号（6个字节长)
						   void*     pbPurchaseKey,
						   unsigned long ulPurchaseKeyLen);

	/////////////////////////////////////////////////////////////////////////////////////
	// 函数功能：
	// 获得电子钱包或存折中的余额
	// 函数参数：
	// lDevHandle:  输入参数，读写器设备句柄
	// balance:		输出参数，电子钱包或存折中的余额
	////////////////////////////////////////////////////////////////////////////////////
	long __stdcall FWCosGetBalance(
		long lDevHandle,
		unsigned int* balance);


/////////////////////////////////////////////////////////////////////////////////////
// 函数功能：
//	设备蜂鸣
// 函数参数：
//	lDevHandle:	输入参数，设备句柄
//  Msec:		输入参数，设备蜂鸣的持续时间(ms)
// 返回：
//        成功返回0，否则失败
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosBeep(long           lDevHandle, __int16 MSec);

#ifdef __cplusplus
}//end of extern "C"
#endif


#endif //__FM1208_H__
