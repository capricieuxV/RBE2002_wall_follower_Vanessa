#ifndef IR_SENSOR
#define IR_SENSOR

#include <Arduino.h>
#include <Romi32U4.h>

#define irPin 18

class IR_sensor
{
private:
public:
    int adc_value;
    void init();
    float calculateDistance(int adc_value);
    void PrintData();
    float ReadData();
};

#endif
