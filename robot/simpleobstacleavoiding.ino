const int trig = 13;
const int echo = 12;
const int in1 = 11;
const int in2 = 10;
const int in3 = 9;
const int in4 = 8;
const int ENA= 5;
const int ENB= 3;


void setup() 
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
}

long dura, dis;

void loop()
{ 
  analogWrite(ENA,85);
  analogWrite(ENB,85);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);  
  
  dura = pulseIn(echo, HIGH);
  dis = dura*0.034/2;
  Serial.print("Distance:");
  Serial.println(dis);
  if(dis<25)
    {
      digitalWrite(in1, LOW); 
      digitalWrite(in2, HIGH); 
      digitalWrite(in3, HIGH); 
      digitalWrite(in4, LOW);
       delay(200);
      digitalWrite(in1, LOW); 
      digitalWrite(in3, LOW); 
      digitalWrite(in2, HIGH); 
      digitalWrite(in4, LOW);
      delay(500);
    }
    
  else
    {
      digitalWrite(in1, HIGH); 
      digitalWrite(in2, LOW); 
      digitalWrite(in4, HIGH); 
      digitalWrite(in3, LOW);
    }  
  delay(0);
}
