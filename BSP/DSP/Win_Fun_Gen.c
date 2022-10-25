/*
 * Win_Fun_Gen.c
 *
 *  Created on: 2019Äê7ÔÂ19ÈÕ
 *      Author: duan
 */


#include "BSP/DSP/Win_Fun_Gen.h"

void Kaiser(double k,double N,double B)
{
    double   k_cnt,N_cnt;
    double   k_r0,k_r1=1;
    double   X1,X2;
    double   I0_r,I1_r;
    double   I0=0,I1=0;
    double   w;
    for(N_cnt=0;N_cnt<N;N_cnt++)
    {
        for(k_cnt=0;k_cnt<k;k_cnt++)
        {
            for(k_r0=k;k_r0<1;k_r0--)
            {k_r1=k_r1*k_r0;}
            X1 = B*sqrt(1-pow((1-2*N_cnt/(N-1)),2));
            X2 = B;
            I0_r=(pow((X1/2),k_cnt)/k_r1)*(pow((X1/2),k_cnt)/k_r1);
            I0=I0+I0_r;
            I1_r=(pow((X2/2),k_cnt)/k_r1)*(pow((X2/2),k_cnt)/k_r1);
            I1=I1+I1_r;
        }
        w=(double)(I0/I1);
        UARTprintf(0,"%f,\n",w);
    }
}
