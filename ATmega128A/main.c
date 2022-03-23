#include "Header.h"

unsigned char instr[20];                          // MCU에서 PC로 DATA를 송신하기 위한 배열
extern unsigned char InstrPacket[20];             // pc에서 송신하는 data를 저장
extern unsigned char StatusPacket[20];            // Dynamixel이 송신하는 Status Packet을 저장

extern int j, k;							      // Dynamixel이 송신하는 Status Packet과 PC가 송신하는 data의 배열 초기화를 위한 변수
extern unsigned char binary[16];                  // 2진 data 배열
extern int Coordinate_X, Coordinate_Y;            // 목표 좌표 (X,Y)   
extern double theta1, theta2;                     // 첫 번째 모터의 목표 회전각도와 두 번째 모터의 목표 회전각도


int main(void)
{
    USART0_init();          // USART0 Initialize
	USART1_init();          // USART0 Initialize
	Direction_Rx();         // Dynamixel 통신방향 설정
	sei();
	
	SynGoalAcceleration(ID_1);        // 첫 번째 모터의 목표 가속도값 설정
	_delay_ms(500);
	k=0;                              // Dynamixel이 송신하는 Status Packet의 배열 초기화를 위한 변수
	SynGoalAcceleration(ID_2);        // 두 번째 모터의 목표 가속도값 설정
	_delay_ms(500);
	k=0;                              // Dynamixel이 송신하는 Status Packet의 배열 초기화를 위한 변수
	
	SyncGoalPosition(ID_1, ID_2, 0, 0);        // 두 모터의 각도를 0으로 초기화
	_delay_ms(500);
	k=0;
	
	sprintf(instr, "send coordinates\n");      
	Tx_MCUtoPC(instr);                         // 좌표를 받을 준비가 되었음을 PC로 송신
	
    while (1)
    {
// 		Ping(ID_1);
// 		_delay_ms(500);
//      k=0;
		
// 		Read_Acceleration(ID_1);
// 		_delay_ms(500);
// 		k=0;
		
		_delay_ms(2);
		if (InstrPacket[0] != '\0')                            // PC에서 송신한 Data (좌표)
		{
		    Transform(InstrPacket);                             // PC에서 송신한 ASCII code Data를 정수형태로 변환 
			sprintf(instr, "X : %d\n", Coordinate_X);
			Tx_MCUtoPC(instr);                                  // 변환한 Data를 PC로 송신
			sprintf(instr, "Y : %d\n", Coordinate_Y);
		    Tx_MCUtoPC(instr);                                  // 변환한 Data를 PC로 송신
			
			if ((pow(Coordinate_X, 2.0) + pow(Coordinate_Y, 2.0)) < 400)         // 첫 번째 링크와 두 번째 링크의 길이로 표현 가능한 (X,Y)의 범위
			{
				InverseKinematics(Coordinate_X, Coordinate_Y);
				SyncGoalPosition(ID_1, ID_2, theta1, theta2);        // 연결된 두 모터에 회전해야할 각도를 전달
				_delay_ms(500);
				k=0;                                                 
			}
			else
			{
				sprintf(instr, "Unavailable coordinates\n");         // 위의 범위를 벗어나는 (X,Y)
				Tx_MCUtoPC(instr);
			}

		 	//reset_arr(InstrPacket, strlen(InstrPacket));             // 새로운 좌표를 받기 위해 이전에 PC가 송신한 DATA(좌표)의 배열을 초기화
			sprintf(instr, "send Coordinate\n");
			Tx_MCUtoPC(instr);                                       // 좌표를 받을 준비가 되었음을 PC로 송신
		}
		j=0;                                                         // 새로운 좌표를 받기 위해 이전에 PC가 송신한 DATA(좌표)의 배열을 초기화
    }
}