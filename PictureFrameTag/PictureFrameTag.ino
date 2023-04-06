#include <ESP8266WiFi.h> 
#include <PubSubClient.h>

#define MAX_MSG_LEN (128)

//Just the pins I used. you are welcome to change
const int buttonLED = 16; // This code uses the built-in led for visual feedback that the button has been pressed
const int led1 = 5;
const int led2 = 4;
const int led3 = 0;
const int led4 = 2;

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = " YOUR ROUTER NAME HERE ";
const char* password = "ROUTER PASSWORD HERE";

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "IP HERE. DNS PREFERRED";

//Frame A (change names to fit your scenario)
const char* mqtt_topic_receive = "FRAME A";
const char* mqtt_topic_send = "FRAME B";
const char* clientID = "Frame A";

//Frame B
//const char* mqtt_topic_receive = "FRAME B";
//const char* mqtt_topic_send = "FRAME A";
//const char* clientID = "Frame B";


//This is for MQTT security information
const char* MQTT_username = "MGTT USERNAME HERE";
const char* MQTT_password = "MQTT PASSWORD HERE";
// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker


const char* customMessage = "ENTER A CUSTOME MESSAGE HERE"

void setup() {
  setupLeds();

  // Begin Serial on 115200
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.print("Connected to WiFi :");
  Serial.println(WiFi.SSID());
 

  client.setCallback(MQTTcallback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect(clientID, MQTT_username, MQTT_password)) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.println(client.state());  //If you get state 5: mismatch in configuration
      delay(2000);
 
    }
  }
  client.publish("Entry", customMessage);
  client.publish(mqtt_topic_send, "on");
  client.subscribe(mqtt_topic_receive);
  
}

void loop() {

    client.loop();
    // idle
    delay(500);
}




void MQTTcallback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");

  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];  //Conver *byte to String
  }
   Serial.print(message);
  if(message == "on") {
    turnLedsOn();
    }   //LED on  
 
}

//Initializes the LEDS in the system
void setupLeds() {
  pinMode(buttonLED, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(buttonLED, HIGH);
}
//Turn the 4 corner lights on the frame on
void turnLedsOn(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
}

//Turn the 4 LEDS in the corner off
void turnLedsOff(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}
//Flash the LEDS until a connection is made (For debug purposes)
void led_connecting(bool sw){

  if(sw==true){
    status = HIGH;
  } else {
    status = LOW;
  }
  digitalWrite(led1, status);
  digitalWrite(led2, status);
  digitalWrite(led3, status);
  digitalWrite(led4, status);  
}
