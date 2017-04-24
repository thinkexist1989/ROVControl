/*******�������������ת������************
 *
 * IEEE 754��׼ �����ȸ�����  32λ    4�ֽ�
 * 1λΪ����λs��0Ϊ�� 1Ϊ��
 * 2~9λΪ����E��E-127=ʵ��ֵ
 * 10~32λΪβ��M������0.8125��ת��Ϊ������Ϊ0.1101����β��Ϊ1101
 * ת����ʽV=(-1)^s*(1+M)*2^(E-127)
 **************************************/


#include <cassert>
#include <cmath>
#include <ctype.h>

class CharToFloat
{
public:
    CharToFloat();
    ~CharToFloat();

    static const unsigned int s = 0x80000000,    //1λΪ����λs  ��Ϊ0����Ϊ1
                       r = 0x7F800000,    //2~9λΪ����E  E-127=ʵ��ֵ
                       m = 0x7FFFFF;      //10~32λΪβ��M
                                          //ת����ʽV=(-1)^s*(1+M)*2^(E-127)
   // static bool check(char c);
    static void convert(int &ieee,unsigned char *hex);
    static int getBinSign(int &ieee);            //�õ�����λ
    static int getBinExp(int &ieee);             //���������
    static int getBinMantissa(int &ieee);        //��ȡβ��
    static int getDecInt(int &ieee);             //�����10������������
    static float getDecFraction(int &ieee);      //��ȡС����ʮ������ʽ
    static float getDecNumber(int &ieee);        //��ȡʮ���Ƹ�������ֵ
};
