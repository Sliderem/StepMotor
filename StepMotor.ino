#include "IRremote.h"
#include "AccelStepper.h"

//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper(1, 3, 2);  //TYPE = 1 only two pins , PUL 3, DIR 2
int enablePin = 4;//Pin used to enable/disable the power in the coils of the motor 

/*-----( Declare objects )-----*/
/*----- Variables, IR Pins -----*/
int receiver = 6;         // Signal Pin of IR receiver to Arduino Digital Pin 6
IRrecv irrecv(receiver);  // create instance of 'irrecv'
decode_results results;   // create instance of 'decode_results'
boolean moveUp = 0;
boolean moveDown = 0;

void setup() {
  Serial.begin(9600);   // set up Serial library at 9600 bps
  Serial.println("Stepper setup - Begin! 27/09 10:46");
  
  Serial.println("Stepper setup - enableIRIn!");
  irrecv.enableIRIn();  // Start the receiver
  Serial.println("Stepper setup - Set-up the stepper motor initial config");
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(600);
  stepper.setAcceleration(10);
  
  Serial.println("Stepper setup - stepper go to initial position!");
  //Move the steper motor to start position Open in our case
  stepper.runToNewPosition(0);//???no need
  //disable the stepper motor
  Serial.println("Stepper setup - disableOutputs");
  stepper.setPinsInverted(false,false,false,false,true);//last pin for enable/disable needs to be inverted
  stepper.setEnablePin(enablePin);//set the enable pin, 4 in our case
  stepper.disableOutputs();//disable the coils of the motor when is started for the first time
  Serial.println("Stepper setup - End!");
}

void loop() {

  if (moveUp == 1) {
    Serial.println("Stepper Run! Move Up");
    stepper.enableOutputs();
    stepper.runToNewPosition(-1000);
    stepper.disableOutputs();
    moveUp = 0;
  }

  if (moveDown == 1) {
 
    Serial.println("Stepper Run! Move Down");
    stepper.enableOutputs();
    stepper.runToNewPosition(1000);
    stepper.disableOutputs();
    moveDown = 0;
  }
  //The function decode(&results)) is deprecated and may not work as expected! Just use decode() without a parameter and IrReceiver.decodedIRData.<fieldname> .
  //if (irrecv.decode(&results))  // have we received an IR signal?
  //If IR recieves a signal .decode() returns true
  if (irrecv.decode())

  {


    Serial.println("IR value Pressed :");
    Serial.println(irrecv.decodedIRData.decodedRawData);
    switch (irrecv.decodedIRData.decodedRawData)
    {

      case 3108437760:  // UP button pressed
        moveUp = 1;
        moveDown = 0;
        Serial.println("moveUp=" + moveUp);
        Serial.println(moveUp);
        Serial.println("moveDown=" + moveDown);
        Serial.println(moveDown);
        break;

      case 3927310080:  // DOWN button pressed
        moveUp = 0;
        moveDown = 1;
        Serial.println("moveUp=" + moveUp);
        Serial.println(moveUp);
        Serial.println("moveDown=" + moveDown);
        Serial.println(moveDown);
        break;
    }

    irrecv.resume();  // receive the next value
  }
}