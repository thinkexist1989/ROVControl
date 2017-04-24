/*******浮点数与二进制转换函数************
 *
 * IEEE 754标准 单精度浮点数  32位    4字节
 * 1位为符号位s，0为正 1为负
 * 2~9位为阶码E，E-127=实际值
 * 10~32位为尾数M，例如0.8125，转换为二进制为0.1101，则尾数为1101
 * 转换形式V=(-1)^s*(1+M)*2^(E-127)
 **************************************/


#include <cassert>
#include <cmath>
#include <ctype.h>

class CharToFloat
{
public:
    CharToFloat();
    ~CharToFloat();

    static const unsigned int s = 0x80000000,    //1位为符号位s  正为0，负为1
                       r = 0x7F800000,    //2~9位为阶码E  E-127=实际值
                       m = 0x7FFFFF;      //10~32位为尾数M
                                          //转换形式V=(-1)^s*(1+M)*2^(E-127)
   // static bool check(char c);
    static void convert(int &ieee,unsigned char *hex);
    static int getBinSign(int &ieee);            //得到符号位
    static int getBinExp(int &ieee);             //计算出阶码
    static int getBinMantissa(int &ieee);        //获取尾数
    static int getDecInt(int &ieee);             //计算出10进制整数部分
    static float getDecFraction(int &ieee);      //获取小数的十进制形式
    static float getDecNumber(int &ieee);        //获取十进制浮点数数值
};
