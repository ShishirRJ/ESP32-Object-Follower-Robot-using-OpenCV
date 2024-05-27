#include <WiFi.h>

const char *ssid = "Enter ssid of network";
const char *password = "Enter password of network";

int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;
int motor2Pin1 = 18;
int motor2Pin2 = 19;
int enable2Pin = 21;

const int freq = 30000;
const int pwmChannel1 = 0;
const int resolution = 8;
const int pwmChannel2 = 1;
int dutyCycle = 200;

WiFiServer server(80);


//motor1 is Left motor
//motor2 is Right motor

void goRight(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, 170);
}

void goLeft(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  ledcWrite(pwmChannel1, 170);
  ledcWrite(pwmChannel2, dutyCycle);
}

void goForward(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
}

void stopCar(){
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  
  server.begin();

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  ledcSetup(pwmChannel1, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel1);
  
  ledcSetup(pwmChannel2, freq, resolution);
  ledcAttachPin(enable2Pin, pwmChannel2);
}

void loop() {
  WiFiClient client = server.available();
  byte data[4];
  
  if (client) {
    while (client.connected()) {
      if (client.available()>=4) {
        client.read(data, 4);
        int x= data[3]*10;
        Serial.printf("(%d, %d, %d)\t X=%d    \n", data[0], data[1], data[2], x);
        
        if(data[0]!=0 && data[2]!=0 &&data[3]!=0){
          if(x>=150 && x<=350){
            goForward();
          }
          if(x<150){
            goLeft();
          }
          if(x>350){
            goRight();
          }
        }
        else{
          stopCar();
        }
        // Process the received message as needed
      }
    }
    client.stop();
  }

  
}
