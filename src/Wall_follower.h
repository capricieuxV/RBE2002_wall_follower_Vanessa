#ifndef WALL_FOLLWER
#define WALL_FOLLWER

#include <Romi32U4.h>
#include <Arduino.h>
#include <Speed_controller.h>
#include <IR_sensor.h>

#define echoPin 1
#define trigPin 0

class Wall_follower{
    private:
    public:
        IR_sensor ir_sensor;
        SpeedController speed_controller;
        float duration; // duration of the sound wave(back and forth)
        float distance; // in cm
        int i;
        float Kp = 2;
        float Kd = 0.03;
        float lastErr = 0.0;
        float err = 0.0;
        float last = 0;
        void init();
        void setConstant(float kp, float kd);
        float getDistanceSonar();
        void wall_following(float dis, float baseEffort, bool left);
};

#endif