//#define SM630_DLL_API _declspec(dllexport)
#include "SM630_DLL.h"

static int       g_nComPort        = 0;          //串口号
static int       g_nBaudRate       = 57600;      //波特率
static HANDLE    g_hCom            = NULL;       //串口句柄
//const int        WAITTIME_PER_BYTE =  10000;    //读每个字节时间(ms)
const int        WAITTIME_PER_BYTE =  100;    //读每个字节时间(ms)

////////////////////////////////////////////////
/////           串口操作                  //////
////////////////////////////////////////////////

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
BOOL   InitCom(int comPort, int baudRate)
{
	CHAR          cCom[10];
	DCB           dcb;
	HANDLE        hCom;
	BOOL          bSuccess;
	COMSTAT       comStat;
	COMMTIMEOUTS  timeOuts;
	DWORD         dwError;

	if( comPort<1 || comPort>8 )
		return FALSE;

	int baud;
	switch (baudRate)
	{
	case 0:
		baud = 57600;
		break;
	case 1:
		baud = 38400;
		break;	
	case 2:
		baud = 115200;
		break;
	case 3:
		baud = 9600;
		break;
	case 38400:
	case 57600:
	case 115200:
		baud = baudRate;
		break;
	default:
		baud = 57600;
	}

	//记录设置信息
	g_nBaudRate = baud;
	g_nComPort = comPort;

	//设置com口
	cCom[0] = 'C';
	cCom[1] = 'O';
	cCom[2] = 'M';
	cCom[3] = '0'+comPort;
	cCom[4] = 0;
	
	//打开com口
	hCom = CreateFile(cCom,
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
		);

	if (hCom == INVALID_HANDLE_VALUE)
	{
		dwError = GetLastError();   //得到错误信息
		return FALSE;
	}
	//
	PurgeComm(hCom, PURGE_TXABORT|PURGE_RXABORT);

	//设置dcb
	bSuccess = GetCommState(hCom, &dcb);
	if (!bSuccess)
	{
		dwError = GetLastError();   //得到错误信息
		CloseHandle(hCom);
		return FALSE;
	}

	dcb.BaudRate = (unsigned long) baud;
	dcb.ByteSize = 8;
	dcb.Parity   = 0;
	dcb.StopBits = 2;
	
	bSuccess = SetCommState(hCom, &dcb);
	if (!bSuccess)
	{
		dwError = GetLastError();   //得到错误信息
		CloseHandle(hCom);
		return FALSE;
	}

	//设置超时
	bSuccess = GetCommTimeouts(hCom, &timeOuts);
	if (!bSuccess)
	{
		dwError = GetLastError();   //得到错误信息
		CloseHandle(hCom);
		return FALSE;
	}
	
	timeOuts.ReadTotalTimeoutMultiplier = WAITTIME_PER_BYTE; 
	timeOuts.WriteTotalTimeoutConstant = 1000;  

	bSuccess = SetCommTimeouts(hCom,&timeOuts);
	if (!bSuccess)
	{
		dwError = GetLastError();   //得到错误信息
		CloseHandle(hCom);
		return FALSE;
	}

	g_hCom = hCom;

	//清除错误标志
	ClearCommError(hCom,&dwError,&comStat);

//	PurgeComm(hCom, PURGE_TXABORT|PURGE_RXABORT);

	return TRUE;
}

/**********************************************
  FUNCTION:   ReleaseCom
  PURPOSE:    关闭串口
***********************************************/
void  ReleaseCom()
{
	if( g_hCom!= NULL && g_hCom!=INVALID_HANDLE_VALUE )
		CloseHandle( g_hCom );
}

BOOL ResetCom()
{
	BOOL ret;

	ReleaseCom();
	ret = InitCom(g_nComPort, g_nBaudRate);

	return ret;
}

//----------------------GetPkgByte--------------------
int   GetPkgByte(int comport,unsigned char *TranChar)
{
	DWORD    num;
	COMSTAT  comstat;
	DWORD    dwError;

    num=0;
	*TranChar=0;
	ClearCommError(g_hCom,&dwError,&comstat);
	ReadFile(g_hCom,TranChar,1,&num,NULL);
	if( num!=1 )
		return 0;
    return 1;
}

/**********************************************
  FUNCTION:   GetByte
  PURPOSE:    从串口读一个字节
  ARGS:
       tranChar： 要接收的字节
  RETURN:
       0:    失败
	   1:    成功
***********************************************/
BOOL GetByte(unsigned char* tranChar)
{
	DWORD    num;
	COMSTAT  comstat;
	DWORD    dwError;
	BOOL     bSuccess;

	return GetPkgByte(0,tranChar);

	if (tranChar == NULL)
		return FALSE;

	if (g_hCom == NULL)
		return FALSE;

    num = 0;
	*tranChar = 0;

	if ( !ClearCommError(g_hCom, &dwError, &comstat) )
	{
		return FALSE;
	}

	//读一个字节的数据
	bSuccess = ReadFile(g_hCom, tranChar, 1, &num, NULL);
	//if( !bSuccess && num!=1 )
	if( !bSuccess || num!=1 )
	{
		ClearCommError(g_hCom, &dwError, &comstat);
		return FALSE;
	}

    return TRUE;
}

/**********************************************
  FUNCTION:   SendByte
  PURPOSE:    向串口写一个字节
  ARGS:
       tranChar： 要发送的字节
  RETURN:
       0:    失败
	   1:    成功
***********************************************/
BOOL SendByte(unsigned char tranChar)
{
    DWORD    num;
	BOOL     bSuccess;

	if (g_hCom == NULL)
	{
		AfxMessageBox("串口未初始化");
		return FALSE;
	}

//	Delay(120);  //延时120微秒
    
	//发送一个字节
	bSuccess = WriteFile(g_hCom, &tranChar, 1, &num, NULL);
	if( !bSuccess && num!=1 )
		return FALSE;

    return TRUE;
}


/**********************************************
  FUNCTION:   GetPackage
  PURPOSE:    收包
  ARGS:
       pData:  接收数据地址
  RETURN:
       0:    失败
	   1:    成功
***********************************************/
BOOL   GetPackage(unsigned char *pData,unsigned int WaitTime)
{   
    unsigned char cChar;
	unsigned char *recvBuf;//recvBuf[256];
	BOOL          bSuccess = FALSE;
    long          checkSum = 0;
	int           nRepeatTime = 0;
	COMSTAT  comstat;
	DWORD    dwError;
	unsigned int i;
	unsigned char j;

	if (!pData)

		return FALSE;
	
	recvBuf=pData;
	if ( !ClearCommError(g_hCom, &dwError, &comstat) )
	{
		return FALSE;
	}
	
/*	bSuccess = GetByte(&cChar);	*/
//	if (bSuccess)
//	{
//		if(cChar!=0x4D)             //判断是否有效包头
//			return FALSE;
//		*recvBuf++ = cChar;
// 	}

	for(i=0;i<WaitTime;i++)
	{
		if(GetByte(&cChar))
		{
			goto GetOK;
		}
	}
	return FALSE;

GetOK:
	if(cChar!=0x4D)             
		return FALSE;
	*recvBuf++ = cChar;
	
	//接收包头，包标识，包长度
	for(i=0;i<3;i++)
	{
//		bSuccess = GetByte(&cChar);
//		if (bSuccess)
//		{
//			*recvBuf++ = cChar;
// 		}
		if(!GetByte(&cChar))
			return FALSE;
		*recvBuf++ = cChar;
	}
	//根据包长度，接收包内容，校验和
	for(j=0;j<pData[3]+1;j++)
	{
// 		bSuccess = GetByte(&cChar);
//
//		if (bSuccess)
//		{
//			*recvBuf++ = cChar;
// 		}	
		if(!GetByte(&cChar))
			return FALSE;
		*recvBuf++ = cChar;
 	}
	return TRUE;
}

/**********************************************
  FUNCTION:   GetPackageLength
  PURPOSE:    得到整个包长度值
  ARGS:
       pData:  包数据起始地址
  RETURN:
       整个包长度值       
***********************************************/
int  GetPackageLength(unsigned char* pData)
{
   // |  包头   |  包标识   |   包长度	  |   ...{内容}     |  校验和    |
   // | 2 bytes |  1 byte   |   1 bytes   |	  ...{包长度}   |  1 bytes   |

	if (!pData)
		return 0;
	int length = 0;
	length = pData[3] + 2 + 1 + 1 + 1;
	return length;
}

/**********************************************
  FUNCTION:   GetPackageContentLength
  PURPOSE:    从包中指定的位置取得包内容长度值
  ARGS:
       pData:  包数据起始地址
  RETURN:
       包内容长度值       
***********************************************/
int GetPackageContentLength(unsigned char* pData)
{
    // |  包头   |  包标识   |   包长度	  |   ...{内容}     |  校验和    |
    // | 2 bytes |  1 byte   |   1 bytes  |	  ...{包长度}   |  1 bytes   |

	if (!pData)
		return 0;
	int length = 0;
	length = pData[3];
	return length;
}

/**********************************************
  FUNCTION:   SendPackage
  PURPOSE:    发包
  ARGS:
       pData:  指针， 要发送数据地址
  RETURN:
       0:    失败
	   1:    成功
***********************************************/
BOOL   SendPackage(unsigned char *pData)
{   
	int iLength;
	BOOL bSuccess = FALSE;
	COMSTAT  comstat;
	DWORD    dwError;

	if (!pData)
		return FALSE;

	iLength = GetPackageLength(pData);  //得到包长度
	if (iLength>MAX_PACKAGE_SIZE)
		return FALSE;

	if ( !ClearCommError(g_hCom, &dwError, &comstat) )
	{
		return FALSE;
	}

	//发送数据
	for (int i=0; i<iLength; i++)
	{
		if ( !SendByte(pData[i]) ) 
			return FALSE;
	} 
	
	return TRUE;
}

/**********************************************
  FUNCTION:   FillPackage
  PURPOSE:    填充数据包
  ARGS:       
      pData:         要填充的包地址
	  nPackageType:  包类型   
	  nLength:       数据包内容长度
	  pContent:      数据包内容
  RETURN:
      0:      错误
      length: 整个包长度
***********************************************/
int FillPackage(unsigned char* pData, int nPackageType,int nLength, unsigned char* pContent)
{
    // |   包头    |  包标识   |   包长度	  |   ...{内容}     |  校验和    |
    // |  2 bytes  |  1 byte   |   1 bytes    |	  ...{包长度}   |  1 bytes   |

	int totalLen = 0;
	long checksum = 0;
	int i;
	if (!pData || nLength<0 || nLength>MAX_PACKAGE_SIZE-HEAD_LENGTH-2-2 )
		return 0;
	if ( (nPackageType != C_COMMAND) 
		&& (nPackageType != C_DATA) 
		&& (nPackageType != C_END_DATA)
		&& (nPackageType != C_ANSWER))
		return 0;
	pData[0] = 0x4D;                //包头
	pData[1] = 0x58;                //包头
	pData[2] = nPackageType;    	//包标识                   
	pData[3] = nLength & 0xff;      //包长度
	if (nLength)
	{
		if (!pContent)
			return 0;
		memcpy(pData+4, pContent, nLength);
	}

	totalLen = nLength + 4; 

	for (i=0; i<totalLen; i++)
	{
		checksum += pData[i];
	}

	pData[totalLen] = checksum & 0xff;

	totalLen += 1;

	return totalLen;
}

/**********************************************
  FUNCTION:   VerifyResposePackage
  PURPOSE:    检验应答包有效性
  ARGS:       
      pData:  指针，应答包地址
  RETURN:
	  -3:     错误
      0:      正确
	  1-20:   错误
***********************************************/
int VerifyResponsePackage(unsigned char nPackageType, unsigned char* pData)
{
	int i;
	long checkSum = 0;

	if (!pData)
		return -3;
	if ( pData[2] != nPackageType )
		return -3;

	int iLength;

	iLength = GetPackageLength(pData);  //得到包长度
	
	//校验
	for (i=0; i<iLength-1; i++)
		checkSum += pData[i];
	
	if ( pData[i] != (checkSum&0xff) ) //正确
	{
		return -3;
	}
//	if (nPackageType == C_ANSWER)
// 		return pData[5];  //确认码
	return 0;
}


/**********************************************
  FUNCTION:   Delay
  PURPOSE:    延时xx微秒
  ARGS:
         nDelayTime:  延时时间(微秒)
  RETURN:
***********************************************/
void Delay(int nDelayTime)
{
	LARGE_INTEGER litmp;
    LONGLONG QPart1,QPart2;


    bool bTimeOut=false;
    double dfFreq;

	QueryPerformanceFrequency(&litmp);// 获得计数器的时钟频率 

    dfFreq = (double) litmp.QuadPart;
	dfFreq = dfFreq/ (1000*1000) ;//////   将频率 转化为  1us 的  频率数

    QueryPerformanceCounter(&litmp); // 获得初始值 
    QPart1 = litmp.QuadPart;

	while(!bTimeOut)
	{
		QueryPerformanceCounter(&litmp); // 获得终止值 　
        QPart2 = litmp.QuadPart;

		if (( (double)(QPart2 - QPart1)  ) / dfFreq >nDelayTime)
			bTimeOut=true;////是否超时
	}
}


//生成图象文件
BOOL MakeBMP(const char* strFileName,unsigned char* pImage,int X,int Y)
{
	unsigned int num;
	int i,j;
	FILE *fp;
	unsigned char head[1078]={
							/***************************/
							//file header
							0x42,0x4d,//file type 
							//0x36,0x6c,0x01,0x00, //file size***
							0x0,0x0,0x0,0x00, //file size***
							0x00,0x00, //reserved
							0x00,0x00,//reserved
							0x36,0x4,0x00,0x00,//head byte***
							/***************************/
							//infoheader
							0x28,0x00,0x00,0x00,//struct size

							//0x00,0x01,0x00,0x00,//map width*** 
							0x00,0x00,0x00,0x00,//map width*** 
							//0x68,0x01,0x00,0x00,//map height***
							0x00,0x00,0x00,0x00,//map height***

							0x01,0x00,//must be 1
							0x08,0x00,//color count***
							0x00,0x00,0x00,0x00, //compression
							//0x00,0x68,0x01,0x00,//data size***
							0x00,0x00,0x00,0x00,//data size***
							0x00,0x00,0x00,0x00, //dpix
							0x00,0x00,0x00,0x00, //dpiy
							0x00,0x00,0x00,0x00,//color used
							0x00,0x00,0x00,0x00,//color important
											
						};
		
	fp=fopen(strFileName,"wb" );
	if( fp==NULL )
		return 0;
	//确定图象宽度数值
	num=X; head[18]= num & 0xFF;
	num=num>>8;  head[19]= num & 0xFF;
	num=num>>8;  head[20]= num & 0xFF;
	num=num>>8;  head[21]= num & 0xFF;
	//确定图象高度数值
	num=Y; head[22]= num & 0xFF;
	num=num>>8;  head[23]= num & 0xFF;
	num=num>>8;  head[24]= num & 0xFF;
	num=num>>8;  head[25]= num & 0xFF;
	
	//确定调色板数值
	j=0;
	for (i=54;i<1078;i=i+4)
	{
		head[i]=head[i+1]=head[i+2]=j; 
		head[i+3]=0;
		j++;
	}	
	
	//写入文件头
	fwrite( head,1078*sizeof(char),1,fp );
	
	//写入图象数据
	for(  i=0;i<Y; i++ )
	{
		fseek( fp,1078*sizeof(char)+(Y-1-i)*X,SEEK_SET );
		fwrite( pImage+i*X,X*sizeof(char),1,fp );
	}
	fclose(fp);
	
	return TRUE;
}
