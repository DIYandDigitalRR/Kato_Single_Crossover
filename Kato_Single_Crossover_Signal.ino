#include "DCrossoverSignal.h"
#include "Arduino.h"

int switch1pin1=A4;//set up digital pin 2 for controlling switch 1
int switch1pin2=A5;//set up digital pin 3 for controlling switch 1
int button=A0;//set up analog pin A0 for reading button 1
int button2=A1;
int Switch=0;//Sets our value for the state of switch 1
int Direction=0;
int XoverSignal=A3;
DoubleCrossover R1(2);
DoubleCrossover Y1(3);
DoubleCrossover G1(4);
DoubleCrossover R2(5);
DoubleCrossover Y2(6);
DoubleCrossover G2(7);
DoubleCrossover R3(8);
DoubleCrossover Y3(9);
DoubleCrossover G3(10);
DoubleCrossover R4(11);
DoubleCrossover Y4(12);
DoubleCrossover G4(13);

void setup() {
  Serial.begin(9600);//sets up our readings in the serial monitor and the baud rate of 9600
  pinMode(switch1pin1,OUTPUT);
  pinMode(switch1pin2,OUTPUT);
  
  pinMode(button,INPUT);
  pinMode(button2,INPUT);
}
enum SWITCHSTATES
{
  ST_OFF,
  ST_STRAIGHT,
  ST_TURN,
  ST_RESET,
  ST_CHANGE1,
  ST_CHANGE2,
};//Sets up states that arduino can hop between

SWITCHSTATES switchState=ST_OFF;

void loop(){
  //Serial.println("Switch");
  //Serial.println(Switch);//display in serial monitor what the State of State 1 is with the text "State 1" in front.
 
int ButtonRead=analogRead(button);//Stores value for button1
int Button2Read=analogRead(button2);
int XoverSignalRead=analogRead(XoverSignal);


  Serial.println("Button");
  Serial.println(ButtonRead);//display in serial monitor what the State of Button 1 is with the text "Button 1" in front.
  Serial.println("Button 2");
  Serial.println(Button2Read);
  Serial.println("Switch State");
  Serial.println(Switch);
  Serial.println("Direction State");
  Serial.println(Direction);
  Serial.println("Xover Signal");
  Serial.println(XoverSignalRead);
  delay(200);// 0.2 second pause between readings
  switch(switchState){
    case ST_OFF:
    switchoff(ButtonRead, Button2Read, Switch, Direction, XoverSignalRead);
    break;
    case ST_STRAIGHT:
    switchstraight(ButtonRead);
    break;
    case ST_TURN:
    switchturn(ButtonRead);
    break;
    case ST_RESET:
    switchreset(ButtonRead);
    break;
    case ST_CHANGE1:
    switchchange1();
    break;
    case ST_CHANGE2:
    switchchange2();
    break;
    
  }
}

void switchoff(int ButtonRead, int Button2Read, int Switch, int Direction, int XoverSignalRead){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,LOW);

if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction==0)){
  G1.SignalON();
  G2.SignalON();
  R3.SignalON();
  R4.SignalON();//State GGRR 1
}

if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction==1)){
  R1.SignalON();
  R2.SignalON();
  G3.SignalON();
  G4.SignalON();//State RRGG 2
}
if ((ButtonRead<500) && (Button2Read<500) && (Direction ==5)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  R4.SignalON();//State RRRR 3
}
if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction==2)){
  G1.SignalON();
  R2.SignalON();
  R3.SignalON();
  G4.SignalON();//State GRGR 4
}
if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction==3)){
  R1.SignalON();
  G2.SignalON();
  G3.SignalON();
  R4.SignalON();//State GRGR 5
}
//if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction==0) && (XoverSignalRead>500)){
//  Y1.SignalON();
//  Y2.SignalON();
//  R3.SignalON();
//  R4.SignalON();//State YYRR 6
//}

//if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction==1)&& (XoverSignalRead>500)){
//  R1.SignalON();
// R2.SignalON();
//  Y3.SignalON();
//  Y4.SignalON();//State RRYY 7
//}

//if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction ==2) && (XoverSignalRead>500)){
//  R1.SignalON();
//  Y2.SignalON();
//  R3.SignalON();
//  Y4.SignalON();//State RYRY 8
//}
//if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction==3) && (XoverSignalRead>500)){
//  Y1.SignalON();
//  R2.SignalON();
//  Y3.SignalON();
//  R4.SignalON();//State YRYR 9
//}
 if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction ==4)){
 R1.SignalON();
 R2.SignalON();
 G3.SignalON();
 R4.SignalON();//State RRGR 10
}
//if ((ButtonRead<500) && (Button2Read<500) && (Switch==0) && (Direction ==0) && (XoverSignalRead>500)){
//  R1.SignalON();
//  R2.SignalON();
//  Y3.SignalON();
//  R4.SignalON();// State RRYR 11
//}
if ((ButtonRead<500) && (Button2Read<500) && (Switch==1) && (Direction ==1)){
  R1.SignalON();
  R2.SignalON();
  R3.SignalON();
  G4.SignalON();// State RRRG 12
}
if ((ButtonRead<500) && (Button2Read<500) && (Switch==1) && (Direction==2)){
 G1.SignalON();
 R2.SignalON();
 R3.SignalON();// State RRRY13
 R4.SignalON();
}
if ((Button2Read>500) && (Direction<=5)){
     switchState=ST_CHANGE1;
 }
   
    if ((Button2Read>500) && (Direction>4)){
     switchState=ST_CHANGE2;    
 }
  if ((ButtonRead>500) && (Switch==1)){
    switchState=ST_STRAIGHT;//sends to straight 1 with button press
  }
  if ((ButtonRead>500) && (Switch==0)){
    switchState=ST_TURN;//sends to turn 1 with button press
  }
}
void switchstraight(int ButtonRead){
  digitalWrite(switch1pin1,HIGH);//powers on turnout
  digitalWrite(switch1pin2,LOW);
  delay(500);//keep power to the turnout for 0.5 seconds
  Switch=0;//sets value to 0
  switchState=ST_RESET;
}
void switchturn(int ButtonRead){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,HIGH);//powers on turnout
  delay(500);//keep power to the turnout for 0.5 seconds
Switch=1;//sets value to 1
Direction=0;
  switchState=ST_RESET;
}

void switchchange1(){;
Direction=(Direction+1);
delay(500);
switchState=ST_RESET;
}

void switchchange2(){;
Direction=0;
delay(500);
switchState=ST_RESET;
}

void switchreset(int ButtonRead){
  R1.SignalOFF();
  Y1.SignalOFF();
  G1.SignalOFF();
  R2.SignalOFF();
  Y2.SignalOFF();
  G2.SignalOFF();
  R3.SignalOFF();
  Y3.SignalOFF();
  G3.SignalOFF();
  R4.SignalOFF();
  Y4.SignalOFF();
  G4.SignalOFF();
  delay(10);
  switchState=ST_OFF;
}
