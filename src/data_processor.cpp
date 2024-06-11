/**
 * @file data_processor.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the Data Processor class for Link G4+ ECU.
 */

#include "../include/data_processor.hpp"

char* DataProcessor::process(std::vector<float> data){
    String payload = "";
    StaticJsonDocument<200> doc;

    doc["timestamp"] = millis();
    doc["device_id"] = "G24";
    doc["RPM"] = data[0];

    serializeJson(doc, payload);

    return (char*)payload.c_str();
}

void DataProcessor::set_mqtt_controller(MQTTController *mqtt_controller){
    _mqtt_controller = mqtt_controller;
    _mqttClient = _mqtt_controller->get_client();
}

void DataProcessor::test(int i, int j){
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["rpm"] = i;
    doc["tps"] = j;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_test(buffer);
}

void DataProcessor::send_gps_data(float lat, float lng, float speed){
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["lat"] = lat;
    doc["lng"] = lng;
    doc["speed"] = speed;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_gps(buffer);
}

void DataProcessor::send_satellites_data(int satellites){
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["satellites"] = satellites;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_satellites(buffer);
}