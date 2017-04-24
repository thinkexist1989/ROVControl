#pragma once

#define THREAD_ID_DEEP  0
#define THREAD_ID_POSE  1

#define POSE_SOCKET_CONNECTED 0
#define MOTOR_SOCKET_CONNECTED 1
#define TEST_SOCKET_CONNECTED 2

#define MOTOR_VALUE_LIMIT 500

#include <fstream>
#include "iswitchled_deep.h"

// CTcpServeDlg 对话框

class CTcpServeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTcpServeDlg)

public:
	CTcpServeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTcpServeDlg();

// 对话框数据
	enum { IDD = IDD_TCPSERVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// TODO:套接字
	static SOCKET m_socket_Deep_listen;
	static SOCKET m_socket_Pose_listen;
	static SOCKET m_sockConn_Pose;  //这个SOCKET才是和下位机通讯用的
	static SOCKET m_sockConn_Motor; //电机和姿态用同一个端口（port7）
	static SOCKET m_sockConn_Deep;
	static SOCKET m_sockConn_Test; //本机测试用
private:	
	// 服务器IP地址 192.168.1.1
	DWORD m_dwIP;
	//服务器端口
	int m_portDeep;
	int m_portPose;
	// 是否已经建立连接标志
	static bool m_bConnectDeep;
	static bool m_bConnectPose;
public:
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnDisconnect();
	virtual BOOL OnInitDialog();

	CString m_showMsg;
private:
	void SetConnect(SOCKET &sock, int &port, bool &mark);
public:
	static bool RecvProc(int nID);
	static void SendMotorSpeed();
	static void SendMotorN(int n1,int n2,int n3,int n4,int n5,int n6,int n7,int n8);
	static void SendSwitchLight(BOOL bSwitch);
	static void SetMotorPID(char sign, float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8);
	static void GetMotorValue(char sign);


	
	static DWORD WINAPI	ThreadProcWaitForSocket(LPVOID lpParameter);
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	static DWORD WINAPI ThreadProcDeep(LPVOID lpParameter);
	static DWORD WINAPI ThreadProcPose(LPVOID lpParameter);
	// 卡尔曼滤波函数
	static void Kalman_Filter(float &Z, float &X, float &P, float R);
	// 计数，当三个欧拉角全部收到后，进行运算
	static bool m_bYaw;
	static bool m_bPitch;
	static bool m_bRoll;

	static bool m_bPose;  //在进行运算之后m_bPose标志置TRUE
	static bool m_bDeep;  //接收到深度信号后m_bDeep标志置TRUE


	static int sgn(int value); 
	static unsigned char GetDirectionBit(); //得到电机正反转位，参数为全局变量GlobalVar::motor
	static unsigned char GetDirectionBit(int m1,int m2,int m3,int m4,int m5,int m6,int m7,int m8);//

	static std::ofstream m_pitchFile;
	static std::ofstream m_rollFile;
	static std::ofstream m_yawFile;
protected:
	afx_msg LRESULT OnSocketconnected(WPARAM wParam, LPARAM lParam);
public:
	CIswitchled_deep m_pose_connected;
	CIswitchled_deep m_motor_connected;

};
