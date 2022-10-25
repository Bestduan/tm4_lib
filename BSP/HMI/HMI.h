#ifndef __HMI_H
#define __HMI_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "APIS/delay.h"
#include "APIS/uartstdio.h"

extern const unsigned char SIN_TABLE[];

void HMICommandPut(const char *Data);
void HMIDrawCurve(const unsigned char *Data ,uint32_t Num);
void HMIShowText(uint32_t TextNum, const char *Data);


#endif
