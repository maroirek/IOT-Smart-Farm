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