#include "include/can_controller.hpp"
#include "include/lte_controller.hpp"
#include "include/wifi_controller.hpp"
#include "include/data_processor.hpp"
#include "include/mqtt_controller.hpp"
#include "include/gps_controller.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

WifiController wifiController("FormulaGades", "g24evo24");
MQTTController mqttController;
DataProcessor dataProcessor;
CANController canController;
GPSController gpsController;

PubSubClient* mqttClient;

void mqtt_callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // if (strcmp(topic, mqttController.mode_topic) == 0) {
    //     tpvTimer.set_mode(payload, length);
    // }else if(strcmp(topic, mqttController.start_topic) == 0){
    //     tpvTimer.start(payload, length);
    // }else if(strcmp(topic, "G24/tpv/test") == 0){
    //     timeSync.trigger(payload, length);
    // }
}

void setup() {
    Serial.begin(115200);
    Serial.println("G24::WifiController - Attempting Wifi Conection...");

    canController.start();
    
    //Connect to WiFi
    if(wifiController.connect()){
      Serial.println("G24::WifiController - Connected to WiFi!");
    }else{
      Serial.println("G24::WifiController - Failed to connect to WiFi! Timeout!");
    }

    //Connect to MQTT
    mqttController.set_callback(mqtt_callback);
    mqttController.connect();
    Serial.println("G24::MQTTController - Connected to MQTT!");

    mqttClient = mqttController.get_client();
    dataProcessor.set_mqtt_controller(&mqttController);
    canController.set_data_proccessor(&dataProcessor);
    gpsController.set_data_processor(&dataProcessor);

    //Start CAN Controller
    xTaskCreate(
        CANController::listenTask,
        "CANController",    
        8192,              
        &canController,              
        1,                
        NULL               
    );
    //Start GPS Controller
    xTaskCreate(
        GPSController::listenTask,
        "GPSController",    
        8192,              
        &gpsController,              
        2,                
        NULL               
    );
}

void loop(){  
  if (!mqttClient->connected()) {
      mqttController.connect();
  }
  mqttClient->loop();
  // mqttController.publish_status(mqttController.toString(tpvTimer.get_status()), mqttController.toString(tpvTimer.get_mode()));
  delay(10);
}