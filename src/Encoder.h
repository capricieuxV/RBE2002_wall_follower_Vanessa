#include <Arduino.h>
#include <Romi32U4.h>
#include <Romi32U4Encoders.h>
#include <Romi32U4Motors.h>

class Encoder{
    private:
        Romi32U4Motors motor;
        Romi32U4Encoders encoder;

        int countLeft = 0;
        int countRight = 0;
        float leftV = 0.0;
        float rightV = 0.0;

        long previousMillis = 0;
        long currentMillis = 0;

        float Kp = 4.7;
        float Ki = 0.25;
        float sumErrL = 0;
        float sumErrR = 0;
        
    public:
        void Init(void);
        void updateCounts();
        float readVelocityLeft();
        float readVelocityRight();
        int getSign(float value);
        void setVelocity(float left, float right);
        int readEncoderCountLeft(void);
        int readEncoderCountRight(void);
};