#include "Header.h"

unsigned char StatusPacket[20];              // Dynamixel이 송신하는 데이터를 수신하기 위한 배열
unsigned char InstrPacket[20];               // PC가 송신하는 데이터를 수신하기 위한 배열
int i,j,k;                                   // 배열 초기화를 위한 변수
int len;                                     // 배열의 길이
/*extern unsigned char instr[20];*/

void USART0_init (void)           // ATmeag128과 PC는 USART0 사용
{
	UCSR0B = 0b10011000;          // 수신완료 인터럽트 개별허용, RxDn, TxDn 핀을 직렬 데이터 송,수신 단자로 동작하도록 설정
	UCSR0C = 0b00000110;          // 비동기 모드, 패티티 비트 사용X, STOP 비트 1개, 전송 데이터 길이 8비트 설정
	UBRR0H = 0;
	UBRR0L = 16;                  // BAUD rate : 57600bps 설정
}

void USART1_init (void)           // Dynamixel과 ATmega128은 USART1 사용
{
	UCSR1B = 0b10011000;          // 수신완료 인터럽트 개별허용, RxDn, TxDn 핀을 직렬 데이터 송,수신 단자로 동작하도록 설정
	UCSR1C = 0b00000110;          // 비동기 모드, 패티티 비트 사용X, STOP 비트 1개, 전송 데이터 길이 8비트 설정
	UBRR1H = 0;
	UBRR1L = 16;                  // BAUD rate : 57600bps 설정
	DDRA &=0b11111101;            // Direction port 설정
	DDRA |=0b00000010;            // Direction port 설정
}

ISR (USART0_RX_vect)                             // PC가 송신하는 DATA를 수신하기 위한 인터럽트
{
	len = strlen(InstrPacket);                   // 배열의 길이
	
	if (j == 0)                                  // 문자열을 수신하기전에 문자열을 저장할 배열 초기화
	{
		for (i=0; i<len; i++)
		{
			InstrPacket[i] = '\0';
		}
	}
	InstrPacket[j++] = UDR0;                     // 수신 배열에 데이터 저장
}

ISR (USART1_RX_vect)                             // Dynamixel이 송신하는 Status Packet을 수신하기 위한 인터럽트
{
	 len = strlen(StatusPacket);                 // 배열의 길이
	 
	 if (k == 0)                                 // 문자열을 수신하기전에 문자열을 저장할 배열 초기화
	 {
		 for (i=0; i<len; i++)
		 {
			 StatusPacket[i] = '\0';
		 }
	 }
	 StatusPacket[k] = UDR1;                     // 수신 배열에 데이터 저장
	 Tx_MCUtoPC_Char(StatusPacket[k]);           // 수신할 때마다 DATA를 PC로 송신 (시리얼통신에서 바로 확인하기 위함)
	 k++;                                        // 배열의 index 증가
}

void Tx_MCUtoPC (unsigned char* Instrpacket)        // ATmega128이 DATA(Status Packet)를 PC로 송신 (문자열)
{
	//strcat (InstrPacket,"\n");
	int len = strlen(Instrpacket);                  // 송신할 문자열 길이
	int i=0;
	
	for (i = 0; i < len; i++)                      // 문자열 길이 만큼 반복
	{	
		if (Instrpacket[i] == '\0')                // 문자열의 끝까지 오면 종료
		 break;
		while (!(UCSR0A & 0x20));                  // UDRE0 = 1이면 송신 데이터를 받을 준비가 되고 while문을 빠져나감
		UDR0 = Instrpacket[i];                     // 문자 송신
	}
}

void Tx_MCUtoPC_Char (unsigned char StatusPacket)        // ATmega128이 DATA(Status Packet)를 PC로 송신 (문자)
{
	    while (!(UCSR0A & 0x20));
		UDR0 = StatusPacket;                             // PC로 문자를 송신
}

void Tx_MCUtoDyn (unsigned char InstrPacket)         // ATmega128이 Instruction Packet을 Dynamixel로 송신
{
	while (!(UCSR1A & 0x20));                        // 송신 버퍼가 비어있는지 확인
	UDR1 = InstrPacket;                              // Dynamixel로 문자를 송신

}

void reset_arr(unsigned char *instr, int len)              // 문자열을 초기화하기 위한 함수
{
	int i;
	
	for (i=0; i<len; i++)
	{
		instr[i] = '\0';
	}
}