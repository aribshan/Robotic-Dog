#include <Servo.h>

Servo tail, head;

int pos = 0;
int sensorPin = A0;
int sensorValue = 0;
int avg = 245;
int limit = 150;
int clap_lower_limit = 250;
int clap_higher_limit = 1200;
int no_of_claps = 0;
long long int cnt = 0;

void setup() {
  head.attach(9);
  tail.attach(10);
  Serial.begin(2000000);
}

void move_servo(int mode, int angle){
  for (pos = 60 - angle/2; pos <= 60 + angle/2; pos += 1) {
    if(mode&1)  head.write(pos);
    if(mode&2)  tail.write(pos);
    delay(5);
  }
  for (pos = 60 + angle/2; pos >= 60 - angle/2; pos -= 1) {
    if(mode&1)  head.write(pos);
    if(mode&2)  tail.write(pos);
    delay(5);
  }
}

void loop() {
 
//  Serial.print((int)cnt);
  sensorValue = analogRead(sensorPin);
  Serial.print(0);  // To freeze the lower limit
  Serial.print(" ");
  Serial.print(600);  // To freeze the upper limit
  Serial.print(" ");
  Serial.print(50*no_of_claps);
  Serial.print(" ");
  Serial.println(sensorValue);

  cnt++;
  
  if(abs(sensorValue - avg) > limit){
    if(cnt > clap_lower_limit){
      no_of_claps++;
      cnt = 0;
    }
  }

  if(no_of_claps > 0 && cnt > clap_higher_limit){
    if(no_of_claps == 1){    
      move_servo(1,60);
      move_servo(1,60);
    }else if(no_of_claps == 2){    
      move_servo(2,60);
      move_servo(2,60);
    }else{
      move_servo(3,60);
      move_servo(3,60); 
    }
    delay(200);
    no_of_claps = 0;
  }

  if(cnt > clap_higher_limit){
    no_of_claps = 0;
  }
}
