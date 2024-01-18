#include <AFMotor.h>
#include <Servo.h> 

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Servo myservo;
int pos = 60;	// variable to store the servo position
int distance = 30; //variable to store distance from the right side
long duration; // duration untile the sound comes back to the sensor
int distance1 = 0; //variable to store distance from left side

void setup() 
{
  motor3.setSpeed(200);
  motor4.setSpeed(200);
  myservo.attach(9);  
  pinMode(A1, OUTPUT);  // Analog pin A1 connected to TRIG
  pinMode(A0, INPUT);   // Analog pin A0 connected to ECHO 
}

void loop() {

 while (distance > 15) {
    verify_distance(&distance);
    run();
  }

  stop();

  //servo moves to right
  for (pos = 60; pos >= 0; pos -= 1)
    {
        myservo.write(pos);
        delay(15);
    }

  delay(500);

  verify_distance(&distance);

  //servo moves to left
  for (pos = 0; pos <= 120; pos += 1)
    {
        myservo.write(pos);
        delay(15);
    }

  delay(500);

  verify_distance(&distance1);

  //servo comes in intial position
  for (pos = 120; pos >= 60; pos -= 1)
    {
        myservo.write(pos);
        delay(15);
    }

  delay(500);

  if (distance > distance1){
    long long time = millis();
    while (millis() - time < 400) {
      right();
    }
  }
  else {
    long long time = millis();
    while (millis() - time < 400) {
      left();
    }
  }

  stop();

  delay(1000);
}

void verify_distance(int *dist){ //verify the distance from the sensor until the surface detected, store it in a variable the funtion receive as input
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);    // Give a pulse of 10 microseconds on TRIG
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  duration = pulseIn(A0, HIGH);  // Check the time elapsed in receiving back the pulse on ECHO
  *dist= duration * 0.034 / 2;  // Convert to distance in centimeters
}

void run(){ //function for moving forward
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}

void stop(){ //function for stop
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void right(){ //function for moving to right
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void left(){ //function for moving to left
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}