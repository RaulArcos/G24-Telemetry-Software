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
}