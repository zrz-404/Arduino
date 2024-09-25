#include <Servo.h>
#define middleSensor A0
#define leftSensor A1
#define rightSensor A2

Servo myservo;
int   pos;

void setup() {
  myservo.attach(9);
  pos = 90;
  myservo.write(pos);
  delay(150);
  Serial.begin(9600);
}

int  isClose(int x, int y)
{
    int tmp = x - y;
    if (tmp >= -100 && tmp <= 100)
      return (1);
    else
      return (0);
}

void changePos(int left, int middle, int right)
{
  if (isClose(left, middle) && !isClose(left, right) && left > right)
    pos = 135;
  else if (isClose(left, middle) && !isClose(left, right) && left < right)
    pos = 0;
  else if (isClose(middle, right) && !isClose(middle, left) && middle > left)
    pos = 45;
  else if (isClose(middle, right) && !isClose(middle, left) && middle < left)
    pos = 180;
  else
    pos = 90;
}

void loop() {
  int middle = analogRead(middleSensor);
  int left   = analogRead(leftSensor);
  int right  = analogRead(rightSensor);

  changePos(left, middle, right);
  myservo.write(pos);
  delay(150);
}
