#include "Encoder.h"

void Encoder::Init(){
    motor.init();
    encoder.init();
}

void Encoder::updateCounts(){
    // store the previous and current encoder counts every 50ms
    long interval = 50;
    currentMillis = millis();

    if((currentMillis - previousMillis) >= interval){
        // update counts every 50 ms
        // reset after it so that we will only hold counts during the interval
        countLeft = encoder.getCountsAndResetLeft();
        countRight = encoder.getCountsAndResetRight();
        int curr_countLeft = countLeft;
        int curr_countRight = countRight;

        Serial.print("\ncountLeft: ");
        Serial.print(curr_countLeft);
        Serial.print("\tcountRight: ");
        Serial.println(curr_countRight);
        Serial.println();
        
        previousMillis = currentMillis;
    }
}

/* 𝑉T = ((2∗𝜋∗𝑟) / (1440𝑐𝑜𝑢𝑛𝑡𝑠)) * (n / T) */
// r = 3.5 cm, T = 50 ms = 0.05 s
float Encoder::readVelocityLeft(){
    // return the left wheel velocity 
    leftV = ((2 * PI * 3.5) / 1440) * countLeft/ 0.05; //cm/s
    return leftV;
}

float Encoder::readVelocityRight(){
    // return the right wheel velocity
    rightV = ((2 * PI * 3.5) / 1440) * countRight/ 0.05; //cm/s
    return rightV;
}

// helper function for checking if ther value is negative or positive
int Encoder::getSign(float value){ return value<0?-1:value>0; }

// cm/s
void Encoder::setVelocity(float left, float right){

  //calculate the errors
  float currL = readVelocityLeft();
  float currR = readVelocityRight();

  float errL = abs(left) - abs(currL);
  float errR = abs(right) - abs(currR);

  // integrate the errors
  sumErrL += errL*0.05;
  sumErrR += errR*0.05;

  // sum up the integral and current errors
  float outputL = Kp * getSign(left)*errL + Ki * getSign(left)*sumErrL;
  float outputR = Kp * getSign(right)*errR + Ki * getSign(right)*sumErrR;

  // simply set velocity for each motor
  motor.setEfforts(outputL, outputR);
}

int Encoder::readEncoderCountLeft(void)
{
  return countLeft;
}

int Encoder::readEncoderCountRight(void)
{
  return countRight;
}