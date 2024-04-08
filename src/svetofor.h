#ifndef SVETOFOR_H
#define SVETOFOR_H

#include <Arduino.h>


class Svetofor{
  public:
    
    Svetofor( int pinOne, int pinTwo, int pinThree ){
      int pin1 = pinOne; 
      int pin2 = pinTwo; 
      int pin3 = pinThree; 
      pinMode( pinOne, OUTPUT );
      pinMode( pinTwo, OUTPUT );
      pinMode( pinThree, OUTPUT );
    }

    void setValueOut( int value1, int value2, int value3 ){
      analogWrite( pin1, value1 );
      analogWrite( pin2, value2 );
      analogWrite( pin3, value3 );
    }

  private:
    int pin1; 
    int pin2; 
    int pin3;
};

#endif