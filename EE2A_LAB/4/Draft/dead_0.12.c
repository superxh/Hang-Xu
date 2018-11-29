#include <18F27K40.h> 
#include <stdio.h> 
#include <string.h>
#use delay(internal=32Mhz,clock_out) //set main frequency at 4MHz 

/***************rs232 setting***************/
#pin_select U1TX=PIN_C0
#pin_select U1RX=PIN_C1 
#use rs232(uart1, baud=9600, ERRORS)

/***************structure***************/
struct IO_Port_Definition
   {
   int unusedA:8;//PIN_A0..7 
   int unusedB:8;//PIN_B0..7 
   int1 ts;//PIN_C0 
   int1 rc;//PIN_C1 
   int1 debug; //PIN_C2 
   int unusedC:5; //PIN_C4..7 
   };
struct IO_Port_Definition Port; 
struct IO_Port_Definition PortDirection; 
#byte Port = 0xF8D 
#byte PortDirection = 0xF88 

/***************variable***************/
char c[32];
int in=0;
//char led4[7]={'L', 'E', 'D', ' ', 'O', 'N', '\0'};
char led4on[]="LED4 ON";
char led4off[]="LED4 OFF";
char led4flash[]="LED4 FLASH";
int pause=1;
/***************RDA_interrupt***************/
#INT_RDA
void rda_isr(void) 
{ 
   Port.debug=0b1;
   //output_low(PIN_C3);//debug
   //delay_ms(500);//debug
   pause=1;
   c[0]=0;//reset c
   in=0;
   do
   {
   c[in]=getc();
   putc(c[in]);
   if(c[in]==127)//backspace check
   {
   output_high(PIN_C3);
   in=in-2;
   }
   in=in+1;
   }
   while((in<31)&&(c[in-1]!=13));
   c[in-1]=0;
   putc(13);
   putc(10);
   //printf(c);
   Port.debug=0b0;
   
}

/***************main_function***************/
void main() 
{ 
   PortDirection.ts=0b0;
   PortDirection.rc=0b1;
   PortDirection.debug=0b0;
   enable_interrupts(INT_RDA); 
   enable_interrupts(GLOBAL); 
   //output_high(PIN_C3);
   while(1)
   {
   
/*******************************/
   //output_high(PIN_C3);//debug
   if (STRICMP(c,led4on)==0)
      {
      puts("OK");
      while(STRICMP(c,led4on)==0)
      {
      output_high(PIN_C4);//debug
      //c[0]=0;//reset c
      }
      }
   if (STRICMP(c,led4off)==0)
      {
      puts("OK");
      while(STRICMP(c,led4off)==0)
      {
      output_low(PIN_C4);//debug      
      //c[0]=0;//reset c
      }
      }
   if (STRICMP(c,led4flash)==0)
      {  
      puts("OK");
      while(STRICMP(c,led4flash)==0)
      {
      output_high(PIN_C4);//debug
      delay_ms(500);
      output_low(PIN_C4);
      delay_ms(500);
      }
      //c[0]=0;//reset c
      }
    else
    {
    puts("ERROR");
    pause=0;
    while(pause==0);
    }
/*******************************/
   }
}
