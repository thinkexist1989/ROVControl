# 水下机器人控制程序 ROVControl
## 更新说明
> 2015.12.16 更新内容：
	1）加入了DlgResizeHelper类，用来实现对话框空间随着对话框缩放
	
> 2015.12.20 更新内容：
	1）修改了电机发送指令协议
	
> 2015.12.21 更新内容：
	1）在GlobalVar中加入了motor_N1~motor_N8变量，用来接收显示当前电机的转速。（无法区别正反转）
	
> 2016.1.15 更新内容：
	1）程序版本升级为Version 1.1	
	2）增加了程序启动界面展示
	3）重新修改了Tcp/ip通讯程序，由于ROV下位机程序修改，姿态信息和电机控制均通过7号端口返回，因此服务器端改为1对多的通讯方式
	4）重新更换了摄像头之后，用户名密码修改了。
	
> 2016.1.18 更新内容：
	1）在TcpServeDlg中增加了两个ActiveX控件，用来显示姿态客户端和电机客户端是否连接过来了。
	2）修改了MainDlg中的姿态角补偿存储，之前存储欧拉角有问题，为了方便，改为直接存储3X3的矩阵元素。
	3）在PID类中增加了成员变量BOOL m_bEnabled，用来指示PID类实例的启用状态。
	
> 2016.1.20 更新内容：
	1）程序版本升级为Version 1.2
	2）增加了遥杆控制指令在主界面上的显示。
	3）电机转速存储和发送改为数组形式，int motor_send[8]和int motorN[8];
	4）加入了电机转速指令变化速度控制，不让转速变化过大，防止暴死。
	5）增加了灯光开关控制，可以控制ROV灯光开关。
	6）增加了电机PID设置界面，用PIDCurveDlg类来显示PID曲线图