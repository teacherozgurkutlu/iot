#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "AndroidAP";
const char* password = "ntvd1574";
const char* mqtt_server = "iot.eclipse.org"; 
//int buttonPin=2;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
String kmt="";
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
} 

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  kmt="";
  for (int i = 0; i < length; i++) {    
  //Serial.print((char)payload[i]);
   kmt=kmt+(String)payload[i];
  } 
  //Serial.print((char)(kmt.toInt()));
  kmt=(char)(kmt.toInt());
  Serial.print(kmt);
  if (kmt=="1")
  {
    
    digitalWrite(4, HIGH);
    }
  if (kmt=="2")
  
  {digitalWrite(4, LOW);}
  if (kmt=="3")
  {digitalWrite(13, HIGH);}
  if (kmt=="4")
  {digitalWrite(13, LOW);}
  
  
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("paho/zgur/single", "tasdelenimkb");
      // ... and resubscribe
      client.subscribe("paho/zgur/singlein");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      for(int i = 0; i<5000; i++){
        
        delay(1);
      }
    }
  }
} 



void setup() {
  // put your setup code here, to run once:
//pinMode(buttonPin, INPUT);
pinMode(13, OUTPUT);
pinMode(4, OUTPUT);
Serial.begin(115200);
setup_wifi();
client.setServer(mqtt_server,1883);
client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
if (!client.connected())
{
  reconnect();
  }

  //if (digitalRead(buttonPin) == LOW)
       //{
        //client.publish("paho/zgur/single", "butonimkb");
        //Serial.print("buton");
        //while(digitalRead(buttonPin) == LOW)
        //{}
        //}  
  //delay(1000);
  client.loop();
  
}
