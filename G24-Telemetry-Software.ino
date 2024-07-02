#include "include/can.hpp"
#include "include/gsm_7600.hpp"
#include "include/wifi_controller.hpp"
#include "include/data_processor.hpp"
#include "include/mqtt.hpp"
#include "include/ublox_gps.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// WifiController wifiController("FormulaGades", "g24evo24");
DataProcessor dataProcessor;
CAN canController;
UboxGPS ubloxGPS;
GSM7600 gsm7600;

MQTT mqtt(gsm7600.get_client());

PubSubClient* mqttClient;

void mqtt_callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // if (strcmp(topic, mqtt.mode_topic) == 0) {
    //     tpvTimer.set_mode(payload, length);
    // }else if(strcmp(topic, mqtt.start_topic) == 0){
    //     tpvTimer.start(payload, length);
    // }else if(strcmp(topic, "G24/tpv/test") == 0){
    //     timeSync.trigger(payload, length);
    // }
}

void setup() {
    Serial.begin(115200);
    Serial.println("G24::GMSController - Attempting LTE Conection...");
    
    gsm7600.begin();
    canController.start();

    //Connect to MQTT
    mqtt.set_callback(mqtt_callback);
    mqtt.connect();
    Serial.println("G24::MQTT - Connected to MQTT!");

    mqttClient = mqtt.get_client();
    dataProcessor.set_mqtt_controller(&mqtt);
    canController.set_data_proccessor(&dataProcessor);
    ubloxGPS.set_data_processor(&dataProcessor);

    //Start CAN Controller
    xTaskCreate(
        CAN::listenTask,
        "CANController",    
        8192,              
        &canController,              
        1,                
        NULL               
    );
    //Start GPS Controller
    xTaskCreate(
        UboxGPS::listenTask,
        "UboxGPS",    
        8192,              
        &ubloxGPS,              
        2,                
        NULL               
    );
}

void loop(){ 
  if (!mqttClient->connected()) {
      mqtt.connect();
  }
  gsm7600.check_connection();
  mqttClient->loop();
  mqtt.publish_status("connected");
  // gsm7600.print_network_info();
  delay(10);
}