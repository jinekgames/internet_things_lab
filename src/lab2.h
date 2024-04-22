#ifndef LAB2_H
#define LAB2_H

#include "BluetoothSerial.h"

#include "config.h"

#include "svetofor.h"
#include "termo.h"


typedef class Parser final {

public:

    Parser()
        : svetofor{SVETOFOR_PIN_0,
                   SVETOFOR_PIN_1,
                   SVETOFOR_PIN_2} {
        SerialBT.begin("DeviceZheKa");
    }
    Parser(const Parser&) = delete;
    Parser(Parser&&) = delete;
    ~Parser() = default;

    Parser& operator = (const Parser&) = delete;
    Parser& operator = (Parser&&) = delete;

public:

    void Tick() {

        if(SerialBT.available()){

            String serialText = SerialBT.readString();

            String fromPhone = " Smartphone ";
            fromPhone.concat(serialText);
            Serial.print(fromPhone);
            SerialBT.print("cmd got\n");

            if(serialText == "get temp" LINE_ENDING) {
                SerialBT.println(termo.GetTemp());
            }
            else if(serialText == "set light" LINE_ENDING) {
                pinMode( 12, OUTPUT );
                Serial.println("Light set on");
                svetofor.setValueOut(1000, 1000, 1000);
            }
            else if(serialText == "set dark" LINE_ENDING) {
                pinMode( 12, OUTPUT );
                Serial.println("Light set off");
                svetofor.setValueOut(0, 0, 0);
            }
            else {
                SerialBT.print("bad cmd\n");
                SerialBT.print("help:\n");
                SerialBT.print("  get temp  - get current temperature\n");
                SerialBT.print("  set light - enable asus aura rgb lightning\n");
                SerialBT.print("  set dark  - energy safe\n");
            }

        }
        delay(20);
    }

private:

    BluetoothSerial SerialBT;

    Svetofor svetofor;
    Termo    termo;

} *pParser;

pParser pTerm;


void setup() {
    Serial.begin(115200);
    Serial.println("SETUP");
    pTerm = new Parser;
}

void loop(){
    pTerm->Tick();
}

#endif