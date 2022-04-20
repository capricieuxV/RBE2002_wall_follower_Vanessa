#ifndef POSITION_ESTIMATION
#define POSITION_ESTIMATION

#include <Romi32U4.h>
#include <math.h> 
#include <Encoder.h>
#include <Encoders.h>

#define R_robot 140 //mm
#define R_center 70 //mm
#define r 35 //mm

class Position{
    private:
        unsigned long time_prev, time_now;
        const float l = 0;
        int countLeft = 0;
        int countRight = 0;
        int getSign(float value);

    public:
        Encoders encoder;

        float x; // x' = x - R(sin(theta)-sin(theta + omega*t)) // mm
        float y; // y' = y + R(cos(theta)-cos(theta + omega*t)) // mm
        float theta; // theta = omega*t // +: ccw; -: cw //1.7+ start ⬆ instead of ->

        float vR, vL, R, omega = 0;
        float degree = 0;

        // track length = 140mm
        struct pose_data {
            float X;
            float Y;
            float THETA;
        };
        void Init(void);
        void UpdatePose(float,float);
        pose_data ReadPose(void);
        void PrintPose(void);
        void Stop(void);
};

#endif