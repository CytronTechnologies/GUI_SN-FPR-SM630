#ifndef __SM630_DLL_H__
#define __SM630_DLL_H__

#ifdef SM630_DLL_API
#else 
//#define SM630_DLL_API _declspec(dllimport) //extern "C"
#define SM630_DLL_API 
#endif
#include <afx.h>
#include <windows.h>
#include <Afxwin.h>
//�����
//20070801
//Yang
#define C_GET_OK			0x01//������ȷ
#define C_GET_FAIL			0x02//����ʧ��

#define C_ADD_FINGER		0x40//����ָ��
#define C_DEL_FINGER		0x42//ɾ��ָ��
#define C_SEARCH_FINGER		0x44//����ָ��
#define C_EMPTY_FINGER		0x46//���ָ�ƿ�
#define C_MARTCH_FINGER		0x48//��ȷ�ȶ�
#define C_READ_INFO			0x4B//��ѯָ�ƿ���Ϣ

#define C_DOWN_TEMPLET		0x50//����ָ��ģ��
#define C_UP_TEMPLET		0x52//�ϴ�ָ��ģ��

#define C_READ_ID			0x60//��ȡID��
#define C_READ_FLASH		0x62//��ȡFlash
#define C_WRITE_FLASH		0x64//дFlash

#define C_FREE				0x70//Free����

#define C_GET_SIZE			0x74//��ȡͼ���С
#define C_GET_BMP			0x75//��ȡͼ��

#define C_READ_IDENTIFIER	0x80//��ȡ��Ʒ��ʶ

#define C_UP_IMAGE			0x93//�ϴ�ͼ��
#define C_DOWN_IMAGE		0x95//����ͼ��
#define C_WRITE_DATA		0x97//д�����
#define C_READ_DATA			0x98//�������
#define C_WRITE_ID			0x99//дID��
#define C_BM				0x9A//��֤����ѡ��

#define C_RESET				0xB7//�ָ�Ĭ������

#define C_CHANGE_B			0xC3//�޸Ĳ�����
#define C_CHANGE_A			0xC5//�޸İ�ȫ�ȼ�

#define C_READ_TIME			0xD5//��ȡ���д���
#define C_READ_FAIL			0xD6//��ȡ����ʧ�ܴ���

#define C_READ_CS			0xD7//��ȡ���ܳ��̱�ʶ

#define C_ENTER_BL			0xB3//���뱣������

#define C_ENTER_BM			0xD3//���뱣������



#define C_COMMAND			0x10//�����
#define C_DATA				0x20//���ݰ�
#define C_END_DATA			0x21//���һ�����ݰ�
#define C_ANSWER			0x30//Ӧ���


#define ANSWER_OK			0x31//�����ɹ�
#define ANSWER_DETECT		0x32//̽�⵽��ָ
#define ANSWER_OUT_TIME		0x33//��ʱ
#define ANSWER_FAIL			0x34//ָ�ƴ���ʧ��
#define ANSWER_NUMBER_E		0x35//ָ�ƺŴ���
#define ANSWER_SEARCHED		0x39//������ָ��
#define ANSWER_NO_SEARCHED	0x3A//û��������ָ��
#define ANSWER_HAVE_FINGER	0x37//��ָ��
#define ANSWER_NO_FINGER	0x38//û��ָ��

//��Ʒ��ʶ
//8�ֽڳ��̱�ʶ
//8�ֽڲ�Ʒ��ʶ
//8�ֽڰ汾��
/*unsigned char Version[8*3]="MIAXIS  SM-630  V0.1   ";*/

#define MAX_FINGER		0xFF//���ָ������256

#define DATA_SECTOR		32//������
#define RANDOM_ADDR		0//�������Ե�ַ
#define ID_ADDR			1024//ID��Ե�ַ
#define DATA_ADDR		2048//ϵͳ������Ե�ַ

#define Flash_SECTOR	34//�û�Flash��

#define FINGER_PAGE		33//ָ�ƶ���

/*unsigned char FingerNumber = 0;//ָ������*/

#define   	MAX_PACKAGE_SIZE  256   	//���ݰ���󳤶�
#define   	HEAD_LENGTH       6 	    //������ȷӦ�������

/**********************************************
  FUNCTION:   InitCom
  PURPOSE:    ��ʼ������
  ARGS:
       comPort:    ���ں�,��1��8
	   baudRate:   ������,0-38400   1-57600  2-115200  ȱʡΪ1-57600
	   3 9600
  RETURN:
       0:    ʧ��
	   1:    �ɹ�
***********************************************/

SM630_DLL_API BOOL InitCom(int comPort, int baudRate);
SM630_DLL_API void ReleaseCom();
SM630_DLL_API BOOL ResetCom();
SM630_DLL_API BOOL SendByte(unsigned char tranChar);
SM630_DLL_API BOOL GetByte(unsigned char* tranChar);

SM630_DLL_API   GetPackage(unsigned char *pData,unsigned int WaitTime);
SM630_DLL_API int  GetPackageLength(unsigned char* pData);
SM630_DLL_API int  GetPackageContentLength(unsigned char* pData);
SM630_DLL_API BOOL SendPackage(unsigned char *pData);
SM630_DLL_API int  FillPackage(unsigned char* pData,int nPackageType, int nLength, unsigned char* pContent);
SM630_DLL_API int  VerifyResponsePackage(unsigned char nPackageType, unsigned char* pData);
SM630_DLL_API void Delay(int nDelayTime);
SM630_DLL_API BOOL MakeBMP(const char* strFileName,unsigned char* pImage,int X,int Y);
#endif