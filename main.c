#include "MAIN.h"
#include "UART.h"
#include "LCD.h"
int count1=0,count2=0;
int dem=0;int set;
int k;long a;int tocdo;
int luu =0;

/****************Chuong trinh tao tre ***********************/
void delay1(long time){

 for (k=0;k<time;k++) ;
}
/************************Ngat timer 0 **********************/
void ngatINT0(void) interrupt 0
{
   luu++;
}
int thoi_gian=0;
void timer0(void) interrupt 1
{
     thoi_gian++;
	if (thoi_gian ==20) {
	tocdo = luu *60 /100;
	thoi_gian =0;
		luu=0;
	}
	TH0=0x3C;
	TL0 = 0xB0;
	TR0=1;
}
/********************ngat tiner2 tao PWM******************/
unsigned char xung;char Lcd_Buff[20];
unsigned char phantramxung;
unsigned char chay=0;// Khai bao bien dem de dem tu 1 den 10
void timer2(void) interrupt 5{ //Ngat timer 2

 TR2=0;
 TF2=0; // Dung chay timer 2
 chay++;
 if(chay<=phantramxung) P2=xung; // Neu bien dem < phan tram xung thi dua gia

 else P2=0x0F; // Neu dem = phan tram xung
 if(chay==10) chay=0; // Neu dem du 10 thi gan lai bang 0 de bat dau chu ki moi
 TR2=1; // Cho chay timer
}


 
/************** chuong trinh chinh ***********************/
void dieukhien(){
  if (phantramxung>0) {
	if (P1_0==0){
	while (P1_0==0) {;}
		phantramxung++;
		set += 20;
		if (phantramxung>9) { phantramxung=10;
		set =202;
		}
	}
		
	if (P1_1==0){
	while(P1_1==0){;}
		phantramxung--;
		set -= 20;
		if (phantramxung <=1) { phantramxung=1;
		set = 21;
		}
	}
	}
	if (P1_2==0){
	  set = 122;
		P1_5=0;
	  P1_6=1;
		xung = 0x01;
		phantramxung=6;
	}
	if (P1_4==0){
    set =122;
		P1_5=1;
		P1_6=0;
		xung =0x02;
		phantramxung=6;
	}
	if (P1_3==0){
    set =0;
		P1_5=1;
		P1_6=1;
		phantramxung=0;
	}
	
}

void main(void){
 lcd1602_init();  // Khoi dong LCD
 EX0 =1; // Cho phep ngat ngoai 0 
 IT0 =1;  // Che do ngat theo suon
 EA=1;
 TMOD = 0x01; // Dung Timer 0 , che do 1 (16bit)  // Cho phep ngat toan cuc 
 TH0 = 0x3C;
 TL0 = 0xB0;
 ET0 =1; // Cho phep ngat TImer 0
 TR0 =1;
	//T2MOD=0xc9;//Timer 2 che do 2 8 bit auto reload,tine1 16 bit
 T2CON=0x04; //timer 2 o che do tu nap 16 bit va nap boi RCAPL2
 RCAP2H=0xFF; //Cho timer2 o che do dem 50.000 micro giay
 RCAP2L=0x9C;
 ET2=1;// Cho phep ngat timer 0
 EA=1;// Cho phep ngat toan cuc
 TR2=1;// Chay timer 0 bat dau dem so chu ki may
 Uart_Init();
 while(1){ dieukhien();
   
	 lcd1602_gotoxy(0,0);
	 sprintf(Lcd_Buff,"Set : %d v/p    ",set);
	 lcd1602_puts(Lcd_Buff);
	 sprintf(Lcd_Buff,"Speed : %d v/p   ",tocdo);
	 lcd1602_gotoxy(0,1);
	 lcd1602_puts(Lcd_Buff);
	 Uart_Write_Text("Hello World! \r\n");
	 
 
 } }