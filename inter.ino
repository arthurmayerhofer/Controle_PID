#include <Servo.h>
#include <NewPing.h>

Servo servo;
NewPing ultra (trigger, echo, range);

int servo = 13;
int trigger = 12;
int echo  =  11;
int range = 200;

const float pi = 3.14159265359;

//raio da base do recipiente

r = 7;
 
// altura do recipiente  

float hr;

// dist ultrassom ate o liquido 

float d1 = 24; // a definir //menor h liquido -- maior dist do ultrassom 
float d2 = d1*(3/4); 
float d3 = d1*(2/4);
float d4 = d1*(1/4); 
float d5 = 0;  // maior h liquido -- menor dist do ultrassom

// altura do liquido
 
float h1 = hr - d1; //menor
float h2 = hr - d2;
float h3 = hr - d3;
float h4 = hr - d4;
float h5 = hr - d5; //maior
  
// MARCADORES do nivel - maior para menor   
  
float n1 = pi*(r*r)*h1; //menor
float n2 = pi*(r*r)*h2;
float n3 = pi*(r*r)*h3;
float n4 = pi*(r*r)*h4;
float n5 = pi*(r*r)*h5; //maior


void setup() {
  
 Serial.begin(9600);
 
 float dist = ultra.ping_cm();
 
 float nivel = pi*(r*r)*(hr - dist);
 
}


void loop() {
 
 x = map = (nivel, n1, n5, 0, 180);
 
 servo.write(x);
 
     
 /* if ((nivel >= n1) && (nivel < n2) ){

      for(pos_inicial = 0, pos_inicial < pos_final, i++)

          servo.write();*/
   }
 
    Serial.print("dist: ");
    Serial.print(ultra.ping_cm());
    Serial.println("cm");
 
    Serial.print("n1: ");
    Serial.print(n1);
    Serial.println("cm3");
    
    Serial.print("n2: ");
    Serial.print(n2);
    Serial.println("cm3");
    
    Serial.print("n3: ");
    Serial.print(n3);
    Serial.println("cm3");
 
    Serial.print("n4: ");
    Serial.print(n4);
    Serial.println("cm3");
 
    Serial.print("n5: ");
    Serial.print(n5);
    Serial.println("cm3");

    Serial.print("angulo: ");
    Serial.print(x);
    Serial.println("graus");
    }
