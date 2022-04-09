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

// PD controller for wall follower
void Wall_follower::wall_following(float dis, float baseEffort){
    float currentDist = ir_sensor.ReadData();
    err = dis - currentDist; // +: curr < target; -: curr > target
    float effort = Kp * err + Kd * (err-lastErr); // +: curr <  target -: curr > target
    speed_controller.Process(baseEffort+effort, baseEffort-effort);
    lastErr = err;
}
    
