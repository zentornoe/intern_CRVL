// snapping_hubDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "Listener.h"
// Csnapping_hubDlg dialog
class Csnapping_hubDlg : public CDialog
{
// Construction
public:
	Csnapping_hubDlg(CWnd* pParent = NULL);	// standard constructor
	~Csnapping_hubDlg();

// Dialog Data
	enum { IDD = IDD_snapping_hub_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()


private:
	DShowLib::Grabber		m_cGrabber[5]; // The instance of the Grabber class.

    DShowLib::FrameHandlerSink::tFHSPtr           m_pSink[5];
	CListener m_cListener[5];		// Image processing will be done by this object.

public:
	afx_msg void OnBnClickedButtondevice();
	afx_msg void OnBnClickedButtonimagesettings();
	void SetButtonStates(void);
private:
	CButton m_cButtonSettings;
	CButton m_cButtonLive;
public:
	afx_msg void OnBnClickedButtonlivevideo();
private:
	CStatic m_cStaticVideoWindow;
public:
	afx_msg void OnBnClickedButtondevice2();
	afx_msg void OnBnClickedButtondevice3();
	afx_msg void OnBnClickedButtondevice4();
	afx_msg void OnBnClickedButtondevice5();
	afx_msg void OnCbnSelchangeCombo1();
	BOOL PreTranslateMessage(MSG * pMsg);
	CEdit mEdit;
	CComboBox mCb;
};
