#ifndef LAB2_H
#define LAB2_H

#include "BluetoothSerial.h"
#include <Adafruit_AHTX0.h>

#include "svetofor.h"


#define LINE_ENDING "\r\n"

#define SVETOFOR_PIN_0 13
#define SVETOFOR_PIN_1 12
#define SVETOFOR_PIN_2 14


typedef class Termometr final { //Change name class to App

public:

    Termometr() {
        SerialBT.begin("DeviceZheKa");
    }
    Termometr(const Termometr&) = delete;
    Termometr(Termometr&&) = delete;
    ~Termometr() = default;

    Termometr& operator = (const Termometr&) = delete;
    Termometr& operator = (Termometr&&) = delete;

public:

    void Tick() {

        if(SerialBT.available()){

            String serialText = SerialBT.readString();

            String fromPhone = " Smartphone ";
            fromPhone.concat(serialText);
            Serial.print(fromPhone);
            SerialBT.print("cmd got\n");

            if(serialText == "get temp" LINE_ENDING) {
                handlers.Temp(SerialBT);
            }
            else if(serialText == "set light" LINE_ENDING) {
                SerialBT.print("set light cmd\n");
                handlers.Light(SerialBT, true);
            }
            else if(serialText == "set dark" LINE_ENDING) {
                SerialBT.print("set dark cmd\n");
                handlers.Light(SerialBT, false);
            }
            else {
                SerialBT.print("bad cmd\n");
            }

        }
        delay(20);
    }

private:

    class Handlers final {
    public:
        Handlers()
        : svetofor{SVETOFOR_PIN_0,
                   SVETOFOR_PIN_1,
                   SVETOFOR_PIN_2} {

            if(!aht.begin()){
                while(true)delay(10);
            }
        }

        void Temp(Stream& SerialBT) {
            aht.getEvent(&humidity, &temp);
            SerialBT.println(temp.temperature);
        }
        void Light(Stream& Serial, bool mode) {
            pinMode( 12, OUTPUT );
            Serial.print("Light set ");
            Serial.println(int(mode));
            if(mode) {
                analogWrite( 12, 4000);
                svetofor.setValueOut(1000, 1000, 1000);
            } else {
                analogWrite( 12, 0);
                svetofor.setValueOut(0, 0, 0);
            }
        }
    private:
        Adafruit_AHTX0  aht;
        sensors_event_t humidity, temp;
        Svetofor        svetofor;
    } handlers;

private:

    BluetoothSerial SerialBT;

} *pTermometr;

pTermometr pTerm;


void setup() {
    Serial.begin(115200);
    Serial.println("SETUP");
    pTerm = new Termometr;
}

void loop(){
    pTerm->Tick();
}

#endif