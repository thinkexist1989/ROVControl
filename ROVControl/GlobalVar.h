#pragma once
#include "stdafx.h"
#include "pid.h"


/************通讯指令*********/

#define     STOP           0x00
#define     MOTOR_SPEED    0x08  //电机返回转速
#define		MOTOR_PID	   0xA5  //电机返回PID值

#define		MOTOR_GET_P	   0x12  //电机设置P
#define		MOTOR_GET_I	   0x34  //电机设置I
#define     MOTOR_GET_D	   0x56  //电机设置D

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
	static bool   laserOn;                      //TODO: 激光器开关状态

	

	static float  deepness;                   //TODO: 深度值
	static float  deepnessP;					//TODO:置信度
	static PID   *pidDeep;

	static float  pitchAngle;                   //TODO: 传感器俯仰角
	static float  pitchAngleP;   
	static PID   *pidPitch;

	static float  rollAngle;                    //TODO: 传感器横滚角
	static float  rollAngleP;
	static PID   *pidRoll;

	static float  yawAngle;                     //TODO: 传感器偏航角
	static float  yawAngleP;
	static PID   *pidYaw;


	static float roll;							//ROV的真实欧拉角
	static float pitch;
	static float yaw;


	static float  xAccelerate;                  //TODO: X轴加速度

	static float  yAccelerate;                  //TODO: Y轴加速度

	static float  zAccelerate;                  //TODO: Z轴加速度

	static int    motor_1;						//TODO:发送用的motor值
	static int    motor_2;
	static int    motor_3;
	static int    motor_4;
	static int    motor_5;
	static int    motor_6;
	static int    motor_7;
	static int    motor_8;

	static int    motor_N1;						//TODO:接收的motor转速值
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
	static int  F2N(float F);   //电机推力转换为转速
	static float  N2F(int N);	 //电机转速转换为推力

	static Eigen::Matrix3f	compensationMatrix;  //角度补偿矩阵	  
	//static float	rollCompensation;
	//static float	pitchCompensation;
	//static float	yawCompensation;

	static Eigen::Matrix3f  GetCompensationMatrix(float yaw,float pitch,float roll); //通过初始的传感器角度得到补偿矩阵   输入的是角度制
	static Eigen::Matrix3f	GetRotationMatrix(float yaw,float pitch,float roll);//通过欧拉角得到旋转矩阵
	static float	GetYawAngle(Eigen::Matrix3f R); //通过矩阵得到偏航角yaw
	static float	GetPitchAngle(Eigen::Matrix3f R); //通过矩阵得到纵倾角pitch
	static float	GetRollAngle(Eigen::Matrix3f R); //通过矩阵得到横滚角roll
};

