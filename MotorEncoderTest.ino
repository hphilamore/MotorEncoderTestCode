
// # Editor     : Lauren from DFRobot
// # Date       : 17.01.2012

// # Product name: Wheel Encoders for DFRobot 3PA and 4WD Rovers
// # Product SKU : SEN0038

// # Description:
// # The sketch for using the encoder on the DFRobot Mobile platform

// # Connection for Uno or other 328-based:
// #        left wheel encoder  -> Digital pin 2
// #        right wheel encoder -> Digital pin 3
// # Note: If your controller is not 328-based, please check https://www.arduino.cc/en/Reference/AttachInterrupt for proper digital pins.


#define LEFT 0
#define RIGHT 1

const float pi = 3.142;
float EnRes = 10;

float T; 
long DrivePeriod;
unsigned long DriveStartTime; 

// the time (in mS) increment to record the encoder output for before outputting to serial 
int TachoIncrement = 500;

// motor one
int enA = 5;
int in1 = 7;
int in2 = 6;
// motor two
int enB = 9;
int in3 = 11;
int in4 = 10;


//long coder[2] = {
//  0,0};
//int lastSpeed[2] = {
//  0,0}; 

float coder[2] = {
  0,0};
float radps[2] = {
  0,0}; 


void setup(){
  
  Serial.begin(9600);                            //init the Serial port to print the data
//  attachInterrupt(LEFT, LwheelSpeed, CHANGE);    //init the interrupt mode for the digital pin 2
//  attachInterrupt(RIGHT, RwheelSpeed, CHANGE);   //init the interrupt mode for the digital pin 3
  attachInterrupt(LEFT, LwheelSpeed, FALLING);    //init the interrupt mode for the digital pin 2
  attachInterrupt(RIGHT, RwheelSpeed, FALLING);   //init the interrupt mode for the digital pin 3

    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
  
}

static unsigned long timer = 0;                //print manager timer

void loop(){
  
//  Drive(200, 200, 2000);   
//  if(millis() - timer > TachoIncrement){                  
//  T = float(millis()-timer) ;
//  radps[LEFT] = 2*pi*1000*float(coder[LEFT])/(EnRes * T); 
//  radps[RIGHT] = 2*pi*1000*float(coder[RIGHT])/(EnRes * T);
//    Serial.print(coder[LEFT]);
//    Serial.print("\t");
//    Serial.print(radps[LEFT]);
//    Serial.print("\t");
//    Serial.print(coder[RIGHT]);
//    Serial.print("\t");
//    Serial.println(radps[RIGHT]);
//    coder[LEFT] = 0;                 //clear the data buffer
//    coder[RIGHT] = 0;
//    timer = millis();
//  }




  for (int i = 0; i < 255; i = i + 10)  
  {
    Drive(i, i, 2000); 

  }
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; i = i - 10)
  {
    Drive(i, i, 2000); 
  
  } 
  
}


void Drive(int leftMotorSpeed, int rightMotorSpeed, long DrivePeriod) 
  {  
     // set motor direction
    if(leftMotorSpeed < 0) 
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      leftMotorSpeed = abs(leftMotorSpeed);
    }
    
    else
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
  
    // set motor direction
    if(rightMotorSpeed < 0) 
    {
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      rightMotorSpeed = abs(rightMotorSpeed);
    }
    
    else
    {
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
  
    DriveStartTime = millis() ;   
            
    while ((millis() - DriveStartTime) < DrivePeriod)         
    {        
      analogWrite(enA, leftMotorSpeed);
      analogWrite(enB, rightMotorSpeed); 
      //tachometer(leftMotorSpeed, rightMotorSpeed);  
      tachometer();
     }

    }


void LwheelSpeed()
{
  coder[LEFT] ++;  //count the left wheel encoder interrupts
}


void RwheelSpeed()
{
  coder[RIGHT] ++; //count the right wheel encoder interrupts
}

void tachometer()
{
  
  if(millis() - timer > TachoIncrement){                  
    T = float(millis()-timer) ;
    radps[LEFT] = 2*pi*1000*float(coder[LEFT])/(EnRes * T); 
    radps[RIGHT] = 2*pi*1000*float(coder[RIGHT])/(EnRes * T);
    Serial.print(coder[LEFT]);
    Serial.print("\t");
    Serial.print(radps[LEFT]);
    Serial.print("\t");
    Serial.print(coder[RIGHT]);
    Serial.print("\t");
    Serial.println(radps[RIGHT]);
    coder[LEFT] = 0;                 //clear the data buffer
    coder[RIGHT] = 0;
    timer = millis();
  
  }
  
  
  }


