#pragma once
#include "stdafx.h"
#include "pid.h"


/************ͨѶָ��*********/

#define     STOP           0x00
#define     MOTOR_SPEED    0x08  //�������ת��
#define		MOTOR_PID	   0xA5  //�������PIDֵ

#define		MOTOR_GET_P	   0x12  //�������P
#define		MOTOR_GET_I	   0x34  //�������I
#define     MOTOR_GET_D	   0x56  //�������D

#define     LIGHT          0x02	
#define     LIGHT_LIGHTNING     0x01
#define     LIGHT_LASER         0x02
#define		CTD				    0x03
#define     CTD_DEEPNESS        0xBB
#define     POSE			    0x05
#define     POSE_PITCH          0x01
#define     POSE_ROLL           0x02
#define     POSE_YAW            0x03
#define     POSE_X_ACCELERATE   0x04
#define     POSE_Y_ACCELERATE   0x05
#define     POSE_Z_ACCELERATE   0x06

#define		GYRO_CONVARIANCE	0.5
#define		DEEP_CONVARIANCE	5

#define		MOTOR_MIDDLE_VALUE  0
#define		MOTOR_RANGE		    2550.0

class GlobalVar
{
public:
	GlobalVar();
	~GlobalVar();

	static int    lightValue;                   //TODO: 0~255
	static bool   laserOn;                      //TODO: ����������״̬

	

	static float  deepness;                   //TODO: ���ֵ
	static float  deepnessP;					//TODO:���Ŷ�
	static PID   *pidDeep;

	static float  pitchAngle;                   //TODO: ������������
	static float  pitchAngleP;   
	static PID   *pidPitch;

	static float  rollAngle;                    //TODO: �����������
	static float  rollAngleP;
	static PID   *pidRoll;

	static float  yawAngle;                     //TODO: ������ƫ����
	static float  yawAngleP;
	static PID   *pidYaw;


	static float roll;							//ROV����ʵŷ����
	static float pitch;
	static float yaw;


	static float  xAccelerate;                  //TODO: X����ٶ�

	static float  yAccelerate;                  //TODO: Y����ٶ�

	static float  zAccelerate;                  //TODO: Z����ٶ�

	static int    motor_1;						//TODO:�����õ�motorֵ
	static int    motor_2;
	static int    motor_3;
	static int    motor_4;
	static int    motor_5;
	static int    motor_6;
	static int    motor_7;
	static int    motor_8;

	static int    motor_N1;						//TODO:���յ�motorת��ֵ
	static int    motor_N2;
	static int    motor_N3;
	static int    motor_N4;
	static int    motor_N5;
	static int    motor_N6;
	static int    motor_N7;
	static int    motor_N8;

	static int*   motorN[8];
	static int*	  motorS[8];
	static int	  motor_last[8];
	static int    motor_send[8];
	static int	  motorI[8];
	static int	  motorV[8];

	static float  motor_p[8];
	static float  motor_i[8];
	static float  motor_d[8];
	
	static void  MotorAddPID(float deep, float yaw, float pitch, float roll);
	static int  F2N(float F);   //�������ת��Ϊת��
	static float  N2F(int N);	 //���ת��ת��Ϊ����

	static Eigen::Matrix3f	compensationMatrix;  //�ǶȲ�������	  
	//static float	rollCompensation;
	//static float	pitchCompensation;
	//static float	yawCompensation;

	static Eigen::Matrix3f  GetCompensationMatrix(float yaw,float pitch,float roll); //ͨ����ʼ�Ĵ������Ƕȵõ���������   ������ǽǶ���
	static Eigen::Matrix3f	GetRotationMatrix(float yaw,float pitch,float roll);//ͨ��ŷ���ǵõ���ת����
	static float	GetYawAngle(Eigen::Matrix3f R); //ͨ������õ�ƫ����yaw
	static float	GetPitchAngle(Eigen::Matrix3f R); //ͨ������õ������pitch
	static float	GetRollAngle(Eigen::Matrix3f R); //ͨ������õ������roll
};

