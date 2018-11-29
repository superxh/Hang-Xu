#include<18F27k40.h>
#include<stdio.h>
#fuses NOMCLR, NOWDT,NOPROTECT,NOCPD,RSTOSC_HFINTRC_64MHZ,CLKOUT
#use delay(internal =64Mhz, clock_out)

struct IO_Port_Definition
   {
   int unusedA:8;//PIN_A0..7
   int B:8;//PIN_B0..7 
   int C:8;//PIN_C0..7 
   };
struct IO_Port_Definition Port; 
struct IO_Port_Definition PortDirection; 
#byte Port = 0xF8D 
#byte PortDirection = 0xF88 

void s0()
{
int i; //clock signal
int freq = 2; //clock frequency
int n = 1; //counter
int c; //remainder
setup_oscillator(0x00000260);
setup_adc_ports(NO_ANALOGS);
while(TRUE)
{
//judge part
c = n%2;
if(c == 1)
{
Port.C = 1;
}
if(c == 0)
{
Port.C = 0;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
//2
//judge part
c = n%2;
if(c == 1)
{
Port.C = 1;
}
if(c == 0)
{
Port.C = 0;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
if(Port.B != 0)
{
return;
}
}
}

void s1()
{
int i; //clock signal
int freq = 2; //clock frequency
int n = 1; //counter
int c; //remainder
setup_oscillator(0x00000360);
setup_adc_ports(NO_ANALOGS);
while(TRUE)
{
//judge part
c = n%2;
if(c == 1)
{
Port.C = 1;
}
if(c == 0)
{
Port.C = 0;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
//2
//judge part
c = n%2;
if(c == 1)
{
Port.C = 1;
}
if(c == 0)
{
Port.C = 0;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
if(Port.B != 1)
{
return;
}
}
}

void s2()
{
int i; //clock signal
int freq = 2; //clock frequency
int n = 1; //counter
int c; //remainder
setup_oscillator(0x00000560);
setup_adc_ports(NO_ANALOGS);
while(TRUE)
{
//judge part
c = n%2;
if(c == 1)
{
Port.C = 1;
}
if(c == 0)
{
Port.C = 0;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
//2
//judge part
c = n%2;
if(c == 1)
{
Port.C = 1;
}
if(c == 0)
{
Port.C = 0;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
if(Port.B != 2)
{
//sdb();
return;
}
}
}

void s3()
{
while(TRUE)
{
s0();
s1();
s2();
if(Port.B != 3)
{
return;
}
}
}


void main()
{
   PortDirection.unusedA=0b00000000;//output
   PortDirection.B=0b00111111;//input
   PortDirection.C=0b00000000;//output
   int WPUB;//weak pull up Pin_B
   #byte WPUB=0x0F18;
   WPUB=0b11111111;
   while(1)
   {
   if(Port.B == 0)
   {
   s0();
   }
   if(Port.B == 1)
   {
   s1();
   }
   if(Port.B == 2)
   {
   s2();
   }
   if(Port.B == 3)
   {
   s3();
   }
   }
}
