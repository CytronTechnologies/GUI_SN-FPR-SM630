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
//命令集合
//20070801
//Yang
#define C_GET_OK			0x01//接收正确
#define C_GET_FAIL			0x02//接收失败

#define C_ADD_FINGER		0x40//增加指纹
#define C_DEL_FINGER		0x42//删除指纹
#define C_SEARCH_FINGER		0x44//搜索指纹
#define C_EMPTY_FINGER		0x46//清空指纹库
#define C_MARTCH_FINGER		0x48//精确比对
#define C_READ_INFO			0x4B//查询指纹库信息

#define C_DOWN_TEMPLET		0x50//下载指纹模板
#define C_UP_TEMPLET		0x52//上传指纹模板

#define C_READ_ID			0x60//读取ID号
#define C_READ_FLASH		0x62//读取Flash
#define C_WRITE_FLASH		0x64//写Flash

#define C_FREE				0x70//Free命令

#define C_GET_SIZE			0x74//获取图像大小
#define C_GET_BMP			0x75//获取图像

#define C_READ_IDENTIFIER	0x80//读取产品标识

#define C_UP_IMAGE			0x93//上传图像
#define C_DOWN_IMAGE		0x95//下载图像
#define C_WRITE_DATA		0x97//写随机数
#define C_READ_DATA			0x98//读随机数
#define C_WRITE_ID			0x99//写ID号
#define C_BM				0x9A//验证保密选项

#define C_RESET				0xB7//恢复默认设置

#define C_CHANGE_B			0xC3//修改波特率
#define C_CHANGE_A			0xC5//修改安全等级

#define C_READ_TIME			0xD5//读取运行次数
#define C_READ_FAIL			0xD6//读取运行失败次数

#define C_READ_CS			0xD7//读取加密厂商标识

#define C_ENTER_BL			0xB3//进入保留命令

#define C_ENTER_BM			0xD3//进入保密命令



#define C_COMMAND			0x10//命令包
#define C_DATA				0x20//数据包
#define C_END_DATA			0x21//最后一个数据包
#define C_ANSWER			0x30//应答包


#define ANSWER_OK			0x31//操作成功
#define ANSWER_DETECT		0x32//探测到手指
#define ANSWER_OUT_TIME		0x33//超时
#define ANSWER_FAIL			0x34//指纹处理失败
#define ANSWER_NUMBER_E		0x35//指纹号错误
#define ANSWER_SEARCHED		0x39//搜索到指纹
#define ANSWER_NO_SEARCHED	0x3A//没有搜索到指纹
#define ANSWER_HAVE_FINGER	0x37//有指纹
#define ANSWER_NO_FINGER	0x38//没有指纹

//产品标识
//8字节厂商标识
//8字节产品标识
//8字节版本号
/*unsigned char Version[8*3]="MIAXIS  SM-630  V0.1   ";*/

#define MAX_FINGER		0xFF//最大指纹数量256

#define DATA_SECTOR		32//参数块
#define RANDOM_ADDR		0//随机数相对地址
#define ID_ADDR			1024//ID相对地址
#define DATA_ADDR		2048//系统参数相对地址

#define Flash_SECTOR	34//用户Flash块

#define FINGER_PAGE		33//指纹队列

/*unsigned char FingerNumber = 0;//指纹容量*/

#define   	MAX_PACKAGE_SIZE  256   	//数据包最大长度
#define   	HEAD_LENGTH       6 	    //接收正确应答包长度

/**********************************************
  FUNCTION:   InitCom
  PURPOSE:    初始化串口
  ARGS:
       comPort:    串口号,从1到8
	   baudRate:   波特率,0-38400   1-57600  2-115200  缺省为1-57600
	   3 9600
  RETURN:
       0:    失败
	   1:    成功
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
