#include "IR_sensor.h"

void IR_sensor::init(){
   pinMode(irPin, INPUT);
}

float IR_sensor::ReadData(){ // distance in cm
    adc_value = analogRead(irPin);
    return 1000 / ((adc_value*0.21) - 7.28);
    // return 1000/(0.23*adc_value-7.5); //group 1
    // return 1/(0.0002267162*(adc_value - 31.164)); //group 3
}

void IR_sensor::PrintData(){
    Serial.println(ReadData());
}