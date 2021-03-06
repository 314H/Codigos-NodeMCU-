#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "RedeWifi; //SSID
char pass[] = "SenhaWifi"; // Password
//-------------------------------------------//

const int trigger = 16;
const int echo = 5;
long T;
float distanceCM;
WiFiClient  client;
const float altura = 13;

unsigned long myChannelField = 885142; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "E4CJ0K465Q5CHG8B"; // Your write API Key

void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  distanceCM = 100 - (distanceCM * 100 / altura); 
  Serial.print("Distance in %: " "%");
  Serial.println(distanceCM);
  ThingSpeak.writeField(myChannelField, ChannelField, distanceCM, myWriteAPIKey);
  delay(1000);
}
