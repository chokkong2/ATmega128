#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

void Ping (unsigned char ID);
void GoalPosition (unsigned char ID, int angle);
void SyncGoalPosition (unsigned char ID1, unsigned char ID2, double firstAngle, double secondAngle);
void SynGoalAcceleration (unsigned char ID1);
void Read_Acceleration (unsigned char ID);
void Direction_Tx (void);
void Direction_Rx (void);

void DecimalToBinary (int decimal);   // 10진수를 LOW, HIGH의 2byte로 분할
unsigned char CheckSum (int check);
int Square (int i, int j);            // i의 j제곱 함수
void Transform (unsigned char *InstrPacket);

#endif /* INSTRUCTION_H_ */