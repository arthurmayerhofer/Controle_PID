#include <NewPing.h>

//pinos do ultrassônico e distância máxima(range)
#define trigger 6
#define echo 7
#define range 200

NewPing sensor(trigger, echo, range);

// pinos da ponte H
int in3 = 3;
int in4 = 4;
int pwm_pin = 10;

double setpoint;
double distance;
double height;
float velocity;
float velmin = 145;

double pipe = 41; //medido com sensor na posição do projeto
double object = 6;

double pastTime;
unsigned long presentTime, lastTime;

double error;
double i_error;
double d_error;
double lastError;

//PI -- Kp = 6, Ki= 5. 
//PID -- Kp = 6, Ki= 5, Kd = 0.3

double kp = 6; 
double ki = 5; 
double kd = 0.3;

void setup() { 
  
  Serial.begin(9600);
  
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pwm_pin, OUTPUT);
}

void loop() {
  
  setpoint = 10; //altura desejada
  
  presentTime = millis();
  pastTime = presentTime - lastTime;

  distance = sensor.ping_cm();
  height = (pipe - distance) - object; 

  Serial.print("Altura: ");
  Serial.print(height);
  Serial.println("cm");
  Serial.println();
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.println();
 
  error = setpoint - height;
  i_error += error * pastTime;
  d_error = (error - lastError)/pastTime;
    
  velocity = kp*error + ki*i_error + kd*d_error;   //PID output             

  lastError = error;   //remember current error
  lastTime = presentTime; 


  if (i_error > 150){
    ki = 0;
  }

  if (velocity > 255){
    velocity = 255;
  }


  Serial.print("Velocity: ");
  Serial.print(velocity);
  Serial.println();
  
//  if (error < 0) {
//    velocity = map(velocity, 70, 255, 145, 250);
//  }
//
//  else{
    velocity = map(velocity, 70, 255, 175, 250);
//  }

//  if (distance < 6){
//    for (double i; velocity > 143; i++){
//      velocity = i;
//    }
//    
//  }
  
  
  Serial.print("Vel2: ");
  Serial.print(velocity);
  Serial.println();

  turnON();
  
  Serial.print("Error: ");
  Serial.print(error);
  Serial.println("cm");
  Serial.println();
  
}

//void h() {
//  double distance = sensor.ping_cm();
//  double height = (pipe - distance) - object;
//}

void turnON(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(pwm_pin, velocity); 
}

  
