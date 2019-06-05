#include <Servo.h>
#include <NewPing.h>

int servo = 13;
int trigger = 12;
int echo  =  11;
int range = 200;

const float pi = 3.14159265359;
 
// altura do recipiente  

float hr;

// dist ultrassom ate o liquido 

float d1; // a definir 
float d2 = d1*(3/4); 
float d3 = d1*(2/4);
float d4 = d1*(1/4); 
float d5; // maior h liquido -- menor dist 

// altura do liquido
 
float h1 = hr - d1;
float h2 = hr - d2;
float h3 = hr - d3;
float h4 = hr - d4;
float h5 = hr - d5;
  
//niveis do agua - maior para menor   
  
float n1 = pi*(r*r)*h1;
float n2 = pi*(r*r)*h2;
float n3 = pi*(r*r)*h3;
float n4 = pi*(r*r)*h4;
float n5 = pi*(r*r)*h5;

Servo servo;
     
NewPing ultra (trigger, echo, range);


void setup() {
  
  Serial.begin(9600);
    
  float dist = ultra.ping_cm();
    

}



void loop() {
      
   if (dist < h1){

      for(i, i<20, i++)

          servo.write();
   }
         
        
     // }

      
      delay(50);
      Serial.print("Ping: ");
      Serial.print(ultra.ping_cm());
      Serial.println("cm");
    }
