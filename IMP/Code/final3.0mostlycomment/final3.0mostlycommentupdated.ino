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
int k=0;//ensure ADC interrupt routine is executed once every triggered
int results1 [MAX_RESULTS+1];// circular buffer for data collected by left coil
int results2 [MAX_RESULTS+1];// circular buffer for data collected by right coil
int filter1 [MAX_RESULTS-4];// filtered data of result1
int filter2 [MAX_RESULTS-4];// filtered data of result2
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
  TCCR1B = 0;
  TCNT1 = 0;
  /* setup Timer1 */
  TCCR1B = bit (CS11) | bit (WGM12); // set prescaler of CTC to be 8
  TIMSK1 = bit (OCIE1B);  //interrupt enabled when the counter matches B
  OCR1B = 39; //trigger the Timer1 interrupt when count to 39//(calculated prescalor and counter for triggering in 50kHz)
}

void loop () 
{ 
  
  
  
  if(k==1)//turn on ADC once in each decission making loop
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
    ADCSRA |= bit (ADATE);   // turn on automatic triggering - sampling frequency is 50 kHz
  }
  
  
  
  if (resultNumber == 2*MAX_RESULTS+2)// if buffers are filled
  {
    /*pre-process data--subtract data by the minimun value to prevent the processed data result from being too large, exceeding the value range*/
    int result1_min=results1[0];
    int result2_min=results2[0];
    for (int i=1;i<MAX_RESULTS+1;i++)//find minimum value
    {
      if(results1[i]<result1_min) result1_min=results1[i];
      if(results2[i]<result2_min) result2_min=results2[i];
    }
    for (int i=1;i<MAX_RESULTS+1;i++)//substract the minimum value
    {
      results1[i]=results1[i]-result1_min;
      results2[i]=results2[i]-result2_min;
    }
    /* apply moving average filter */
    for (int i=0;i<50;i++)// taking average over every 5 samples
    {
      filter1[i]=results1[i+1]+results1[i+2]+results1[i+3]+results1[i+4]+results1[i+5];
      filter2[i]=results2[i+1]+results2[i+2]+results2[i+3]+results2[i+4]+results2[i+5];
    }
    /* find the maximum magnitude of data */
    int filter1_min=filter1[0];
    int filter1_max=filter1[0];
    int filter2_min=filter2[0];
    int filter2_max=filter2[0];
    for (int i=0;i<50;i++)//find the max and min value
    {
      if(filter1[i]<filter1_min) filter1_min=filter1[i];
      if(filter1[i]>filter1_max) filter1_max=filter1[i];
      if(filter2[i]<filter2_min) filter2_min=filter2[i];
      if(filter2[i]>filter2_max) filter2_max=filter2[i];
    }
    int magnitude_left=filter1_max-filter1_min;
    int magnitude_right=filter2_max-filter2_min;
    /* because the two sensor is not identical and the difference is non-linear, the filted data needs to be segmented weighted */
    float weighted_left;
    float weighted_right;
    if(magnitude_left>400) weighted_left = 1.5*magnitude_left;
    if(magnitude_left>900)weighted_left = 1.5*magnitude_left;
    if(magnitude_right>400)weighted_right = magnitude_right;
    if(magnitude_right>900)weighted_right = magnitude_right;
    Serial.println (weighted_left);
    Serial.println (weighted_right);
    /* sidejudgement*/
    if (weighted_left >=450 || weighted_right >= 450)
    {
      if (weighted_left > weighted_right)// if the left voltage is bigger than the right, turn left
      {
        Serial.println ("Turn left");
        int pwmcount=0;
        while(pwmcount<15)
        {
          /* left wheel keep still and right wheel move forward */
          digitalWrite(pin_right, HIGH); //set PWM at 500Hz with duty cycle=50%
          delay(1);    
          digitalWrite(pin_right, LOW);   
          delay(1);              
          pwmcount++;
        }
      }
      if (weighted_left < weighted_right)// if the left voltage is smaller than the right, turn right
     {
        Serial.println ("Turn right");
        int pwmcount=0;
        while(pwmcount<15)
        {
          /* right wheel keep still and left wheel move forward */
          digitalWrite(pin_left, HIGH); 
          delay(1);    
          digitalWrite(pin_left, LOW);    
          delay(1);              
          pwmcount++;
        }
      }
      delay(1);//delay between loops to ensure ADC be ready again
      k=1;//allow ADC to be turn on again after all decissions done 
    }
  }
  
  
  
  
}
