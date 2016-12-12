//  ***********************************************************************************************************************************************************
//  * Sam's Moodlamp with additional Temperature Sensor. Based off ricardouvina's sin wave Moodlamp (http://www.instructables.com/id/Mood-Lamp-with-Arduino/) *
//  * Also includes a personally modified version of the "ARDUINO SERIAL MONITOR" (http://www.instructables.com/id/HOW-TO-use-the-ARDUINO-SERIAL-MONITOR/)    *
//  *                                          to view the temperature of the temperature sensor to ensure it is working.                                     *
//  *                                                                    Last edited 9/12/16                                                                  *
//  ***********************************************************************************************************************************************************

float RGB[3]; // Creates a floating array known as 'RGB' with 3 sections.
int tmpPin = 0; // Temperature Sensor in Analog Pin A0.
int redLed   = 9;  // Red LED in Digital Pin 11 (PWM)
int greenLed = 10;  // Green LED in Digital Pin 10 (PWM)
int blueLed  = 11;   // Blue LED in Digital Pin 9 (PWM)
int alertLed = 7;
int speakerPin = 12;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 415, 392, 370, 349, 330, 311, 294, 277, 261};
//            mid C  C#   D    D#   E    F    F#   G    G#   A    G#   G   F#    F    E    D#   D    C#  mid C

void setup() {
  pinMode(redLed, OUTPUT); // Tell's ARDUINO that redLed is an output.
  pinMode(greenLed, OUTPUT); // Tell's ARDUINO that greenLed is an output.
  pinMode(blueLed, OUTPUT); // Tell's ARDUINO that blueLed is an output.
  pinMode(alertLed, OUTPUT); // Tell's ARDUINO THAT alertLed is an output.
 
  // Sets all the outputs to low at the start of the program.
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(alertLed, LOW);

  // Begins the serial monitoring at a baud rate of 9600 bits per second.
  Serial.begin(9600);

  buzzerTune();
}

void loop() {        
  debug(); // Optional/Debugging Only - Debug Temperature Sensor by running the serial monitor on its readings.
  AlertLED(); // Flash Alert LED to show transition to Mood Lamp function
  moodLamp(); // Run Moodlamp Function
  reset(); // Run Reset Function to Reset LEDs to 0
  delay(300);
  AlertLED(); // Flash Alert LED to show transition to temperature function
  temperature(); // Run Temperature Function
  delay(300);
  reset(); // Reset Colour Values to 0
}

void moodLamp () {
  for (float x = 0; x < PI; x = x + 0.00001) {
    RGB[0] = 255 * abs(sin(x * (180 / PI)));      // CALCULATE VALUE OF RED LED
    RGB[1] = 255 * abs(sin((x + PI / 3) * (180 / PI))); // CALCULATE VALUE OF GREEN LED
    RGB[2] = 255 * abs(sin((x + (2 * PI) / 3) * (180 / PI))); // CALCULATE VALUE OF BLUE LED

    // WRITE THE CALCULATED VALUE ONTO COLOUR CHANNEL PINS
    analogWrite(redLed, RGB[0]);
    analogWrite(greenLed, RGB[1]);
    analogWrite(blueLed, RGB[2]);
  }
  delay(30000);
}

void temperature() {
  int temperatureSensor = analogRead(tmpPin);
  // IF TEMPERATURE IS HIGH, SET LED TO RED
  if (temperatureSensor  > 200) {
    analogWrite(redLed, 0);
    analogWrite(greenLed, 255);
    analogWrite(blueLed, 255);
  }

  // IF TEMPERATURE IS MID-RANGE, SET LED TO PURPLE
  if (temperatureSensor  < 200 && temperatureSensor  > 100) {
    analogWrite(redLed, 255);
    analogWrite(greenLed, 0);
    analogWrite(blueLed, 255);
  }

  // IF TEMPERATURE IS LOW, SET LED TO BLUE
  if (temperatureSensor  < 100) {
    analogWrite(redLed, 255);
    analogWrite(greenLed, 255);
    analogWrite(blueLed, 0);
  }
}

void reset() {
  // RESET THE COLOUR CHANNELS OF RGB LED, WHILE SHOWING A VISUAL INDICATOR THAT IT'S COMPLETE.
  analogWrite(redLed, 0);
  analogWrite(greenLed, 0);
  analogWrite(blueLed, 0);
}

void debug() {
  //DEBUGGING CODE - FOR LOOP ENSURES THAT SERIAL MONITOR CODE PRINTS READING 50 TIMES BEFORE PROGRAM STARTS. CAN BE COMMENTED OUT LOOP FUNCTION TO SKIP THIS PROCESS
  int n, i;
  Serial.print("Temperature Readings:");
  Serial.print('\n');
  for (int i = 0, loopCount = 20; i < loopCount; i++) {
    int temperatureSensor = analogRead(tmpPin);
    Serial.println(temperatureSensor);
    if (Serial.available() > 0)
    {
      temperatureSensor = Serial.read();
      Serial.print(temperatureSensor);
      Serial.println();
    }
  }
  Serial.print('\n');    
}

void AlertLED() {
  // THIS FOR LOOP FLASHES THE ALERT LED TO VISUALLY SHOW THE PROGRAM SWITCHING BETWEEN FUNCTIONS.
    digitalWrite(alertLed, HIGH);
    delay(800);
    digitalWrite(alertLed, LOW);
  }

void buzzerTune() {
// This for loop iterates through all of the tones set in the 'tones' variable.
    for (int i = 0, toneCount = 20; i < toneCount; i++) {
    tone(speakerPin, tones[i]);
    delay(50);
  }
  noTone(speakerPin);
}
