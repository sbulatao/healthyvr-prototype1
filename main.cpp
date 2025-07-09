// For the ESP32 to flash to get data from Polar V3 and H10
#include <BLEDevice.h> // BLE w/ Polar V3 and H10
#include <Time.h> // Timekeeping functionality

// Zephyr
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/bluetooth.h>
// #include <zephyr/bluetooth/classic/hfp_hf.h>
// #include <zephyr/settings/settings.h>

// https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/bluetooth/st_ble_sensor/src/main.c 
#include "button_svc.h"
#include "led_svc.h"

// Communications to ESP32 C3 (HealthyPi 5)
#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
// #include <ESP32Time> // set and retrieve internal RTC time on ESP32 boards

///////////////////////////////////////////////////////////////////////////////
//               
///////////////////////////////////////////////////////////////////////////////

// Find BLE devices such as V3 and H10


// Get data from V3


// Get data from H10


// Send data to ESP32


// WILL NEED FOR LATER USE
///////////////////////////////////////////////////////////////////////////////
//           Master-Slave Bluetooth Communication for other ESP32            //
///////////////////////////////////////////////////////////////////////////////

BluetoothSerial SerialPolar; // Bluetooth communication

void setup(){
  Serial.begin(115200); // 115200 baud rate
  pinMode(BUILTIN_LED, OUTPUT);
  SerialPolar.begin("ESP32_Slave_Polar");
  Serial.println("ESP32 Slave Polar Bluetooth Started. Waiting for Master HealthyPi 5 to connect...");

  while(!SerialPolar.connected()){
    delay(1000); // wait for 1 sec
    Serial.println("Waiting for Master HealthyPi 5.....")
  }

  Serial.println("*** Connected to ESP32_Master_HealthyPi_5 ***"); // successfully connected

  digitalWrite(BUILTIN_LED, HIGH) // turning on built-in led for successful connection
}

void loop(){
  if(SerialPolar.available()){ // checking if data is recieved from master device via bluetooth
    // READ DATA as strings
    String incomingData = SerialPolar.readString();
    Serial.print("Received JSON: ");
    Serial.println(incomingData);

    // JSON document to hold parsed data
    JsonDocument jsonDoc; // Adjust size HERE
    DeserializationError error = deserializeJson(jsonDoc, incomingData);

    if (error){ // checking deserialization was successful
      Serial.print("JSON Deserialization failed: ");
      Serial.println(error.c_str()); // prints error msg
      return;
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    // EXTRACTING DATA 
    // from Vantage V3
    int spO = jsonDoc["spO"]; // Oxygen Saturation 
    int ecg = jsonDoc["ecg"]; // Electrical Activity of the Heart
    int skin_temp = jsonDoc["skin_temperature"]; // Skin Temperature
    // from H10
    int heart_rate = jsonDoc["heart_rate"]; // BPM
    
    // output

    // digital write 

    // confirmation status back to master dev
    SerialPolar.println("Successfully Sent");
  
    ///////////////////////////////////////////////////////////////////////////////
    delay(100);
  }
  
}

