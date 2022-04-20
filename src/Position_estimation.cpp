#include  "Position_estimation.h"

void Position::Init(void)
{
    encoder.Init();
    x = 0;
    y = 0;
    theta = 0;;
    countLeft = 0;
    countRight = 0;
}

void Position::Stop(void)
{
    // TODO: stop
}

Position::pose_data Position::ReadPose(void)
{
    return {x,y,theta};
}

void Position::PrintPose(void)
{
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(theta);
}

// helper function for checking if ther value is negative or positive
int Position::getSign(float value){ return value<0?-1:value>0; }

void Position::UpdatePose(float target_speed_left, float target_speed_right)
{
    unsigned long interval = 50;
    time_now = millis();
    unsigned long time_diff = time_now - time_prev;

    if((time_now - time_prev) >= interval){
        // update counts every 50 ms
        // reset after it so that we will only hold counts during the interval
        countLeft = encoder.ReadEncoderCountLeft();
        countRight = encoder.ReadEncoderCountRight();

        if(encoder.ReadVelocityLeft() == encoder.ReadVelocityRight()){ // to prevent NaN case
            Serial.println("Edge case");
        }
        else if(target_speed_left == target_speed_right){ // straight fwd ⬆
            vR = encoder.ReadVelocityRight();
            vL = encoder.ReadVelocityLeft();
            R = (vR + vL) / (vR - vL) * R_center;
            omega = (vR - vL) / R_center;

            // in this case, y should not change
            x += cos(theta)*vL*time_diff / 1000 / 10; // cm
            y += sin(theta)*vL*time_diff / 1000 / 10; // cm

            //  in this case, theat should not change
            theta += omega * time_diff / 1000; // radian
        }
        else if(target_speed_left == -target_speed_right){ // rotation with two wheels rotate
            vL = encoder.ReadVelocityLeft();
            vR = encoder.ReadVelocityRight();
            omega = vR / R_center;

            // in this case, x, y should not change
            x -= sin(theta)*(abs(vR)-abs(vL))*time_diff / 1000 / 10; // cm
            y += cos(theta)*(abs(vR)-abs(vL))*time_diff / 1000 / 10; // cm

            // in this case, theta should change over time
            theta += omega * time_diff / 1000; // +: cw; -: ccw;
        }
        else{ // curve movement
            vR = encoder.ReadVelocityRight();
            vL = encoder.ReadVelocityLeft();
            R = (vR + vL) / (vR - vL) * R_robot / 2;
            omega = (vR - vL) / R_robot;

            // in this case, x, y should change over time
            x -= R * (sin(theta) - sin(theta + omega * 0.005)) / 10.0; // cm
            y += R * (cos(theta) - cos(theta + omega * time_diff / 1000.0)) /10.0; // cm

            // in this case, theta should change over time
            theta += omega * time_diff / 1000.0; // radian
        }
        time_prev = time_now;
    }
}

