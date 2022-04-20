#include <Romi32U4.h>
#include "Encoders.h"

int count_left = 0;
int count_right = 0;
int prev_count_left = 0;
int prev_count_right = 0;
uint32_t last_update = 0;

Romi32U4Encoders encoders;

void Encoders::Init(void)
{
    //nothing to initialize, however, good practice to have a init function anyway
    encoders.init();
}

void Encoders::PrintVelocities(void)
{
    Serial.print("Velocity of left wheel: ");
    Serial.print(ReadVelocityLeft());
    Serial.print('\t');
    Serial.print("Velocity of right wheel: ");
    Serial.println(ReadVelocityRight());
}   

int Encoders::ReadEncoderCountLeft(void)
{
  return count_left;
}

int Encoders::ReadEncoderCountRight(void)
{
  return count_right;
}

float Encoders::ReadVelocityLeft(void)
{
    float measurement = (C_wheel/N_wheel)*(count_left-prev_count_left)/((float)interval/1000);
    return measurement;
}

float Encoders::ReadVelocityRight(void)
{
    float measurement = (C_wheel/N_wheel)*(count_right-prev_count_right)/((float)interval/1000);
    return measurement;
}

boolean Encoders::UpdateEncoderCounts(void)
{
  uint32_t now = millis();
  if(now - last_update >= interval)
  {    
    prev_count_left = count_left;
    prev_count_right = count_right;
    count_left = encoders.getCountsLeft();
    count_right = encoders.getCountsRight();
    last_update = now;
    return 1;
  }
  return 0;
}
