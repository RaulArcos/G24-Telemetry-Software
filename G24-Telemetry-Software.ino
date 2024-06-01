#include "include/can_controller.hpp"
#include "include/lte_controller.hpp"
#include "include/wifi_controller.hpp"
#include "include/data_processor.hpp"
#include "include/mqtt_controller.hpp"
#include "driver/gpio.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

WifiController wifiController("FormulaGades", "g24evo24");
MQTTController mqttController;
DataProcessor dataProcessor;
CANController *canController = new CANController();

const gpio_num_t buttonPin = GPIO_NUM_2; // Change as per your circuit
const uint64_t debounceInterval = 50; // Debounce interval in milliseconds
uint64_t lastDebounceTime = 0; // Variable to store last debounce time

// twai_message_t m1 = canController.createBoolMessage(false, false, false, false, false, false, false, true);
// twai_message_t m2 = canController.createBoolMessage(false, false, false, false, false, false, false, false);

int test = 0;
char* doc;

void setup() {
    Serial.begin(115200);
    Serial.println("G24::WifiController - Attempting Wifi Conection...");
    
    //Connect to WiFi
    if(wifiController.connect()){
      Serial.println("G24::WifiController - Connected to WiFi!");
    }else{
      Serial.println("G24::WifiController - Failed to connect to WiFi! Timeout!");
    }

    //Connect to MQTT
    mqttController.connect();
    Serial.println("G24::MQTTController - Connected to MQTT!");

    //Start CAN Controller
    xTaskCreate(
        CANController::listenTask,
        "CANController",    
        4096,              
        canController,              
        1,                
        NULL               
    );

    gpio_set_direction(buttonPin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(buttonPin, GPIO_PULLUP_ONLY);

}

void loop(){  
  doc = dataProcessor.process({test});
  mqttController.publish_telemetry("g24/telemetry", doc);
  test = test + 1;
  delay(100);

  // TempGearData temp = canController->getTempGearData();
  // BattWheelSpeedData batt = canController->getBattWheelSpeedData();
  // EngineData eng = canController->getEngineData();

  // doc = dataProcessor.process({temp.getECT()});
  // Serial.println(doc);

  // mqttController.publish_telemetry("g24/telemetry", doc);

}