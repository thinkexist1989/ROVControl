# ˮ�»����˿��Ƴ��� ROVControl
## ����˵��
> 2015.12.16 �������ݣ�
	1��������DlgResizeHelper�࣬����ʵ�ֶԻ���ռ����ŶԻ�������
> 2015.12.20 �������ݣ�
	1���޸��˵������ָ��Э��
> 2015.12.21 �������ݣ�
	1����GlobalVar�м�����motor_N1~motor_N8����������������ʾ��ǰ�����ת�١����޷���������ת��
> 2016.1.15 �������ݣ�
	1������汾����ΪVersion 1.1	
	2�������˳�����������չʾ
	3�������޸���Tcp/ipͨѶ��������ROV��λ�������޸ģ���̬��Ϣ�͵�����ƾ�ͨ��7�Ŷ˿ڷ��أ���˷������˸�Ϊ1�Զ��ͨѶ��ʽ
	4�����¸���������ͷ֮���û��������޸��ˡ�
> 2016.1.18 �������ݣ�
	1����TcpServeDlg������������ActiveX�ؼ���������ʾ��̬�ͻ��˺͵���ͻ����Ƿ����ӹ����ˡ�
	2���޸���MainDlg�е���̬�ǲ����洢��֮ǰ�洢ŷ���������⣬Ϊ�˷��㣬��Ϊֱ�Ӵ洢3X3�ľ���Ԫ�ء�
	3����PID���������˳�Ա����BOOL m_bEnabled������ָʾPID��ʵ��������״̬��
> 2016.1.20 �������ݣ�
	1������汾����ΪVersion 1.2
	2��������ң�˿���ָ�����������ϵ���ʾ��
	3�����ת�ٴ洢�ͷ��͸�Ϊ������ʽ��int motor_send[8]��int motorN[8];
	4�������˵��ת��ָ��仯�ٶȿ��ƣ�����ת�ٱ仯���󣬷�ֹ������
	5�������˵ƹ⿪�ؿ��ƣ����Կ���ROV�ƹ⿪�ء�
	6�������˵��PID���ý��棬��PIDCurveDlg������ʾPID����ͼ