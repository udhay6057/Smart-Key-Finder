#include <ESP8266WiFi.h> 

#include <WiFiClient.h> 

#include <ESP8266WebServer.h> 

ESP8266WebServer server(80);
int D2;

const int buz_pin = D2;

char ssid[] = "VV";

char pass[] = "12345678";

String html_code = "<!DOCTYPE html><html><head><h1>Smart Key Finder</h1><style>.button {border: none;padding: 12px 40px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;}.button1 {background-color: black; color: white; border: 3px solid #1c1c1b;border-radius: 30px}body {text-align: center;}</style></head><body><h2>Have you lost your key<br> then why to wait..<br>Click the below button...<br><form action=\"/BUZ\" method=\"POST\"><button><b>Click me</b></button></body></html>";

boolean buzzing_state = false;

void handleRoot() { 

server.send(200, "text/html", html_code + "Current state: <b>" + buzzing_state);

}

void handleBUZ() { 

buzzing_state = !buzzing_state; 

server.sendHeader("Location","/"); 

server.send(303); 

}

void handleNotFound(){

server.send(404, "text/plain", "404: Not found"); 

}

void setup(void){ 

  Serial.begin(115200);        

  delay(10);

  pinMode(buz_pin, OUTPUT); 

  Serial.print("\n\nConnecting Wifi... ");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)

  {    

    delay(500);

  }

  Serial.println("OK!");

  Serial.print("IP address: http://127.0.0.1:5500/index.html ");

  Serial.println(WiFi.localIP());
}
void loop(void){
 server.handleClient(); 
 if (buzzing_state == true) {
 digitalWrite(buz_pin, HIGH);
 delay(400);
 yield();
 digitalWrite(buz_pin, LOW);
}
}
