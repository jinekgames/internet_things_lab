#include <Arduino.h>
#include <Adafruit_AHTX0.h>

#define NEWCODE
#if defined(NEWCODE)
#include "lab2.h"
#else


class inGadj{
  public:
    
    inGadj( int pinNum ){
      pinIn = pinNum;
      pinMode( pinNum, INPUT );
    }

    int getValueIn(){
      return analogRead( pinIn );
    }

  private:
    int pinIn;
}; 

class outGadj{
  public:
    
    outGadj( int pinOne, int pinTwo, int pinThree ){
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


inGadj touch = inGadj( 13 );
outGadj traficLight = outGadj( 15, 2 ,4 );

int valueIn = 0;
int valueOut = 0;

void setup() {

  Serial.begin(115200);

}

void loop() {
  delay( 100 );
  valueIn = touch.getValueIn();
  Serial.println( valueIn );
  if( valueIn != 0 ){
    traficLight.setValueOut( 5000, 5000, 5000 );
  }else{
    traficLight.setValueOut( 0, 0, 0 );
  }
}
#endif