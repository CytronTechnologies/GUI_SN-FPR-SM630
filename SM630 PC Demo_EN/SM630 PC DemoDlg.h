// SM630 PC DemoDlg.h : header file
//

#if !defined(AFX_SM630PCDEMODLG_H__F69F8D1E_4001_450C_B6CB_AFE8B317A8AD__INCLUDED_)
#define AFX_SM630PCDEMODLG_H__F69F8D1E_4001_450C_B6CB_AFE8B317A8AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSM630PCDemoDlg dialog

class CSM630PCDemoDlg : public CDialog
{
// Construction
public:
	CSM630PCDemoDlg(CWnd* pParent = NULL);	// standard constructor

	void EnableButton(void);
	void DisableButton(void);
	void ShowBMP(void);

// Dialog Data
	//{{AFX_DATA(CSM630PCDemoDlg)
	enum { IDD = IDD_SM630PCDEMO_DIALOG };
	CEdit	m_ctl_Number;
	int		m_Comm;
	CString	m_YMessage;
	CString	m_BanBen;
	CString	m_StrNumber;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSM630PCDemoDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSM630PCDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SM630PCDEMODLG_H__F69F8D1E_4001_450C_B6CB_AFE8B317A8AD__INCLUDED_)
