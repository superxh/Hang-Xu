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
#define SERIALBUFFSIZE 32
char      Serial_buffer[SERIALBUFFSIZE];
int       Serial_next_in = 0;
int       Serial_next_out = 0;
short int SerialCmdWaitFlg = FALSE;
short int CmdDoneFlag;
char  CmdStr[15];

/***************getcmd(dealing with Serial_buffer)***************/
void GetCom(char * command_string) 
{    
int length;    
char c;    
length=0;  
/* Reset command received flag*/  
SerialCmdWaitFlg = FALSE;  
/* Ignore leading spaces */  
do 
{ 
c=Serial_buffer[Serial_next_out]; 
/*  Get  a  character  from  the  Serial  buffer  */ 
Serial_next_out=(Serial_next_out+1)  %  SERIALBUFFSIZE; 
}  
while(c  =='  '); 
/*  A  non-space  character  has  been  entered  */ 
command_string[length++]=c; 
/*  Get  rest  of  command  string  -  until  space  or  CR  terminated  or  input  string  is  too  long*/ 
while  ((c  !=  '  ')&&(c  !=  13)&&(length<20)) 
{ 
c=Serial_buffer[Serial_next_out]; 
/*  Get  a  character  from  the  Serial  buffer  */ 
Serial_next_out=(Serial_next_out+1)  %  SERIALBUFFSIZE; 
command_string[length++]=c; 
} 
command_string[--length]  =  0; /*  Null  terminate  string  */  
} 

/***************RDA_interrupt***************/
#INT_RDA
void rda_isr(void) 
{ 
   Port.debug=0b1;
   do
   {
   Serial_buffer[Serial_next_in]=getc();
   putc(Serial_buffer[Serial_next_in]);
   Serial_next_in=Serial_next_in+1;
   }
   while(Serial_buffer[Serial_next_in-1] != 13);
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

   while(1)
   {
   
/*******************************/
   GetCom(CmdStr);
   printf(CmdStr)
   if (1)
      {
      
      //putc(c); // Send it back to the PC
      //output_high(PIN_C3);
      }
      
/*******************************/
   }
}
