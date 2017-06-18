
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
  attachInterrupt(LEFT, LwheelSpeed, CHANGE);    //init the interrupt mode for the digital pin 2
  attachInterrupt(RIGHT, RwheelSpeed, CHANGE);   //init the interrupt mode for the digital pin 3
  
}

void loop(){
  
  static unsigned long timer = 0;                //print manager timer
  
  if(millis() - timer > 500){                   
    //Serial.print("Coder value: ");

    T = float(millis()-timer) ;
    
        radps[LEFT] = 2*pi*1000*float(coder[LEFT])/(EnRes * T); 
        radps[RIGHT] = 2*pi*1000*float(coder[RIGHT])/(EnRes * T);


    
    Serial.print(coder[LEFT]);
    Serial.print("\t");
    Serial.print(radps[LEFT]);
    Serial.print("\t");
    //Serial.print("[Left Wheel] ");
    Serial.print(coder[RIGHT]);
    Serial.print("\t");
    Serial.println(radps[RIGHT]);
    //Serial.println("[Right Wheel]");
    
//    lastSpeed[LEFT] = coder[LEFT];   //record the latest speed value
//    lastSpeed[RIGHT] = coder[RIGHT];
    coder[LEFT] = 0;                 //clear the data buffer
    coder[RIGHT] = 0;
    timer = millis();
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
