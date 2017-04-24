/*PID�����㷨��*/

#define MIDDLEVALUE 2810
#define UPPERVALUE  3740
#define LOWERVALUE  1880


class PID
{
public:
	PID(float kp = 0, float ki = 0, float kd = 0, float t = 0.2);
    ~PID();

    float Int_Error, Last_Error;
    float Kp, Ki, Kd;//PID����
    //float Upper_Ltd, Lower_Ltd;//������½�
    float T;

	BOOL m_bEnalbed;

    
	float PIDControl(float input, float output, float precision);
	float CourseControl(float val);
    float translationCourseControl(float val);
    float DepthControl(float val);

private:
    bool  isMiddleSpped;

    float PID_CourseContinuos(float Error);
    float PID_translationCourseContinuos(float Error);
    float PID_DepthContinuos(float Error);


};

