#include "stdafx.h"
#include "pid.h"
#include <math.h>

PID::PID(float kp, float ki, float kd, float t)
	: Kp(kp)
	, Ki(ki)
	, Kd(kd)
	, T(t)
	, Int_Error(0)
	, m_bEnalbed(FALSE)
{
   // isMiddleSpped = false;
}

PID::~PID()
{

}


float PID::PIDControl(float input, float output, float precision)
{
	float error = input - output;
	
	if (abs(error) <= precision) return 0;

	float val;
	 
	if (Int_Error > -32767 && Int_Error < 32767)
		Int_Error += error * T;
	float Der_Error;
	Der_Error = (error - Last_Error) / T;
	Last_Error = error;
	val = Kp * error + Ki * Int_Error + Kd * Der_Error;

	return val;
}

float PID::CourseControl(float val)
{
    float command;
    command = PID_CourseContinuos(val);
    //if (command > Upper_Ltd)
    //    command = Upper_Ltd;
    //if (command <Lower_Ltd)
    //    command = Lower_Ltd;
    return command;
}

float PID::translationCourseControl(float val)
{
    float command;
    command = PID_CourseContinuos(val);
    //if (command > Upper_Ltd)
    //    command = Upper_Ltd;
    //if (command < Lower_Ltd)
    //    command = Lower_Ltd;
    return command;
}

float PID::DepthControl(float val)
{
    float command;
    command = PID_DepthContinuos(val);
    //if (command > Upper_Ltd)
    //    command = Upper_Ltd;
    //if (command < Lower_Ltd)
    //    command = Lower_Ltd;
    return command;
}

float PID::PID_CourseContinuos(float Error)
{
    if (abs(Error) < 2)
        return 0;

    float Output;
    if (Int_Error > -32767 && Int_Error < 32767)
    Int_Error += Error * T;
    float Der_Error;
    Der_Error = (Error - Last_Error) / T;
    Last_Error = Error;
    Output = Kp * Error + Ki * Int_Error + Kd * Der_Error;
    return Output;
}

float PID::PID_translationCourseContinuos(float Error)
{
    if (abs(Error) < 2)
        return 0;

    float Output;
    if (Int_Error > -32767 && Int_Error < 32767)
        Int_Error += Error * T;
    float Der_Error;
    Der_Error = (Error - Last_Error) / T;
    Last_Error = Error;
    Output = Kp * Error + Ki * Int_Error + Kd * Der_Error;
    return Output;
}

float PID::PID_DepthContinuos(float Error)
{
    float Output;
    if (abs(Error) <=0.2)
    {
        int Values = 40;
        if (isMiddleSpped)
        {
            Values = 0;
        }
        isMiddleSpped = !isMiddleSpped;
        return (float)Values;
    }
    if ((Int_Error > (float)-32767) && (Int_Error < (float)32767))
        Int_Error += Error * T;

    float Der_Error;
    Der_Error = (Error - Last_Error) / T;
    Last_Error = Error;
    Output = Kp * Error + Ki * Int_Error + Kd * Der_Error;
    return Output;
}

