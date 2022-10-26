/*
 * string.c
 *
 *  Created on: 2018��5��16��
 *      Author: duan
 */

#include "string.h"

//ϣ������
// ���ʱ�临�Ӷ� ---- ���ݲ������еĲ�ͬ����ͬ����֪��õ�ΪO(n(logn)^2)
// ����ʱ�临�Ӷ� ---- O(n)
// ƽ��ʱ�临�Ӷ� ---- ���ݲ������еĲ�ͬ����ͬ��
// ���踨���ռ� ------ O(1)
// �ȶ��� ------------ ���ȶ�
// ���---------------��С����
void ShellSort(double A[], int n)
{
    int i = 0;
    int h = 0;
    while (h <= n)                          // ���ɳ�ʼ����
    {
        h = 3 * h + 1;
    }
    while (h >= 1)
    {
        for (i = h; i < n; i++)
        {
            int j = i - h;
            double get = A[i];
            while (j >= 0 && A[j] > get)
            {
                A[j + h] = A[j];
                j = j - h;
            }
            A[j + h] = get;
        }
        h = (h - 1) / 3;                    // �ݼ�����
    }
}

double my_pow(double x, double y)
{
    double m=1;
    if(y==0) {
        return 1;
    }
    else {
        while(y--)
        {
            m=m*x;
        }
        return m;
    }
}

int8_t my_strcmp(int8_t *str1,int8_t *str2)
{
    while(1)
    {
        if(*str1!=*str2)return 1;//�����
        str1++;
        str2++;
        if(*str1=='\0')break;//�Ա������
    }
    return 0;//�����ַ������
}
void my_strcopy(int8_t*str1,int8_t *str2)
{
    while(1)
    {
        *str2=*str1;    //����
        if(*str1=='\0')break;//���������.
        str1++;
        str2++;
    }
}
int8_t my_strlen(int8_t*str)//��������'/0'
{
    int8_t len=0;
    while(1)
    {
        if(*str=='\0')break;//���������.
        len++;
        str++;
    }
    return len;
}

//������ת�ַ����������ַ������ȣ�Precision����ȷ��С����λ��
uint8_t my_numstr(double value_f, int8_t *String)
{
    uint32_t ui32Pos=0;
    uint32_t ui32Count=0;
    uint32_t ui32Idx=0;
    uint32_t dec_num,int_num;
    int8_t   pcBuf[16];

    if((int32_t)value_f<0)
    {
        *String='-';
        value_f=-value_f;
    }
    int_num = (uint32_t)(value_f);
    dec_num = (uint32_t)((value_f-int_num)*10000);
    while(int_num)
    {
        pcBuf[ui32Count] = ((uint32_t)int_num%10)+'0';
        ui32Count++;
        int_num= int_num/10;
    }
    ui32Pos+=ui32Count;
    while (ui32Count!=0)
    {
        ui32Count--;
        String[ui32Idx] = pcBuf[ui32Count];
        ui32Idx++;
    }
    String[ui32Idx]='.';
    ui32Pos++;
    while(ui32Count!=4)
    {
        pcBuf[ui32Count] = ((uint32_t)dec_num%10)+'0';
        ui32Count++;
        dec_num= dec_num/10;
    }
    ui32Pos+=ui32Count;
    while (ui32Count)
    {
        ui32Count--;
        ui32Idx++;
        String[ui32Idx] = pcBuf[ui32Count];
    }
    return ui32Pos;
}

//���ַ���תΪ����
//֧��16����ת��,����16������ĸ�����Ǵ�д��,�Ҹ�ʽΪ��0X��ͷ��.
//֧�ָ���   ֧�ָ�����
//*str:�����ַ���ָ��
//*res:ת����Ľ����ŵ�ַ.
//����ֵ:0���ɹ�ת�����.����,�������.
//1,���ݸ�ʽ����.2,16����λ��Ϊ0.3,��ʼ��ʽ����.4,ʮ����λ��Ϊ0.
int my_strnum(int8_t*str,double *res)
{
    uint32_t t;
    int tnum;
    int bnum=0;      //���ֵ�����λ��
    int b_num=-1;    //���ֵ�С��λ��
    int8_t *p;
    uint8_t hexdec=10;   //Ĭ��Ϊʮ��������
    uint8_t flag_num=0;  //0,Ϊ����;1,��ʾΪ������.
    uint8_t flag=0;      //0,û�з��ű��;1,��ʾ����;2,��ʾ����.
    p=str;
    *res=0;//����.
    while(1)
    {
        if((*p<='9'&&*p>='0')||(*p=='.')||((*str=='-'||*str=='+')&&bnum==0)
                ||(*p<='F'&&*p>='A')||(*p=='X'&&bnum==1))//�����Ϸ�
        {
            if(*p>='A')hexdec=16;   //�ַ����д�����ĸ,Ϊ16���Ƹ�ʽ.
            if(*str=='-'){flag=2;str+=1;}//ƫ�Ƶ�����
            else if(*str=='+'){flag=1;str+=1;}//ƫ�Ƶ�����
            if(*p=='.') {flag_num=1;}
            if (flag_num==0) {
                bnum++;            //λ������.
            }else {
                b_num++;        //λ������.
            }
        }
        else break;
        p++;
    }
    p=str;              //���¶�λ���ַ�����ʼ�ĵ�ַ.
    if(hexdec==16)      //16��������
    {
        if(bnum<3)return 2;         //λ��С��3��ֱ���˳�.��Ϊ0X��ռ��2��,���0X���治������,������ݷǷ�.
        if(*p=='0' && (*(p+1)=='X'))//������'0X'��ͷ.
        {
            p+=2;   //ƫ�Ƶ�������ʼ��ַ.
            bnum-=2;//��ȥƫ����
        }else return 3;//��ʼͷ�ĸ�ʽ����
    }else if(bnum==0)return 4;//λ��Ϊ0��ֱ���˳�.
    while(bnum) {
        bnum--;
        if(*p<='9'&&*p>='0') t=*p-'0';   //�õ����ֵ�ֵ
        else t=*p-'A'+10;               //�õ�A~F��Ӧ��ֵ
        *res+=t*my_pow(hexdec,bnum);
        p++;
    }
    if(b_num!=-1)
    {
        while(b_num) {
                *res+=(*(p+b_num)-'0')*my_pow(0.1,b_num);
                b_num--;
            }
    }
    if(flag==2)//�Ƿ���
    {
        tnum=-*res;
        *res=tnum;
    }
    return 0;//�ɹ�ת��
}

void my_bytnum(int8_t *string,double *value,double max)
{
    int16_t b_value;
    b_value=*string<<8|*(string+1);
    *value=b_value/32768.0f*max;
}

void my_numbyt(int8_t *string,double *value,double max)
{
    int16_t b_value;
    b_value=*value/max*32768.0f;
    *string=b_value>>8;
    *(string+1)=b_value&0x00ff;
}
