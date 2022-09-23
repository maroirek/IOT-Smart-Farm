#include <Arduino.h>
#include <Adafruit_Sensor.h>  // Library : Adafruit Unified Sensor
#include <ESP32Servo.h>
 
#include <DHT.h>
#include <DHT_U.h>  // Library : DHT sensor library
#include "Wire.h"
#include "SPI.h"
#include "MQ135.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include "WiFi.h" 



#define DEEP_SLEEP_TIME 5
#define DHTPIN 21// IMPORTANT D2 on NodeMCU is GPIO 4
#define DHTTYPE DHT22
#define Cap 23  

// WiFi
char* ssid = "viveHamadi";                 // Your personal network SSID
const char* wifi_password = "samy1243"; // Your personal network password

//MQTT
const char* mqtt_server = "192.168.137.231";  // IP of the MQTT broker

//Topics_in
const char* pompe_topic = "esp32/water";
const char* ventilo_topic = "esp32/air";
const char* servo_topic    ="esp32/servo";
// const char* led_topic = "esp32/light";

const char* humidity_topic = "serre/humidity";
const char* temperature_topic ="serre/temperature";
const char* soil_topic = "serre/soli";
const char* lum_topic = "serre/lum";
const char* CO2_topic = "serre/gaz";
const char* niveau_topic = "serre/reservoir";

const char* mqtt_username = "vivealik"; // MQTT username
const char* mqtt_password = "fifisurtoi"; // MQTT password
const char* clientID_1 = "client_livingroom";// MQTT client ID
const char* clientID = "Esp32Client"; // MQTT client ID

// Initializes the espClient
WiFiClient espClient;
PubSubClient client(espClient);

const int wet  = 1615;   //you need to replace this value with Value_1
const int dry= 3450;  //you need to replace this value with Value_2
int Liquid_level=0; 

int sMValue = 0;
int soilmoisturepercent=0;

const int ANALOGPIN= 35 ;

MQ135 gasSensor = MQ135(ANALOGPIN);
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
unsigned long interval = 30000;

//GPIOS
 int R1= 25;      //pompe
 int R2= 14;      //ventilo
 int R3= 27;      //lum

Servo myservo;  // create servo object to control a servo
int pos = 10;    // variable to store the servo position
///Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
 int servoPin = 13;

//Function to connect to WIFI
void connect_wifi () {

   WiFi.begin(ssid, wifi_password);

   while (WiFi.status() != WL_CONNECTED) {

     delay(500);
     Serial.print(".");
   Serial.println("WiFi connected");
   Serial.print("IP address: ");
   Serial.println(WiFi.localIP());} }


//Function to connect to MQTT
void connect_MQTT()
{

   Serial.print("Connecting to ");
   Serial.println(ssid);

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)

   if (client.connect(clientID, mqtt_username, mqtt_password) || client.connect(clientID_1, mqtt_username, mqtt_password)  ) {
           Serial.println("Connected to MQTT Broker!");
           client.subscribe("esp32/water");
           client.subscribe("esp32/air");
           client.subscribe("esp32/servo");
           client.subscribe("esp32/lum");
           }
  else {
         Serial.println("Connection to MQTT Broker failed...");}

