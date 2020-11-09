#include "stdafx.h"
#include "snapping_hub.h"
#include "snapping_hubDlg.h"
#include ".\snapping_hubdlg.h"
#include "string.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <afxdlgs.h>
#include <direct.h>
#include <windows.h>	//for Sleep();


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Save some typing...
using namespace DShowLib;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Csnapping_hubDlg dialog



Csnapping_hubDlg::Csnapping_hubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Csnapping_hubDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


Csnapping_hubDlg::~Csnapping_hubDlg()
{
}

void Csnapping_hubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTONLIVEVIDEO, m_cButtonLive);
	DDX_Control(pDX, IDC_STATICVIDEO, m_cStaticVideoWindow);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
	DDX_Control(pDX, IDC_COMBO1, mCb);
}

// Csnapping_hubDlg message handlers

BEGIN_MESSAGE_MAP(Csnapping_hubDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTONDEVICE, OnBnClickedButtondevice)
	ON_BN_CLICKED(IDC_BUTTONLIVEVIDEO, OnBnClickedButtonlivevideo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONDEVICE2, &Csnapping_hubDlg::OnBnClickedButtondevice2)
	ON_BN_CLICKED(IDC_BUTTONDEVICE3, &Csnapping_hubDlg::OnBnClickedButtondevice3)
	ON_BN_CLICKED(IDC_BUTTONDEVICE4, &Csnapping_hubDlg::OnBnClickedButtondevice4)
	ON_BN_CLICKED(IDC_BUTTONDEVICE5, &Csnapping_hubDlg::OnBnClickedButtondevice5)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Csnapping_hubDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

void Csnapping_hubDlg::SetButtonStates(void)
{
	bool bDevValid = m_cGrabber[0].isDevValid();
	bool bIsLive = m_cGrabber[1].isLive();


	m_cButtonLive.EnableWindow(bDevValid);

	if (!bDevValid)
	{
		m_cButtonLive.SetWindowText(TEXT("Live Start"));
	}


	if (bIsLive)
	{
		m_cButtonLive.SetWindowText(TEXT("Live Stop"));
	}
	else
	{
		m_cButtonLive.SetWindowText(TEXT("Live Start"));
	}


}


BOOL Csnapping_hubDlg::OnInitDialog()
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



	// Resize the video window to 640*480 pixels.
	//m_cStaticVideoWindow.SetWindowPos(NULL,0,0,640,480,SWP_NOMOVE|SWP_NOZORDER);

	// Assign this window to the Grabber object for live video display.
	m_cGrabber[0].setHWND(m_cStaticVideoWindow.m_hWnd);
	m_cGrabber[1].setHWND(m_cStaticVideoWindow.m_hWnd);
	m_cGrabber[2].setHWND(m_cStaticVideoWindow.m_hWnd);
	m_cGrabber[3].setHWND(m_cStaticVideoWindow.m_hWnd);
	m_cGrabber[4].setHWND(m_cStaticVideoWindow.m_hWnd);

	
	// Add the CListener object to the the Grabber object.
	for (int i = 0; i<5; i++)
	{
		m_cGrabber[i].addListener(&m_cListener[i]);
		m_cListener[i].SetParent(this);
	}
	for (int i = 0; i<5; i++)
	{


		// Set the sink
		m_pSink[i] = FrameHandlerSink::create(DShowLib::eRGB24, 3);
		m_pSink[i]->setSnapMode(false); // Automatically copy every frame to the sink and call CListener::frameReady().
		m_cGrabber[i].setSinkType(m_pSink[i]);

		char devName[128];
		sprintf(devName, "device_%d.xml", i);
		// Try to load the previously used video capture device.
		if (m_cGrabber[i].loadDeviceStateFromFile(devName))
		{
			m_cGrabber[i].startLive(false); // The live video will be displayed by the CListener object.
		}
	}

	SetWindowText(TEXT("snapping_hub ") + CString(m_cGrabber[0].getDev().c_str()));

	SetButtonStates();

	return TRUE;  // return TRUE unless you set the focus to a control.
}

void Csnapping_hubDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//////////////////////////////////////////////////////////////////////////
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon. For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//////////////////////////////////////////////////////////////////////////

void Csnapping_hubDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle.
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
//////////////////////////////////////////////////////////////////////////
// The system calls this function to obtain the cursor to display while
// the user dragsthe minimized window.
//////////////////////////////////////////////////////////////////////////

HCURSOR Csnapping_hubDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
// Show the device select dialog, if the "Device" button has been clicked.
// If live video is displayed, it has to be stopped.
//////////////////////////////////////////////////////////////////////////

void Csnapping_hubDlg::OnBnClickedButtondevice()
{
	// If live video is running, stop it.
	if(m_cGrabber[0].isDevValid() && m_cGrabber[0].isLive())
	{
		m_cGrabber[0].stopLive();
	}

	m_cGrabber[0].showDevicePage(this->m_hWnd);

	// If we have selected a valid device, save it to the file "device.xml", so
	// the application can load it automatically when it is started the next time.
	if( m_cGrabber[0].isDevValid())
	{
		m_cGrabber[0].saveDeviceStateToFile("device_0.xml");
	}

	// Now display the device's name in the caption bar of the application.
	SetWindowText(TEXT("snapping_hub"));

}

//////////////////////////////////////////////////////////////////////////
// Show the image settings dialog of IC Imaging Control. 
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// This method sets the states of the dialog's buttons.
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// This method starts and stops the live video.
//////////////////////////////////////////////////////////////////////////

void Csnapping_hubDlg::OnBnClickedButtonlivevideo()
{
	CString nbr;
	mCb.GetLBText(mCb.GetCurSel(), nbr);

	CString str;
	mEdit.GetWindowTextW(str);

	if( m_cGrabber[0].isDevValid())
	{
		if (m_cGrabber[0].isLive()|| m_cGrabber[1].isLive()|| m_cGrabber[2].isLive()||m_cGrabber[3].isLive()|| m_cGrabber[4].isLive())
		{
			m_cGrabber[0].stopLive();
			m_cGrabber[1].stopLive();
			m_cGrabber[2].stopLive();
			m_cGrabber[3].stopLive();
			m_cGrabber[4].stopLive();
		}
		else
		{
			//cam 1
			tFrameHandlerSinkPtr pSink1 = m_cGrabber[0].getSinkTypePtr();
			//cam 2
			tFrameHandlerSinkPtr pSink2 = m_cGrabber[1].getSinkTypePtr();
			//cam3
			tFrameHandlerSinkPtr pSink3 = m_cGrabber[2].getSinkTypePtr();
			//cam4
			tFrameHandlerSinkPtr pSink4 = m_cGrabber[3].getSinkTypePtr();
			//cam5
			tFrameHandlerSinkPtr pSink5 = m_cGrabber[4].getSinkTypePtr();

			m_cGrabber[0].startLive();
			Sleep(100);
			Error e1 = pSink1->snapImages(1);
			m_cGrabber[0].stopLive();

			m_cGrabber[1].startLive();
			Sleep(100);
			Error e2 = pSink2->snapImages(1);
			m_cGrabber[1].stopLive();

			m_cGrabber[2].startLive();
			Sleep(100);
			Error e3 = pSink3->snapImages(1);
			m_cGrabber[2].stopLive();

			m_cGrabber[3].startLive();
			Sleep(100);
			Error e4 = pSink4->snapImages(1);
			m_cGrabber[3].stopLive();

			m_cGrabber[4].startLive();
			Sleep(100);
			Error e5 = pSink5->snapImages(1);
			m_cGrabber[4].stopLive();

			str = CString("data\\") + str + "_" + nbr;

			pSink1->getLastAcqMemBuffer()->save(str + "_1.bmp");
			pSink2->getLastAcqMemBuffer()->save(str + "_2.bmp");
			pSink3->getLastAcqMemBuffer()->save(str + "_3.bmp");
			pSink4->getLastAcqMemBuffer()->save(str + "_4.bmp");
			pSink5->getLastAcqMemBuffer()->save(str + "_5.bmp");

			MessageBox(_T("Images Saved."), NULL, MB_OK);			
		}

	}
	SetButtonStates();
}

//////////////////////////////////////////////////////////////////////////

void Csnapping_hubDlg::OnClose()
{
	m_cGrabber[0].stopLive();

	CDialog::OnClose();
}


void Csnapping_hubDlg::OnBnClickedButtondevice2()
{

	// If live video is running, stop it.
	if (m_cGrabber[1].isDevValid() && m_cGrabber[1].isLive())
	{
		m_cGrabber[1].stopLive();
	}

	m_cGrabber[1].showDevicePage(this->m_hWnd);

	// If we have selected a valid device, save it to the file "device.xml", so
	// the application can load it automatically when it is started the next time.
	if (m_cGrabber[1].isDevValid())
	{
		m_cGrabber[1].saveDeviceStateToFile("device_1.xml");
	}



}


void Csnapping_hubDlg::OnBnClickedButtondevice3()
{

	// If live video is running, stop it.
	if (m_cGrabber[2].isDevValid() && m_cGrabber[2].isLive())
	{
		m_cGrabber[2].stopLive();
	}

	m_cGrabber[2].showDevicePage(this->m_hWnd);

	// If we have selected a valid device, save it to the file "device.xml", so
	// the application can load it automatically when it is started the next time.
	if (m_cGrabber[2].isDevValid())
	{
		m_cGrabber[2].saveDeviceStateToFile("device_2.xml");
	}

	

}


void Csnapping_hubDlg::OnBnClickedButtondevice4()
{

	// If live video is running, stop it.
	if (m_cGrabber[3].isDevValid() && m_cGrabber[3].isLive())
	{
		m_cGrabber[3].stopLive();
	}

	m_cGrabber[3].showDevicePage(this->m_hWnd);

	// If we have selected a valid device, save it to the file "device.xml", so
	// the application can load it automatically when it is started the next time.
	if (m_cGrabber[3].isDevValid())
	{
		m_cGrabber[3].saveDeviceStateToFile("device_3.xml");
	}



}




void Csnapping_hubDlg::OnBnClickedButtondevice5()
{

	// If live video is running, stop it.
	if (m_cGrabber[4].isDevValid() && m_cGrabber[4].isLive())
	{
		m_cGrabber[4].stopLive();
	}

	m_cGrabber[4].showDevicePage(this->m_hWnd);

	// If we have selected a valid device, save it to the file "device.xml", so
	// the application can load it automatically when it is started the next time.
	if (m_cGrabber[4].isDevValid())
	{
		m_cGrabber[4].saveDeviceStateToFile("device_4.xml");
	}



}


void Csnapping_hubDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}

BOOL Csnapping_hubDlg::PreTranslateMessage(MSG* pMsg)
{
	CString defa;
	mEdit.GetWindowTextW(defa);
	if ("" == defa) {
		mEdit.SetCueBanner(_T("First enter the file name..."), TRUE);
	}
	else {

		if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT1)->m_hWnd && pMsg->wParam == VK_RETURN) {	//is "Enter" pressed?
			Csnapping_hubDlg::OnBnClickedButtonlivevideo();	//call : capture fuction
		}

		return 0;
		//if you press "Enter" -> Capture function will work
	}
}
