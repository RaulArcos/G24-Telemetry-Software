/**
 * @file mqtt.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the MQTT Controller for AWS - G24 Telemetry.
 */

#include "../include/mqtt.hpp"
#include <ArduinoJson.h>


MQTT::MQTT(TinyGsmClient *client): _modem_client(client) {
    _client.setClient(*_modem_client);
    _client.setServer(_mqtt_server, _mqtt_port);
}

void MQTT::set_callback(std::function<void(char*, byte*, unsigned int)> func){
    _client.setCallback(func);
}

void MQTT::connect() {
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

PubSubClient* MQTT::get_client() {
    return &_client;
}

void MQTT::publish_telemetry(const char* topic, const char* message){
    _client.publish(topic, message);
}

void MQTT::publish_status(const char* message){
    _client.publish(status_topic, message);
}

void MQTT::publish_test(const char* message){
    _client.publish(test_topic, message);
}

void MQTT::publish_gps(const char* message){
    _client.publish(gps_topic, message);
}

void MQTT::publish_satellites(const char* message){
    _client.publish(satellites_topic, message);
}

void MQTT::publish_can_frame_0(const char* message){
    _client.publish(can_frame_0_topic, message);
}

void MQTT::publish_can_frame_1(const char* message){
    _client.publish(can_frame_1_topic, message);
}

void MQTT::publish_can_frame_2(const char* message){
    _client.publish(can_frame_2_topic, message);
}

void MQTT::callback(char* topic, byte* payload, unsigned int length){
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

