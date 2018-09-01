//  Mood Lamp

#include <SoftwareSerial.h>
//  This value controls how fast the mood lamp runs.
int pulseSpeed = 5;

int ldrPin = 0;     // LDR in Analog Input 0 to read the surrounding light.
int redLed = 11;    // red LED in Digital Pin 11.
int greenLed = 10;  // green LED in Digital Pin 10.
int blueLed = 9;    // blue LED in DIgital Pin 9.

// The value of the light in the room.
int ambientLight;

// The brightness of the lamp (2-255).
int power = 120;

//Array to store value of power to RGB
float RGB[2];


float CommonMathVariable = 180 / PI;

//Initializing LEDs
void setup () {

 
  Serial.begin(9600);

  // Send data out to the LEDs.
  pinMode (redLed, OUTPUT);
  pinMode (greenLed, OUTPUT);
  pinMode (blueLed, OUTPUT);

  //  Sets all the outputs(LEDs) to LOW(OFF), so that they do not turn on during startup.
  digitalWrite (redLed, LOW);
  digitalWrite (greenLed, LOW);
  digitalWrite (blueLed, LOW);

}   

//Loop to cycle through colors & brightnesses 


void loop () {

 
  for (float x = 0; x < PI; x = x + 0.00005) {

    //makes the LEDs fade in and out at differen intervals
    RGB[0] = power * sin(x  * (CommonMathVariable));                // Red LED.
    RGB[1] = power * sin((x + PI / 2) * (CommonMathVariable));      // Green LED.
    RGB[2] = power * sin((x + (PI * 2 / 3)) * (CommonMathVariable)); // Blue LED.

    // Ambient light in the room
    ambientLight = analogRead(ldrPin);

    // Turns on when it is dark. Less light = greater resistance.
    if (ambientLight > 700) {

      // This shuts the LED off for a bit once the pulse is less than 20 to mix the other 2 colours.
      if (abs (RGB[0]) < 10) {
        RGB[0] = 0;
      }
      if (abs (RGB[1]) < 10) {
        RGB[1] = 0;
      }
      if (abs (RGB[2]) < 10) {
        RGB[2] = 0;
      }

      // varies the delay, When one colour is dim, the delay is longer.
      // keeps the that colour dim for a bit longer to let the other two mix.

      if (abs (RGB[0]) < 40) {
        delay (15 * pulseSpeed);
      }
      else if (abs (RGB[1]) < 20) {   
      }
      else if (abs (RGB[2]) < 30) {
        delay (10 * pulseSpeed);
      }

     
      
      else {}

      //  writes abs value to LEDs
      analogWrite (redLed, abs (RGB[0]));
      analogWrite (greenLed, abs (RGB[1]));
      analogWrite (blueLed, abs (RGB[2]));

    } 

    //If it is too bright in the room, the LEDs are set back to LOW(OFF).
    else {
      digitalWrite (redLed, LOW);
      digitalWrite (greenLed, LOW);
      digitalWrite (blueLed, LOW);
    }

  }   
}     
