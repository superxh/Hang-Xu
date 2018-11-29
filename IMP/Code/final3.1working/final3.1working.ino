/* 
Author: IMP Group B
Date complete: 26/04/2018
Filename: Current-tracking robot
Target device: Arduino Uno Rev3
Program function: to control the robot to track a current-carrying wire
*/

const byte pin_left = 6;  // Pin6 controls the left wheel
const byte pin_right = 9;  // Pin9 controls the right wheel
const byte adc_left = 0;  // A0, connected to the left coil
const byte adc_right = 1;  // A1, connected to the right coil
const int MAX_RESULTS = 54;// buffer size
int k=0;
int results1 [MAX_RESULTS+1];// circular buffer for data collected by left coil
int results2 [MAX_RESULTS+1];// circular buffer for data collected by right coil
int filter1 [MAX_RESULTS-4];
int filter2 [MAX_RESULTS-4];
int resultNumber=0;// counter for ADC sampling


/* Analogue to digital converter complete interrupt service routine */
ISR (ADC_vect)
{
    if(resultNumber < 55) results1 [resultNumber] = analogRead (adc_left);// sampling channel 1,read and save signal sensed by the left coil 
    if(resultNumber >= 55)results2 [resultNumber-55] = analogRead (adc_right);// shift to sampling channel 2,read and save signal sensed by the right coil 
    resultNumber++;
    if (resultNumber >= 2*MAX_RESULTS+2) ADCSRA = 0; // after finishing sampling, turn off ADC and wait for data getting processed
  } 
  
EMPTY_INTERRUPT (TIMER1_COMPB_vect);// the interrupt of timer1 is empty as it is only used to trigger ADC
 
void setup ()
{
  Serial.begin (9600);// set baud rate to be 9600 for the interface between arduino and PC
  pinMode(5, OUTPUT);//connected to H-bridge for backward rotation of the left wheel
  pinMode(6, OUTPUT);//connected to H-bridge for forward rotation of the left wheel
  pinMode(9, OUTPUT);//connected to H-bridge for forward rotation of the right wheel
  pinMode(10, OUTPUT);//connected to H-bridge for backward rotation of the right wheel
  /* reset Timer1 */
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  //////////////////
  /* setup Timer1 */
  TCCR1B = bit (CS11) | bit (WGM12); // set prescaler of CTC to be 8
  TIMSK1 = bit (OCIE1B);  //interrupt enable compare B
  OCR1A = 39;  
  OCR1B = 39; //trigger the Timer1 interrupt when count to 39//(calculated prescalor and counter for triggering in 50kHz)
}

void loop () 
{ 
  if(k==1) //k is the value to ensure ADC oonly triggered once
  {
    k=0;
    resultNumber=0;//reset index of ADC buffer
    /* reset ADC */
    ADCSRA = 0;
    ADCSRB = 0;
    /* setup ADC */
    ADCSRA =  bit (ADEN) | bit (ADIE) | bit (ADIF); // turn ADC on | enable ADC interrupt | wait and turn interrupt off after the ADC service complete 
    ADCSRA |= bit (ADPS2);  // Prescaler of 16, ADC clock 1000kHz to ensure the ADC reading is fast enough to complete in a 50kHz Timer loop
    ADCSRB = bit (ADTS0) | bit (ADTS2);  // Timer/Counter1 Compare Match B, everytime when timer count to OCR1B=39(50kHz), trigger the ADC interrupt
    ADCSRA |= bit (ADATE);   // turn on automatic triggering - sampling frequency 50 kHz
  }
  
  if (resultNumber == 2*MAX_RESULTS+2)
  {

  //sidejudge//////////////////////////////////////////////////////////////////////
  int result_min=results[0];
  int result2_min=results2[0];
  for (int i=1;i<MAX_RESULTS+1;i++)
  {
    if(results[i]<result_min) result_min=results[i];
    if(results2[i]<result2_min) result2_min=results2[i];
  }
  //moving average
  for (int i=1;i<MAX_RESULTS+1;i++)
  {
    results[i]=results[i]-result_min;
    results2[i]=results2[i]-result2_min;
  }
  for (int i=0;i<50;i++)
  {
    filter[i]=results[i+1]+results[i+2]+results[i+3]+results[i+4]+results[i+5];
    filter2[i]=results2[i+1]+results2[i+2]+results2[i+3]+results2[i+4]+results2[i+5];
  }

  ///////////////////
  int filter_min=filter[0];
  int filter_max=filter[0];
  int filter2_min=filter2[0];
  int filter2_max=filter2[0];
  for (int i=0;i<50;i++)
  {
    if(filter[i]<filter_min) filter_min=filter[i];
    if(filter[i]>filter_max) filter_max=filter[i];
    if(filter2[i]<filter2_min) filter2_min=filter2[i];
    if(filter2[i]>filter2_max) filter2_max=filter2[i];
  }
  ///////////////////
  int constantleft=filter_max-filter_min;
  int constantright=filter2_max-filter2_min;

  float distanceleft;// >160:ownside
  float distanceright;// >250: ownside 

  if(constantleft>400)
  {
  distanceleft = 1.5*constantleft;
  }
  if(constantleft>900)
  {
  distanceleft = 1.5*constantleft;
  }
  
  if(constantright>400)
  {
  distanceright = constantright;
  }
  if(constantright>900)
  {
  distanceright = constantright;
  }
  Serial.println (distanceleft);
  Serial.println (distanceright);
  if (distanceleft >=450 || distanceright >= 450)
  {
  if (distanceleft > distanceright)
  {
    turning = 2;
    Serial.println ("left");
    int pwmcount=0;
    while(pwmcount<15)
    {
      digitalWrite(pin_right, HIGH); 
      delay(1);    
      digitalWrite(pin_right, LOW);   
      delay(1);              
      pwmcount++;
    }
 }
  if (distanceleft < distanceright)
  {
    turning = 3;
    Serial.println ("right");
    int pwmcount=0;
    while(pwmcount<15)
    {
      digitalWrite(pin_left, HIGH); 
      delay(1);    
      digitalWrite(pin_left, LOW);    
      delay(1);              
      pwmcount++;
    }
  }
  if (distanceleft == distanceright)
  {
    turning = 1;
  }
  }
  else
  {
    turning = 0;
  }
  /////////////////////////////////////////////////////////////////////////////////
  

  delay(1);
  /////////////////////////////////////////////////////////////////////////////////
  
  k=1;
  }  // end of setup
  }
