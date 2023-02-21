
#ifndef __FM1208_H__
#define __FM1208_H__

#if defined(linux) || defined(__LYNX) || defined(__unix) || defined(_AIX)
#define _stdcall 
#define __stdcall
#endif

// ��ȫȨ��
#ifndef MWTOKEN_SEC
	#define	MWTOKEN_SEC
	#define	FWCOS_SEC_ALW				((unsigned long)0x00000000)	// ��Զ����
	#define	FWCOS_SEC_USER				((unsigned long)0x00000001)	// �û�����Ȩ��
	#define FWCOS_SEC_SO				((unsigned long)0x0000000A) // ����ԱȨ��
	#define FWCOS_SEC_NEVER				((unsigned long)0x000000EF) // ��Զ������
#endif

#ifndef	MWTOKEN_ALGID
	#define	MWTOKEN_ALGID
	#define	TOKEN_ALGID_DES				((unsigned long)0x00000000)
	#define	TOKEN_ALGID_SSF				((unsigned long)0x00000001)
	#define	TOKEN_ALGID_SCB2			((unsigned long)0x00000002)
	#define	TOKEN_ALGID_SHA1			((unsigned long)0x00000030)
	#define TOKEN_ALID_ANY				((unsigned long)0xFFFFFFFF)
#endif

//��Կ���ͱ�ʶ
#ifndef FWCOS_KEYTYPE
   #define FWCOS_KEYTYPE
   #define FW_KEYTYPE_FILEPROTECT       (0x01)//�ļ���·������Կ
   #define FW_KEYTYPE_EXVERIFY          (0x02)//�ⲿ��֤��Կ
   #define FW_KEYTYPE_PIN               (0x03)//������Կ
   #define FW_KEYTYPE_UNLOCK            (0x04)//����������Կ
   #define FW_KEYTYPE_CREDIT			(0x05)//Ȧ����Կ
   #define FW_KEYTYPE_DEBIT				(0x06)//Ȧ����Կ
   #define FW_KEYTYPE_PURCHASE			(0x07)//������Կ
   #define FW_KEYTYPE_OVERDRAWLIMIT     (0x08)//�޸�͸֧�޶�
   #define FW_KEYTYPE_INTERNAL			(0x09)//�ڲ���Կ
   #define FW_KEYTYPE_RELOADPIN			(0x0A)//��װ������Կ
#endif 


#define FT_READ_MSG			0x00
#define FT_WRITE_MSG		0x01
#define FT_READ_ACK			0x02

#define MAX_PACKET_SIZE_READ		(64 *1024 )

#define READ_LEN_ONETIME	(59)//add by cdt ÿ���������ֽ���
#define WRITE_LEN_ONETIME	(54)//add by cdt ÿ�����д���ֽ���
#define SIZE_ONEPAGE		(512)//528//ÿһҳ������
#define MAX_SIZE_FALSH		(2*1024*1024)//false�Ĵ洢����(2M)
#define MAX_LENGTH_PAGES	(MAX_SIZE_FALSH/SIZE_ONEPAGE)//���õ����ҳ��
#define MAX_LENGTH_AUTHEN   (32) //��֤���������󳤶�

#define OFFSET_USERPIN      (33)//�û���������ҳ��ƫ�Ƶ�ַ
#define OFFSET_SOPIN		(40)//����Ա��������ҳ��ƫ�Ƶ�ַ
#define OFFSET_AUTHENKEY	(47)//��֤�õ���Կ����ҳ��ƫ�Ƶ�ַ
#define OFFSET_MAINTAINKEY  (97)//Ӧ��ά����Կ����ҳ��ƫ�Ƶ�ַ��ÿ����Կ��Ϣռ51���ֽڣ������ 7 ��ά����Կ


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
// �������ܣ�
//	���Ӷ�д���豸������豸���
// ����������
//	port:	����������豸�˿�����(USB�򴮿�)
//	baud:	�������������ʱ�Ĳ�����
// ���أ�
//        �ɹ����ؾ���ֵ����1������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosConnect(__int16 port, int baud);



/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	�ͷ��豸���
// ����������
//	lDevHandle:	����������豸���
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosDisconnect(long lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	��λ�������ظ�λ��Ϣ
// ����������
//	lDevHandle:	   ����������豸���
//      pbReturnInfo:	   �����������Ÿ�λ��Ϣ�Ļ�����
//      pulReturnInfoLen:  �������/������������ݳ���
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosReset(long lDevHandle,
                         void* pbReturnInfo,
			 unsigned long*	pulReturnInfoLen);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	������Ӧ�ã��հ׿�������ִ��һ�δ˺������г�ʼ��
// ����������
//	lDevHandle:	����������豸���
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateMainApp(long           lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	ѡ��Ӧ��
// ����������
//	lDevHandle:	����������豸���
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosSelecteApp(long           lDevHandle);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	ɾ���ļ�ϵͳ
// ����������
//	lDevHandle:	����������豸���
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosDeleteFileSys(
                             long           lDevHandle);



/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	�ڵ�ǰӦ��Ŀ¼�½���һ����Ŀ¼�ļ�
// ����������
//	lDevHandle:	����������豸���
//	usDirFileID:	�����������Ŀ¼���ļ���ʶ��
//  usDirSize:		���������Ŀ¼�Ŀռ��С
//	ulCreateSec:	�������������Ŀ¼�½����ļ���Ȩ��
//	ulDeleteSec:	���������ɾ������Ŀ¼��Ȩ��

// ���أ�
//        �ɹ�����0������ʧ��
// ��ע��
//	����ɹ�������Ŀ¼�ļ�����ǰĿ¼Ϊ��������Ŀ¼��Ҳ����˵��ǰĿ¼Ϊ��
//	����Ŀ¼/Ӧ��Ŀ¼/������Ŀ¼
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosCreateDirectory(
                             long           lDevHandle,
                             unsigned short usDirFileID,
							 unsigned short usDirSize,
                             unsigned long  ulCreateSec,
                             unsigned long  ulDeleteSec);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	����Ӧ��Ŀ¼�½���һ������ר��Ŀ¼�ļ�
// ����������
//	lDevHandle:		����������豸���
//	usDirFileID:	�����������Ŀ¼���ļ���ʶ��
//	ulCreateSec:	�������������Ŀ¼�½����ļ���Ȩ��
//	ulDeleteSec:	���������ɾ������Ŀ¼��Ȩ��
//  pbDirName:      �����������Ŀ¼�����ƣ�5~16�ֽ�
//  ucDirNameLength:���������Ŀ¼���Ƶĳ���(5-16)
// ���أ�
//        �ɹ�����0������ʧ��
// ��ע��
//       ���ǽ���Ǯ��Ӧ�õ�ǰ������
/////////////////////////////////////////////////////////////////////////////////////
long _stdcall FWCosCreateADF(long   lDevHandle,
							 unsigned short usDirFileID,
							 unsigned long  ulCreateSec,
                             unsigned long  ulDeleteSec,
							 void*          pbDirName,
							 unsigned char  ucDirNameLength);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	ѡ��Ӧ�õ���Ŀ¼
// ����������
//	lDevHandle:	    ����������豸���
//	usDirID:		���������Ŀ¼��ʶ��
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosSelectDirectory(
                             long            lDevHandle,
                             unsigned short  usDirID);
/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	�ڵ�ǰӦ��Ŀ¼�»��ߵ�ǰӦ��Ŀ¼����Ŀ¼�½���һ���������ļ�
// ����������
//	lDevHandle:	    ����������豸���
//	usDirFileID:	�����������Ŀ¼���ļ���ʶ��������˲���Ϊ0x00000000
//						���ʾ�ڵ�ǰӦ��Ŀ¼�½���һ���������ļ�
//	usFileID:		�����������Ҫ�����Ķ������ļ���ʶ��
//	usFileLen:		����������ļ�����
//  cryptyType:     ������������ݴ���ļ��ܷ�ʽ��0�����ķ�ʽ��1������+MACУ�鷽ʽ��2������+MACУ�鷽ʽ
//	ulReadSec:		�����������ȡ�ļ���Ȩ��
//	ulUpdateSec:	��������������ļ���Ȩ��
//	ulDeleteSec:	���������ɾ���ļ���Ȩ��
// ���أ�
//        �ɹ�����0������ʧ��
// ��ע��
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
// �������ܣ�
//	�ڵ�ǰӦ��Ŀ¼�»��ߵ�ǰӦ��Ŀ¼����Ŀ¼�½���һ��������¼�ļ�
// ����������
//	lDevHandle:		    ����������豸���
//	usDirFileID:		�����������Ŀ¼���ļ���ʶ��������˲���Ϊ0x00000000
//						���ʾ�ڵ�ǰӦ��Ŀ¼�½���һ��������¼�ļ�
//  ucFRecord           ��¼�ļ������ͣ�0->������¼�ļ���1->ѭ����¼�ļ���2->�䳤��¼�ļ�
//	usFileID:			�����������Ҫ�����Ķ�����¼�ļ���ʶ��
//	bRecordNum:			�����������¼��Ŀ
//	bRecordLen:			�����������¼����
//  cryptyType:         ������������ݴ���ļ��ܷ�ʽ��0�����ķ�ʽ��1������+MACУ�鷽ʽ��2������+MACУ�鷽ʽ
//	ulReadSec:			�����������ȡ��¼��Ȩ��
//	ulUpdateSec:		������������¼�¼��Ȩ��
//	ulDeleteSec:		���������ɾ����¼��Ȩ��
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
// �������ܣ�
//	���ǰӦ��Ŀ¼�µ���Ŀ¼
// ����������
//	lDevHandle:	        ����������豸���
//	usDirFileID:		�����������Ŀ¼���ļ���ʶ��
// ���أ�
//        �ɹ�����0������ʧ��
// ��ע��
//	�ڽ����ļ����ļ��İ�ȫ������û�з������ã�ֻ���ڼ�����ļ��İ�ȫȨ�޲�������
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosActiveDirectory(
                             long            lDevHandle,
                             unsigned short  usDirFileID);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	��ȡ�������ļ�
// ����������
//	lDevHandle:	        ����������豸���
//  usFileID:       ����������������ļ��ı�ʶ��
//	pbBinData:		�����������Ŷ�ȡ���������ݵĻ�����
//	usOffset:		�����������ȡ����ʼƫ����
//	usReadLen:		�����������ȡ�ĳ���
//  cryptyType:   ������������ݴ���ļ��ܷ�ʽ��0�����ķ�ʽ��1������+MACУ�鷽ʽ��2������+MACУ�鷽ʽ
//  pProKey:        ��������������õ���·������Կ�����ļ�Ϊ���ܷ�ʽ�ǣ�Ӧ����ӵ���·������Կһ��
//  ulKeyLen:       �������, ��·������Կ�ĳ���
// ���أ�
//        �ɹ�����0������ʧ��
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
// �������ܣ�
//	���¼�¼�ļ�
// ����������
//	lDevHandle:	    ����������豸���
//  usFileID:       ����������������ļ��ı�ʶ��
//	usOffset:		�����������ȡ����ʼƫ����
//	pbBinData:		������������µĶ���������
//	usUpdateLen:	������������µĳ���
//  cryptyType:   ������������ݴ���ļ��ܷ�ʽ��0�����ķ�ʽ��1������+MACУ�鷽ʽ��2������+MACУ�鷽ʽ
//  pProKey:        ��������������õ���·������Կ�����ļ�Ϊ���ܷ�ʽ�ǣ�Ӧ����ӵ���·������Կһ��
//  ulKeyLen:       �������, ��·������Կ�ĳ���
// ���أ�
//        �ɹ�����0������ʧ��
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
// �������ܣ�
//	��Ӽ�¼
// ����������
//	lDevHandle:	        ����������豸���
//  bRecordFileID:      �����������¼�ļ��ı�ʶ��
//	pbRecData:			���������Ҫ��ӵļ�¼����
//	bAppendLen;			���������Ҫ��ӵļ�¼����
//  cryptyType:       ������������ݴ���ļ��ܷ�ʽ��0�����ķ�ʽ��1������+MACУ�鷽ʽ��2������+MACУ�鷽ʽ
//  pProKey:            ��������������õ���·������Կ�����ļ�Ϊ���ܷ�ʽ�ǣ�Ӧ����ӵ���·������Կһ��
//  ulKeyLen:           �������, ��·������Կ�ĳ���
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
// �������ܣ�
//	���¼�¼�ļ�
// ����������
//	lDevHandle:	        ����������豸���
//  ucFRecord           ��¼�ļ������ͣ�����ֻ��ȡ����ֵ��0��1����0->������¼�ļ���1->�䳤��¼�ļ�
//  bRecordFileID:      �����������¼�ļ��ı�ʶ��
//	bRecordNum:			�����������Ҫ���µļ�¼��
//	pbRecData:			������������µļ�¼����
//	bUpdateLen;			������������µļ�¼����
//  cryptyType:       ������������ݴ���ļ��ܷ�ʽ��0�����ķ�ʽ��1������+MACУ�鷽ʽ��2������+MACУ�鷽ʽ
//  pProKey:            ��������������õ���·������Կ�����ļ�Ϊ���ܷ�ʽ�ǣ�Ӧ����ӵ���·������Կһ��
//  ulKeyLen:           �������, ��·������Կ�ĳ���
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
// �������ܣ�
//	��֤�û���Կ���߹���Ա��Կ
// ����������
//	lDevHandle:	    ����������豸���
//	pbKey:			����������û���Կ�����߹���Ա��Կ
//	ulKeyLen:		�����������Կ����
//	ulKeyType:		�����������Կ���� FW_KEYTYPE_EXVERIFY���ⲿ��֤��Կ
//                            FW_KEYTYPE_PIN���û�����

//
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosVerifyKey(
                             long            lDevHandle,
                             const void*     pbKey,
                             unsigned long   ulKeyLen,
                             unsigned long   ulKeyType);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	�޸��û���Կ���߹���Ա��Կ
// ����������
//	lDevHandle:	    ����������豸���
//	pbOldPin:		�������������Կ
//  ulOldKeyLen��   �������������Կ����
//  pbNewKey:       �������������Կ
//  ulNewKeyLen:    �������������Կ����
//	bKeyType:		�����������Կ���ͱ�ʶ��
//                       FW_KEYTYPE_FILEPROTECT : �ļ���·������Կ
//                       FW_KEYTYPE_EXVERIFY    : �ⲿ��֤��Կ
//                       FW_KEYTYPE_PIN         : ������Կ
//                       FW_KEYTYPE_UNLOCK      : ����������Կ
//                       FW_KEYTYPE_PURCHASE    : ������Կ
//                       FW_KEYTYPE_CREDIT      : Ȧ����Կ
// 
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosUpdateKey(
                             long            lDevHandle,
                             const void*     pbOldKey,
                             unsigned long   ulOldKeyLen,
                             const void*     pbNewKey,
                             unsigned long   ulNewKeyLen,
                             unsigned long   bKeyType);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	��ȡ������¼�ļ�
// ����������
//	lDevHandle:	        ����������豸���
//  ucFRecord           ��¼�ļ������ͣ�����ֻ��ȡ����ֵ��0��1����0->������¼�ļ���1->�䳤��¼�ļ�
//  bRecordFileID:      �����������¼�ļ��ı�ʶ��
//	bRecordNum:			�����������Ҫ��ȡ�ļ�¼��
//	pbRecData:			�����������Ŷ�ȡ��¼���ݵĻ�����
//	bRecordLen;			�����������Ҫ��ȡ�ļ�¼����
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosReadRecord(
								 long			lDevHandle,
								 unsigned char  ucFRecord,
								 unsigned char  bRecordFileID,
								 unsigned char	bRecordNum,
								 void*			pbRecData,
								 unsigned short	bRecordLen);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	������Կ�ļ�
// ����������
//	lDevHandle:	        ����������豸���
//  usDirFileID         �������������Ŀ¼�ļ��Ķ̱�ʶ��
//  usFileID:			�����������¼�ļ��ı�ʶ��
//	uFileLen:			�����������Կ�ļ��ĳ���
//	ulGenSec:			�������������Կ�ļ��а�װ��Կ��Ȩ��
/////////////////////////////////////////////////////////////////////////////////////

long __stdcall FWCosCreateKeyFile(
			long			lTokenHandle,
			unsigned short	usDirFileID,
			unsigned short	usFileID,
			unsigned short  uFileLen,
			unsigned long	ulGenSec);



	/////////////////////////////////////////////////////////////////////////////////////
	// �������ܣ�
	//	�����Կ
	// ����������
	//	lDevHandle:		����������豸�����ͨ�� FWCosConnect ������ȡ
	//	bKeyType:			�����������Կ���ͱ�ʶ��
    //                       FW_KEYTYPE_FILEPROTECT : �ļ���·������Կ
	//                       FW_KEYTYPE_EXVERIFY    : �ⲿ��֤��Կ
	//                       FW_KEYTYPE_PIN         : ������Կ
	//                       FW_KEYTYPE_UNLOCK      : ����������Կ
	//                       FW_KEYTYPE_PURCHASE    : ������Կ
	//                       FW_KEYTYPE_CREDIT      : Ȧ����Կ
	//	pbKeyValue:			�����������Կֵ
	//	ulKeyValueLen:		�����������Կֵ�ĳ���
	// ��ע��
	//	1	��ִ�д˺���ǰ������ȷ����ǰĿ¼��Ӧ��Ŀ¼
	/////////////////////////////////////////////////////////////////////////////////////
	long __stdcall FWCosAddKey(
					long			lDevHandle,
					unsigned char	bKeyType,
					const void*		pbKeyValue,
					unsigned long	ulKeyValueLen);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	�����Կ��ǿ����
// ����������
//	lDevHandle:		����������豸�����ͨ�� FWCosConnect ������ȡ
//	bKeyType:			�����������Կ���ͱ�ʶ��
//                       FW_KEYTYPE_FILEPROTECT : �ļ���·������Կ
//                       FW_KEYTYPE_EXVERIFY    : �ⲿ��֤��Կ
//                       FW_KEYTYPE_PIN         : ������Կ
//                       FW_KEYTYPE_UNLOCK      : ����������Կ
//						 FW_KEYTYPE_CREDIT      : Ȧ�棨��Ǯ����Կ
//                       FW_KEYTYPE_PURCHASE    : ������Կ
//  ucKeyID:            �������������Կ�ı�ʶ��(ID)
//	pbKeyValue:			�����������Կֵ
//	ulKeyValueLen:		�����������Կֵ�ĳ���
//  ucSecUpdate:        ������������¸���Կ��Ȩ��
//  ucNextSt:           �����������֤����Կ��ĺ���״̬�������ⲿ��֤��Կ������ΪFWCOS_SEC_SO����Ϊ������Կ������ΪFWCOS_SEC_USER��������Ϊ 0
//	ucMaxCntError:		������������������(1-15)���ò��������ļ���·������Կ���ⲿ��֤��Կ��������Կ����������Կ��Ч
//  cryptyType:         ����������˲�����Ч��������Ϊ0

// ��ע��
//	1	��ִ�д˺���ǰ������ȷ����ǰĿ¼��Ӧ��Ŀ¼
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
// �������ܣ�
//	�޸��û�����
// ����������
//	lDevHandle:		����������豸�����ͨ�� FWCosConnect ������ȡ
//	pbOldPin:			����������ɿ���
//	ulOldPinLen:		����������ɿ����
//	pbNewPin:			����������¿���
//	ulNewPinLen:		����������¿����
/////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosUpdatePin(
							  long			lDevHandle,
							  const void*		pbOldPin,
							  unsigned long	ulOldPinLen,
							  const void*		pbNewPin,
							  unsigned long	ulNewPinLen);


/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
// ��һ��Ǯ���ļ�������ڴ��
// ����������
// lDevHandle:  �����������д���豸���
// ucKeyID:		���������Ȧ����Կ��ʶ��
// value:		���������Ȧ��Ľ��
// terminalID:	����������ն˻����
// pbCreditKey: ����������Ѱ�װ��Ȧ����Կ
// ulCreditKeyLen:�����������װ��Ȧ����Կ�ĳ���
////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosCredit(
						   long lDevHandle,
						   unsigned char ucKeyID,//��Կ��ʶ��
						   unsigned int  value,//Ȧ����(32λ)
						   unsigned char* terminalID,//�ն˻���ţ�6���ֽڳ�)
						   void*     pbCreditKey,
						   unsigned long ulCreditKeyLen);

/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
// Ǯ������
// ����������
// lDevHandle:  �����������д���豸���
// ucKeyID:		���������������Կ��ʶ��
// value:		������������ѵĽ��
// terminalID:	����������ն˻����
// pbPurchaseKey: ����������Ѱ�װ��������Կ
// ulPurchaseKeyLen:�����������װ��������Կ�ĳ���
////////////////////////////////////////////////////////////////////////////////////
long __stdcall FWCosPurchase(
						   long lDevHandle,
						   unsigned char ucKeyID,//��Կ��ʶ��
						   unsigned int  value,//���ѽ��(32λ)
						   unsigned char* terminalID,//�ն˻���ţ�6���ֽڳ�)
						   void*     pbPurchaseKey,
						   unsigned long ulPurchaseKeyLen);

	/////////////////////////////////////////////////////////////////////////////////////
	// �������ܣ�
	// ��õ���Ǯ��������е����
	// ����������
	// lDevHandle:  �����������д���豸���
	// balance:		�������������Ǯ��������е����
	////////////////////////////////////////////////////////////////////////////////////
	long __stdcall FWCosGetBalance(
		long lDevHandle,
		unsigned int* balance);


/////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�
//	�豸����
// ����������
//	lDevHandle:	����������豸���
//  Msec:		����������豸�����ĳ���ʱ��(ms)
// ���أ�
//        �ɹ�����0������ʧ��
/////////////////////////////////////////////////////////////////////////////////////

long _stdcall FWCosBeep(long           lDevHandle, __int16 MSec);

#ifdef __cplusplus
}//end of extern "C"
#endif


#endif //__FM1208_H__
