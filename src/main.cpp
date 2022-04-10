#include <Arduino.h>
#include <Romi32U4.h>
#include <Wall_follower.h>

Wall_follower robot;

void setup() {
  Serial.begin(115200);
  robot.init();
}


void loop() 
{
  robot.wall_following(10, 35, true);
}
