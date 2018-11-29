#include<18F27K40.h>
#include<stdio.h>
#use delay(internal=64MHZ,clock_out)

/***************structure***************/
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

void sdb()
{
setup_oscillator(0x00000860);
setup_adc_ports(NO_ANALOGS);

}

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
Port.C = 0b00000001;
}
if(c == 0)
{
Port.C = 0b00000000;
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
Port.C = 0b00000001;
}
if(c == 0)
{
Port.C = 0b00000000;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
if(Port.B != 0b00000000)
{
//sdb();
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
Port.C = 0b00000001;
}
if(c == 0)
{
Port.C = 0b00000000;
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
Port.C = 0b00000001;
}
if(c == 0)
{
Port.C = 0b00000000;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
if(Port.B != 0b00000001)
{
//sdb();
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
Port.C = 0b00000001;
}
if(c == 0)
{
Port.C = 0b00000000;
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
Port.C = 0b00000001;
}
if(c == 0)
{
Port.C = 0b00000000;
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
if(Port.B != 0b00000010)
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
if(Port.B != 0b00000011)
{
return;
}
}
}

void s4()
{
Port.C=0;
int freq = 1;
//#use delay(internal=16MHZ,clock_out)
sdb();
while(TRUE)
{
Port.C = Port.C+1;
delay_ms(1000/freq);
if(Port.C == 64)
{
Port.C = 0;
delay_ms(1000/freq);
}
if(Port.B != 0b00000100)
{
Port.C=0;
return;
}
}
}

void s5()
{
Port.C=63;
int freq = 1;
//#use delay(internal=16MHZ,clock_out)
sdb();
while(TRUE)
{
Port.C = Port.C-1;
delay_ms(1000/freq);
if(Port.C == -1)
{
Port.C = 63;
delay_ms(1000/freq);
}
if(Port.B != 0b00000101)
{
Port.C=0;
return;
}
}
}

