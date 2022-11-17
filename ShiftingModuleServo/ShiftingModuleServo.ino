// Written by Ian Huerta
//
#include <Servo.h> // Include Stepper library (header)

// Definitions
const int spr = 2038; // Steps per revolution (factory)
// Motor outputs
const int pwm_pin = 3;
// Button inputs
const int upb = 4, downb = 5, upt = 6, downt = 7;
//
const int vtx = 6;

int upc_state = 0, upp_state = 0;
int downc_state = 0, downp_state = 0;
int uptc_state = 0, uptp_state = 0;
int downtc_state = 0, downtp_state = 0;
// Shifter control
const int speeds = 9;
int speed_count = 1;
int wait = 350; // Waiting time
int pos = 64; // Steps for 11 deg displacement ~2.3 [mm]
int tune = 18; // Small tunning displacement
// Stepper instance
Stepper motor = Stepper(spr, in1, in3, in2, in4);

void setup()
{
  Serial.begin(9600); // For debbuging
  pinMode(upb, INPUT_PULLUP);
  pinMode(downb, INPUT_PULLUP);
  pinMode(upt, INPUT_PULLUP);
  pinMode(downt, INPUT_PULLUP);
  motor.setSpeed(10); // Best torque at this speed ~34.3[mN*m]
}

void loop()
{
  // Machine states for shifting up
  upc_state = digitalRead(upb);
  if(upc_state != upp_state)
  {
    if(upc_state == HIGH)
    {
      Serial.println("fall UP");
    }
    if(upc_state == LOW)
    {
      Serial.println("rise UP");
      if(speed_count != speeds)
      {
        motor.step(pos);
        speed_count++;
        Serial.println(speed_count);
      }
      delay(wait);
    }
  }
  upp_state = upc_state;
  
  // Machine states for shifting down
  downc_state = digitalRead(downb);
  if(downc_state != downp_state)
  {
    if(downc_state == HIGH)
    {
      Serial.println("fall DOWN");
    }
    if(downc_state == LOW)
    {
      Serial.println("rise DOWN");
      if(speed_count != 1)
      {
        motor.step(-pos);
        speed_count--;
        Serial.println(speed_count);
      }
      delay(wait);
    }
  }
  downp_state = downc_state;

  // Machine states for tuning up
  uptc_state = digitalRead(upt);
  if(uptc_state != uptp_state)
  {
    if(uptc_state == HIGH)
    {
      Serial.println("fall tuneUP");
    }
    if(uptc_state == LOW)
    {
      Serial.println("rise tuneUP");
      motor.step(tune);
      delay(wait);
    }
  }
  uptp_state = uptc_state;
  
  // Machine states for tuning up
  downtc_state = digitalRead(downt);
  if(downtc_state != downtp_state)
  {
    if(downtc_state == HIGH)
    {
      Serial.println("fall tuneDOWN");
    }
    if(downtc_state == LOW)
    {
      Serial.println("rise tuneDOWN");
      motor.step(-tune);
      delay(wait);
    }
  }
  downtp_state = downtc_state;

  
}
