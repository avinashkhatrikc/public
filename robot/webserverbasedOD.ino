#include <ESP8266WiFi.h>
 
const char* ssid = "Avinash";
const char* password = "11111111";

const int trig = D3;
const int echo = D4;
const int in1 = D5;
const int in2 = D6;
const int in3 = D7;
const int in4 = D8;
const int ENA= D2;
const int ENB= D1;

WiFiServer server(80);
void setup() 
{
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
  Serial.print(WiFi.localIP());
  Serial.println("/");
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
       Serial.println("Back");
      digitalWrite(in1, LOW); 
      digitalWrite(in3, LOW); 
      digitalWrite(in2, HIGH); 
      digitalWrite(in4, LOW);
      Serial.println("Right");
      delay(500);
    }
    
  else
    {
            // Check if a client has connected
           WiFiClient client = server.available();
           if (!client) {
             return;
           }

           // Wait until the client sends some data
           Serial.println("new client");
           while(!client.available()){
             delay(1);
           }

           // Read the first line of the request
           String request = client.readStringUntil('\r');
           Serial.println(request);
           client.flush();

               // Match the request
           if (request.indexOf("/forward=1") != -1)  {  
            digitalWrite(in1, HIGH); //Start first motor
            digitalWrite(in2, LOW);
            digitalWrite(in4, HIGH); //Start second motor
            digitalWrite(in3, LOW);
            Serial.println("Motor On and Running in forward Direction");
            client.println("Motor On and Running in forward Direction");
          }
          
          if (request.indexOf("/stop=1") != -1)  {  
            digitalWrite(in1, LOW); //Stop first motor
            digitalWrite(in2, LOW);
          
            digitalWrite(in3, LOW); //Stop second motor
            digitalWrite(in4, LOW);
            Serial.println("Motor is Stop");
            client.println("Motor is Stop");
          }
          
          if (request.indexOf("/backward=1") != -1)  {
            
          digitalWrite(in1, LOW); 
          digitalWrite(in2, HIGH); 
          digitalWrite(in3, HIGH); 
          digitalWrite(in4, LOW);
          
            Serial.println("Motor On and Running in backward Direction");
            client.println("Motor On and Running in backward Direction");
          }
           
   
          // Return the response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println(""); //  do not forget this one
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<h1 align=center>Nast AI Delivery Robot</h1>");
          client.println("<h2 align=center>WiFi Based Obstacle detection robot</h2>");
          client.println("<br><br>");
          client.println("<p align=center><a href=\"/forward=1\"\"><button><h1>  Forward  </h1></button></a></p><br/>");
          client.println("<p align=center><a href=\"/stop=1\"\" ><button><h1>   Stop    </h1></button></a></p><br/>");
          client.println("<p align=center><a href=\"/backward=1\"\" ><button> <h1>  Reverse  </h1></button></a></p><br/>");
          client.println("</html>");
          delay(1);
          Serial.println("Client disonnected");
          Serial.println("");
    }  
  delay(0);
}
