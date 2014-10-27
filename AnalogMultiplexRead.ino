/*
An open-source LM35DZ Temperature Sensor for Arduino. This project will be enhanced on a regular basis
(cc) by Daniel Spillere Andrade , http://www.danielandrade.net
http://creativecommons.org/license/cc-gpl
GRT March 29,2014:  Modified to use the CD4051 as a multiplexer for inputs
*/
 
int pin = 0; // analog pin
int tempc = 0,tempf=0; // temperature variables
int samples[8]; // variables to make a better precision
String strRowOne = "";
String strRowTwo = "";
String strTemp = "";
int maxi = -100,mini = 100; // to start max/min temperature
int i;
int j;
int r0 = 0; //value of the select pin on the 4051 (A on the data sheet)
int r1 = 0; //value of the select pin on the 4051 (B on the data sheet)
int r2 = 0; //value of the select pin on the 4051 (C on the data sheet)

void setup()
{
pinMode(2,OUTPUT); //s0 --> A
pinMode(3,OUTPUT); //s1 --> B
pinMode(4,OUTPUT); //s2 --> C

Serial.begin(9600); // start serial communication
}

void loop()
{
for (j=0;j<=7;j++){   // read first four pins of the 4051
  r0 = bitRead(j,0);  // read the first bit of our loop counter
  r1 = bitRead(j,1);  // read the second bit of our loop counter
  r2 = bitRead(j,2);
  digitalWrite(2,r0); // write to the first Select pin on the 4051
  digitalWrite(3,r1); // write to the second Select pin of the 4051
  digitalWrite(4,r2); // you get the idea
  
  for(i = 0;i<=7;i++){ // gets 8 samples of temperature  
  samples[i] = ( 5.0 * analogRead(pin) * 100.0) / 1024.0;
  tempc = tempc + samples[i];
  delay(10);
//  Serial.println(samples[i],DEC);
  }

  tempc = tempc/8.0; // better precision
  tempf = (tempc * 9)/ 5 + 32; // converts to fahrenheit
 
  if(tempc > maxi) {maxi = tempc;} // set max temperature
  if(tempc < mini) {mini = tempc;} // set min temperature
  strTemp = String(tempc,DEC);

 if(j==0)
  {
    strRowOne = ""; // Initialize the strings
    strRowTwo = "";
  }
  if(j<=3)
  {
 //   strRowOne = String(strRowOne + " " +j + " " + r2 + r1 + r0);
    strRowOne = String(strRowOne + " " + strTemp + " | ");
  }
  else
  {
 //   strRowTwo = String(strRowTwo + " " + j + " " + r2 + r1 + r0);
    strRowTwo = String(strRowTwo + " " + strTemp + " | ");
  }
  if(j==7)
  {
   Serial.println(strRowOne);
   Serial.println(strRowTwo);
   Serial.println("Next Sample");
  }
  tempc = 0;
  delay(10); // delay before loop
}
}
