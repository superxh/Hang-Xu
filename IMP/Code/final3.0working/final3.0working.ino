//const byte adcPin = 0;  // A0

const int MAX_RESULTS = 54;
int k=0;
int results [MAX_RESULTS+1];
int results2 [MAX_RESULTS+1];
int filter [MAX_RESULTS-4];
int filter2 [MAX_RESULTS-4];
int resultNumber=0;
int turning;//0:stop 1:stright 2:turnleft 3:turnright

// ADC complete ISR
ISR (ADC_vect)
  {
    if(resultNumber < 55)
    {
    results [resultNumber] = analogRead (0);
    }
    if(resultNumber >= 55)
    {
    results2 [resultNumber-55] = analogRead (1);
    }
    resultNumber++;
    if (resultNumber >= 2*MAX_RESULTS+2)
    {
      ADCSRA = 0;  // turn off ADC
    }
  }  // end of ADC_vect
  
EMPTY_INTERRUPT (TIMER1_COMPB_vect);
 
void setup ()
  {
  Serial.begin (9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  // reset Timer 1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1B = bit (CS11) | bit (WGM12);  // CTC, prescaler of 8
  TIMSK1 = bit (OCIE1B);  
  OCR1A = 39;    
  OCR1B = 39;   // 20 uS - sampling frequency 50 kHz



  // wait for buffer to fill
  }
    


void loop () 
  { 
  if(k==0)
  {
  k=1;
  resultNumber=0;
  ADCSRA = 0;
  ADCSRB = 0;
  ADCSRA =  bit (ADEN) | bit (ADIE) | bit (ADIF);   // turn ADC on, want interrupt on completion
  ADCSRA |= bit (ADPS2);  // Prescaler of 16
  //ADMUX = bit (REFS0) | (adcPin & 7);
  ADCSRB = bit (ADTS0) | bit (ADTS2);  // Timer/Counter1 Compare Match B
  ADCSRA |= bit (ADATE);   // turn on automatic triggering
  }
  
  if (resultNumber == 2*MAX_RESULTS+2)
  {
//  for (int i = 0; i < MAX_RESULTS+1; i++)
//  {
//    Serial.println (results [i]);
//  }
//  Serial.println ("ok\n\n\n\n\n\n\n");
//  for (int i = 0; i < MAX_RESULTS+1; i++)
//  {
//    Serial.println (results2 [i]);
//  }
//  Serial.println ("ok\n\n\n\n\n\n\n");

  
  //sidejudge//////////////////////////////////////////////////////////////////////
  int result_min=results[0];
  //int result_max=results[0];
  int result2_min=results2[0];
  //int result2_max=results2[0];
  for (int i=1;i<MAX_RESULTS+1;i++)
  {
    if(results[i]<result_min) result_min=results[i];
    //if(results[i]>result_max) result_max=results[i];
    if(results2[i]<result2_min) result2_min=results2[i];
    //if(results2[i]>result2_max) result2_max=results2[i];
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
  //data print
//  for (int i = 0; i < MAX_RESULTS+1; i++)
//  {
//    Serial.println (results [i]);
//  }
//  Serial.println ("ok\n\n\n\n\n\n\n");
//  for (int i = 0; i < MAX_RESULTS+1; i++)
//  {
//    Serial.println (results2 [i]);
//  }
//  Serial.println ("ok\n\n\n\n\n\n\n");
  //filterprint
//  for (int i = 0; i < 50; i++)
//  {
//    Serial.println (filter [i]);
//  }
//  Serial.println ("ok\n\n\n\n\n\n\n");
//  for (int i = 0; i < 50; i++)
//  {
//    Serial.println (filter2 [i]);
//  }
//  Serial.println ("ok\n\n\n\n\n\n\n");
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
//  Serial.println (constantleft);
//  Serial.println (constantright);
  float distanceleft;// >160:ownside
  float distanceright;// >250: ownside 

  if(constantleft>400)
  {
  //distanceleft = 1.45*constantleft;
  distanceleft = 1.5*constantleft;
  }
  if(constantleft>900)
  {
  //distanceleft = 1.7*constantleft;
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
  digitalWrite(9, HIGH); 
  delay(1);    
  digitalWrite(9, LOW);   
  //digitalWrite(9, HIGH);  
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
  digitalWrite(6, HIGH); 
  delay(1);    
  digitalWrite(6, LOW);  
  //digitalWrite(9, HIGH);   
  delay(1);              
  pwmcount++;
  }
  }
  if (distanceleft == distanceright)
  {
    turning = 1;
  //Serial.println ("center");
//    int pwmcount=0;
//  while(pwmcount<30)
//  {
//  digitalWrite(6, HIGH); 
//  digitalWrite(9, HIGH);
//  delay(1);    
//  digitalWrite(6, LOW);  
//  digitalWrite(9, LOW);  
//  delay(1);              
//  pwmcount++;
//  }
  }
  }
  else
  {
    turning = 0;
  }
  /////////////////////////////////////////////////////////////////////////////////
  
  //powerdecide//////////////////////////////////////////////////////////////////////
//  if (turning == 0)
//  {
//  analogWrite(5,0);   //L-
//  analogWrite(6,0);   //L+
//  analogWrite(9,0);   //R+
//  analogWrite(10,0);  //R- 
//  }
//  if (turning == 1)
//  {
//  analogWrite(5,0);   //L-
//  analogWrite(6,95);  //L+
//  analogWrite(9,110); //R+
//  analogWrite(10,0);  //R- 
//  }
//  if (turning == 2)
//  {
//  analogWrite(5,0);   //L-
//  analogWrite(6,0);   //L+                        
//  analogWrite(9,110); //R+
//  analogWrite(10,0);  //R- 
//  }
//  if (turning == 3)
//  {
//  analogWrite(5,0);   //L-
//  analogWrite(6,95);  //L+
//  analogWrite(9,0);   //R+
//  analogWrite(10,0);  //R- 
//  }
  delay(1);
  /////////////////////////////////////////////////////////////////////////////////
  
  k=0;
  }  // end of setup
  }
