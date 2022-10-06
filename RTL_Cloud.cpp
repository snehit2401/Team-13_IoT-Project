//Code that works hopefully
/* 
  Sketch generated by the Arduino IoT Cloud Thing "C.C.IoT. Project"
  https://create.arduino.cc/cloud/things/d545c232-cda6-49f5-b323-9e6ffebca440 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  int obj_position;
  int screen_position;
  bool start;
  bool lED_on;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"

// defines pins numbers
const int stepPin1 = 16;
const int dirPin1 = 17;
const int stepPin2 = 33;
const int dirPin2 = 32;
const int stepsPR = 800;
const int led_pin = 15;

int curPos1 = 0; // current position
int curPos2 = 0;
int diff1 = 0; // difference
int diff2 = 0;

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(9600);
    // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
    delay(1500);

    // Defined in thingProperties.h
    initProperties();

    // Connect to Arduino IoT Cloud
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);

    /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
    // Sets the two pins as Outputs
    pinMode(stepPin1, OUTPUT);
    pinMode(dirPin1, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(dirPin2, OUTPUT);
    pinMode(led_pin, OUTPUT);
    
    digitalWrite(led_pin, HIGH);


}

void loop()
{
    ArduinoCloud.update();
    // Your code here
    // take user input (inPos1, inPos2)
    //hold curPos till next input
}

/*
  Since ScreenPosition is READ_WRITE variable, onScreenPositionChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onScreenPositionChange()
{
    diff2 = screen_position - curPos2;
    curPos2 = screen_position;   
    // Add your code here to act upon ScreenPosition change
    if (diff2 > 0)
    {
        digitalWrite(dirPin2, HIGH); // Enables the motor to move forward
    }
    else
    {
        diff2 = -diff2;
        digitalWrite(dirPin2, LOW);
    }
    for (int x = 0; x < (stepsPR * diff2) / 8; x++) // Makes 800 pulses for making one full cycle rotation, half rotation for 1mm movement
    {
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(500);
        //send curPos2 to dashboard
    }
    delay(1000);
}

/*
  Since Start is READ_WRITE variable, onStartChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onStartChange()
{
    // Add your code here to act upon Start change
    if (start == true)
    {
        diff2 = 0 - curPos2;
        curPos2 = 0;
        // Add your code here to act upon ScreenPosition change
        if (diff2 > 0)
        {
            digitalWrite(dirPin2, HIGH); // Enables the motor to move forward
        }
        else
        {
            diff2 = -diff2;
            digitalWrite(dirPin2, LOW);
        }
        for (int x = 0; x < (stepsPR * diff2) / 8; x++) // Makes 800 pulses for making one full cycle rotation, half rotation for 1mm movement
        {
            digitalWrite(stepPin2, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin2, LOW);
            delayMicroseconds(500);
            //send curPos2 to dashboard
        }
        delay(1000);

        diff1 = 0 - curPos1;
        curPos1 = 0;
        // Add your code here to act upon ObjPosition change
        if (diff1 > 0)
        {
            digitalWrite(dirPin1, HIGH); // Enables the motor to move forward
        }
        else
        {
            diff1 = -diff1;
            digitalWrite(dirPin1, LOW);
        }
        for (int x = 0; x < (stepsPR * diff1) / 8; x++) // Makes stepsPR pulses for making one full cycle rotation, half rotation for 1mm movement
        {
            digitalWrite(stepPin1, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin1, LOW);
            delayMicroseconds(500);
            //curPos1 += 2/stepsPR;
            //send curPos1 to dashboard
        }
        delay(1000);

        curPos1 = 0; // current position
        curPos2 = 0;
        obj_position = 0; // input position
        screen_position = 0;
        diff1 = 0; // difference
        diff2 = 0;
        start = false;
        digitalWrite(led_pin, LOW);
        lED_on = false;
    }
}

/*
  Since ObjPosition is READ_WRITE variable, onObjPositionChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onObjPositionChange()
{
    diff1 = obj_position - curPos1;
    curPos1 = obj_position;
    // Add your code here to act upon ObjPosition change
    if (diff1 > 0)
    {
        digitalWrite(dirPin1, HIGH); // Enables the motor to move forward
    }
    else
    {
        diff1 = -diff1;
        digitalWrite(dirPin1, LOW);
    }
    for (int x = 0; x < (stepsPR * diff1) / 8; x++) // Makes stepsPR pulses for making one full cycle rotation, half rotation for 1mm movement
    {
        digitalWrite(stepPin1, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin1, LOW);
        delayMicroseconds(500);
        //curPos1 += 2/stepsPR;
        //send curPos1 to dashboard
    }
    delay(1000);
}

/*
  Since LEDOn is READ_WRITE variable, onLEDOnChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLEDOnChange()  {
  // Add your code here to act upon LEDOn change
  if(digitalRead(led_pin) == LOW){
    digitalWrite(led_pin, HIGH);
  }
  else{
    digitalWrite(led_pin, LOW);
  }
}