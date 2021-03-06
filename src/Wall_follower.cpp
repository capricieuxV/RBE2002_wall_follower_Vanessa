#include "Wall_follower.h"

void Wall_follower::init(){
  ir_sensor.init();
  speed_controller.Init();
}

float Wall_follower::getDistanceSonar(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 /2;
  return distance;
}

void Wall_follower::setConstant(float kp, float kd){
  this->Kp = kp;
  this->Kd = kd;
}

// PD controller for wall follower
void Wall_follower::wall_following(float dis, float baseEffort, bool isLeft){
    float currentDist = ir_sensor.ReadData();
    err = dis - currentDist; // +: curr < target; -: curr > target
    float effort = Kp * err + Kd * (err-lastErr); // +: curr <  target -: curr > target
    if(isLeft){
      speed_controller.Process(baseEffort+effort, baseEffort-effort);
    }else{
      speed_controller.Process(baseEffort-effort, baseEffort+effort);
    }
    lastErr = err;
}
    
