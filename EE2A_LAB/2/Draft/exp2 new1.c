/* 
Author: Group 2 (Hang Xu, Wen Wu, Wenjun Ma)
Date reviesed: 13/12/2017
Filename: EE2A Experiment2 PIC Introduction
Target device: PIC18F27K40
Fuse settings:NOMCLR, NOWDT,NOPROTECT,NOCPD,RSTOSC_HFINTRC_64MHZ,CLKOUT
Program function: 
(i)To use IO-mapped data structures to talk to interface pins.
(ii)To implement the basic functionality of a synchronous finite state machine and the equivalent implementation on a processor.
(iii)To combine multiple, disjoint program fragments together into one package that can be rapidly demonstrated.
(iv)To implement logical bit-wise operations in software
(v)To implement look-up tables on both inputs and outputs (lambda logic) of synthesised finite state machines.
*/

#include<18F27k40.h>
#include<stdio.h>
#fuses NOMCLR, NOWDT,NOPROTECT,NOCPD
#use delay(internal =64Mhz, clock_out)
struct IO_Port_Definition
{
   int1 B0;
   int1 B1;
   int1 B2;
   int1 B3;
   int ModeSelect:4; //PIN_B4..7
   int C0_5:6;//PIN_C0...5
   int UnusedC:2;//PIN_C6..7
};
struct IO_Port_Definition Port;
struct IO_Port_Definition PortDirection;
#byte Port = 0xF8E
#byte PortDirection = 0xF89

void s0()
{
    while(Port.ModeSelect==0)
   {
      setup_oscillator(OSC_HFINTRC_4MHZ);
   }
   return;
}
void s1()
{
    while(Port.ModeSelect==1)
   {
      setup_oscillator(OSC_HFINTRC_8MHZ);
   }
   return;
}
void s2()
{
    while(Port.ModeSelect==2)
   {
      setup_oscillator(OSC_HFINTRC_16MHZ);
   }
   return;
}
void s3()
{
   while(Port.ModeSelect==3)
   {
      setup_oscillator(OSC_HFINTRC_4MHZ);
      Port.C0_5= 1;
      delay_ms(500);// time to change
      Port.C0_5 = 0;
      setup_oscillator(OSC_HFINTRC_8MHZ);
      Port.C0_5= 1;
      delay_ms(500);// time to change
      Port.C0_5 = 0;
      setup_oscillator(OSC_HFINTRC_16MHZ);
      Port.C0_5= 1;
      delay_ms(500);// time to change
      Port.C0_5 = 0;
   }
   return;
}
void s4()
{
   Port.C0_5=0;
   while (Port.ModeSelect==4)
   {
      Port.C0_5=(Port.C0_5+1)%64;
      delay_ms(500);
   }
   return;
}
void s5()
{
   Port.C0_5=63;
   while (Port.ModeSelect==5)
   {
      Port.C0_5--;
      delay_ms(500);
      if (Port.C0_5==-1) Port.C0_5=63;
   }
   return;
}
void s6()
{
   Port.C0_5=0;
   while(Port.ModeSelect==6)
   {
      Port.C0_5=Port.C0_5^(Port.C0_5>>2);
      delay_ms(500);
      if (Port.C0_5==100000) Port.C0_5=0;
   }
   return;
}
void s7()
{
   int Binary3_Low=0;//low,binary
   int Gray3_High=0;//high,gray
   while(Port.ModeSelect==7)
   {
      Binary3_Low++;
      Gray3_High=(Gray3_High)^(Gray3_High>>2);
      Port.C0_5=Binary3_Low+Gray3_High*1000;
      delay_ms(500);
      if(Port.C0_5==0b111111)
      {
         Binary3_Low=0;
         Gray3_High=0;
      }
   }
   return;
}
void s8()
{
   while(Port.ModeSelect==8)
   {
      Port.C0_5=(Port.B0)&(Port.B1) + ((Port.B1)&(Port.B2))*2;
   }
   return;
}
void s9()
{
   while(Port.ModeSelect==9)
   {
      Port.C0_5=(Port.B0)|(Port.B1) + ((Port.B1)|(Port.B2))*2;
   }
   return;
}
void s10()
{
   while(Port.ModeSelect==10)
   {
      Port.C0_5=~((Port.B0)+Port.B1*2+Port.B2*4+Port.B3*8);
   }
   return;
}
void s11()
{
   while(Port.ModeSelect==11)
   {
      Port.C0_5=(Port.B0)^(Port.B1) + ((Port.B1)^(Port.B2))*2;
   }
   return;
}
void s12()
{
   while(Port.ModeSelect==12)
   {
      switch (Port.B0+Port.B1*2)
      {
         case 1: Port.C0_5=0b000000;
         case 2: Port.C0_5=0b000001;
         case 3: Port.C0_5=~Port.C0_5;
      }
   }
   return;
}

void s13()
{
   int LUT_Freq[16]={1,2,4,7,9,13,16,17,20,23,26,28,30,32,35,36};
   int Index_Input=Port.B0+Port.B1*2+Port.B2*4+Port.B0*8;
   while(Port.ModeSelect==13)
   {
      Port.C0_5=(Port.C0_5+1)%64;
      delay_ms(1000/LUT_Freq[Index_Input]);
   }
   return;
}

void s14()
{
   int LUT_Freq[2]={2,16};
   Port.C0_5=0;
   while (Port.ModeSelect==14)
   {
      while(Port.B0==0)
      {
         Port.C0_5=(Port.C0_5+1)%64;
         delay_ms(1000/LUT_Freq[Port.B1]);
      }
      while(Port.B0==0)
      {
         Port.C0_5--;
         delay_ms(1000/LUT_Freq[Port.B1]);
         if(Port.C0_5==-1) Port.C0_5=63;
      }
   }
   return;
}
void main()
{
   PortDirection.B0=0b1;//input
   PortDirection.B1=0b1;//input
   PortDirection.B2=0b1;//input
   PortDirection.B3=0b1;//input
   PortDirection.ModeSelect=0b1111;//input
   PortDirection.C0_5=0b000000;//output
   PortDirection.UnusedC=0b00;//output
   int WPUB;//weak pull up Pin_B
   #byte WPUB=0x0F18;
   WPUB=0b11111111;
   while(1)
   {
      Switch(Port.ModeSelect)
      {
         case 0:s0();
         case 1:s1();
         case 2:s2();
         case 3:s3();
         case 4:s4();
         case 5:s5();
         case 6:s6();
         case 7:s7();
         case 8:s8();
         case 9:s9();
         case 10:s10();
         case 11:s11();
         case 12:s12();
         case 13:s13();
         case 14:s14();
      }
   }
}
