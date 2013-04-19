/*
 * WiiChuckDemo -- 
 *
 * 2008 Tod E. Kurt, http://thingm.com/
 *
 */

#include <Wire.h>
#include "nunchuck_funcs.h"
#include <Servo.h>


Servo servoTesth;
Servo servoTestv;

//Servo servoTesth;
//Servo servoTestv;

byte accx,accy,accz,zbut,cbut,xjoy,yjoy;
int ledPin = 13;

int xpos;
int ypos;
int servoTestx;
int servoTesty;


int still = false;
int stillcount = 0;


void setup()
{
    Serial.begin(19200);
    nunchuck_setpowerpins();
    nunchuck_init(); // send the initilization handshake
    
    Serial.print("WiiChuckDemo ready\n");
    
    servoTesth.attach(10);  
    servoTesth.write(90);
   
    servoTestv.attach(8);
    servoTestv.write(90);
    
    xpos = 125;
    
    pinMode(ledPin, OUTPUT);
    
   
}

void loop()
{

        nunchuck_get_data(); //Read data from numchuck

        zbut = nunchuck_zbutton(); // (0 or 1)
        xjoy = nunchuck_joyx();    // X axis of Joystick (Between aprox 35-220)
        yjoy = nunchuck_joyy();    // Y axis of Joystick (Between aprox 35-220)       
        Serial.print("\tJoy X:"); Serial.print(xjoy);  
        Serial.print("\tZ:"); Serial.print(zbut);
        Serial.print("\tStill:"); Serial.println(still);

       
        xpos = (xjoy - 125) * (-1);
        ypos = (yjoy - 130) * (-1);
                
        
                
        servoTestx = 90 + xpos;
        servoTesty = 90 + ypos;
             
        if(servoTesty < 45 )
        {
          servoTesty = 45;
        }
        
        if(servoTesty > 135 )
        {
          servoTesty = 135;
        }
        
        if(servoTestx < 25 )
        {
          servoTestx = 25;
        }
        
        if(servoTestx > 165 )
        {
          servoTestx = 165;
        }
        
        if(!still)
        {
          servoTesth.write(servoTestx);
          servoTestv.write(servoTesty);
        }
       
       
        if(zbut == 1)
        {
        //  digitalWrite(ledPin, HIGH);
          still = true;
        }else{
        //  digitalWrite(ledPin, LOW);
          still = false;
         }  
     
         
}


