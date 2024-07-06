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

void check_connections(void* pvParameters){
    while(true){
        Serial.println("Checking connections...");
        if (!gsm7600.check_connection()) {
            Serial.println("GSM connection failed, attempting to reconnect...");
            delay(5000); // Add a delay before attempting to reconnect
            gsm7600.connect();
        }
        if (!mqttClient->connected()) {
            mqtt.connect();
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("G24::GMSController - Attempting LTE Conection...");
    
    mqtt.set_mutex(dataProcessor.get_mutex());
    gsm7600.set_mutex(dataProcessor.get_mutex());

    gsm7600.begin();
    if (!gsm7600.is_connected()) {
        Serial.println("Failed to connect to the network");
        return;
    }
    canController.start();

    //Connect to MQTT
    mqtt.set_callback(mqtt_callback);
    mqtt.connect();
    Serial.println("G24::MQTT - Connected to MQTT!");

    mqttClient = mqtt.get_client();
    dataProcessor.set_mqtt_controller(&mqtt);
    canController.set_data_proccessor(&dataProcessor);
    ubloxGPS.set_data_processor(&dataProcessor);

    // Start CAN Controller on Core 0
    xTaskCreatePinnedToCore(
        CAN::listenTask,
        "CANController",
        8192,
        &canController,
        10,
        NULL,
        1 // Core 0
    );

    // Start GPS Controller on Core 1
    xTaskCreatePinnedToCore(
        UboxGPS::listenTask,
        "UboxGPS",
        8192,
        &ubloxGPS,
        3,
        NULL,
        0 // Core 1
    );

    // Start Check Connections on Core 1
    xTaskCreatePinnedToCore(
        check_connections,
        "CheckConnections",
        8192,
        NULL,
        2,
        NULL,
        0 // Core 1
    );  
}

void loop(){  
    mqtt.loop(); 
    vTaskDelay(pdMS_TO_TICKS(10));
}