#ifndef SVETOFOR_H
#define SVETOFOR_H

#include <Arduino.h>


class Svetofor{
public:
  
  Svetofor( uint8_t pinOne, uint8_t pinTwo, uint8_t pinThree )
    : pin1(pinOne)
    , pin2(pinTwo)
    , pin3(pinThree) {

    pinMode( pin1, OUTPUT );
    pinMode( pin2, OUTPUT );
    pinMode( pin3, OUTPUT );
  }

  void setValueOut( int value1, int value2, int value3 ){
    analogWrite( pin1, value1 );
    analogWrite( pin2, value2 );
    analogWrite( pin3, value3 );
  }

private:
  uint8_t pin1, pin2, pin3;
};

#endif