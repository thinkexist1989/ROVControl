// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ROVControl.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_cameraPort(8000)
	,m_cameraPort2(6002)
	, m_userName(_T("admin"))
	, m_userName2(_T("admin"))
	, m_userPSWD(_T("Xiaolong159753"))
	, m_userPSWD2(_T("admin"))
	, m_userID(-1)
	, m_realplayHandle(-1)
	, m_bIsRunning(FALSE)
	, m_bIsRunning2(FALSE)
	, m_bIsRecording(FALSE)
	, m_bIsLogin(FALSE)
{

	m_ipValue = htonl(inet_addr("192.168.1.139"));
	m_ipValue2 = htonl(inet_addr("192.168.1.99"));
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAMERAIP, m_cameraIp);
	DDX_Control(pDX, IDC_CAMERAIP2, m_cameraIp2);
	DDX_Text(pDX, IDC_CAMERAPORT, m_cameraPort);
	DDX_Text(pDX, IDC_CAMERAPORT2, m_cameraPort2);
	DDX_Text(pDX, IDC_USERNAME, m_userName);
	DDX_Text(pDX, IDC_USERNAME2, m_userName2);
	DDX_Text(pDX, IDC_PASSWD, m_userPSWD);
	DDX_Text(pDX, IDC_PASSWD2, m_userPSWD2);
	DDX_IPAddress(pDX, IDC_CAMERAIP, m_ipValue);
	DDX_IPAddress(pDX, IDC_CAMERAIP2, m_ipValue2);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK2, &CLoginDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bIsLogin) {
		if(DoLogin()) {
			m_bIsLogin = TRUE;
			if(DoCameraPreview())
				m_bIsRunning = TRUE;
		}
	}
	
	//CDialogEx::OnOK();
}

BOOL CLoginDlg::DoLogin()
{
	UpdateData(TRUE);
	
	CString DeviceIp;
	BYTE nField0,nField1,nField2,nField3; 
	m_cameraIp.GetAddress(nField0,nField1,nField2,nField3);
	DeviceIp.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);

	memset(&m_deviceInfo,0,sizeof(NET_DVR_DEVICEINFO_V30));

	m_userID = NET_DVR_Login_V30(DeviceIp.GetBuffer(DeviceIp.GetLength()),m_cameraPort, \
		m_userName.GetBuffer(m_userName.GetLength()),m_userPSWD.GetBuffer(m_userPSWD.GetLength()),&m_deviceInfo);
	if(m_userID == -1)
	{
		MessageBox("登陆失败，请重新登陆!\n");
		return FALSE;
	}

	return TRUE;
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(NET_DVR_Init()) {
		NET_DVR_SetConnectTime(2000,1);
		NET_DVR_SetReconnect(10000,TRUE);
	}
	else {
		MessageBox("初始化HCNetSDK失败！");
		OnCancel();
	}

	m_hPreview = ::TMCC_Init(TMCC_INITTYPE_REALSTREAM);

	if(m_hPreview == NULL) {
		MessageBox("初始化安霸SDK失败！");
		OnCancel();
	}
	else{
		::TMCC_SetAutoReConnect(m_hPreview, TRUE);        //设置断开重连
		::TMCC_SetDisplayShow(m_hPreview, TRUE);          //设置显示
		::TMCC_SetStreamBufferTime(m_hPreview, 0);        //设置显示前缓冲时间
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CLoginDlg::DoCameraPreview()
{
	//m_previewInfo.hPlayWnd	     = GetParent()->GetDlgItem(IDC_STATIC_PLAY)->m_hWnd;
	m_previewInfo.hPlayWnd       = AfxGetMainWnd()->GetDlgItem(IDC_STATIC_PLAY)->m_hWnd;
	m_previewInfo.lChannel		 = m_deviceInfo.byStartChan;
	m_previewInfo.dwStreamType	 = 0;
	m_previewInfo.dwLinkMode	 = 0;
	m_previewInfo.bBlocked		 = TRUE;

	m_realplayHandle = NET_DVR_RealPlay_V40(m_userID, &m_previewInfo, NULL, NULL);
	if(m_realplayHandle == -1) {
//		MessageBox("启动实时预览失败！");
		return FALSE;
	}
	return TRUE;
}

BOOL CLoginDlg::DoClose()
{
	DoStopPlaying();
	NET_DVR_Logout_V30(m_userID); 
	m_userID = -1;
	m_bIsLogin = FALSE;
	return TRUE;
}

BOOL CLoginDlg::DoStopPlaying()
{
	if(m_realplayHandle != -1) {
		if(m_bIsRecording) {
			//StopRecord();
		}
		NET_DVR_StopRealPlay(m_realplayHandle);
		m_realplayHandle=-1;
		m_bIsRunning = FALSE;
	}

	return TRUE;
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CLoginDlg::DoAddInfo( int depth, float pitch, float roll, float yaw )
{
	NET_DVR_SHOWSTRINGINFO depthInfo;
	depthInfo.wShowString = 1;
	depthInfo.wStringSize = 12;
	depthInfo.wShowStringTopLeftX = 10;
	depthInfo.wShowStringTopLeftY = 10;
	//strcpy(depthInfo.sString,"DEPTH:000");
	strcpy_s(depthInfo.sString,"DEPTH:000");

	NET_DVR_SHOWSTRINGINFO pitchInfo;
	pitchInfo.wShowString = 1;
	pitchInfo.wStringSize = 12;
	pitchInfo.wShowStringTopLeftX = 10;
	pitchInfo.wShowStringTopLeftY = 40;
	strcpy_s(pitchInfo.sString,"PITCH:000.00");

	NET_DVR_SHOWSTRINGINFO rollInfo;
	rollInfo.wShowString = 1;
	rollInfo.wStringSize = 12;
	rollInfo.wShowStringTopLeftX = 10;
	rollInfo.wShowStringTopLeftY = 70;
	strcpy_s(rollInfo.sString,"ROLL:000.00");

	NET_DVR_SHOWSTRINGINFO yawInfo;
	yawInfo.wShowString = 1;
	yawInfo.wStringSize = 12;
	yawInfo.wShowStringTopLeftX = 10;
	yawInfo.wShowStringTopLeftY = 100;
	strcpy_s(yawInfo.sString,"YAW:000.00");


	NET_DVR_SHOWSTRING showString;
	showString.dwSize = sizeof(NET_DVR_SHOWSTRING);
	showString.struStringInfo[0] = depthInfo;
	showString.struStringInfo[1] = pitchInfo;
	showString.struStringInfo[2] = rollInfo;
	showString.struStringInfo[3] = yawInfo;

	BOOL bResult = NET_DVR_SetDVRConfig(m_userID, NET_DVR_SET_SHOWSTRING, m_deviceInfo.byStartChan, &showString, sizeof(NET_DVR_SHOWSTRING));
	if(!bResult) {
		MessageBox("添加字符串失败！");
	}
}

void CLoginDlg::DoAddInfo2( int X, int Y, int Z, int Rz )
{
	NET_DVR_SHOWSTRINGINFO XInfo;
	XInfo.wShowString = 1;
	XInfo.wStringSize = 12;
	XInfo.wShowStringTopLeftX = 10;
	XInfo.wShowStringTopLeftY = 10;
	sprintf_s(XInfo.sString,"X:%d",X);

	NET_DVR_SHOWSTRINGINFO YInfo;
	YInfo.wShowString = 1;
	YInfo.wStringSize = 12;
	YInfo.wShowStringTopLeftX = 10;
	YInfo.wShowStringTopLeftY = 40;
	sprintf_s(YInfo.sString,"Y:%d",Y);

	NET_DVR_SHOWSTRINGINFO ZInfo;
	ZInfo.wShowString = 1;
	ZInfo.wStringSize = 12;
	ZInfo.wShowStringTopLeftX = 10;
	ZInfo.wShowStringTopLeftY = 70;
	sprintf_s(ZInfo.sString,"Z:%d",Z);

	NET_DVR_SHOWSTRINGINFO RzInfo;
	RzInfo.wShowString = 1;
	RzInfo.wStringSize = 12;
	RzInfo.wShowStringTopLeftX = 10;
	RzInfo.wShowStringTopLeftY = 100;
	sprintf_s(RzInfo.sString,"Rz:%d",Rz);



	NET_DVR_SHOWSTRING showString;
	showString.dwSize = sizeof(NET_DVR_SHOWSTRING);
	showString.struStringInfo[0] = XInfo;
	showString.struStringInfo[1] = YInfo;
	showString.struStringInfo[2] = ZInfo;
	showString.struStringInfo[3] = RzInfo;

	BOOL bResult = NET_DVR_SetDVRConfig(m_userID, NET_DVR_SET_SHOWSTRING, m_deviceInfo.byStartChan, &showString, sizeof(NET_DVR_SHOWSTRING));
	if(!bResult) {
		MessageBox("添加字符串失败！");
	}
}


void CLoginDlg::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bIsRunning2) {
		m_hPreview = ::TMCC_Init(TMCC_INITTYPE_REALSTREAM);
		if(NULL != m_hPreview) {
			::TMCC_SetAutoReConnect(m_hPreview, TRUE);        //设置断开重连
			::TMCC_SetDisplayShow(m_hPreview, TRUE);          //设置显示
			::TMCC_SetStreamBufferTime(m_hPreview, 0);        //设置显示前缓冲时间

			tmPlayRealStreamCfg_t	info;
			memset(&info, 0, sizeof(tmPlayRealStreamCfg_t));
			info.dwSize = sizeof(tmPlayRealStreamCfg_t);    //该结构大小

			UpdateData(TRUE);

			CString DeviceIp;
			BYTE nField0,nField1,nField2,nField3; 
			m_cameraIp2.GetAddress(nField0,nField1,nField2,nField3);
			DeviceIp.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);

			sprintf(info.szAddress, "%s",DeviceIp); //要连接的设备的IP地址
			sprintf(info.szUser, "%s", m_userName2);           //用户名
			sprintf(info.szPass, "%s", m_userPSWD2);           //密码
			info.iPort     = m_cameraPort2;                          //设备端口
			info.byChannel = 0;                             //通道号
			info.byStream  = 0;                             //码流类型 【0-主码流，1-从码流】

			int iRet = ::TMCC_ConnectStream(m_hPreview, &info, AfxGetMainWnd()->GetDlgItem(IDC_STATIC_PLAY2)->m_hWnd);//第三个参数传递要显示视频的窗口句柄

			if(iRet == TMCC_ERR_SUCCESS) {
				m_bIsRunning2 = TRUE;
			}
		}
	}

}
