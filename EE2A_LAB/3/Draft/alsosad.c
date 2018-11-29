#include<18F27K40.h>
#use delay(internal=32Mhz,clock_out)
#pin_select PWM4=PIN_C0
#pin_select SDO2=PIN_C3
#pin_select SDO1=PIN_C4
#pin_select SCK2=PIN_C5
#pin_select SCK1=PIN_C7

int SineTab1e[3][32]={
{137,163,189,212,233,250,263,270,273,270,263,250,233,212,189,163,137,110,84,61,40,23,10,3,0,3,10,23,40,61,84,110}
,{137   ,189   ,233   ,263   ,273   ,263   ,233   ,189   ,137   ,84   ,40   ,10   ,0   ,10   ,40   ,84   ,137   ,189   ,233   ,263   ,273   ,263   ,233   ,189   ,137   ,84   ,40   ,10   ,0   ,10   ,40   ,84   }
,{137   ,176   ,211   ,237   ,253   ,256   ,248   ,230   ,205   ,177   ,151   ,130   ,117   ,111   ,114   ,124   ,137   ,149   ,159   ,162   ,156   ,143   ,122   ,96   ,68   ,43   ,25   ,17   ,20   ,36   ,62   ,97   }
};
int Look_Up_Table_Index=0;
int Select_Table=0;

struct IO_Port_Definition
{
   int1 LDAC;//PIN_C0
   int1 debug;//PIN_C1
   int1 cs; //PIN_C2
   int1 SDO2;//PIN_C3
   int1 SDO1;//PIN_C4
   int1 SCK2;//PIN_C5
   int1 unused;//PIN_C6
   int1 SCK1;//PIN_C7
};
struct IO_Port_Definition Port;
struct IO_Port_Definition PortDirection;
#byte Port = 0xF8F
#byte PortDirection = 0xF8A

#int_timer2
void Timer2_Service_Routine(void)
{

Port.debug = 0b1;
Port.cs = 0b0;
//spi_write2(02);
//spi_write2(00);
spi_write2(SineTab1e[Select_Table][Look_Up_Table_Index]>>8);
spi_write(SineTab1e[Select_Table][Look_Up_Table_Index]&0x00FF);
Port.cs = 0b1;
//Look_Up_Table_Index=++Look_Up_Table_Index % 32;
Port.debug = 0b0;
}

void main()
{
PortDirection.debug = 0b0;
PortDirection.cs = 0b0;

setup_spi(SPI_MASTER|SPI_L_TO_H); 
setup_spi2(SPI_MASTER|SPI_L_TO_H); 

setup_timer_2(T2_CLK_INTERNAL|T2_DIV_BY_4,249,1);
setup_ccp2(CCP_PWM|CCP_USE_TIMER1_AND_TIMER2); 
setup_pwm4(PWM_ENABLED|PWM_ACTIVE_LOW|PWM_TIMER2);
set_pwm4_duty(32);

enable_interrupts(INT_TIMER2);
enable_interrupts(GLOBAL);
while(1)
{
}

}
