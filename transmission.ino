#include "SoftwareSerial.h"

// Initialize XBee radio on digital ports 2 and 3 - 1U2SDD2: ANTENNA CONTROL
SoftwareSerial XBee = SoftwareSerial(2,3);

// Initialize analog pins for sensors
int sensorPin1 = A0;
int sensorPin2 = A1;
// Initialize variables to hold data read from sensors
int sensorOneValue = 0;
int sensorTwoValue = 0;
int difference = 0;
// Initialize messages to be sent by XBee to 2U1SDD1: INPUT
byte doStep = 0x01;
byte stepBack = 0x02;
byte message = 0x00;
byte dontStep = 0x00;
// Initialize variable to hold current rotation of motors
int currentPos = 520;

void setup()
{
    //Begin serial and XBee processes at the same baud rate
    Serial.begin(9600);
    XBee.begin(9600);
}

void loop()
{
  //1U2SDD1: ANALOG-DIGITAL-CONVERSION
  sensorOneValue = analogRead(sensorPin1);
  sensorTwoValue = analogRead(sensorPin2);
  
  delay(1000);

  Serial.print("Sensor One Data =");
  Serial.println(sensorOneValue);

  Serial.print("Sensor Two Data =");
  Serial.println(sensorTwoValue);

  //1U2SDD3: SIGNAL COMPARISON
  difference = sensorOneValue - sensorTwoValue;
  Serial.print("Difference = ");
  Serial.println(difference);

  //1U2SDD4: SIGNAL PROCESSING / 2U1SDD4: POSITIONING CALCULATION
  if(currentPos < difference){
    message = doStep;
    currentPos -= 4;
  }
  else if(currentPos > difference){
    message = stepBack;
    currentPos += 4;
  }
  else{
    message = dontStep;
  }

  //1U2SDD5: OUTPUT
  XBee.write(message);
  
  delay(300);
}
