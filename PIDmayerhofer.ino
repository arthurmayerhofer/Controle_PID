#include <NewPing.h>

//pinos do ultrassônico e distância máxima(range)
#define trigger 3
#define echo 5
#define range 200

NewPing sensor(trigger, echo, range);

//pinos potênciometros
int pot_kp = A0;
int pot_ki = A2;
int pot_kd = A4;
int pot_set = A6;

// pinos da ponte H
int in3 = 7;
int in4 = 9;
int pwm_pin = 11;

double setpoint;
double distance;
double height;
float velocity;

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
//
//double kp = 6; 
//double ki = 5; 
//double kd = 0.3;

void setup() { 
  
  Serial.begin(1200);
  
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pwm_pin, OUTPUT);

  pinMode(pot_kp, INPUT);
  pinMode(pot_ki, INPUT);
  pinMode(pot_kd, INPUT);
  pinMode(pot_set, INPUT);
}

void loop() {
  
  double kp = map(analogRead(pot_kp), 0, 1023, 0, 63) * 0.1; 
  double ki = map(analogRead(pot_ki), 0, 1023, 0, 70) * 0.01;
  double kd = map(analogRead(pot_kd), 0, 1023, 0, 15) * 0.01;
  double setpoint = map(analogRead(pot_set), 0, 1023, 0, 40);

//  setpoint = 10; //altura desejada
  
  presentTime = millis();
  pastTime = presentTime - lastTime;

  distance = sensor.ping_cm();
  height = (pipe - distance) - object; 
 
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

  velocity = map(velocity, 70, 255, 175, 250);

//  Serial.print("Vel2: ");
//  Serial.print(velocity);
//  Serial.println();

  turnON();

//  Serial.print("Altura: ");
//  Serial.print(height);
//  Serial.println("cm");
//  Serial.println();
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.println();

  Serial.print("kp: ");
  Serial.print(kp);
  Serial.println();

  Serial.print("ki: ");
  Serial.print(ki);
  Serial.println();

  Serial.print("kd: ");
  Serial.print(kd);
  Serial.println();

  Serial.print("setpoint: ");
  Serial.print(setpoint);
  Serial.println();

  Serial.print("Error: ");
  Serial.print(error);
  Serial.println("cm");
  Serial.println();
  
}

void turnON(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(pwm_pin, velocity); 
}
