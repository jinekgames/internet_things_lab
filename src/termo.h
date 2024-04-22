#pragma once

#include <Adafruit_AHTX0.h>

class Termo final {
public:

    Termo() {
        if(!aht.begin()){
            while(true)delay(10);
        }
    }

    float GetTemp() {
        Update();
        return temp.temperature;
    }

private:

    void Update() {
        aht.getEvent(&humidity, &temp);
    }


private:

    Adafruit_AHTX0  aht;
    sensors_event_t humidity, temp;

};
