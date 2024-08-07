#include "include/can.hpp"
#include "include/gsm_7600.hpp"
#include "include/wifi_controller.hpp"
#include "include/data_processor.hpp"
#include "include/mqtt.hpp"
#include "include/ublox_gps.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>


SemaphoreHandle_t xMutex = xSemaphoreCreateMutex();

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
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            if (!gsm7600.check_connection()) {
            Serial.println("GSM connection failed, attempting to reconnect...");
            delay(5000); // Add a delay before attempting to reconnect
            gsm7600.connect();
            }
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("G24::GMSController - Attempting LTE Conection...");
    
    dataProcessor.set_mutex(xMutex);
    mqtt.set_mutex(xMutex);
    gsm7600.set_mutex(xMutex);

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
    
    xTaskCreatePinnedToCore(
        check_connections,
        "CheckConnections",
        4096,
        NULL,
        2,
        NULL,
        1
    );  
}

void loop(){ 
    if (!mqttClient->connected()) {
        mqtt.connect();
    } 
    mqtt.loop(); 
    canController.listen();
    ubloxGPS.listen();
    vTaskDelay(pdMS_TO_TICKS(10));
}