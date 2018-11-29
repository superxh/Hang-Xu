#include<18F27K40.h>
#include<stdio.h>
#use delay(internal=64MHZ,clock_out)

void test() //测试频率1HZ
{
//#use delay(internal=16MHZ,clock_out)
while(TRUE)
{
output_high(PIN_C0);
delay_ms(500);
output_low(PIN_C0);
delay_ms(500);

}
}

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
output_high(PIN_C0);
}
if(c == 0)
{
output_low(PIN_C0);
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
output_high(PIN_C0);
}
if(c == 0)
{
output_low(PIN_C0);
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(32*freq));
i = 0;
delay_ms(1000/(32*freq));
//
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0)))
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
output_high(PIN_C0);
}
if(c == 0)
{
output_low(PIN_C0);
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(16*freq));
i = 0;
delay_ms(1000/(16*freq));
//
//2
//judge part
c = n%2;
if(c == 1)
{
output_high(PIN_C0);
}
if(c == 0)
{
output_low(PIN_C0);
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(16*freq));
i = 0;
delay_ms(1000/(16*freq));
//
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1)))
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
output_high(PIN_C0);
}
if(c == 0)
{
output_low(PIN_C0);
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(8*freq));
i = 0;
delay_ms(1000/(8*freq));
//
//2
//judge part
c = n%2;
if(c == 1)
{
output_high(PIN_C0);
}
if(c == 0)
{
output_low(PIN_C0);
}
//
//clock part
i = 1;
n = n + 1;
delay_ms(1000/(8*freq));
i = 0;
delay_ms(1000/(8*freq));
//
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0)))
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
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==1)))
{
return;
}
}
}

void s4()
{
int n = 0;
int freq = 1;
//#use delay(internal=16MHZ,clock_out)
sdb();
while(TRUE)
{
if(n==64)
{
n=0;
}
output_c(n);
delay_ms(1000/freq);
n=n+1;
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0)))
{
output_c(0);
return;
}
}
}

void s5()
{
int n = 63;
int freq = 1;
//#use delay(internal=16MHZ,clock_out)
sdb();
while(TRUE)
{
if(n==-1)
{
n=63;
}
output_c(n);
delay_ms(1000/freq);
n=n-1;
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1)))
{
output_c(0);
return;
}
}
}

void s6()
{
int n = 0;
int freq = 1;
int a,b,c,d,e,f;//a:C0,b:C1...
int a1,b1,c1,d1,e1,f1;//a1:C0,b1:C1...
int nn;
//#use delay(internal=4MHZ,clock_out)
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
output_c(nn);
delay_ms(1000/freq);
n=n+1;
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0)))
{
output_c(0);
return;
}
}
}

void s7()
{
int n = 0;
int freq = 1;
int a,b,c;
int a1,b1,c1;
int nn;
//#use delay(internal=16MHZ,clock_out)
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
output_c(nn);
delay_ms(1000/freq);
n=n+1;
if(!((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==1)))
{
output_c(0);
return;
}
}
}

void s8()
{
sdb();
while(TRUE)
{
if(input(PIN_B0)*input(PIN_B2)==1)
{
output_high(PIN_C0);
}
else
{
output_low(PIN_C0);
}
if(input(PIN_B1)*input(PIN_B3)==1)
{
output_high(PIN_C1);
}
else
{
output_low(PIN_C1);
}
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0)))
{
output_c(0);
return;
}
}
}

void s9()
{
sdb();
while(TRUE)
{
if(input(PIN_B0)+input(PIN_B2)==0)
{
output_low(PIN_C0);
}
else
{
output_high(PIN_C0);
}
if(input(PIN_B1)+input(PIN_B3)==0)
{
output_low(PIN_C1);
}
else
{
output_high(PIN_C1);
}
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1)))
{
output_c(0);
return;
}
}
}

void s10()
{
sdb();
while(TRUE)
{
if(input(PIN_B0)==1)
{
output_low(PIN_C0);
}
else
{
output_high(PIN_C0); 
}
if(input(PIN_B1)==1)
{
output_low(PIN_C1);
}
else
{
output_high(PIN_C1);
}
if(input(PIN_B2)==1)
{
output_low(PIN_C2);
}
else
{
output_high(PIN_C2);
}
if(input(PIN_B3)==1)
{
output_low(PIN_C3);
}
else
{
output_high(PIN_C3);
}
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0)))
{
output_c(0);
return;
}
}
}

void s11()
{
sdb();
while(TRUE)
{
if(input(PIN_B0)==input(PIN_B2))
{
output_low(PIN_C0);
}
else
{
output_high(PIN_C0);
}
if(input(PIN_B1)==input(PIN_B3))
{
output_low(PIN_C1);
}
else
{
output_high(PIN_C1);
}
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==1)))
{
output_c(0);
return;
}
}
}

Void s12()
{
sdb();
while(TRUE)
{
//if((input(PIN_B0)==0)&&(input(PIN_B1)==0))
//{
//  output_low(PIN_C0);
//}
if((input(PIN_B0)==0)&&(input(PIN_B1)==1))
{
output_low(PIN_C0);
}
if((input(PIN_B0)==1)&&(input(PIN_B1)==0))
{
output_high(PIN_C0);
}
if((input(PIN_B0)==1)&&(input(PIN_B1)==1))
{
output_high(PIN_C0);
delay_ms(500);
output_low(PIN_C0);
delay_ms(500);
}
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0)))
{
output_c(0);
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
int i=input(PIN_B3)+(input(PIN_B2)*2)+(input(PIN_B1)*4)+(input(PIN_B0)*8);//0 MSB
if (i == 0){freq=2;}
if (i == 1){freq=4;}
if (i == 2){freq=5;}
if (i == 3){freq=6;}
if (i == 4){freq=7;}
if (i == 5){freq=8;}
if (i == 6){freq=9;}
if (i == 7){freq=10;}
if (i == 8){freq=20;}
if (i == 9){freq=21;}
if (i == 10){freq=22;}
if (i == 11){freq=23;}
if (i == 12){freq=24;}
if (i == 13){freq=27;}
if (i == 14){freq=28;}
if (i == 15){freq=30;}
gg = 1000/freq;
output_c(1);
delay_ms(gg);
output_c(2);
delay_ms(gg);
output_c(4);
delay_ms(gg);
output_c(8);
delay_ms(gg);
output_c(16);
delay_ms(gg);
output_c(32);
delay_ms(gg);
output_c(64);
delay_ms(gg);
output_c(128);
delay_ms(gg);
output_c(0);

if(!((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1)))
{
output_c(0);
return;
}
}
}

void s14()
{
//int x;
sdb();

float num=1.0;
int sp;
while(true)
{
if(num==384){num=129;}
if(num==258){num=3;}
if(num==1.5){num=129;}
if(num==64.5){num=192;}
if((num==3)||(num==6)||(num==12)||(num==24)||(num==48)||(num==96)||(num==192)||(num==384)){num=(num/3);}
if(num==129){num=128;}
if((num==1)||(num==2)||(num==4)||(num==8)||(num==16)||(num==32)||(num==64)||(num==128)||(num==256)||(num==0.5)){num=num;}
while(input(PIN_B2)==1&&input(PIN_B3)==1)
{
if(num==256){num=1;}
if(num==0.5){num=128;}
output_c((int)num);
int dir=input(PIN_B0);
if(dir==1){num=num*2;}
if(dir==0){num=num/2;}
if(input(PIN_B1)==1){sp=1;}
if(input(PIN_B1)==0){sp=5;}
delay_ms(250/sp);
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0)))
{
return;
}
}
if(num==256){num=1;}
if(num==0.5){num=128;}
if((num==1)||(num==2)||(num==4)||(num==8)||(num==16)||(num==32)||(num==64)){num=num*3;}
if(num==128){num=129;}
if((num==3)||(num==6)||(num==12)||(num==24)||(num==48)||(num==96)||(num==192)||(num==384)||(num==1.5)||(num==258)||(num==64.5)){num=num;}
while(input(PIN_B2)==0&&input(PIN_B3)==0)//||(input(PIN_B2)==1&&input(PIN_B3)==0))
{
if(num==384){num=129;}
if(num==258){num=3;}
if(num==1.5){num=129;}
if(num==64.5){num=192;}
output_c((int)num);
int dir=input(PIN_B0);
if(dir==1){num=num*2;}
if(dir==0){num=num/2;}
if(input(PIN_B1)==1){sp=1;}
if(input(PIN_B1)==0){sp=5;}
delay_ms(250/sp);
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0)))
{
return;
}
}
if(!((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0)))
{
output_c(0);
return;
}
}
}


void s15()
{
while(TRUE)
{

if((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0))//B7高位
{
s0();
}
if((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1))
{
s1();
}
if((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0))
{
s2();
}

if((input(PIN_B4)==0)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==1))
{
s3();
}
if((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0))
{
s4();
}
if((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1))
{
s5();
}
if((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0))
{
s6();
}
if((input(PIN_B4)==0)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==1))
{
s7();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0))
{
s8();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1))
{
s9();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0))
{
s10();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==0)&&(input(PIN_B6)==1)&&(input(PIN_B7)==1))
{
s11();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==0))
{
s12();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==0)&&(input(PIN_B7)==1))
{
s13();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==0))
{
s14();
}
if((input(PIN_B4)==1)&&(input(PIN_B5)==1)&&(input(PIN_B6)==1)&&(input(PIN_B7)==1))//B7高位
{
output_c(0);
}
}
}


void main()
{
//test();
//s0();
//s1();
//s2();
//s3();
//s4();
//s5();
//s6();
//s7();
//s8();
//s9();
//s10();
//s11();
//s12();
s15();
}

