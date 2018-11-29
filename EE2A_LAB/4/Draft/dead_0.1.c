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

/***************RDA_interrupt***************/
#INT_RDA
void rda_isr(void) 
{ 
   Port.debug=0b1;
   if (kbhit())
   {

   }
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

   if (1)
      {
      
      //putc(c); // Send it back to the PC
      //output_high(PIN_C3);
      }
      
/*******************************/
   }
}
