#include <stdio.h>
void Uart_Init()
{
	// Khoi tao UART o mode 1 , 9600 baud 
  SM0 = 0; SM1 =1;
	TMOD &= 0x0F;
  TMOD |= 0x20;	
	// 0010 xxxx - Timer 1 hoat dong o che do 8 bit tu dong nap lai 
	
	TH1 = 0xF3;   // Toc do baud 2400 
	
	TR1 = 1  ;   // TImer 1 bat dau chay 
	
	TI=1;      // San sang gui du lieu 
	
	REN =1; // Cho phep nhan du lieu 
}

void Uart_Write (char c){
  while (TI==0);
	TI=0;
	SBUF = c;
}

void Uart_Write_Text(char *str){
  unsigned char i =0;
	while (str[i] !=0){
	 Uart_Write(str[i]);
		i++;
	}
}

char Uart_Data_Ready(){
  return RI;
}

char Uart_Read(){
	RI =0;
	return SBUF;}
