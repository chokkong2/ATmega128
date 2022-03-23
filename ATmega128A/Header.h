#ifndef HEADER_H_
#define HEADER_H_

#define pING 0x01
#define READ_DATA 0x02
#define WRITE_DATA 0x03
#define REG_WRITE 0x04
#define ACTION 0x05
#define RESET 0x06
#define SYNC_WRITE 0x83
#define BULK_READ 0x92

#define GoalPosition_Address 0x1E
#define GoalAcceleration_Address 0x49

#define header 0xFF
#define Broadcasting_ID 0xFE
#define ID_1 0x01
#define ID_2 0x02

#define L1 10           // 첫 번째 링크의 길이
#define L2 10           // 두 번째 링크의 길이

#define THETA2_1 (atan(sqrt(1-pow(C2, 2.0))/C2) +M_PI)
#define THETA2_2 (atan(-sqrt(1-pow(C2, 2.0))/C2)-M_PI)
#define THETA2_3 (atan(sqrt(1-pow(C2, 2.0))/C2))
#define THETA2_4 (atan(-sqrt(1-pow(C2,2.0))/C2))
#define THETA1 atan2(Y,X) - atan2(L2*sin(theta2),(L1+L2*C2))

#define _USE_MATH_DEFINES
#include <math.h>

#define F_CPU 160000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "USART.h"
#include "Instruction.h"
#include "InverseKinematics.h"

#endif /* HEADER_H_ */