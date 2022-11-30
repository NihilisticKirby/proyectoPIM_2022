// Written by Ian Huerta
//
#include <Servo.h> // Include Stepper library (header)
Servo mg995;

// Motor outputs
const char pwm_pin = 3;
// Button inputs
const char upb = 4, downb = 5, upt = 6, downt = 7;
//
const char vtx = 8;

char upc_state = 0, upp_state = 0;
char downc_state = 0, downp_state = 0;
char uptc_state = 0, uptp_state = 0;
char downtc_state = 0, downtp_state = 0;
// Shifter control variables
int speeds = 9;
int speed_count = 1;
int preset = 0;
int curr_angle = 180;
int wait = 350; // Waiting time

void setup()
{
  Serial.begin(9600); // For debbuging
  pinMode(vtx, INPUT);
  pinMode(upb, INPUT_PULLUP);
  pinMode(downb, INPUT_PULLUP);
  pinMode(upt, INPUT_PULLUP);
  pinMode(downt, INPUT_PULLUP);
  mg995.attach(pwm_pin);
  mg995.write(curr_angle);
}

void shiftUp()
{
  if(speed_count != speeds)
  {
    curr_angle -= 12;
    mg995.write(curr_angle - preset);
    speed_count++;
    Serial.print("Speed: ");
    Serial.print(speed_count);
    Serial.print(" Angle: ");
    Serial.print(curr_angle);
    Serial.print("+");
    Serial.println(preset);
  }
}

void shiftDown()
{
  if(speed_count != 1)
  {
    curr_angle += 12;
    mg995.write(curr_angle - preset);
    speed_count--;
    Serial.print("Speed: ");
    Serial.print(speed_count);
    Serial.print(" Angle: ");
    Serial.print(curr_angle);
    Serial.print("+");
    Serial.println(preset);
  }
}

void tuneUp()
{
  if(preset != 96)
  preset += 2;
  mg995.write(curr_angle - preset);
  Serial.print(" Angle: ");
  Serial.print(curr_angle);
  Serial.print("+");
  Serial.println(preset);
}

void tuneDown()
{
  if(preset != 0)
  preset -= 2;
  mg995.write(curr_angle - preset);
  Serial.print(" Angle: ");
  Serial.print(curr_angle);
  Serial.print("+");
  Serial.println(preset);
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
        shiftUp();
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
        shiftDown();
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
      //Serial.println("fall tuneUP");
    }
    if(uptc_state == LOW)
    {
      //Serial.println("rise tuneUP");
      tuneUp();
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
      //Serial.println("fall tuneDOWN");
    }
    if(downtc_state == LOW)
    {
      //Serial.println("rise tuneDOWN");
      tuneDown();
      delay(wait);
    }
  }
  downtp_state = downtc_state;

  
}