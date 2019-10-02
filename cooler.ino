#include <PID_v1.h>
#include <NewPing.h>



// pinos da ponte H
int in3 = 2;
int in4 = 4;
int pwm_pin = 3;

// pinos do ultrassônico e distância máxima(range)
int trigger = 12;
int echo  =  11;
int range = 200;

NewPing sensor(trigger, echo, range);

double Kp=2, Ki=5, Kd=1;
double Setpoint, Input, Output;

double h_tubo = 40; //medido com sensor na posição do projeto
double h_obj = 4;

double distance = sensor.ping_cm();
double h = (h_tubo - distance) - h_obj;

PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
//SetControllerDirection();
void setup() { 

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pwm_pin, OUTPUT);

  Input = h; //altura atual (variável controlada)
  Setpoint = Serial.read(); //altura desejada

 //aciona o controle PID
  pid.SetMode(AUTOMATIC);

  Serial.begin(9600);  
}

void loop() {
 
 pid.Compute();
 analogWrite(pwm_pin, Output);  }
}
