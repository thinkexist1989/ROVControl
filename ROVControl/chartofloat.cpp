#include "stdafx.h"
#include "chartofloat.h"


CharToFloat::CharToFloat()
{
}

CharToFloat::~CharToFloat()
{
}

void CharToFloat::convert(int &ieee, unsigned char *hex)
{
//    for(int i = 0,temp = 0;i<8;ieee |= temp<<4*(7-i),i++)
//        temp = isdigit(hex[i])?(hex[i]-'0'):(isupper(hex[i])?(hex[i]-55):(hex[i]-87));
    for(int i = 0, temp = 0;i<4;i++){
        temp = (unsigned char)hex[i];
        ieee |= temp<<8*(3-i);
    }
}

int CharToFloat::getBinSign(int &ieee)
{
    return (s&ieee)>>31;
}

int CharToFloat::getBinExp(int &ieee)
{
    return ((r&ieee)>>23)-127;
}

int CharToFloat::getBinMantissa(int &ieee)
{
    return m&ieee;
}

int CharToFloat::getDecInt(int &ieee)
{
    int exp = 0,mantissa = 0,decInt = 0,high = 1;
    exp = getBinExp(ieee);
    mantissa = getBinMantissa(ieee);
    decInt = (m&mantissa)>>(23-exp);
    decInt |= (high = high <<exp);
    return decInt;
}

float CharToFloat::getDecFraction(int &ieee)
{
    int distillBit = 1, exp = getBinExp(ieee) ;       //提取位 保存阶码;
    float result = 0.0;                              // 保存计算出来的结果
    for(int i=0;i<=22-exp;i++)
        if((ieee&(distillBit<<(22-exp-i)))>>(22-exp-i))
            result = result+1/(float)pow(2.0,i+1+0.0);
    return result;
}

float CharToFloat::getDecNumber(int &ieee)
{
    //float result = getDecInt(ieee)+ getDecFraction(ieee);
    double result =pow (2.0,getBinExp(ieee))*(1 + getBinMantissa(ieee)*pow(2.0,-23));
    return (float)(getBinSign(ieee)?-result:result);
}

