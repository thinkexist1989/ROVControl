#include "StdAfx.h"
#include "GlobalVar.h"
#include <math.h>

using Eigen::AngleAxisf;
using Eigen::Vector3f;
using Eigen::Matrix3f;


GlobalVar::GlobalVar()
{
}


GlobalVar::~GlobalVar()
{
}

int    GlobalVar::lightValue;                   //TODO: 0~255
bool   GlobalVar::laserOn;                      //TODO: 激光器开关状态
float    GlobalVar::deepness;                     //TODO: 深度值

float  GlobalVar::deepnessP;                   //TODO: 俯仰角

float  GlobalVar::pitchAngle;                   //TODO: 俯仰角[-90~90] 
float  GlobalVar::rollAngle;                    //TODO: 横滚角[-180~180]
float  GlobalVar::yawAngle;                     //TODO: 偏航角[-180~180]

float  GlobalVar::pitchAngleP = 1;                   //TODO: 俯仰角置信度
float  GlobalVar::rollAngleP = 1;                    //TODO: 横滚角置信度
float  GlobalVar::yawAngleP = 1;					 //TODO: 偏航角置信度

float GlobalVar::roll;
float GlobalVar::pitch;
float GlobalVar::yaw;

float  GlobalVar::xAccelerate;                  //TODO: X轴加速度
float  GlobalVar::yAccelerate;                  //TODO: Y轴加速度
float  GlobalVar::zAccelerate;                  //TODO: Z轴加速度
int    GlobalVar::motor_1;
int    GlobalVar::motor_2;
int    GlobalVar::motor_3;
int    GlobalVar::motor_4;
int    GlobalVar::motor_5;
int    GlobalVar::motor_6;
int    GlobalVar::motor_7;
int    GlobalVar::motor_8;

int    GlobalVar::motor_N1;
int    GlobalVar::motor_N2;
int    GlobalVar::motor_N3;
int    GlobalVar::motor_N4;
int    GlobalVar::motor_N5;
int    GlobalVar::motor_N6;
int    GlobalVar::motor_N7;
int    GlobalVar::motor_N8;
int*   GlobalVar::motorN[8] = { &GlobalVar::motor_N1, &GlobalVar::motor_N2, &GlobalVar::motor_N3, &GlobalVar::motor_N4,\
							    &GlobalVar::motor_N5, &GlobalVar::motor_N6, &GlobalVar::motor_N7, &GlobalVar::motor_N8};
int*   GlobalVar::motorS[8] = { &GlobalVar::motor_1, &GlobalVar::motor_2, &GlobalVar::motor_3, &GlobalVar::motor_4,\
								&GlobalVar::motor_5, &GlobalVar::motor_6, &GlobalVar::motor_7, &GlobalVar::motor_8};
int	   GlobalVar::motor_last[8] = {0,0,0,0,0,0,0,0};
int    GlobalVar::motor_send[8] = {0,0,0,0,0,0,0,0};

int	   GlobalVar::motorI[8] = {0,0,0,0,0,0,0,0};
int	   GlobalVar::motorV[8] = {0,0,0,0,0,0,0,0};

float  GlobalVar::motor_p[8] = {0.01,0.01,0.01,0.01,0.01,0.01,0.01,0.01};
float  GlobalVar::motor_i[8] = {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};
float  GlobalVar::motor_d[8] = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};


PID   * GlobalVar::pidDeep = new PID();
PID   * GlobalVar::pidYaw = new PID();
PID   * GlobalVar::pidPitch = new PID();
PID   * GlobalVar::pidRoll = new PID();

//float	GlobalVar::rollCompensation;
//float	GlobalVar::pitchCompensation;
//float	GlobalVar::yawCompensation;

Matrix3f GlobalVar::compensationMatrix;

Matrix3f GlobalVar::GetCompensationMatrix(float yaw,float pitch,float roll)
{
	Matrix3f Rs0 = GetRotationMatrix(yaw,pitch,roll);   //Rt0 = Rs0 * Rts
	Matrix3f Rt0 = GetRotationMatrix(yaw,0,0);
	
	return Rs0.inverse()*Rt0;
}

Matrix3f GlobalVar::GetRotationMatrix(float yaw,float pitch,float roll)
{
	 Matrix3f a;
	 //a = AngleAxisf(yaw/180.00*M_PI,Vector3f::UnitZ())
		//		   * AngleAxisf(pitch/180.00*M_PI,Vector3f::UnitY())
		//		   * AngleAxisf(roll/180.00*M_PI,Vector3f::UnitX());
	 a(0,0) = cos(pitch/180*M_PI)*cos(yaw/180*M_PI);
	 a(1,0) = cos(pitch/180*M_PI)*sin(yaw/180*M_PI);
	 a(2,0) = -sin(pitch/180*M_PI);
	 a(0,1) = sin(roll/180*M_PI)*sin(pitch/180*M_PI)*cos(yaw/180*M_PI) \
		     -cos(roll/180*M_PI)*sin(yaw/180*M_PI);
	 a(1,1) = sin(roll/180*M_PI)*sin(pitch/180*M_PI)*sin(yaw/180*M_PI) \
		     +cos(roll/180*M_PI)*cos(yaw/180*M_PI);
	 a(2,1) = sin(roll/180*M_PI)*cos(pitch/180*M_PI);
	 a(0,2) = cos(roll/180*M_PI)*sin(pitch/180*M_PI)*cos(yaw/180*M_PI) \
		     +sin(roll/180*M_PI)*sin(yaw/180*M_PI);
	 a(1,2) = cos(roll/180*M_PI)*sin(pitch/180*M_PI)*sin(yaw/180*M_PI) \
		     -sin(roll/180*M_PI)*cos(yaw/180*M_PI);
	 a(2,2) = cos(roll/180*M_PI)*cos(pitch/180*M_PI);
	 return a;
}

float GlobalVar::GetYawAngle(Eigen::Matrix3f R)
{
	return atan2(R(1,0),R(0,0))/M_PI*180.0;
}

float GlobalVar::GetPitchAngle(Eigen::Matrix3f R)
{
	return asin(-R(2,0))/M_PI*180.0;
}

float GlobalVar::GetRollAngle(Eigen::Matrix3f R)
{
	return atan2(R(2,1),R(2,2))/M_PI*180.0;
}

void  GlobalVar::MotorAddPID(float deep, float yaw, float pitch, float roll)
{
	//motor_1 += F2N(deep + pitch + roll);
	//motor_2;
	//motor_3 += F2N(deep + pitch - roll);
	//motor_4;
	//motor_5 += F2N(deep - pitch + roll);
	//motor_6;
	//motor_7;
	//motor_8 += F2N(deep - pitch - roll);
}

int  GlobalVar::F2N(float F)   //电机推力转换为转速 转速最大2550
{
	int N = F>=0 ? sqrt(F / 13.328)*pow(10.0, 3) : -sqrt(abs(F) / 4.96468)*pow(10.0, 3);
	if(abs(N) >= 2550) {
		return F>= 0 ? 2550 : -2550;
	}
	else
		return N;
}
float  GlobalVar::N2F(int N)	 //电机转速转换为推力
{
	return N >= 0 ? 1.3328*pow(10.0, -5)*pow((float)N, 2) : -4.96468*pow(10.0, -6)*pow((float)N, 2);
}