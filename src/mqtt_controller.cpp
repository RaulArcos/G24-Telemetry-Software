/**
 * @file mqtt_controller.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the MQTT Controller for AWS - G24 Telemetry.
 */

#include "../include/mqtt_controller.hpp"
#include <ArduinoJson.h>


MQTTController::MQTTController() {
    _client.setServer(_mqtt_server, _mqtt_port);
}

void MQTTController::set_callback(std::function<void(char*, byte*, unsigned int)> func){
    _client.setCallback(func);
}

void MQTTController::connect() {
    while (!_client.connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = "ESP32-";
        clientId += String(random(0xffff), HEX);
        
        if (_client.connect(clientId.c_str())) {
            Serial.println("Connected");

            // _client.subscribe(mode_topic);
            // _client.subscribe(start_topic);
            // _client.subscribe("G24/tpv/test");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(_client.state());
            Serial.println(" Waiting 1 seconds");
            delay(1000);
        }
    }
}

PubSubClient* MQTTController::get_client() {
    return &_client;
}

void MQTTController::publish_telemetry(const char* topic, const char* message){
    _client.publish(topic, message);
}

void MQTTController::publish_test(const char* message){
    _client.publish(test_topic, message);
}

void MQTTController::publish_gps(const char* message){
    _client.publish(gps_topic, message);
}

void MQTTController::publish_satellites(const char* message){
    _client.publish(satellites_topic, message);
}

void MQTTController::callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

