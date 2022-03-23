#include "Header.h"

unsigned char instr[20];
extern unsigned char InstrPacket[20];             // pc에서 송신하는 data를 저장
extern unsigned char StatusPacket[20];   // Dynamixel이 송신하는 Status Packet을 저장

extern int j, k;
extern unsigned char binary[16];                     // 2진 data 배열
extern int Coordinate_X, Coordinate_Y;               // 목표 좌표 (X,Y)   
extern double theta1, theta2;


int main(void)
{
    USART0_init();          // USART0 Initialize
	USART1_init();          // USART0 Initialize
	Direction_Rx();         // Dynamixel 통신방향 설정
	sei();
	
	SynGoalAcceleration(ID_1);
	_delay_ms(500);
	k=0;
	SynGoalAcceleration(ID_2);
	_delay_ms(500);
	k=0;
	
	SyncGoalPosition(ID_1, ID_2, 0, 0);        // 연결된 두 모터에 회전해야할 각도를 전달
	_delay_ms(500);
	k=0;
	
	sprintf(instr, "send coordinates\n");
	Tx_MCUtoPC(instr);
	
    while (1)
    {
// 		Ping(ID_1);
// 		_delay_ms(500);
//         k=0;
		
// 		Read_Acceleration(ID_1);
// 		_delay_ms(500);
// 		k=0;
		
// 		InverseKinematics(16,9);
// 		_delay_ms(100);
// 		InverseKinematics(5,5);
// 		_delay_ms(100);
// 		InverseKinematics(10,10);
// 		_delay_ms(100);
// 		InverseKinematics(17,9);
// 		_delay_ms(100);
// 		InverseKinematics(3,3);
// 		_delay_ms(100);

		_delay_ms(2);
		if (InstrPacket[0] != '\0')                            // PC에서 송신한 Data
		{
		    Transform(InstrPacket);                             // PC에서 송신한 ASCII code Data를 정수형태로 변환 
			sprintf(instr, "X : %d\n", Coordinate_X);
			Tx_MCUtoPC(instr);                                  // 변환한 Data를 PC로 송신
			sprintf(instr, "Y : %d\n", Coordinate_Y);
		    Tx_MCUtoPC(instr);                                  // 변환한 Data를 PC로 송신
			
			if ((pow(Coordinate_X, 2.0) + pow(Coordinate_Y, 2.0)) < 400)
			{
				InverseKinematics(Coordinate_X, Coordinate_Y);
				SyncGoalPosition(ID_1, ID_2, theta1, theta2);        // 연결된 두 모터에 회전해야할 각도를 전달
				_delay_ms(500);
				k=0;
			}
			else
			{
				sprintf(instr, "Unavailable coordinates\n");
				Tx_MCUtoPC(instr);
			}

		 	reset_arr(InstrPacket, strlen(InstrPacket));
			sprintf(instr, "send Coordinate\n");
			Tx_MCUtoPC(instr);                                   // 모터의 회전이 끝나고 다음 입력을 받을 준비가 됨
		}
		j=0;
    }
}