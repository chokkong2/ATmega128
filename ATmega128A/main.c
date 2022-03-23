#include "Header.h"

unsigned char instr[20];                          // MCU���� PC�� DATA�� �۽��ϱ� ���� �迭
extern unsigned char InstrPacket[20];             // pc���� �۽��ϴ� data�� ����
extern unsigned char StatusPacket[20];            // Dynamixel�� �۽��ϴ� Status Packet�� ����

extern int j, k;							      // Dynamixel�� �۽��ϴ� Status Packet�� PC�� �۽��ϴ� data�� �迭 �ʱ�ȭ�� ���� ����
extern unsigned char binary[16];                  // 2�� data �迭
extern int Coordinate_X, Coordinate_Y;            // ��ǥ ��ǥ (X,Y)   
extern double theta1, theta2;                     // ù ��° ������ ��ǥ ȸ�������� �� ��° ������ ��ǥ ȸ������


int main(void)
{
    USART0_init();          // USART0 Initialize
	USART1_init();          // USART0 Initialize
	Direction_Rx();         // Dynamixel ��Ź��� ����
	sei();
	
	SynGoalAcceleration(ID_1);        // ù ��° ������ ��ǥ ���ӵ��� ����
	_delay_ms(500);
	k=0;                              // Dynamixel�� �۽��ϴ� Status Packet�� �迭 �ʱ�ȭ�� ���� ����
	SynGoalAcceleration(ID_2);        // �� ��° ������ ��ǥ ���ӵ��� ����
	_delay_ms(500);
	k=0;                              // Dynamixel�� �۽��ϴ� Status Packet�� �迭 �ʱ�ȭ�� ���� ����
	
	SyncGoalPosition(ID_1, ID_2, 0, 0);        // �� ������ ������ 0���� �ʱ�ȭ
	_delay_ms(500);
	k=0;
	
	sprintf(instr, "send coordinates\n");      
	Tx_MCUtoPC(instr);                         // ��ǥ�� ���� �غ� �Ǿ����� PC�� �۽�
	
    while (1)
    {
// 		Ping(ID_1);
// 		_delay_ms(500);
//      k=0;
		
// 		Read_Acceleration(ID_1);
// 		_delay_ms(500);
// 		k=0;
		
		_delay_ms(2);
		if (InstrPacket[0] != '\0')                            // PC���� �۽��� Data (��ǥ)
		{
		    Transform(InstrPacket);                             // PC���� �۽��� ASCII code Data�� �������·� ��ȯ 
			sprintf(instr, "X : %d\n", Coordinate_X);
			Tx_MCUtoPC(instr);                                  // ��ȯ�� Data�� PC�� �۽�
			sprintf(instr, "Y : %d\n", Coordinate_Y);
		    Tx_MCUtoPC(instr);                                  // ��ȯ�� Data�� PC�� �۽�
			
			if ((pow(Coordinate_X, 2.0) + pow(Coordinate_Y, 2.0)) < 400)         // ù ��° ��ũ�� �� ��° ��ũ�� ���̷� ǥ�� ������ (X,Y)�� ����
			{
				InverseKinematics(Coordinate_X, Coordinate_Y);
				SyncGoalPosition(ID_1, ID_2, theta1, theta2);        // ����� �� ���Ϳ� ȸ���ؾ��� ������ ����
				_delay_ms(500);
				k=0;                                                 
			}
			else
			{
				sprintf(instr, "Unavailable coordinates\n");         // ���� ������ ����� (X,Y)
				Tx_MCUtoPC(instr);
			}

		 	//reset_arr(InstrPacket, strlen(InstrPacket));             // ���ο� ��ǥ�� �ޱ� ���� ������ PC�� �۽��� DATA(��ǥ)�� �迭�� �ʱ�ȭ
			sprintf(instr, "send Coordinate\n");
			Tx_MCUtoPC(instr);                                       // ��ǥ�� ���� �غ� �Ǿ����� PC�� �۽�
		}
		j=0;                                                         // ���ο� ��ǥ�� �ޱ� ���� ������ PC�� �۽��� DATA(��ǥ)�� �迭�� �ʱ�ȭ
    }
}