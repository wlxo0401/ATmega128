﻿//************************************************************************
// 16*2 Character LCD 8bit Interface for WinAVR
// RS = PC0, R/W = PC1, EN = PC2, DB7~DB0 : PA7~PA0
//************************************************************************

void lcd_busy(void)
{   
/*
	DDRA = 0x00;
	do {    
		PORTC &= 0b00000110; 	// RS = 0    
		PORTC |= 0b00000010; 	// RW = 1   
		PORTC |= 0b00000100; 	// E = 1      
	} while(PINA & 0x80);
     
	DDRA = 0xff;
*/
	_delay_ms(50);
}

void lcd_command(unsigned char cmd)
{
	lcd_busy();
    
	PORTA = cmd;     
	PORTC &= 0b00000110;    	// RS = 0
	PORTC &= 0b00000101;    	// RW = 0 
	PORTC |= 0b00000100;    	// E = 1 
	PORTC &= 0b00000011;    	// E = 0, LCD 라이트 타이밍에 따라 E = 1 -> 0   
	_delay_us(1);            	// 일정시간 시간지연 
}       

void lcd_init()
{
	DDRA = 0xff;
	DDRC = DDRC | 0x0f;
    
	_delay_ms(15);           	// 15ms 이상 대기          
	
	PORTA = 0b00110000;        
	PORTC &= 0b00000000;    	// E,RW,RS = 0,0,0
	_delay_us(4100);         	// 4.1ms 이상 대기  
	PORTC &= 0b00000000;    	// E,RW,RS = 0,0,0
	_delay_us(100);          	// 100us 이상 대기    
	PORTC &= 0b00000000;    	// E,RW,RS = 0,0,0
    
	lcd_command(0b00111000);	// 평션 셋 : 8-bit 모드 
	lcd_command(0b00001000);	// 디스플레이 오프
	lcd_command(0b00000001);	// 디스플레이 클리어
	lcd_command(0b00000110);	// 엔트리 모드 

	lcd_command(0b00001111);	// 디스플레이 온, 커셔 온, 커셔 깜박임 
}         

void lcd_data(unsigned char byte)
{
	lcd_busy();
    
	PORTC |= 0b00000001; 		// RS=1
	PORTC &= 0b00000101; 		// RW=0 
	PORTC |= 0b00000100; 		// E=1 
	_delay_us(50); 			// 일정시간 시간지연 
	PORTA = byte;   
	_delay_us(50); 			// 일정시간 시간지연 
	PORTC &= 0b00000011; 		// E=0, LCD 라이트 타이밍에 따라 E=1 -> 0   
}

void lcd_string(char *str)
{
int i=0;
     
	while(1) {
		if (str[i] == '\0') break;
		lcd_data(str[i++]);	
	} 
}

void lcd_display_clear()
{
	lcd_command(0b00000001);
}

void lcd_cursor_home()
{
	lcd_command(0b00000010);
}

void lcd_entry_mode(int ID, int S)
{
unsigned char cmd;
	
	cmd = 0b00000100;
	if (ID == 1) cmd = cmd | 0b00000010;
	if (S == 1) cmd = cmd | 0b00000001;
	lcd_command(cmd);
}

void lcd_display_OnOff(int D, int C, int B)
{
unsigned cmd;
	
	cmd = 0b00001000;
	if (D == 1) cmd = cmd | 0b00000100;
	if (C == 1) cmd = cmd | 0b00000010;
	if (B == 1) cmd = cmd | 0b00000001;
	lcd_command(cmd);
}

void lcd_cursordisplay_shift(int SC, int RL)
{
unsigned cmd;
	
	cmd = 0b00010000;
	if (SC == 1) cmd = cmd | 0b00001000;
	if (RL == 1) cmd = cmd | 0b00000100;
	lcd_command(cmd);
}

void lcd_display_position(unsigned char row, unsigned char col)
{
unsigned cmd;

	cmd = 0b10000000 | ((row-1)*0x40+(col-1));
	lcd_command(cmd);
}
