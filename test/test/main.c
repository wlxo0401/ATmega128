#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL
unsigned char SEG[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
                         0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

void buzzer(int hz, int count);

int main(void)
{
	int n = 1;
	int a;
	
	unsigned char var1;
	DDRA = 0xff;        			// ��Ʈ A ���
	DDRB = 0xff;					// ��Ʈ B ���
	DDRE = 0x00;					// ��Ʈ E�� PE4~PE7 �Է� AC
	PORTE = 0xf0;					// ��Ʈ E�� PE4~PE7 Ǯ-��
	PORTB = 0b11110111;  
	PORTA = SEG[n];
	
	while(1) {
		var1 = PINE & 0xf0; 		// ��Ʈ E ���� 4��Ʈ ����ũ
		switch(var1) {
			case 0b11100000 : 				// X4�� ������
				if(n<4){
					for(n;n<=4;n++){
						PORTA = SEG[n];
						PORTB = 0b11111110;
						_delay_ms(5000);
						a = n;
						}
					}
				n=a;
				PORTA = SEG[n];
				PORTB = 0b11111110; 
				break; 	//	FND S0 ǥ�� 
			case 0b11010000 : 				// X5�� ������
				if(n<3){
					for(n;n<=3;n++){
						PORTA = SEG[n];
						PORTB = 0b11111101;
						_delay_ms(5000);
						a = n;
					}
				}else if(n>3)
				{
					for(n; n>=3;n--){
							PORTA = SEG[n];
							PORTB = 0b11111101;
							_delay_ms(5000);
							a = n;
					}
					
				}
				n=a;
				PORTA = SEG[n];
				PORTB = 0b11111101; 
				break; 	//	FND S1 ǥ��
			case 0b10110000 : 				// X6�� ������
			
				if(n<2){
					for(n;n<=2;n++){
						PORTA = SEG[n];
						PORTB = 0b11111011;
						_delay_ms(5000);
						a = n;
					}
				}else if(n>2){
						for(n; n>=2;n--){
							PORTA = SEG[n];
							PORTB = 0b11111011;
							_delay_ms(5000);
							a = n;
					}
						
				}
				n=a;
				PORTA = SEG[n];
				PORTB = 0b11111011; 
				break; 	//	FND S2 ǥ��
			case 0b01110000 : 				// X7�� ������
				if(n<1){
					for(n;n<=1;n++){
						PORTA = SEG[n];
						PORTB = 0b11110111;
						_delay_ms(5000);
						a = n;
					}
				}else if(n>1){
					for(n; n>=1;n--){
						PORTA = SEG[n];
						PORTB = 0b11110111;
						_delay_ms(5000);
						a = n;
					}
								
				}
				n=a;
				PORTA = SEG[n];
				PORTA = SEG[1];
				PORTB = 0b11110111; 
				break; 	//	FND S3 ǥ��
			default : break;
		}
		_delay_ms(1000);
		if(n >= 16) n = 0;
	}
}