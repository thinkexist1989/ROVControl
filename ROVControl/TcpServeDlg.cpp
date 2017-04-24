// TcpServeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ROVControl.h"
#include "TcpServeDlg.h"
#include "afxdialogex.h"
#include "GlobalVar.h"
#include "chartofloat.h"
#include "iswitchled_deep.h"


// CTcpServeDlg �Ի���

IMPLEMENT_DYNAMIC(CTcpServeDlg, CDialogEx)

CTcpServeDlg::CTcpServeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTcpServeDlg::IDD, pParent)
{
	m_portDeep = 0;
	m_portPose = 0;
	m_showMsg = _T("");
}

SOCKET CTcpServeDlg::m_socket_Deep_listen = INVALID_SOCKET;
SOCKET CTcpServeDlg::m_socket_Pose_listen = INVALID_SOCKET;
SOCKET CTcpServeDlg::m_sockConn_Pose = INVALID_SOCKET;
SOCKET CTcpServeDlg::m_sockConn_Deep = INVALID_SOCKET;
SOCKET CTcpServeDlg::m_sockConn_Motor = INVALID_SOCKET;
SOCKET CTcpServeDlg::m_sockConn_Test = INVALID_SOCKET;
bool   CTcpServeDlg::m_bConnectDeep = FALSE;
bool   CTcpServeDlg::m_bConnectPose = FALSE;
bool CTcpServeDlg::m_bYaw = FALSE;
bool CTcpServeDlg::m_bPitch = FALSE;
bool CTcpServeDlg::m_bRoll = FALSE; 

bool CTcpServeDlg::m_bPose = FALSE;
bool CTcpServeDlg::m_bDeep = FALSE;

std::ofstream CTcpServeDlg::m_pitchFile(MTI_PITCH_FILE_DIR);
std::ofstream CTcpServeDlg::m_rollFile(MTI_ROLL_FILE_DIR);
std::ofstream CTcpServeDlg::m_yawFile(MTI_YAW_FILE_DIR);


CTcpServeDlg::~CTcpServeDlg()
{
	m_pitchFile.close();
	m_rollFile.close();
	m_yawFile.close();
}

void CTcpServeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IPADDRESS, m_dwIP);
	DDX_Text(pDX, IDC_EDIT_PORT1, m_portDeep);
	DDV_MinMaxInt(pDX, m_portDeep, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_portPose);
	DDV_MinMaxInt(pDX, m_portPose, 0, 65535);
	DDX_Text(pDX, IDC_SHOWMSG, m_showMsg);
	DDX_Control(pDX, IDC_ISWITCHLED_POSE, m_pose_connected);
	DDX_Control(pDX, IDC_ISWITCHLED_MOTOR, m_motor_connected);
}


BEGIN_MESSAGE_MAP(CTcpServeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CTcpServeDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, &CTcpServeDlg::OnBnClickedBtnDisconnect)
	ON_MESSAGE(WM_SOCKETCONNECTED, &CTcpServeDlg::OnSocketconnected)
END_MESSAGE_MAP()


void CTcpServeDlg::OnBnClickedBtnConnect()
{
	UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetConnect(m_socket_Deep_listen,m_portDeep,m_bConnectDeep);
	SetConnect(m_socket_Pose_listen,m_portPose,m_bConnectPose);

	if(m_bConnectDeep && m_bConnectPose){
		CString str;
		CTime tm = CTime::GetCurrentTime();
		str =tm.Format("%Y��%m��%d�� %X��");
		m_showMsg += str;
		m_showMsg += "�˿���ȫ���󶨳ɹ�\r\n";

		GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BTN_CONNECT,"������");

		//int a = THREAD_ID_DEEP;
		//HANDLE hThreadDeep = CreateThread(NULL,0,ThreadProcDeep,NULL,0,NULL);
		//CloseHandle(hThreadDeep);

		//a = THREAD_ID_POSE;
		//HANDLE hThreadPose = CreateThread(NULL,0,ThreadProcPose,NULL,0,NULL);
		//CloseHandle(hThreadPose);

		HANDLE hThreadWaitForSocket = CreateThread(NULL,0,ThreadProcWaitForSocket,(LPVOID)this,0,NULL);

		::SendMessage(GetParent()->m_hWnd,WM_TCPCONNECT,NULL,NULL);

	}
	if(m_bConnectDeep || m_bConnectPose){
		GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);

	
}


void CTcpServeDlg::OnBnClickedBtnDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if(m_bConnectDeep && m_bConnectPose){
		
		m_bConnectDeep = FALSE;
		m_bConnectPose = FALSE;

		closesocket(m_socket_Deep_listen);
		closesocket(m_socket_Pose_listen);

		CString str;
		CTime tm = CTime::GetCurrentTime();
		str =tm.Format("%Y��%m��%d�� %X��");
		m_showMsg += str;
		m_showMsg += "�׽�����ȫ���ر�\r\n";

		m_pose_connected.SetActiveNoEvent(FALSE);
		m_motor_connected.SetActiveNoEvent(FALSE);

		::SendMessage(GetParent()->m_hWnd,WM_TCPDISCONNECT,NULL,NULL);

	}
	else{
		if(m_bConnectDeep == TRUE) {
			m_bConnectDeep = FALSE;		
			closesocket(m_socket_Deep_listen);

			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			m_showMsg += "��ȶ˿��׽����ѹر�\r\n";	
						
			::SendMessage(GetParent()->m_hWnd,WM_TCPDISCONNECT,NULL,NULL);
		}
		else{
			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			m_showMsg += "��ȶ˿�δ��������\r\n";
		}

		if(m_bConnectPose == TRUE) {
			m_bConnectPose = FALSE;		
			closesocket(m_socket_Pose_listen);

			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			m_showMsg += "��̬�˿��׽����ѹر�\r\n";
		}
		else{
			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			m_showMsg += "��̬�˿�δ��������\r\n";
		}
	}

	if(~(m_bConnectDeep & m_bConnectPose)){
		GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
		SetDlgItemText(IDC_BTN_CONNECT,"��������");
	}
	UpdateData(FALSE);
}

BOOL CTcpServeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_IPADDRESS,"192.168.1.1");   //��ʼ��IP��ַ�ؼ���EDIT�ؼ�ΪĬ�ϵ�ֵ
	SetDlgItemInt(IDC_EDIT_PORT1,6);
	SetDlgItemInt(IDC_EDIT_PORT2,7);

	//m_pitchFile.open(MTI_PITCH_FILE_DIR);
	//m_rollFile.open(MTI_ROLL_FILE_DIR);
	//m_yawFile.open(MTI_YAW_FILE_DIR);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CTcpServeDlg::SetConnect(SOCKET &sock, int &port,bool &mark)
{
	if(mark == FALSE) {

		sock = socket(AF_INET,SOCK_STREAM,0);

		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr = htonl(m_dwIP);
		addrSrv.sin_port = htons(port);
		addrSrv.sin_family = AF_INET;

		int retval = bind(sock,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
		if(SOCKET_ERROR == retval){
			closesocket(sock);
			
			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			str.Format("�˿�%d��ʧ�ܣ���\r\n",port);
			m_showMsg += str;
		}
		else{
			mark = TRUE;
			listen(sock,SOMAXCONN);
		}
	}
	else{
		CString str;
		CTime tm = CTime::GetCurrentTime();
		str =tm.Format("%Y��%m��%d�� %X��");
		m_showMsg += str;
		str.Format("�˿�%d�����ѽ�����\r\n",port);
		m_showMsg += str;
	}
}

bool CTcpServeDlg::RecvProc( int nID )
{

	//SOCKET &sock = nID ? m_socket_Pose_listen : m_socket_Deep_listen;
	/*bool   &mark = nID ? m_bConnectPose : m_bConnectDeep;
	SOCKET &sockConn = nID ? m_sockConn_Pose : m_sockConn_Deep;*/
	//SOCKADDR_IN addrClient;
	//int	len = sizeof(SOCKADDR);

	//sockConn = accept(sock,(SOCKADDR*)&addrClient,&len);

	bool   &mark = m_bConnectPose;
	SOCKET &sockConn = nID ? m_sockConn_Pose : m_sockConn_Motor;
	
	while(mark){
		unsigned char recvBuf[40];
		bool dataOK = FALSE;

		recv(sockConn,(char*)recvBuf,22,0);

		int  dataLen = recvBuf[3];        //
		int  dataClass = recvBuf[2];      //

		if((recvBuf[0] == 0xFF) && (recvBuf[1] == 0xFE))    //
		{
			if (recvBuf[2] == MOTOR_SPEED || recvBuf[2] == MOTOR_PID){
				dataOK = TRUE;
			}
			else{
				int checkvalue = 0;        //
				for (int i = 2; i <= 2 + 1 + dataLen; i++)
				{
					checkvalue += recvBuf[i];
				}
				if ((recvBuf[4 + dataLen] == (checkvalue & 0xFF)) || (recvBuf[4 + dataLen] == 0x00) && (recvBuf[5 + dataLen] == 0x33))  //
				{
					dataOK = TRUE;
				}
			}
		}

		if(dataOK == TRUE)   //
		{
			int  ieee = 0; //�յ�POSE����ʱ���ת�����2���ƴ���
			unsigned char dataBuf[4] = {0x00}; //����POSE������32λ����
			float Z = 0;

			switch (dataClass) {
			case STOP:    //

				break;
			case LIGHT:
				switch (recvBuf[4]){
				case LIGHT_LIGHTNING:
					GlobalVar::lightValue = recvBuf[5]; 
					break;
				case LIGHT_LASER:
					if(recvBuf[5]){
						GlobalVar::laserOn = true;
					}
					else
						GlobalVar::laserOn = false;
					break;
				default:
					break;
				}
				break;
			case CTD:     //�������¶ȡ��������
				switch (recvBuf[4]){
				case CTD_DEEPNESS:        //�������
					m_bDeep = TRUE;
					Z = recvBuf[5]*256 + recvBuf[6];    //
					Kalman_Filter(Z,GlobalVar::deepness,GlobalVar::deepnessP,DEEP_CONVARIANCE);
					break;
				default:
					break;
				}
				break;
			case MOTOR_SPEED:				
				for(int i = 0; i < 8; i++){
					*(GlobalVar::motorN[i]) = ((int)recvBuf[i*4 + 3]) << 8 + (int)recvBuf[i*4 + 4];
					GlobalVar::motorV[i] = recvBuf[i*4 + 5];
					GlobalVar::motorI[i] = recvBuf[i*4 + 6];
				}
				break;
			case MOTOR_PID:
				for(int i = 0;i <8;i++){
					GlobalVar::motor_p[i] = (float)recvBuf[i*4 + 3]/100.0;
					GlobalVar::motor_i[i] = (float)recvBuf[i*4 + 4]/100.0;
					GlobalVar::motor_d[i] = (float)recvBuf[i*4 + 5]/100.0;
				}
				break;
			case POSE: {                           //��̬

				for(int i = 0;i<4;i++){
					dataBuf[i] = recvBuf[i+5];
				}

				switch (recvBuf[4]){
				case POSE_PITCH:                  //������
					m_bPitch = TRUE;
					CharToFloat::convert(ieee,dataBuf);
					Z = CharToFloat::getDecNumber(ieee);
					m_pitchFile<<Z<<std::endl;
					GlobalVar::pitch = Z;
					Kalman_Filter(Z,GlobalVar::pitchAngle,GlobalVar::pitchAngleP,GYRO_CONVARIANCE);
					break;
				case POSE_ROLL:                   //�����
					m_bRoll = TRUE;
					CharToFloat::convert(ieee,dataBuf);
					Z = CharToFloat::getDecNumber(ieee);
					m_rollFile<<Z<<std::endl;
					GlobalVar::roll = Z;
					Kalman_Filter(Z,GlobalVar::rollAngle,GlobalVar::rollAngleP,GYRO_CONVARIANCE);
					break;
				case POSE_YAW:                    //ƫ����
					m_bYaw = TRUE;
					CharToFloat::convert(ieee,dataBuf);
					Z = CharToFloat::getDecNumber(ieee);
					m_yawFile<<Z<<std::endl;
					GlobalVar::yaw = Z;
					Kalman_Filter(Z,GlobalVar::yawAngle,GlobalVar::yawAngleP,GYRO_CONVARIANCE);
					break;
				case POSE_X_ACCELERATE:           //X����ٶ�
					CharToFloat::convert(ieee,dataBuf);
					GlobalVar::xAccelerate = CharToFloat::getDecNumber(ieee);
					break;
				case POSE_Y_ACCELERATE:           //Y����ٶ�
					CharToFloat::convert(ieee,dataBuf);
					GlobalVar::yAccelerate = CharToFloat::getDecNumber(ieee);
					break;
				case POSE_Z_ACCELERATE:           //Z����ٶ�
					CharToFloat::convert(ieee,dataBuf);
					GlobalVar::zAccelerate = CharToFloat::getDecNumber(ieee);
					break;
				default:
					break;
				}
				if(m_bYaw == TRUE && m_bPitch == TRUE && m_bRoll == TRUE) {
					m_bYaw = m_bPitch = m_bRoll = FALSE;

					/*ŷ���ǲ��������Խ׶���ʱ����*/
					//Eigen::Matrix3f Rs0 = GlobalVar::GetRotationMatrix(GlobalVar::yawAngle,GlobalVar::pitchAngle,GlobalVar::rollAngle);
					//Eigen::Matrix3f Rt0 = Rs0*GlobalVar::compensationMatrix;
					//GlobalVar::yaw   = GlobalVar::GetYawAngle(Rt0);
					//GlobalVar::pitch = GlobalVar::GetPitchAngle(Rt0);
					//GlobalVar::roll  = GlobalVar::GetRollAngle(Rt0);	

					m_bPose = TRUE;
				}
				break;
			}
			default:
				break;
			}
		}		
	}
	closesocket(sockConn);

	return FALSE;
}

DWORD WINAPI CTcpServeDlg::ThreadProcWaitForSocket( LPVOID lpParameter )
{
	CTcpServeDlg* pthis = (CTcpServeDlg*)lpParameter;
	while(m_bConnectDeep){
		SOCKADDR_IN addrClient;
		int	len = sizeof(SOCKADDR);
		
		SOCKET sockConn = accept(m_socket_Pose_listen,(SOCKADDR*)&addrClient,&len);
		if(addrClient.sin_addr.S_un.S_addr == inet_addr("192.168.1.10")) {
			m_sockConn_Pose = sockConn;
			HANDLE hThread = CreateThread(NULL,0,ThreadProc,LPVOID(&m_sockConn_Pose),0,NULL);
			CloseHandle(hThread);
			::SendMessage(pthis->m_hWnd,WM_SOCKETCONNECTED,(WPARAM)POSE_SOCKET_CONNECTED,NULL);
		}
		else if(addrClient.sin_addr.S_un.S_addr == inet_addr("192.168.1.11")){
			m_sockConn_Motor = sockConn;
			HANDLE hThread = CreateThread(NULL,0,ThreadProc,LPVOID(&m_sockConn_Motor),0,NULL);
			CloseHandle(hThread);
			::SendMessage(pthis->m_hWnd,WM_SOCKETCONNECTED,(WPARAM)MOTOR_SOCKET_CONNECTED,NULL);
		}
		else if(addrClient.sin_addr.S_un.S_addr == inet_addr("127.0.0.1")){
			m_sockConn_Test = sockConn;
			HANDLE hThread = CreateThread(NULL,0,ThreadProc,LPVOID(&m_sockConn_Test),0,NULL);
			CloseHandle(hThread);
			::SendMessage(pthis->m_hWnd,WM_SOCKETCONNECTED,(WPARAM)TEST_SOCKET_CONNECTED,NULL);
		}
	}

	return 0;
}

DWORD WINAPI CTcpServeDlg::ThreadProc(LPVOID lpParameter)
{
	bool   &mark = m_bConnectPose;
	SOCKET &sockConn = *((SOCKET*)lpParameter);
	
	while(mark){
		unsigned char recvBuf[40];
		bool dataOK = FALSE;

		if(recv(sockConn,(char*)recvBuf,40,0) == WSAESHUTDOWN)
			break;

		int  dataLen = recvBuf[3];        //
		int  dataClass = recvBuf[2];      //

		if((recvBuf[0] == 0xFF) && (recvBuf[1] == 0xFE))    //
		{
			if ((recvBuf[2] == MOTOR_SPEED) || (recvBuf[2] == MOTOR_PID)){
				dataOK = TRUE;
			}
			else{
				int checkvalue = 0;        //
				for (int i = 2; i <= 2 + 1 + dataLen; i++)
				{
					checkvalue += recvBuf[i];
				}
				if ((recvBuf[4 + dataLen] == (checkvalue & 0xFF)) || (recvBuf[4 + dataLen] == 0x00) && (recvBuf[5 + dataLen] == 0x33))  //
				{
					dataOK = TRUE;
				}
			}
		}

		if(dataOK == TRUE)   //
		{
			int  ieee = 0; //�յ�POSE����ʱ���ת�����2���ƴ���
			unsigned char dataBuf[4] = {0x00}; //����POSE������32λ����
			float Z = 0;

			switch (dataClass) {
			case STOP:    //

				break;
			case LIGHT:
				switch (recvBuf[4]){
				case LIGHT_LIGHTNING:
					GlobalVar::lightValue = recvBuf[5]; 
					break;
				case LIGHT_LASER:
					if(recvBuf[5]){
						GlobalVar::laserOn = true;
					}
					else
						GlobalVar::laserOn = false;
					break;
				default:
					break;
				}
				break;
			case CTD:     //�������¶ȡ��������
				switch (recvBuf[4]){
				case CTD_DEEPNESS:        //�������
					m_bDeep = TRUE;
					Z = recvBuf[5]*256 + recvBuf[6];    //
					Kalman_Filter(Z,GlobalVar::deepness,GlobalVar::deepnessP,DEEP_CONVARIANCE);
					break;
				default:
					break;
				}
				break;
			case MOTOR_SPEED:		
				for (int i = 0; i < 8; i++){
				//	*(GlobalVar::motorN[i]) = ((int)recvBuf[i*4 + 3]) << 8 + (int)recvBuf[i*4 + 4];
					*(GlobalVar::motorN[i]) = ((int)recvBuf[i*4 + 3]) *256 + (int)recvBuf[i*4 + 4];
				}
				break;
			case MOTOR_PID:
				for(int i = 0;i <8;i++){
					GlobalVar::motor_p[i] = (float)recvBuf[i*4 + 3]/100.0;
					GlobalVar::motor_i[i] = (float)recvBuf[i*4 + 4]/100.0;
					GlobalVar::motor_d[i] = (float)recvBuf[i*4 + 5]/100.0;
				}
				break;
			case POSE: {                           //��̬

				for(int i = 0;i<4;i++){
					dataBuf[i] = recvBuf[i+5];
				}

				switch (recvBuf[4]){
				case POSE_PITCH:                  //������
					m_bPitch = TRUE;
					CharToFloat::convert(ieee,dataBuf);
					Z = CharToFloat::getDecNumber(ieee);
					m_pitchFile<<Z<<std::endl;
					GlobalVar::pitchAngle = Z;
					//Kalman_Filter(Z,GlobalVar::pitchAngle,GlobalVar::pitchAngleP,GYRO_CONVARIANCE);
					break;
				case POSE_ROLL:                   //�����
					m_bRoll = TRUE;
					CharToFloat::convert(ieee,dataBuf);
					Z = CharToFloat::getDecNumber(ieee);
					m_rollFile<<Z<<std::endl;
					GlobalVar::rollAngle = Z;
					//Kalman_Filter(Z,GlobalVar::rollAngle,GlobalVar::rollAngleP,GYRO_CONVARIANCE);
					break;
				case POSE_YAW:                    //ƫ����
					m_bYaw = TRUE;
					CharToFloat::convert(ieee,dataBuf);
					Z = CharToFloat::getDecNumber(ieee);
					m_yawFile<<Z<<std::endl;
					GlobalVar::yawAngle = Z;
					//Kalman_Filter(Z,GlobalVar::yawAngle,GlobalVar::yawAngleP,GYRO_CONVARIANCE);
					break;
				case POSE_X_ACCELERATE:           //X����ٶ�
					CharToFloat::convert(ieee,dataBuf);
					GlobalVar::xAccelerate = CharToFloat::getDecNumber(ieee);
					break;
				case POSE_Y_ACCELERATE:           //Y����ٶ�
					CharToFloat::convert(ieee,dataBuf);
					GlobalVar::yAccelerate = CharToFloat::getDecNumber(ieee);
					break;
				case POSE_Z_ACCELERATE:           //Z����ٶ�
					CharToFloat::convert(ieee,dataBuf);
					GlobalVar::zAccelerate = CharToFloat::getDecNumber(ieee);
					break;
				default:
					break;
				}
				if(m_bYaw == TRUE && m_bPitch == TRUE && m_bRoll == TRUE) {
					m_bYaw = m_bPitch = m_bRoll = FALSE;

					/*ŷ���ǲ��������Խ׶���ʱ����*/
					Eigen::Matrix3f Rs0 = GlobalVar::GetRotationMatrix(GlobalVar::yawAngle,GlobalVar::pitchAngle,GlobalVar::rollAngle);
					Eigen::Matrix3f Rt0 = Rs0*GlobalVar::compensationMatrix;
					GlobalVar::yaw   = GlobalVar::GetYawAngle(Rt0);
					GlobalVar::pitch = GlobalVar::GetPitchAngle(Rt0);
					GlobalVar::roll  = GlobalVar::GetRollAngle(Rt0);

					m_bPose = TRUE;
				}
				break;
			}
			default:
				break;
			}
		}		
	}
	closesocket(sockConn);

	return 0;
}

DWORD WINAPI CTcpServeDlg::ThreadProcDeep( LPVOID lpParameter )
{
	return RecvProc(THREAD_ID_DEEP);
}

DWORD WINAPI CTcpServeDlg::ThreadProcPose( LPVOID lpParameter )
{
	return RecvProc(THREAD_ID_POSE);
}


void CTcpServeDlg::SendSwitchLight(BOOL bSwitch)
{
	unsigned char sendBuf[21];

    sendBuf[0] = 0xAA;   //0xAA  0x55  0xAA  Ϊ��ͷ
	sendBuf[1] = 0x55;   
    sendBuf[2] = 0xAA;   
    sendBuf[3] = 0x14; 
	sendBuf[4] = 0x1F;  
	sendBuf[5] = 0x99;    

	sendBuf[6] = 0x00; 

	sendBuf[7] = 0x00;

	if(bSwitch == TRUE)
		sendBuf[8] = 0x55;
	else
		sendBuf[8] = 0x00;


	//sendBuf[9]  = 0x00;
	//sendBuf[10] = 0x00;
	//sendBuf[11] = 0x00;
	//sendBuf[12] = 0x00;
	//sendBuf[13] = 0x00;
	//sendBuf[14] = 0x00;
	//sendBuf[15] = 0x00;
	//sendBuf[16] = 0xFF;
	sendBuf[17] = 0xFF;
	sendBuf[18] = 0x33;
	sendBuf[19] = 0xF3;
	sendBuf[20] = '\0';

	if(m_sockConn_Motor != INVALID_SOCKET){
		send(m_sockConn_Motor,(char*)sendBuf,20,0);
	}
}

void CTcpServeDlg::SendMotorSpeed()
{
	int N[8] = {0};

	for (int i=0;i<8;i++){
		//N[i] = GlobalVar::motor_send[i];
		if(sgn(GlobalVar::motor_send[i]) == sgn(GlobalVar::motor_last[i])){
			if((abs(GlobalVar::motor_send[i]) - abs(GlobalVar::motor_last[i])) >= MOTOR_VALUE_LIMIT){
				if(sgn(GlobalVar::motor_send[i]) == 0){
					N[i] = GlobalVar::motor_last[i] + MOTOR_VALUE_LIMIT;
					GlobalVar::motor_last[i] = N[i];
				}
				else{
					N[i] = GlobalVar::motor_last[i] - MOTOR_VALUE_LIMIT;
					GlobalVar::motor_last[i] = N[i];
				}
			}
			else{
				N[i] = GlobalVar::motor_send[i];
				GlobalVar::motor_last[i] = N[i];
			}
		}
		else{
			if(abs(GlobalVar::motor_send[i]-GlobalVar::motor_last[i]) >= MOTOR_VALUE_LIMIT){
				if(sgn(GlobalVar::motor_send[i]) == 0){
					N[i] = GlobalVar::motor_last[i] + MOTOR_VALUE_LIMIT;
					GlobalVar::motor_last[i] = N[i];
				}
				else{
					N[i] = GlobalVar::motor_last[i] - MOTOR_VALUE_LIMIT;
					GlobalVar::motor_last[i] = N[i];
				}
			}
			else{
				N[i] = GlobalVar::motor_send[i];
				GlobalVar::motor_last[i] = N[i];
			}
		}
	}

	SendMotorN(N[0],N[1],N[2],N[3],N[4],N[5],N[6],N[7]);
	//SendMotorN(GlobalVar::motor_send[0],GlobalVar::motor_send[1],GlobalVar::motor_send[2],GlobalVar::motor_send[3],\
		       GlobalVar::motor_send[4],GlobalVar::motor_send[5],GlobalVar::motor_send[6],GlobalVar::motor_send[7]);
}

void CTcpServeDlg::SendMotorN(int n1,int n2,int n3,int n4,int n5,int n6,int n7,int n8)
{
	unsigned char sendBuf[21];

	/*****************************ָ���ʽ*************************/
    /*
     *    ֡ͷ        ����                       ������                                У��λ        ֡β
     *  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   
     * 0xAA 0x55 0xAA 0x14 0x1F 0x3C 0x00 0x37 0xDC 0xDC 0xDC 0xDC 0xDC 0xDC 0xDC 0xDC 0xFF 0xFF 0x33 0xF3  
     *
     * */

    sendBuf[0] = 0xAA;   //0xAA  0x55  0xAA  Ϊ��ͷ
	sendBuf[1] = 0x55;   
    sendBuf[2] = 0xAA;   
    sendBuf[3] = 14;    //0x14  ֡���ȣ����ڹ̶�   Ҳ����Ϊ��֡ͷ��һ���֣�
	sendBuf[4] = 0x1F;  //��bit4Ϊ0x1Fʱ����ʾ���ã���bit4Ϊ0xF1ʱ����ʾ��ѯ��
	sendBuf[5] = 0x3C;    //   0x3c	       0x5a	            0x78
		                  //   �ٶ�	  8�������PID����	�������ֵ

	sendBuf[6] = 0x00;    //��bit4Ϊ0x1Fʱ��bit5Ϊ0x5aʱ����ʾ����8�������PID������ͨ��BIT6ѡ�����õ���P ��I ��D
					    	// 0x12	  0x34    0x56
	                       //   P	    I      	D

	sendBuf[7] = GetDirectionBit(n1,n2,n3,n4,n5,n6,n7,n8);   //�������ٶ�ʱ��ͨ��BIT7ѡ���ĸ������ת��
															// ͨ���ж�BIT7��һλ��ֵΪ0��1�ж���ת��ת��
															 //���統BIT7Ϊ0x37ʱ�����������Ϊ 00110111


	sendBuf[8]  = (abs(n1) / 10) >= 255? 255:(abs(n1) / 10);       //�����ٶ�ʱΪ8��������ٶ�/10������SP1Ϊ100ʱ����ʾת������Ϊ1000�����ٶ����ֵΪ2550ת��
	sendBuf[9]  = (abs(n2) / 10) >= 255? 255:(abs(n2) / 10);       //����PIDʱ��Ϊ8�������P  I  D���� * 100������SP1Ϊ23ʱ����ʾ����PID����Ϊ0.23 ��;
	sendBuf[10] = (abs(n3) / 10) >= 255? 255:(abs(n3) / 10);		  //���õ������ֵʱ��Ϊ8������Ľ���ֵ / 10����SP1Ϊ145����ʾ1�ŵ������ֵΪ1450��
	sendBuf[11] = (abs(n4) / 10) >= 255? 255:(abs(n4) / 10);
	sendBuf[12] = (abs(n5) / 10) >= 255? 255:(abs(n5) / 10);
	sendBuf[13] = (abs(n6) / 10) >= 255? 255:(abs(n6) / 10);
	sendBuf[14] = (abs(n7) / 10) >= 255? 255:(abs(n7) / 10);
	sendBuf[15] = (abs(n8) / 10) >= 255? 255:(abs(n8) / 10);

    int checkValue = 0;   //����У��ֵ �д���ȶ

    for(int i = 3;i < 16;i++){
        checkValue += sendBuf[i];
    }

    //sendBuf[16] = checkValue&0xFF;
	sendBuf[16] = 0xFF;//����ʱ�ó���У��0xFF
    sendBuf[17] = 0xFF;
	sendBuf[18] = 0x33;
	sendBuf[19] = 0xF3;
    sendBuf[20] = '\0';
	if(m_sockConn_Motor != INVALID_SOCKET){
		send(m_sockConn_Motor,(char*)sendBuf,20,0);
	}
}


int CTcpServeDlg::sgn(int value) //����0����0��С��0����1
{
	return value >= 0 ? 0 : 1;
}

unsigned char CTcpServeDlg::GetDirectionBit()
{
	//return sgn(GlobalVar::motor_1) + (sgn(GlobalVar::motor_2) << 1) + (sgn(GlobalVar::motor_3) << 2)
	//	+ (sgn(GlobalVar::motor_4) << 3) + (sgn(GlobalVar::motor_5) << 4) + (sgn(GlobalVar::motor_6) << 5)
	//	+ (sgn(GlobalVar::motor_7) << 6) + (sgn(GlobalVar::motor_8) << 7);
	
	char a = 0;
	for (int i = 0;i < 8; i++){
		a += sgn(GlobalVar::motor_send[i]) << i;
	}
	return a;
}


unsigned char CTcpServeDlg::GetDirectionBit(int m1,int m2,int m3,int m4,int m5,int m6,int m7,int m8)
{
	return sgn(m1) + (sgn(m2) << 1) + (sgn(m3) << 2)+ (sgn(m4) << 3) + \
       	(sgn(m5) << 4) + (sgn(m6) << 5)+ (sgn(m7) << 6) + (sgn(m8) << 7);
}

void CTcpServeDlg::GetMotorValue(char sign)
{
	unsigned char sendBuf[21];

	sendBuf[0] = 0xAA;   //0xAA  0x55  0xAA  Ϊ��ͷ
	sendBuf[1] = 0x55;   
	sendBuf[2] = 0xAA;   
	sendBuf[3] = 14;    //0x14  ֡���ȣ����ڹ̶�   Ҳ����Ϊ��֡ͷ��һ���֣�
	sendBuf[4] = 0xF1;  //��bit4Ϊ0x1Fʱ����ʾ���ã���bit4Ϊ0xF1ʱ����ʾ��ѯ��
	sendBuf[5] = sign;   //MOTOR_PID or MOTOR_SPEED 
					    //   0x3c	       0x5a	            0x78
						//   �ٶ�	  8�������PID����	�������ֵ


	int checkValue = 0;   //����У��ֵ �д���ȶ

	for(int i = 3;i < 16;i++){
		checkValue += sendBuf[i];
	}

	//sendBuf[16] = checkValue&0xFF;
	sendBuf[16] = 0xFF;//����ʱ�ó���У��0xFF
	sendBuf[17] = 0xFF;
	sendBuf[18] = 0x33;
	sendBuf[19] = 0xF3;
	sendBuf[20] = '\0';
	if(m_sockConn_Motor != INVALID_SOCKET){
		send(m_sockConn_Motor,(char*)sendBuf,20,0);
	}
}

void CTcpServeDlg::SetMotorPID(char sign, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8)
{
		unsigned char sendBuf[21];

    sendBuf[0] = 0xAA;   //0xAA  0x55  0xAA  Ϊ��ͷ
	sendBuf[1] = 0x55;   
    sendBuf[2] = 0xAA;   
    sendBuf[3] = 14;    //0x14  ֡���ȣ����ڹ̶�   Ҳ����Ϊ��֡ͷ��һ���֣�
	sendBuf[4] = 0x1F;  //��bit4Ϊ0x1Fʱ����ʾ���ã���bit4Ϊ0xF1ʱ����ʾ��ѯ��
	sendBuf[5] = MOTOR_PID;    //   0x3c	       0x5a	            0x78
		                  //   �ٶ�	  8�������PID����	�������ֵ

	sendBuf[6] = sign;    //��bit4Ϊ0x1Fʱ��bit5Ϊ0x5aʱ����ʾ����8�������PID������ͨ��BIT6ѡ�����õ���P ��I ��D
					    	// 0x12	  0x34    0x56
	                       //   P	    I      	D
	sendBuf[7] = 0x00;  

	sendBuf[8]  = v1*100;       //�����ٶ�ʱΪ8��������ٶ�/10������SP1Ϊ100ʱ����ʾת������Ϊ1000�����ٶ����ֵΪ2550ת��
	sendBuf[9]  = v2*100;       //����PIDʱ��Ϊ8�������P  I  D���� * 100������SP1Ϊ23ʱ����ʾ����PID����Ϊ0.23 ��;
	sendBuf[10] = v3*100;		  //���õ������ֵʱ��Ϊ8������Ľ���ֵ / 10����SP1Ϊ145����ʾ1�ŵ������ֵΪ1450��
	sendBuf[11] = v4*100;
	sendBuf[12] = v5*100;
	sendBuf[13] = v6*100;
	sendBuf[14] = v7*100;
	sendBuf[15] = v8*100;

    int checkValue = 0;   //����У��ֵ �д���ȶ

    for(int i = 3;i < 16;i++){
        checkValue += sendBuf[i];
    }

    //sendBuf[16] = checkValue&0xFF;
	sendBuf[16] = 0xFF;//����ʱ�ó���У��0xFF
    sendBuf[17] = 0xFF;
	sendBuf[18] = 0x33;
	sendBuf[19] = 0xF3;
    sendBuf[20] = '\0';
	if(m_sockConn_Motor != INVALID_SOCKET){
		send(m_sockConn_Motor,(char*)sendBuf,20,0);
	}
}


// �������˲�����
void CTcpServeDlg::Kalman_Filter(float &Z, float &X, float &P, float R)
{
	
	float Kg = P/(P + R);
	X = X + Kg*(Z - X);
	P = (1-Kg)*P;
}




afx_msg LRESULT CTcpServeDlg::OnSocketconnected(WPARAM wParam, LPARAM lParam)
{
	switch(wParam){
		case POSE_SOCKET_CONNECTED:{
			m_pose_connected.SetActiveNoEvent(TRUE);
			
			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			m_showMsg += "��̬�ͻ��������ӣ�192.168.1.10��\r\n";
			
			break;
		}
		case MOTOR_SOCKET_CONNECTED:{
			m_motor_connected.SetActiveNoEvent(TRUE);

			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			m_showMsg += "����ͻ��������ӣ�192.168.1.11��\r\n";

			break;
		}
		case TEST_SOCKET_CONNECTED:{
			m_pose_connected.SetActiveNoEvent(TRUE);
			m_motor_connected.SetActiveNoEvent(TRUE);

			CString str;
			CTime tm = CTime::GetCurrentTime();
			str =tm.Format("%Y��%m��%d�� %X��");
			m_showMsg += str;
			m_showMsg += "�������Կͻ��������ӣ�127.0.0.1��\r\n";

			break;
		}

		default:
			break;
	}

	UpdateData(FALSE);
	return 0;
}
