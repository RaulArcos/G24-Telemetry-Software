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
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["rpm"] = i;
    doc["tps"] = j;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_test(buffer);
    delay(40);
    xSemaphoreGive(_mqtt_mutex);
}

void DataProcessor::send_gps_data(float lat, float lng, float speed){
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
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
    xSemaphoreGive(_mqtt_mutex);
}

void DataProcessor::send_satellites_data(int satellites){
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["satellites"] = satellites;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_satellites(buffer);
    xSemaphoreGive(_mqtt_mutex);
}

void DataProcessor::send_frame1(int rpmHigh, int rpmLow, int tpsHigh, int tpsLow, int maphigh, int maplow, int d4){
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["rpm"] = rpmHigh * 256 + rpmLow;
    doc["tps"] = (tpsHigh * 256 + tpsLow);
    doc["map"] = (maphigh * 256 + maplow);
    doc["d4"] = d4;
    char buffer[256];
    serializeJson(doc, buffer);
    // _mqtt_controller->publish_frame1(buffer);
    xSemaphoreGive(_mqtt_mutex);
}

void DataProcessor::send_frame2(int d1, int d2, int d3, int lambdatargethigh, int lambdatargetlow, int lambdahigh, int lambdalow){
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["d1"] = d1;
    doc["d2"] = d2;
    doc["d3"] = d3;
    doc["lambdatarget"] = (lambdatargethigh * 256 + lambdatargetlow);
    doc["lambda"] = (lambdahigh * 256 + lambdalow) / 1000;
    char buffer[256];
    serializeJson(doc, buffer);
    // _mqtt_controller->publish_frame2(buffer);
    xSemaphoreGive(_mqtt_mutex);
}