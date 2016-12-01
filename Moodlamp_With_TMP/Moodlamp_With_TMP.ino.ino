//  ***********************************************************************************************************************************************************
//  * Sam's Moodlamp with additional Temperature Sensor. Based off ricardouvina's sin wave Moodlamp (http://www.instructables.com/id/Mood-Lamp-with-Arduino/) *
//  * Also includes a personally modified version of the "ARDUINO SERIAL MONITOR" (http://www.instructables.com/id/HOW-TO-use-the-ARDUINO-SERIAL-MONITOR/)    *
//  *                                          to view the temperature of the temperature sensor to ensure it was working.                                    *
//  *                                                                    Last edited 28/11/16                                                                 *
//  ***********************************************************************************************************************************************************

float RGB[3]; // Creates a floating array known as 'RGB' with 3 sections.
int ldrPin = 0;     // LDR in Analog Input 0 to read the temperature. 
int redLed   = 9;  // Red LED in Digital Pin 11 (PWM)
int greenLed = 10;  // Green LED in Digital Pin 10 (PWM)
int blueLed  = 11;   // Blue LED in Digital Pin 9 (PWM)
 
void setup(){
  pinMode(redLed,OUTPUT);  // Tell's ARDUINO that redLed is an output.
  pinMode(greenLed,OUTPUT);// Tell's ARDUINO that greenLed is an output.
  pinMode(blueLed,OUTPUT); // Tell's ARDUINO that blueLed is an output.
 
  // Sets all the outputs to low at the start of the program.
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,LOW);
  digitalWrite(blueLed,LOW);
  
 // Begins the serial monitoring. 
 Serial.begin(9600);  
}

void loop(){
  for (float x=0;x<PI;x=x+0.00001){
    RGB[0]=255*abs(sin(x*(180/PI)));            // calculate the brightness for the red led
    RGB[1]=255*abs(sin((x+PI/3)*(180/PI)));     // calculate the brightness for the green led
    RGB[2]=255*abs(sin((x+(2*PI)/3)*(180/PI))); // calculate the brightness for the blue led
      //  write the brightness on the leds
      analogWrite(redLed,RGB[0]);
      analogWrite(greenLed,RGB[1]);.
      analogWrite(blueLed,RGB[2]);
    }
    
    delay(30000);
    
    // Sets the Green colour channel of the RGB to low.
    digitalWrite(greenLed,LOW);
   
    int temperatureSensor = analogRead(ldrPin);
    Serial.println(temperatureSensor);
   
    if (temperatureSensor  > 230){
        temperatureSensor = 230;
    }
   
    if (temperatureSensor < 100){
        temperatureSensor = 100;
    }
    float scaleFactor;
   
    scaleFactor = temperatureSensor - 100 / 100;
   
    int RedOutput = 255 * scaleFactor;
    int BlueOutput = 255 * (1 - scaleFactor);
    
    analogWrite(redLed, RedOutput);
    analogWrite(blueLed, BlueOutput);
       
    //delay(60000);
    
    //
    
    if (Serial.available() > 0)
  {
    temperatureSensor = Serial.read();
    Serial.print(temperatureSensor);   
    Serial.print("        ");      
    Serial.print(temperatureSensor, HEX);
    Serial.print("       ");     
    Serial.print(char(temperatureSensor));
    
    if(temperatureSensor == '1') // Single Quote! This is a character.
    {
      digitalWrite(redLed,HIGH);
      Serial.print(" LED ON ");
    }
    
    if(temperatureSensor == '0')
    {
      digitalWrite(redLed,LOW);
      Serial.print(" LED OFF");
    }
    
    Serial.println();    // End the line

  // END Serial Available
  }
}
