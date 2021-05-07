#include <ESP8266WiFi.h>
#include <PubSubClient.h>



//LED library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif





int counter = 0;
int rainbowstate = 0;
int k = 0;
int n = 0;
int val = 0;
//const int del = 2; 


const int stepPin = D8; 
//D8 //2
const int dirPin = D6; 
//D6 //3
const int enablePIN = D4;
//D4
const int del = 313;



// Update these with values suitable for your network.
const char* ssid = "FRITZ";
const char* password = "Corksnapu";
const char* mqtt_server = "192.168.178.71";

WiFiClient espClient5;
PubSubClient client(espClient5);

long lastMsg = 0;
char msg[50];
int value = 0;
int lastvalue = 0;



void setup() {
Serial.begin(9600); 
setup_wifi();
client.setServer(mqtt_server, 1883);
client.setCallback(callback);

 pinMode(stepPin,OUTPUT); 
 pinMode(dirPin,OUTPUT);
 pinMode(enablePIN,OUTPUT);


  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  delay(1000);
}

void loop() {
     if (!client.connected()) {
      reconnect();
    }
    client.loop();



while(val < n){
   //Serial.println("0");
   digitalWrite(enablePIN,LOW); 
   digitalWrite(dirPin,HIGH);
   digitalWrite(stepPin,HIGH); 
   delayMicroseconds(del); 
   digitalWrite(stepPin,LOW);
   delayMicroseconds(del); 
  val++;
  }
//Serial.println(val);
//Serial.println(n);
while(val > n){
   //Serial.println("1");
   digitalWrite(enablePIN,LOW); 
   digitalWrite(dirPin,LOW);
   digitalWrite(stepPin,HIGH); 
   delayMicroseconds(del); 
   digitalWrite(stepPin,LOW);
   delayMicroseconds(del); 
  val--;
  }

digitalWrite(enablePIN,HIGH); 
//Serial.println(val);
//Serial.println(n);



delay(400);
}






























void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
 // Serial.println();
 // Serial.print("Connecting to ");
 // Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  //  Serial.print(".");
  }

 // Serial.println("");
 // Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
  //  Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client5")) {
   //   Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("myhouse/living/starwars/status", "hello world");
      // ... and resubscribe


      client.subscribe("myhouse/living/starwars/state");
  
      
    } else {
      delay(5000);
    }
  }
}



void callback(char* topic, byte* payload, unsigned int length) {

int i = 0;
 // Hilfsvariablen für die Convertierung der Nachricht in ein String
 char message_buff[100];
 
 // Kopieren der Nachricht und erstellen eines Bytes mit abschließender \0
 for(i=0; i<length; i++) {
 message_buff[i] = payload[i];
 }
 message_buff[i] = '\0';

String msgString = String(message_buff);


   if (String(topic) == "myhouse/living/starwars/state"){
   k = round(msgString.toInt());
   //Serial.print(k);
   if (k != lastvalue){
   lastvalue = k;
   Serial.println(k);
   n=k*16*4;

   }


   }
}









