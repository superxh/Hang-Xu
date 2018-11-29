#include<18F27k40.h>
#include<stdio.h>
#fuses NOMCLR, NOWDT,NOPROTECT,NOCPD,RSTOSC_HFINTRC_64MHZ,CLKOUT
#use delay(internal =64Mhz, clock_out)

struct IO_Port_Definition
   {
   int unusedA:8;//PIN_A0..7
   int1 B0;
   int1 B1;
   int1 B2;
   int1 B3;
   int Bswitch:4;
   int C:8;//PIN_C0..7 
   int unusedC:2;//PIN_C6..7 
   };
struct IO_Port_Definition Port; 
struct IO_Port_Definition PortDirection; 
#byte Port = 0xF8D 
#byte PortDirection = 0xF88 

void sdb()
{
setup_oscillator(0x00000860);
setup_adc_ports(NO_ANALOGS);
}

void s0()
{
int freq = 1; //clock frequency
setup_oscillator(0x00000260);
setup_adc_ports(NO_ANALOGS);
while(TRUE)
{
Port.C = 0;
delay_ms(1000/(32*freq));
Port.C = 1;
delay_ms(1000/(32*freq));
if(Port.Bswitch != 0)
{
return;
sdb();
}
}
}

void s1()
{
int freq = 1; //clock frequency
setup_oscillator(0x00000360);
setup_adc_ports(NO_ANALOGS);
while(TRUE)
{
Port.C = 0;
delay_ms(1000/(32*freq));
Port.C = 1;
delay_ms(1000/(32*freq));
if(Port.Bswitch != 1)
{
return;
sdb();
}
}
}

void s2()
{
int freq = 1; //clock frequency
setup_oscillator(0x00000560);
setup_adc_ports(NO_ANALOGS);
while(TRUE)
{
Port.C = 0;
delay_ms(1000/(32*freq));
Port.C = 1;
delay_ms(1000/(32*freq));
if(Port.Bswitch != 2)
{
return;
sdb();
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
if(Port.Bswitch != 3)
{
return;
sdb();
}
}
}

void s4()
{
sdb();
Port.C=0;
while(TRUE)
{
Port.C=(Port.C+1)%64;
delay_ms(500);
if(Port.Bswitch != 4)
{
return;
}
}
}

void s5()
{
sdb();
Port.C=63;
while(TRUE)
{
Port.C = Port.C - 1;
delay_ms(500);
if (Port.C == 0) 
{
Port.C=64;
}
if(Port.Bswitch != 5)
{
return;
}
}
}

void s6()
{
int n = 0;
int freq = 2;
int a,b,c,d,e,f;//a:C0,b:C1...
int a1,b1,c1,d1,e1,f1;//a1:C0,b1:C1...
int nn;
sdb();
while(TRUE)
{
if(n==64)
{
n = 0;
}
a = n%2;
b = ((n - a)/2)%2;
c = ((((n - a)/2) - b)/2)%2;
d = ((((((n - a)/2) - b)/2) - c)/2)%2;
e = ((((((((n - a)/2) - b)/2) - c)/2) - d)/2)%2;
f = ((((((((((n - a)/2) - b)/2) - c)/2) - d)/2) - e)/2)%2;
f1 = f;
e1 = f + e;
if(e1 == 2){e1 = 0;}
d1 = e + d;
if(d1 == 2){d1 = 0;}
c1 = d + c;
if(c1 == 2){c1 = 0;}
b1 = c + b;
if(b1 == 2){b1 = 0;}
a1 = b + a;
if(a1 == 2){a1 = 0;}
a = a1;
b = b1;
c = c1;
d = d1;
e = e1;
f = f1;
nn = 32*f + 16*e + 8*d + 4*c + 2*b + a ; 
Port.C=nn;
delay_ms(1000/freq);
n=n+1;
if(Port.Bswitch != 6)
{
return;
}
}
}

void s7()
{
int n = 0;
int freq = 2;
int a,b,c;
int a1,b1,c1;
int nn;
sdb();
while(TRUE)
{
if(n==8)
{
n=0;
}
a = n%2;
b = ((n - a)/2)%2;
c = ((((n - a)/2) - b)/2)%2;
c1 = c;
b1 = c + b;
if(b1 == 2){b1 = 0;}
a1 = b + a;
if(a1 == 2){a1 = 0;}
a = a1;
b = b1;
c = c1;
nn = n + 32*c + 16*b + 8*a ;
Port.C = nn;
delay_ms(1000/freq);
n=n+1;
if(Port.Bswitch != 7)
{
return;
}
}
}

void s8()
{
sdb();
Port.C = 0;
while(TRUE)
{
int C0 = (Port.B0)&(Port.B2);
int C1 = ((Port.B1)&(Port.B3));
Port.C= C0 + C1*2;
if(Port.Bswitch != 8)
{
return;
}
}
}

void s9()
{
sdb();
Port.C = 0;
while(TRUE)
{
int C0 = (Port.B0)|(Port.B2);
int C1 = (Port.B1)|(Port.B3);
Port.C= C0 + C1*2;
if(Port.Bswitch != 9)
{
return;
}
}
}

void s10()
{
sdb();
Port.C = 0;
while(TRUE)
{
int C0 = ~(Port.B0);
int C1 = ~(Port.B1);
int C2 = ~(Port.B2);
int C3 = ~(Port.B3);
Port.C= C0 + C1*2 + C2*4 + C3*8;
if(Port.Bswitch != 10)
{
return;
}
}
}

void s11()
{
sdb();
Port.C = 0;
while(TRUE)
{
int C0 = (Port.B0)^(Port.B2);
int C1 = (Port.B1)^(Port.B3);
Port.C= C0 + C1*2;
if(Port.Bswitch != 11)
{
return;
}
}
}

void s12()
{
sdb();
   while(TRUE)
   {
   int B0 = Port.B0;
   int B1 = Port.B1;
   if(B0+B1*2 == 0){Port.C=0;};
   if(B0+B1*2 == 1){Port.C=0;};
   if(B0+B1*2 == 2){Port.C=1;};
   if(B0+B1*2 == 3)
   {
   Port.C=0;
   delay_ms(1000/2);
   Port.C=1;
   delay_ms(1000/2);
   }
   if(Port.Bswitch != 12)
   {
   return;
   }
   }
}

void s13()
{
sdb();
int freq;
int gg;
while(true)
{
int i=Port.B0+Port.B1*2+Port.B2*4+Port.B3*8;//0 MSB
int LUT_Freq[16]={1,2,4,7,9,13,16,17,20,23,26,28,30,32,35,36};
gg = 1000/freq;
Port.C=1;
delay_ms(1000/LUT_Freq[i]);
Port.C=2;
delay_ms(1000/LUT_Freq[i]);
Port.C=4;
delay_ms(1000/LUT_Freq[i]);
Port.C=8;
delay_ms(1000/LUT_Freq[i]);
Port.C=16;
delay_ms(1000/LUT_Freq[i]);
Port.C=32;
delay_ms(1000/LUT_Freq[i]);
Port.C=64;
delay_ms(1000/LUT_Freq[i]);
Port.C=128;
delay_ms(1000/LUT_Freq[i]);
Port.C=1;
if(Port.Bswitch != 13)
{
output_c(0);
return;
}
}
}

void main()
{
   PortDirection.unusedA=0b00000000;//output
   PortDirection.B0=0b1;//input
   PortDirection.B1=0b1;
   PortDirection.B2=0b1;
   PortDirection.B3=0b1;
   PortDirection.Bswitch=0b1111;
   PortDirection.C=0b000000;//output
   PortDirection.unusedC=0b00;//output
   int WPUB;//weak pull up Pin_B
   #byte WPUB=0x0F18;
   WPUB=0b11111111;
   while(1)
   {
   if(Port.Bswitch == 0)
   {
   s0();
   }
   if(Port.Bswitch == 1)
   {
   s1();
   }
   if(Port.Bswitch == 2)
   {
   s2();
   }
   if(Port.Bswitch == 3)
   {
   s3();
   }
   if(Port.Bswitch == 4)
   {
   s4();
   }
   if(Port.Bswitch == 5)
   {
   s5();
   }   
   if(Port.Bswitch == 6)
   {
   s6();
   }   
   if(Port.Bswitch == 7)
   {
   s7();
   }   
   if(Port.Bswitch == 8)
   {
   s8();
   }   
   if(Port.Bswitch == 9)
   {
   s9();
   }   
   if(Port.Bswitch == 10)
   {
   s10();
   }   
   if(Port.Bswitch == 11)
   {
   s11();
   }   
   if(Port.Bswitch == 12)
   {
   s12();
   } 
   if(Port.Bswitch == 13)
   {
   s13();
   } 
   }
}
