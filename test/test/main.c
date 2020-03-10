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
	DDRA = 0xff;        			// 포트 A 출력
	DDRB = 0xff;					// 포트 B 출력
	DDRE = 0x00;					// 포트 E의 PE4~PE7 입력 AC
	PORTE = 0xf0;					// 포트 E의 PE4~PE7 풀-업
	PORTB = 0b11110111;  
	PORTA = SEG[n];
	
	while(1) {
		var1 = PINE & 0xf0; 		// 포트 E 하위 4비트 마스크
		switch(var1) {
			case 0b11100000 : 				// X4를 누르면
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
				break; 	//	FND S0 표시 
			case 0b11010000 : 				// X5를 누르면
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
				break; 	//	FND S1 표시
			case 0b10110000 : 				// X6를 누르면
			
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
				break; 	//	FND S2 표시
			case 0b01110000 : 				// X7를 누르면
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
				break; 	//	FND S3 표시
			default : break;
		}
		_delay_ms(1000);
		if(n >= 16) n = 0;
	}
}