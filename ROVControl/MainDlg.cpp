
// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ROVControl.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include <dwmapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg �Ի���




CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, m_bTcp(FALSE)
	, m_bPreview(FALSE)
	, m_bJoyStick(FALSE)
	, m_bPID(FALSE)
	, m_bMotorTest(FALSE)
	, m_bPIDCurve(FALSE)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_SETTING);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IANGULARGAUGEX1, m_motorX1);
	DDX_Control(pDX, IDC_IANGULARGAUGEX2, m_motorX2);
	DDX_Control(pDX, IDC_IANGULARGAUGEX3, m_motorX3);
	DDX_Control(pDX, IDC_IANGULARGAUGEX4, m_motorX4);
	DDX_Control(pDX, IDC_IANGULARGAUGEX5, m_motorX5);
	DDX_Control(pDX, IDC_IANGULARGAUGEX6, m_motorX6);
	DDX_Control(pDX, IDC_IANGULARGAUGEX7, m_motorX7);
	DDX_Control(pDX, IDC_IANGULARGAUGEX8, m_motorX8);
	DDX_Control(pDX, IDC_ILINEARGAUGEX1, m_deepX);
	DDX_Control(pDX, IDC_ICOMPASSX1, m_yawX);
	DDX_Control(pDX, IDC_ILINEARGAUGEX2, m_pitchX);
	DDX_Control(pDX, IDC_IANGULARGAUGEX9, m_rollX);


	/**TODO:��ȫ�ֱ����Ϳؼ���������**/
	//DDX_Text(pDX, IDC_ROLL,GlobalVar::roll);
	//DDX_Text(pDX, IDC_YAW, GlobalVar::yaw);
	//DDX_Text(pDX, IDC_PITCH,GlobalVar::pitch);
	//DDX_Text(pDX, IDC_DEEP,GlobalVar::deepness);
	DDX_Control(pDX, IDC_ILEDARROW_UP, m_moveForward);
	DDX_Control(pDX, IDC_IROTATIONDISPLAYX1, m_rotation);
	DDX_Control(pDX, IDC_ILEDARROW_LEFT, m_moveLeft);
	DDX_Control(pDX, IDC_ILEDARROW_RIGHT, m_moveRight);
	DDX_Control(pDX, IDC_ILEDARROW_DOWN, m_moveBackward);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_TCP, &CMainDlg::OnTcp)
	ON_COMMAND(ID_MOTORTEST, &CMainDlg::OnMotortest)
	ON_MESSAGE(WM_TCPCONNECT, &CMainDlg::OnTcpconnet)
	ON_MESSAGE(WM_TCPDISCONNECT, &CMainDlg::OnTcpdisconnect)
	ON_COMMAND(ID_JOYSTICK, &CMainDlg::OnJoystick)
	ON_COMMAND(ID_PREVIEW, &CMainDlg::OnPreview)
	ON_STN_DBLCLK(IDC_STATIC_PLAY, &CMainDlg::OnStnDblclickStaticPlay)
	ON_BN_CLICKED(IDC_BTN_QUICKSTART, &CMainDlg::OnBnClickedBtnQuickstart)
	ON_WM_TIMER()
	ON_COMMAND(ID_COMPENSATION, &CMainDlg::OnCompensation)
	ON_COMMAND(ID_PID, &CMainDlg::OnPid)
	ON_COMMAND(ID_APP_ABOUT, &CMainDlg::OnAppAbout)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_LIGHT, &CMainDlg::OnBnClickedButtonLight)
	ON_COMMAND(ID_PIDCURVE, &CMainDlg::OnPidcurve)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	/*******���´���Ϊ�˿���ë����Ч��*********/
	//BOOL bDwm ;
	//DwmIsCompositionEnabled (&bDwm);
	//if (bDwm){  
	//	MARGINS mrg = {-1};  
	//	DwmExtendFrameIntoClientArea (m_hWnd , &mrg );
	//	SetBackgroundColor (RGB(0, 0, 0));
	//} 
	/*::SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,::GetWindowLongPtr(GetSafeHwnd(),GWL_EXSTYLE)|WS_EX_LAYERED);
	this->SetLayeredWindowAttributes(0,(255*95)/100,LWA_ALPHA);*/

	/****************************************/

	//this->SetWindowPos(NULL,0,0,1366,768,SWP_NOMOVE|SWP_NOOWNERZORDER);
	m_LoadingDlg.DoModal(); //չʾ��½�Ի���

	GetDlgItem(IDC_BTN_QUICKSTART)->SetFocus();

	//m_motorX1.put_Position(55);
	//m_motorX2.put_Position(-22);

	m_angleCompensationFile.open(COMPENSATION_FILE_DIR,std::fstream::in|std::fstream::out);

	if(!m_angleCompensationFile.is_open()){
		CString str;
		str.Format("%s�����ڣ�Ĭ�ϴ�����ŷ�����޲���", COMPENSATION_FILE_DIR);
		MessageBox(str);
	}
	else{
		char a;
		do
		{
			m_angleCompensationFile.get(a);
		} while (a != '\n');
		//m_angleCompensationFile.get(a);
		m_angleCompensationFile >> (float)GlobalVar::compensationMatrix(0,0) >> (float)GlobalVar::compensationMatrix(0,1) >> (float)GlobalVar::compensationMatrix(0,2)
								>> (float)GlobalVar::compensationMatrix(1,0) >> (float)GlobalVar::compensationMatrix(1,1) >> (float)GlobalVar::compensationMatrix(1,2)
								>> (float)GlobalVar::compensationMatrix(2,0) >> (float)GlobalVar::compensationMatrix(2,1) >> (float)GlobalVar::compensationMatrix(2,2);
		m_angleCompensationFile.close();
		

		//GlobalVar::compensationMatrix = GlobalVar::GetCompensationMatrix(GlobalVar::yawCompensation,
		//	GlobalVar::pitchCompensation,
		//	GlobalVar::rollCompensation);
	}
	

	SetTimer(1, 200, NULL);
	SetTimer(2, 500, NULL);


	//����Resizehelpʵ�ֿ������ŶԻ���仯���仯��
	m_Resizehelper.Init(m_hWnd);

	//ActiveX�ؼ���С�̶������FIX
	m_Resizehelper.Fix(m_motorX1.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_motorX2.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_motorX3.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_motorX4.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_motorX5.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_motorX6.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_motorX7.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_motorX8.m_hWnd, DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_pitchX.m_hWnd,  DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_rollX.m_hWnd,   DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_yawX.m_hWnd,    DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);
	m_Resizehelper.Fix(m_deepX.m_hWnd,   DlgResizeHelper::kWidth, DlgResizeHelper::kHeight);

	//return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
	return FALSE;  //��ϣ��������edit�ؼ���
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		dc.SetStretchBltMode(COLORONCOLOR);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMainDlg::OnTcp()
{
	// TODO: �ڴ���������������
	if(m_bTcp == FALSE){
		m_tcpServeDlg.Create(IDD_TCPSERVE_DIALOG,this);  //��ʼ��tcpServe�Ի���	
		m_bTcp = TRUE;
	}
	
	m_tcpServeDlg.CenterWindow();
	m_tcpServeDlg.ShowWindow(SW_SHOW);
}


void CMainDlg::OnMotortest()
{
	// TODO: �ڴ���������������
	m_bMotorTest = TRUE;
	CMotorTestDlg DlgTest;
	DlgTest.DoModal();
	m_bMotorTest = FALSE;

}


afx_msg LRESULT CMainDlg::OnTcpconnet(WPARAM wParam, LPARAM lParam)
{
	GetMenu()->EnableMenuItem(ID_MOTORTEST,MF_ENABLED); //������԰�ťENABLE
	DrawMenuBar();    //���»��Ʋ˵��� ����ֻ�����ŵ��˵������������Ӧ�ı�
	return 0;
}


afx_msg LRESULT CMainDlg::OnTcpdisconnect(WPARAM wParam, LPARAM lParam)
{
	GetMenu()->EnableMenuItem(ID_MOTORTEST,MF_DISABLED||MF_GRAYED);
	DrawMenuBar();
	return 0;
}


void CMainDlg::OnJoystick()
{
	// TODO: �ڴ���������������
	if(m_bJoyStick == FALSE){
		if(!m_JoyStickDlg.Create(IDD_JOYSTICK_DIALOG,this)){
			return;
		}
		m_bJoyStick = TRUE;
	}
	m_JoyStickDlg.CenterWindow();
	m_JoyStickDlg.ShowWindow(SW_SHOW);
}


void CMainDlg::OnPreview()
{
	// TODO: �ڴ���������������
	if(m_bPreview == FALSE) {
		m_LoginDlg.DoModal();
		if(m_LoginDlg.m_bIsRunning) {
			GetMenu()->ModifyMenuA(0,MF_BYPOSITION, ID_PREVIEW, "ֹͣԤ��");
			DrawMenuBar();
			m_bPreview = TRUE;
		}
	}
	else if(m_bPreview == TRUE) {
		if(m_LoginDlg.DoClose()) {
			GetMenu()->ModifyMenuA(0,MF_BYPOSITION, ID_PREVIEW, "��ʼԤ��");
			DrawMenuBar();
			m_bPreview = FALSE;
		}
	}
}

void CMainDlg::OnStnDblclickStaticPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("˫��ȫ����ʾ����Ŀǰ��δ���!","��ʾ",MB_ICONWARNING);
}


void CMainDlg::OnBnClickedBtnQuickstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bJoyStick == FALSE){
		m_JoyStickDlg.Create(IDD_JOYSTICK_DIALOG,this);
		m_bJoyStick = TRUE;
	}

	if(m_bTcp == FALSE){
		m_tcpServeDlg.Create(IDD_TCPSERVE_DIALOG,this);  //��ʼ��tcpServe�Ի���
		m_tcpServeDlg.OnBnClickedBtnConnect();
		m_bTcp = TRUE;
	}

	if(m_bPreview == FALSE) {
		if(NET_DVR_Init()) {
			NET_DVR_SetConnectTime(2000,1);
			NET_DVR_SetReconnect(10000,TRUE);

			m_LoginDlg.m_userID = NET_DVR_Login_V30("192.168.1.139",8000,"admin","12345",&m_LoginDlg.m_deviceInfo);

			if(m_LoginDlg.m_userID != -1) {
				m_LoginDlg.m_bIsLogin = TRUE;
				if(m_LoginDlg.DoCameraPreview()) {
					m_LoginDlg.m_bIsRunning = TRUE;
					GetMenu()->ModifyMenuA(0,MF_BYPOSITION, ID_PREVIEW, "ֹͣԤ��");
					DrawMenuBar();
					m_bPreview = TRUE;
				}
			}
		}
	}
	GetDlgItem(IDC_BTN_QUICKSTART)->EnableWindow(FALSE);
}


void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if (nIDEvent == 1){	
		//if(m_LoginDlg.m_bIsRunning == TRUE && m_bJoyStick == TRUE) {	
		//	m_LoginDlg.DoAddInfo2(m_JoyStickDlg.m_XAxis,(int)m_JoyStickDlg.m_joyState->lY,m_JoyStickDlg.m_ZAxis,(int)m_JoyStickDlg.m_joyState->lRx);
		//}
		if (m_bTcp == TRUE){
			m_deepX.put_Position(GlobalVar::deepness);
			m_motorX1.put_Position(GlobalVar::motor_N1/MOTOR_RANGE*100);
			m_motorX2.put_Position(GlobalVar::motor_N2/MOTOR_RANGE*100);
			m_motorX3.put_Position(GlobalVar::motor_N3/MOTOR_RANGE*100);
			m_motorX4.put_Position(GlobalVar::motor_N4/MOTOR_RANGE*100);
			m_motorX5.put_Position(GlobalVar::motor_N5/MOTOR_RANGE*100);
			m_motorX6.put_Position(GlobalVar::motor_N6/MOTOR_RANGE*100);
			m_motorX7.put_Position(GlobalVar::motor_N7/MOTOR_RANGE*100);
			m_motorX8.put_Position(GlobalVar::motor_N8/MOTOR_RANGE*100);

			m_yawX.put_Direction(GlobalVar::yaw);
			m_pitchX.put_Position(GlobalVar::pitch);
			m_rollX.put_Position(GlobalVar::roll);

			CString str;
			//������̬�ı�����ʾ��������λ����
			str.Format("%.2f",GlobalVar::pitch);
			SetDlgItemText(IDC_PITCH,str);
			
			str.Format("%.2f",GlobalVar::roll);
			SetDlgItemText(IDC_ROLL,str);

			str.Format("%.2f",GlobalVar::yaw);
			SetDlgItemText(IDC_YAW,str);

			//���ô�����ԭʼ������ʾ��������λ����
			str.Format("%.2f",GlobalVar::pitchAngle);
			SetDlgItemText(IDC_PITCH_MTi,str);

			str.Format("%.2f",GlobalVar::rollAngle);
			SetDlgItemText(IDC_ROLL_MTi,str);

			str.Format("%.2f",GlobalVar::yawAngle);
			SetDlgItemText(IDC_YAW_MTi,str);

			UpdateData(FALSE);
		}

		if (m_JoyStickDlg.Get_FB() >= 20)
			m_moveForward.SetActiveNoEvent(TRUE);
		else
			m_moveForward.SetActiveNoEvent(FALSE);

		if (m_JoyStickDlg.Get_FB() <= -20)
			m_moveBackward.SetActiveNoEvent(TRUE);
		else
			m_moveBackward.SetActiveNoEvent(FALSE);

		if (m_JoyStickDlg.Get_LR() >= 20)
			m_moveRight.SetActiveNoEvent(TRUE);
		else
			m_moveRight.SetActiveNoEvent(FALSE);

		if (m_JoyStickDlg.Get_LR() <= -20)
			m_moveLeft.SetActiveNoEvent(TRUE);
		else
			m_moveLeft.SetActiveNoEvent(FALSE);


		m_rotation.put_RotationAngle(m_JoyStickDlg.Get_YAW()/2550.0*90.0);
	}

	//���͵��ת��ָ���������ԶԻ�����ʱ��m_bMotorTest == True����ͣ��
	if (nIDEvent == 2){
		if (m_bTcp == TRUE && m_bJoyStick == TRUE){
			//m_tcpServeDlg.SendMotorSpeed();
			if ((m_bMotorTest == FALSE) && (m_bPIDCurve == FALSE)) {
				int FB = m_JoyStickDlg.Get_FB();
				int LR = m_JoyStickDlg.Get_LR();
				int Yaw = m_JoyStickDlg.Get_YAW();
				int UD = m_JoyStickDlg.Get_UD();
				GlobalVar::motor_send[0] = -FB - LR - Yaw;
				GlobalVar::motor_send[2] = -FB + LR + Yaw;
				GlobalVar::motor_send[4] =  FB - LR + Yaw;
				GlobalVar::motor_send[6] =  FB + LR - Yaw;
				GlobalVar::motor_send[1] = -UD;
				GlobalVar::motor_send[3] = -UD;
				GlobalVar::motor_send[5] = -UD;
				GlobalVar::motor_send[7] = -UD;


				//int pidPitch = GlobalVar::pidPitch->PIDControl(0,GlobalVar::pitch,0.1);
				//int pidRoll	 = GlobalVar::pidPitch->PIDControl(0,GlobalVar::roll,0.1);

				//GlobalVar::motor_send[1] += -pidPitch + pidRoll;
				//GlobalVar::motor_send[3] += -pidPitch - pidRoll;
				//GlobalVar::motor_send[5] +=  pidPitch + pidRoll;
				//GlobalVar::motor_send[7] +=  pidPitch - pidRoll;
				m_tcpServeDlg.SendMotorSpeed();
			}
		}

		int pidPitch = GlobalVar::pidPitch->PIDControl(30,GlobalVar::pitch,0.1);
		int pidRoll	 = GlobalVar::pidRoll->PIDControl(0,GlobalVar::roll,0.1);
		GlobalVar::motor_send[1] += -pidPitch + pidRoll;
		GlobalVar::motor_send[3] += -pidPitch - pidRoll;
		GlobalVar::motor_send[5] +=  pidPitch + pidRoll;
		GlobalVar::motor_send[7] +=  pidPitch - pidRoll;

		m_tcpServeDlg.SendMotorN(GlobalVar::motor_send[0],GlobalVar::motor_send[1],GlobalVar::motor_send[2],GlobalVar::motor_send[3],GlobalVar::motor_send[4],GlobalVar::motor_send[5],GlobalVar::motor_send[6],GlobalVar::motor_send[7]);

	}


	CDialogEx::OnTimer(nIDEvent);
}

//��̬������У����ť
void CMainDlg::OnCompensation()
{
	// TODO: �ڴ���������������
	if (IDOK == MessageBox("����ȷ����У����������������ȡ��","��̬������У��",MB_OKCANCEL))
	{
		//GlobalVar::yawCompensation = GlobalVar::yawAngle;
		//GlobalVar::pitchCompensation = GlobalVar::pitchAngle;
		//GlobalVar::rollCompensation = GlobalVar::rollAngle;

		GlobalVar::compensationMatrix = GlobalVar::GetCompensationMatrix(GlobalVar::yawAngle, GlobalVar::pitchAngle, GlobalVar::rollAngle);

		m_angleCompensationFile.open(COMPENSATION_FILE_DIR,std::fstream::out);

		if(!m_angleCompensationFile.is_open()){
			MessageBox("D:\\333.txt������");
		}
		else{
			m_angleCompensationFile<<"��:\\\\1\t\\\\2\t\\\\3\n"
								<< GlobalVar::compensationMatrix(0,0) << "\t" << GlobalVar::compensationMatrix(0,1) << "\t" << GlobalVar::compensationMatrix(0,2) << "\n"
								<< GlobalVar::compensationMatrix(1,0) << "\t" << GlobalVar::compensationMatrix(1,1) << "\t" << GlobalVar::compensationMatrix(1,2) << "\n"
								<< GlobalVar::compensationMatrix(2,0) << "\t" << GlobalVar::compensationMatrix(2,1) << "\t" << GlobalVar::compensationMatrix(2,2) << "\n";
			m_angleCompensationFile.close();
		}

		MessageBox("У���ɹ���У�������ѱ���","��ʾ");
	}
	
}


void CMainDlg::OnPid()
{
	// TODO:  �ڴ���������������
	if (m_bPID == FALSE){
		if (!m_PidDlg.Create(IDD_PID_DIALOG, this)){
			return;
		}
		m_bPID = TRUE;
	}
	m_PidDlg.CenterWindow();
	m_PidDlg.ShowWindow(SW_SHOW);

}


void CMainDlg::OnAppAbout()
{
	// TODO:  �ڴ���������������
	m_LoadingDlg.DoModal();
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������

	m_Resizehelper.OnSize(); //ʵ�ֿؼ����Ŵ��ڴ�С�仯
}

void CMainDlg::OnBnClickedButtonLight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static bool b = true;
	if (b == true){
		m_tcpServeDlg.SendSwitchLight(FALSE);
		b = false;
		SetDlgItemText(IDC_BUTTON_LIGHT,"�ƹ�OFF");
	}
	else{
		m_tcpServeDlg.SendSwitchLight(TRUE);
		b = true;
		SetDlgItemText(IDC_BUTTON_LIGHT,"�ƹ�ON");
	}
}


void CMainDlg::OnPidcurve()
{
	// TODO: �ڴ���������������
	CPIDCurveDlg dlg;
	m_bPIDCurve = TRUE;
	dlg.DoModal();
	m_bPIDCurve = FALSE;
}
