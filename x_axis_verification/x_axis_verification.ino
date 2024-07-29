////WARNING!!!
//check if x-calibration starts to drive in the down direction first!


// libraries and declarations
#include <AccelStepper.h>

////signum function
//int sgn(int val) {
//  if (val > 0) return 1;
//  if (val < 0) return -1;
//  return 0;
//}

  // Define the endstop pins
  #define SX1 2
  #define SX2 3
  #define SX3 4
  #define SX4 5
  #define SY5 6
  #define SY6 7

  #define STEP_PINMX1 8
  #define DIR_PINMX1 9
  #define STEP_PINMX2 10
  #define DIR_PINMX2 11
  #define STEP_PINMY 12
  #define DIR_PINMY 13 
   //constructor of the stepper motors
  AccelStepper stepperMX1(AccelStepper::DRIVER, STEP_PINMX1, DIR_PINMX1);
  AccelStepper stepperMX2(AccelStepper::DRIVER, STEP_PINMX2, DIR_PINMX2);
  AccelStepper stepperMY3(AccelStepper::DRIVER, STEP_PINMY, DIR_PINMY);
  AccelStepper stepperMY4(AccelStepper::DRIVER, STEP_PINMY, DIR_PINMY);
  
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("serial communication working");
  // Set maximum speed and acceleration for each stepper
  stepperMX1.setMaxSpeed(1000);
  stepperMX1.setAcceleration(500);
  stepperMX2.setMaxSpeed(1000);
  stepperMX2.setAcceleration(500);
  stepperMY3.setMaxSpeed(1000);
  stepperMY3.setAcceleration(500);
  stepperMY4.setMaxSpeed(1000);
  stepperMY4.setAcceleration(500);

  //// Set the initial position for each stepper
  //stepperMX1.setCurrentPosition(0);
  //stepperMX2.setCurrentPosition(0);
  //stepperMY3.setCurrentPosition(0);
  //stepperMY4.setCurrentPosition(0);

//  // Set the speed for each stepper
//  stepperMX1.setSpeed(800);
//  stepperMX2.setSpeed(800);
//  stepperMY3.setSpeed(800);
//  stepperMY4.setSpeed(800);
  
  Serial.println("speed and acceleration is set");
  
  // Initialize the endstop pins
  pinMode(SX1, INPUT_PULLUP);
  pinMode(SX2, INPUT_PULLUP);
  pinMode(SX3, INPUT_PULLUP);
  pinMode(SX4, INPUT_PULLUP);
  pinMode(SY5, INPUT_PULLUP);
  pinMode(SY6, INPUT_PULLUP); 
  Serial.println("succesfully initalized endstop switches"); 
  
  //set all endstop switches as boolean values
//  bool SX1State = digitalRead(SX1);
//  bool SX2State = digitalRead(SX2);
//  bool SX3State = digitalRead(SX3);
//  bool sX4State = digitalRead(SX4);
//  bool sY5State = digitalRead(SY5);
//  bool sY6State = digitalRead(SY6);
    
  // x-axis calibration I
  // Finds both endstops of the x-axis, to find the starting point of x-axis calibration II
  Serial.println("starting x-calibration I");
  while (true) {
    if (digitalRead(SX1) == HIGH && digitalRead(SX2) == HIGH) {
      stepperMX1.setSpeed(800);
      stepperMX2.setSpeed(-800);
    } else if (digitalRead(SX1) == LOW && digitalRead(SX2) == HIGH) {
      stepperMX2.setSpeed(-200 );
      stepperMX1.setSpeed(0); // Stop MX1
    } else if (digitalRead(SX1) == HIGH && digitalRead(SX2) == LOW) {
      stepperMX1.setSpeed(200 );
      stepperMX2.setSpeed(0); // Stop MX2
    } else if (digitalRead(SX1) == LOW && digitalRead(SX2) == LOW){
      stepperMX1.setSpeed(0);
      stepperMX2.setSpeed(0);
      break; // Exit the loop if none of the conditions are met
    }
    stepperMX1.runSpeed();
    stepperMX2.runSpeed();
  }
  Serial.println("x-calibration I completed");


  // X-axis calibration II
  // counts the steps to get the x-length of both profiles
  
  Serial.println("starting x-calibration II");
  stepperMX1.setCurrentPosition(0);
  stepperMX2.setCurrentPosition(0);
  
  
  while (true) {
    if (digitalRead(SX3) == HIGH && digitalRead(SX4) == HIGH && digitalRead(SX1) == LOW && digitalRead(SX2) == LOW) {
      stepperMX1.setSpeed(-800);
      stepperMX2.setSpeed(800);
    } else if (digitalRead(SX3) == LOW && digitalRead(SX4) == HIGH && digitalRead(SX1) == HIGH && digitalRead(SX2) == HIGH) {
      stepperMX2.setSpeed(200 );
      stepperMX1.setSpeed(0); // Stop MX1
    } else if (digitalRead(SX3) == HIGH && digitalRead(SX4) == LOW && digitalRead(SX1) == HIGH && digitalRead(SX2) == HIGH) {
      stepperMX1.setSpeed(-200 );
      stepperMX2.setSpeed(0); // Stop MX2
    } else if (digitalRead(SX3) == LOW && digitalRead(SX4) == LOW && digitalRead(SX1) == HIGH && digitalRead(SX2) == HIGH){
      stepperMX1.setSpeed(0);
      stepperMX2.setSpeed(0);
      break; // Exit the loop if none of the conditions are met
    }
    stepperMX1.runSpeed();
    stepperMX2.runSpeed();
  }
  // Print the current positions
  Serial.print("Stepper MX1 Position: ");
  Serial.println(stepperMX1.currentPosition());
  Serial.print("Stepper MX2 Position: ");
  Serial.println(stepperMX2.currentPosition());
  Serial.println("x-calibration II complete");    
  // x-axis verification I
  long MX1current = stepperMX1.currentPosition();
  long MX2current = stepperMX2.currentPosition();

  stepperMX1.setCurrentPosition(0);
  stepperMX2.setCurrentPosition(0);

  
  Serial.print("starting x-axis verification");
  //
  while (true) {
    if (digitalRead(SX1) == HIGH && digitalRead(SX2) == HIGH) {
      stepperMX1.setSpeed(800);
      stepperMX2.setSpeed(-800);
    } else if (digitalRead(SX1) == LOW && digitalRead(SX2) == HIGH) {
      stepperMX2.setSpeed(-200 );
      stepperMX1.setSpeed(0); // Stop MX1
    } else if (digitalRead(SX1) == HIGH && digitalRead(SX2) == LOW) {
      stepperMX1.setSpeed(200 );
      stepperMX2.setSpeed(0); // Stop MX2
    } else if (digitalRead(SX1) == LOW && digitalRead(SX2) == LOW){
      stepperMX1.setSpeed(0);
      stepperMX2.setSpeed(0);
      break; // Exit the loop if none of the conditions are met
    }
    stepperMX1.runSpeed();
    stepperMX2.runSpeed();
  }
  long MX1verified = stepperMX1.currentPosition();
  long MX2verified = stepperMX2.currentPosition();
  
  long MX1goal = abs(MX1verified) - abs(MX1current);
  long MX2goal = abs(MX2verified) - abs(MX2current);
  
  if (MX1goal < 1000 && MX2goal < 1000) {
    Serial.println("x-verification successfull");
    Serial.println("Abweichung MX1 =" + String(MX1goal));
    Serial.println("Abweichung MX2 =" + String(MX2goal));
  } else {
    Serial.println("x-verification failed");
    Serial.println("Abweichung MX1 =" + String(MX1goal));
    Serial.println("Abweichung MX2 =" + String(MX2goal));
  }
//  
//  long MX1current = stepperMX1.currentPosition();
//  long MX2current = stepperMX2.currentPosition();
//  
//  long MX1goal = (abs(MX1current) - 5000) * sgn(MX1current);
//  long MX2goal = (abs(MX2current) - 5000) * sgn(MX2current);
//
//  Serial.println("---");
//  Serial.println(MX1goal);
//  Serial.println(MX2goal);
//  
//  long MX1goalSlow = sgn(MX1current)*10000;
//  long MX2goalSlow = sgn(MX2current)*10000;
//
//  Serial.println(MX1goalSlow);
//  Serial.println(MX2goalSlow);
//
//  long MX1
//
//  while (stepsMoved < stepsToMove) {
//    stepper.runSpeed();
//    stepsMoved++;
 }
  // checks if the deviation between measured rail length and real rail lentgh is to big

void loop() {
  // put your main code here, to run repeatedly:

}
