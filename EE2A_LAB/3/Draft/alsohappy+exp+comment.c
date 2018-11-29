/*******************************************************************************
Author: Group 2 (Hang Xu, Wen Wu, Wenjun Ma)
Date complete: 27/11/2017
Filename: EE2A Experiment3: Integrated Mechatronic Project Wire-Following Signal Generator
Target device: PIC18F27K40
Fuse settings:Default
Program function: Design and build a test signal generator which generates a 1 kHz, 2 kHz 
                  and 1 kHz+ 2 kHz combined signal for the integrated mechatronic project vehicle
*******************************************************************************/

#include<18F27K40.h>
#use delay(internal=32Mhz,clock_out) //set main frequency at 32MHz
#use spi(MASTER,DO=PIN_C3,MODE=0,CLK=PIN_C5,BITS=8) //set SPI
#pin_select PWM4=PIN_A0 //select PIN_A0 as output of PWM

int16 SineTab1e[3][32]=
{
   {2048   ,2447   ,2831   ,3185   ,3495   ,3750   ,3939   ,4056   ,4095   ,4056   ,3939   ,3750   ,3495   ,3185   ,2831   
   ,2447   ,2048   ,1648   ,1264   ,910   ,600   ,345   ,156   ,39   ,0   ,39   ,156   ,345   ,600   ,910   ,1264   ,1648   },//LUT for 1 kHz signal
   {2048   ,2831   ,3495   ,3939   ,4095   ,3939   ,3495   ,2831   ,2048   ,1264   ,600   ,156   ,0   ,156   ,600   ,1264   
   ,2048   ,2831   ,3495   ,3939   ,4095   ,3939   ,3495   ,2831   ,2048   ,1264   ,600   ,156   ,0   ,156   ,600   ,1264   },//LUT for 2 kHz signal
   {2048   ,2639   ,3163   ,3562   ,3795   ,3845   ,3717   ,3443   ,3071   ,2660   ,2269   ,1953   ,1748   ,1670   ,1715   
   ,1855   ,2048   ,2240   ,2380   ,2425   ,2347   ,2142   ,1826   ,1435   ,1024   ,652   ,378   ,250   ,300   ,533   ,932   ,1456   }//LUT for combined 1 kHz + 2 kHz signal
};
int Look_Up_Table_Index=0;
int Select_Table;

struct IO_Port_Definition
{
   int1 PWM;//PIN_A0
   int unusedA:7;//PIN_A1..7
   int SignalSelect:2;//PIN_B0..1
   int unusedB:6;//PIN_B2..7
   int1 unusedC1;//PIN_C0
   int1 debug;//PIN_C1
   int1 cs; //PIN_C2
   int1 SDO;//PIN_C3
   int1 unusedC2;//PIN_C4
   int1 SCK;//PIN_C5
   int1 unusedC3:2;//PIN_C6/PIN_C7
};
struct IO_Port_Definition Port;
struct IO_Port_Definition PortDirection;
#byte Port = 0xF8D
#byte PortDirection = 0xF88

#int_timer2
void Timer2_Service_Routine(void)
{
   if (Port.SignalSelect==0b00)
   {
      Select_Table=0;//1 kHz signal
   }
   if (Port.SignalSelect==0b01)
   {
      Select_Table=1;//2 kHz signal
   }
   if (Port.SignalSelect==0b10)
   {
      Select_Table=2;//combined 1 kHz + 2 kHz signal
   }
   Port.debug = 0b1;
   Port.cs = 0b0;//SPI Chip select signal low
   spi_xfer((4096+SineTab1e[Select_Table][Look_Up_Table_Index])>>8); //High byte(+4096(2^12) for SHDN=1)
   spi_xfer((4096+SineTab1e[Select_Table][Look_Up_Table_Index])&0x00FF);// Low byte
   Port.cs = 0b1;//SPI Chip select signal high
   Look_Up_Table_Index=++Look_Up_Table_Index % 32;//if already count to 32, then reset to 0
   Port.debug = 0b0;
  }  

void main()
{
   int BWPU;//weak pull up PIN_B
   #byte BWPU = 0x0F18;
   BWPU = 0b11111111;
   
   PortDirection.cs = 0b0;//output
   PortDirection.PWM = 0b0;
   PortDirection.unusedA = 0b0000000;
   PortDirection.SignalSelect = 0b11;//input
   PortDirection.unusedB = 0b000000;
   PortDirection.unusedC1=0b0;
   PortDirection.debug=0b0;
   PortDirection.cs = 0b0;
   PortDirection.SDO=0b0;
   PortDirection.unusedC2=0b0;
   PortDirection.SCK=0b0;
   PortDirection.unusedC3=0b00;

   setup_timer_2(T2_CLK_INTERNAL|T2_DIV_BY_1,249,1);//32kHz
   setup_ccp2(CCP_PWM|CCP_USE_TIMER1_AND_TIMER2); // Configure CCP2 as a PWM,CCP2 is paired with Timer 2
   setup_pwm4(PWM_ENABLED|PWM_ACTIVE_LOW|PWM_TIMER2);
   set_pwm4_duty(32);//active low for 1us

   enable_interrupts(INT_TIMER2);// Timer 2 interrupt enable
   enable_interrupts(GLOBAL);// 'Global' interrupt enable
   while(1)
   {
   }

}
