#include<SoftwareSerial.h>
#include<Servo.h>

#define Servo1 9
Servo MG995_1;

int received;
int difference;
int motorPos = 2000;

//For communicating with zigbee - 2U1SDD2: ANTENNA CONNECTION
SoftwareSerial zigbee(6,7);

void setup()
{
    Serial.begin(9600);
    zigbee.begin(9600);
    MG995_1.attach(Servo1);
 
    MG995_1.writeMicroseconds(2000);

}

void loop()
{

    //check if data has been received 
    if (zigbee.available() > 0)
    {
        //2U1SDD1: INPUT
        received = zigbee.read();

        //2U1SDD8: STEPPER MOTOR INSTRUCTIONS
        if(received == 1){
          motorPos -= 3;
        }

        else if(received == 2){
          motorPos += 3;
        }

        //2U1SDD6: PULSE WIDTH MODULATION - 2U1SDD7: DIGITAL-ANALOG-CONVERSION
        MG995_1.writeMicroseconds(motorPos);
        delay(200);
    }
}
