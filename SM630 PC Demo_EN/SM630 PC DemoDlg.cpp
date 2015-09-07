// SM630 PC DemoDlg.cpp : implementation file
//
#include "SM630_DLL.h"
#include "stdafx.h"
#include "SM630 PC Demo.h"
#include "SM630 PC DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSM630PCDemoDlg *pDlg;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSM630PCDemoDlg dialog

CSM630PCDemoDlg::CSM630PCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSM630PCDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSM630PCDemoDlg)
	m_Comm = -1;
	m_YMessage = _T("");
	m_BanBen = _T("");
	pDlg = this;
	m_StrNumber = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSM630PCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSM630PCDemoDlg)
	DDX_Control(pDX, IDC_EDIT_Number, m_ctl_Number);
	DDX_Radio(pDX, IDC_RADIO1, m_Comm);
	DDX_Text(pDX, IDC_STATIC_TI, m_YMessage);
	DDX_Text(pDX, IDC_STATIC_Ban, m_BanBen);
	DDX_Text(pDX, IDC_EDIT_Number, m_StrNumber);
	DDV_MaxChars(pDX, m_StrNumber, 3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSM630PCDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSM630PCDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSM630PCDemoDlg message handlers

BOOL CSM630PCDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Comm = 0;
	m_YMessage = "IDLE";
	UpdateData(FALSE);//update display
	m_ctl_Number.SetWindowText("0");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSM630PCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSM630PCDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSM630PCDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSM630PCDemoDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	ReleaseCom();

	return CDialog::DestroyWindow();
}

void CSM630PCDemoDlg::ShowBMP(void)
{
	CStatic *pStatic;
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)LoadImage( GetModuleHandle(NULL),(LPCTSTR)"Test.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap  == NULL)
			hBitmap  = (HBITMAP)LoadImage( NULL,(LPCTSTR)"Test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	pStatic=(CStatic *)GetDlgItem(IDC_STATIC_Image);
	pStatic->SetBitmap(hBitmap);//show picture
	DeleteObject(hBitmap);
}

void CSM630PCDemoDlg :: DisableButton(void)
{
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
}

void CSM630PCDemoDlg :: EnableButton(void)
{
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
}

void Test630Return(CString* p)
{
	ReleaseCom();

	pDlg->m_YMessage = *p;
	pDlg->GetDlgItem(IDC_STATIC_TI)->SetWindowText(pDlg->m_YMessage);//update display
	pDlg->EnableButton();
}

UINT ReadVersion(LPVOID pParam)
{
	unsigned int Step = 0;
	unsigned char ch;
	unsigned char pData[MAX_PACKAGE_SIZE];

	CString Stemp;

	//步骤0 读取版本号
	//-------------------------------------------------------------------------
	ch=C_READ_IDENTIFIER;	//0x80//读取产品标识
	//发送命令
	FillPackage(pData,C_COMMAND,1,&ch);
	if(!SendPackage(pData))
	{
		//Stemp = "发送数据失败";
		Stemp = "Send Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//接收回应
	if(!GetPackage(pData,1))
	{
		//Stemp = "接收失败";
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(VerifyResponsePackage(pData[2], pData))
	{
		//Stemp = "校验和错误";
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[4]!=C_GET_OK)
	{
		//Stemp = "指令返回错误";
		Stemp = "Response Code Error!";
		Test630Return(&Stemp);
		return 1;	
	}

	//接收返回值
	if(!GetPackage(pData,1))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}	
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}

	//display success
	unsigned char Temp[25];
	memcpy(Temp,&pData[5],24);
	Temp[24] = 0;
	pDlg->m_BanBen.Format("%s",Temp);
	pDlg->GetDlgItem(IDC_STATIC_Ban)->SetWindowText(pDlg->m_BanBen);//update display

	//Stemp = "版本号读取成功";
	Stemp = "Read Version Success!";
	Test630Return(&Stemp);

	return 1;
}

void CSM630PCDemoDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//update display

	if(!InitCom(m_Comm + 1,0))
	{
		AfxMessageBox("Open COM Failure!");
		return;
	}

	//show status
	m_YMessage = "Reading Version...";
	
	UpdateData(FALSE);//update display

	DisableButton();

	//2 startup thread
	AfxBeginThread(ReadVersion,NULL);
}

UINT ReadImage(LPVOID pParam)
{
	unsigned int i;
	unsigned int j;
	unsigned int Step = 0;
	unsigned int Length;
	unsigned char ch;
	unsigned char pData[MAX_PACKAGE_SIZE];

	CString Stemp;

	ch=C_ENTER_BL;	//0x80//读取产品标识
	//发送命令
	FillPackage(pData,C_COMMAND,1,&ch);
	if(!SendPackage(pData))
	{
		Stemp = "Send Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//接收回应
	if(!GetPackage(pData,1))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[4]!=C_GET_OK)
	{
		Stemp = "Response Code Error!";
		Test630Return(&Stemp);
		return 1;	
	}


	//pDlg->m_YMessage = "请放手指";
	pDlg->m_YMessage = "Put on the finger...";
	pDlg->GetDlgItem(IDC_STATIC_TI)->SetWindowText(pDlg->m_YMessage);

	unsigned char pTemplate[128*152];
	int nFileLength=128*152;
	memset(pTemplate, 0, nFileLength);
	ch= C_UP_IMAGE;   //			0x93//upload picture
	FillPackage(pData,C_COMMAND,1,&ch);
	if(!SendPackage(pData))
	{
		Stemp = "Send Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//receive responses
	if(!GetPackage(pData,1))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[4]!=C_GET_OK)
	{
		Stemp = "Response Code Error!";
		Test630Return(&Stemp);
		return 1;	
	}

	for(j=0;j<152;j++)
	{
		//recevie responses info.
		if(!GetPackage(pData,100))
		{
			Stemp = "Receive Data Failure!";
			Test630Return(&Stemp);
			return 1;
		}

		if(VerifyResponsePackage(pData[2], pData))
		{
			Stemp = "Checkout Error!";
			Test630Return(&Stemp);
			return 1;
		}

		if(j==0)
		{
			if(pData[5]==ANSWER_OUT_TIME)
			{
				Stemp = "No finger...";
				Test630Return(&Stemp);
				return 1;
			}

 		}

		unsigned int t = (j*100)/152;
		//pDlg->m_YMessage.Format("正在上传图像 已完成 %d",t);
		pDlg->m_YMessage.Format("Uploading picture. Completed %d",t);
		pDlg->m_YMessage += "%";
		pDlg->GetDlgItem(IDC_STATIC_TI)->SetWindowText(pDlg->m_YMessage);
		
		Length = GetPackageLength(pData); 
		for(i=0;i<128;i++)
		{
			pTemplate[128*j+i]=pData[i+4];
		}
		
		unsigned char nchar=0X01;
		FillPackage(pData,C_ANSWER,1,&nchar);
		if(!SendPackage(pData))
		{
			Stemp = "Send Data Failure!";
			Test630Return(&Stemp);
			return 1;
		}
	}

	//show picture
	if(0 == MakeBMP("test.bmp", pTemplate,128,152))
	{
		//Stemp = "生成图像失败";
		Stemp = "Create picture failure!";
		Test630Return(&Stemp);
		return 1;
	}
	pDlg->ShowBMP();

	//Stemp = "上传图像成功";
	Stemp = "Upload picture success!";
	Test630Return(&Stemp);

	return 1;
}

void CSM630PCDemoDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//update display

	if(!InitCom(m_Comm + 1,0))
	{
		AfxMessageBox("Open COM Failure!");
		return;
	}

	//show status
	//m_YMessage = "正在读取图像";
	m_YMessage = "Upload picture...";
	
	UpdateData(FALSE);//update display

	DisableButton();

	//2 startup thread
	AfxBeginThread(ReadImage,NULL);
}

unsigned int FingerNumber = 0;

UINT AddFinger(LPVOID pParam)
{
	unsigned int Step = 0;
	unsigned char pData[MAX_PACKAGE_SIZE];
	
	CString Stemp;

	//pDlg->m_YMessage = "请按手指";
	pDlg->m_YMessage = "Press finger...";
	pDlg->GetDlgItem(IDC_STATIC_TI)->SetWindowText(pDlg->m_YMessage);//update display
	unsigned char tch[10];
	tch[0] = C_ADD_FINGER;       //		0x40//add fingerprint
	tch[1] = FingerNumber>>8;
	tch[2] = FingerNumber;
	FillPackage(pData,C_COMMAND,3,tch);
	
	if(!SendPackage(pData))
	{
		Stemp = "Send Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//receive responses 
	if(!GetPackage(pData,1))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[4]!=C_GET_OK)
	{
		Stemp = "Response Code Error!";
		Test630Return(&Stemp);
		return 1;	
	}

	//receive responses value
	if(!GetPackage(pData,100))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}	
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[5]==ANSWER_NUMBER_E)
	{
		//Stemp = "编号错误";
		Stemp = "Number error!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_OUT_TIME)
	{
		//Stemp = "没有手指";
		Stemp = "Don't detect finger!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_FAIL)
	{
		//Stemp = "指纹处理失败";
		Stemp = "Deal with fingerprint failure!";
		Test630Return(&Stemp);
		return 1;
	}
	//pDlg->m_YMessage = "请再按一次";
	pDlg->m_YMessage = "Press again.";
	pDlg->GetDlgItem(IDC_STATIC_TI)->SetWindowText(pDlg->m_YMessage);//update display
	//recevie responses value
	if(!GetPackage(pData,100))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}	
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[5]==ANSWER_NUMBER_E)
	{
		Stemp = "Number error!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_OUT_TIME)
	{
		Stemp = "Don't detect finger!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_FAIL)
	{
		Stemp = "Deal with fingerprint failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//Stemp = "增加指纹成功";
	Stemp = "Add fingerprint success!";
	Test630Return(&Stemp);

	return 1;
}

void CSM630PCDemoDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//update display

	if(!InitCom(m_Comm + 1,0))
	{
		AfxMessageBox("Open COM Failure!");
		return;
	}

	//show status
	//m_YMessage = "增加手指";
	m_YMessage = "Add fingerprint...";
	
	FingerNumber =atoi((char*)(LPCTSTR)m_StrNumber);

	if(FingerNumber>=768 || FingerNumber<0)
	{
		CString Stemp;
		//Stemp = "请输入正确指纹编号";
		Stemp = "Input error!(0~768)";
		Test630Return(&Stemp);
		return;
	}

	UpdateData(FALSE);//update display

	DisableButton();

	//2 开启线程
	AfxBeginThread(AddFinger,NULL);
}

UINT SearchFinger(LPVOID pParam)
{
	unsigned int Step = 0;
	unsigned char pData[MAX_PACKAGE_SIZE];
	
	CString Stemp;
	unsigned char tch[10];

	pDlg->m_YMessage = "Press finger...";
	pDlg->GetDlgItem(IDC_STATIC_TI)->SetWindowText(pDlg->m_YMessage);//update display
	tch[0]=C_SEARCH_FINGER;		     //0x44//搜索指纹
	tch[1]=0;
	tch[2]=0;
	tch[3]=3;
	tch[4]=0;
	FillPackage(pData,C_COMMAND,5,tch);
	
	if(!SendPackage(pData))
	{
		Stemp = "Send Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//接收回应
	if(!GetPackage(pData,1))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[4]!=C_GET_OK)
	{
		Stemp = "Response Code Error!";
		Test630Return(&Stemp);
		return 1;	
	}

	//接收返回值
	if(!GetPackage(pData,100))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}	
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[5]==ANSWER_NUMBER_E)
	{
		Stemp = "Number error!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_OUT_TIME)
	{
		Stemp = "Don't detect finger!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_FAIL)
	{
		Stemp = "Deal with fingerprint failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]!=ANSWER_OK)
	{
		//Stemp = "未知错误";
		Stemp = "Unknown error!";
		Test630Return(&Stemp);
		return 1;
	}
	//接收返回值
	if(!GetPackage(pData,100))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}	
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[5]==ANSWER_NUMBER_E)
	{
		Stemp = "Number error!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_OUT_TIME)
	{
		Stemp = "Don't detect finger!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_FAIL)
	{
		Stemp = "Deal with fingerprint failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]==ANSWER_NO_SEARCHED)
	{
		//Stemp = "没有找到指纹";
		Stemp = "No fingerprint!";
		Test630Return(&Stemp);
		return 1;
	}
	if(pData[5]!=ANSWER_SEARCHED)
	{
		Stemp = "Unknown error!";
		Test630Return(&Stemp);
		return 1;
	}

	unsigned long t = pData[6]<<8;
	t += pData[7];
	//Stemp.Format("搜索到指纹  编号：%d",t);
	Stemp.Format("Fingerprint number: %d",t);
	Test630Return(&Stemp);

	return 1;
}

void CSM630PCDemoDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//update display

	if(!InitCom(m_Comm + 1,0))
	{
		AfxMessageBox("Open COM Failure!");
		return;
	}

	//显示状态
	m_YMessage = "Searching...";
	
	UpdateData(FALSE);//update display

	DisableButton();

	//2 开启线程
	AfxBeginThread(SearchFinger,NULL);	
}

UINT DelFinger(LPVOID pParam)
{
	unsigned int Step = 0;
	unsigned char pData[MAX_PACKAGE_SIZE];
	
	CString Stemp;
	unsigned char tch[10];

	tch[0]=C_DEL_FINGER;     //清空指纹库
	tch[1]=FingerNumber>>8;
	tch[2]=FingerNumber;

	//发送命令
	FillPackage(pData,C_COMMAND,3,tch);
	if(!SendPackage(pData))
	{
		Stemp = "Send Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//接收回应
	if(!GetPackage(pData,10))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[4]!=C_GET_OK)
	{
		Stemp = "Response Code Error!";
		Test630Return(&Stemp);
		return 1;	
	}

	//接收返回值
	if(!GetPackage(pData,10))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}	
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[5]!=ANSWER_OK)
	{
		//Stemp = "删除指纹失败";
		Stemp = "Delete fingerprint failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//Stemp = "删除指纹成功";
	Stemp = "Delete fingerprint success!";
	Test630Return(&Stemp);

	return 1;
}

void CSM630PCDemoDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//update display

	if(!InitCom(m_Comm + 1,0))
	{
		AfxMessageBox("Open COM Failure!");
		return;
	}

	//显示状态
	//m_YMessage = "删除指纹";
	m_YMessage = "Deleting...";
	
	FingerNumber =atoi((char*)(LPCTSTR)m_StrNumber);

	if(FingerNumber>=768)
	{
		CString Stemp;
		//Stemp = "请输入正确指纹编号";
		Stemp = "Input the fingerprint number...";
		Test630Return(&Stemp);
		return;
	}

	UpdateData(FALSE);//update display

	DisableButton();

	//2 开启线程
	AfxBeginThread(DelFinger,NULL);	
}

UINT EmptyFinger(LPVOID pParam)
{
	unsigned int Step = 0;
	unsigned char ch;
	unsigned char pData[MAX_PACKAGE_SIZE];
	
	CString Stemp;

	ch=C_EMPTY_FINGER;     //清空指纹库
	//发送命令
	FillPackage(pData,C_COMMAND,1,&ch);
	if(!SendPackage(pData))
	{
		Stemp = "Send Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//接收回应
	if(!GetPackage(pData,10))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[4]!=C_GET_OK)
	{
		Stemp = "Response Code Error!";
		Test630Return(&Stemp);
		return 1;	
	}

	//接收返回值
	if(!GetPackage(pData,1))
	{
		Stemp = "Receive Data Failure!";
		Test630Return(&Stemp);
		return 1;
	}	
	if(VerifyResponsePackage(pData[2], pData))
	{
		Stemp = "Checkout Error!";
		Test630Return(&Stemp);
		return 1;
 	}
	if(pData[5]!=ANSWER_OK)
	{
		//Stemp = "清空指纹失败";
		Stemp = "Empty fingerprint failure!";
		Test630Return(&Stemp);
		return 1;
	}

	//Stemp = "清空指纹成功";
	Stemp = "Empty fingeprint success!";
	Test630Return(&Stemp);

	return 1;
}

void CSM630PCDemoDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//update display

	if(!InitCom(m_Comm + 1,0))
	{
		//AfxMessageBox("串口打开失败");
		AfxMessageBox("Open COM Failure!");
		return;
	}

	//显示状态
	//m_YMessage = "清空指纹";
	m_YMessage = "Emptying...";
	
	UpdateData(FALSE);//update display

	DisableButton();

	//2 开启线程
	AfxBeginThread(EmptyFinger,NULL);	
}
