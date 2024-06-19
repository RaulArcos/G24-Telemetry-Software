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

void DataProcessor::send_frame_0(int rpmh, int rpml, int tpsh, int tpsl, int brkh, int brkl, int gear){
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["rpm"] = (rpmh * 256) + rpml;
    doc["tps"] = (tpsh * 256) + tpsl;
    doc["brk"] = (brkh * 256) + brkl;
    doc["gear"] = gear;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_can_frame_0(buffer);
    xSemaphoreGive(_mqtt_mutex);
}

void DataProcessor::send_frame_1(int lfws, int rfws, int lrws, int rrws, int maph, int mapl, int ect){
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["lfws"] = lfws;
    doc["rfws"] = rfws;
    doc["lrws"] = lrws;
    doc["rrws"] = rrws;
    doc["map"] = (maph * 256) + mapl;
    doc["ect"] = ect;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_can_frame_1(buffer);
    xSemaphoreGive(_mqtt_mutex);
}

void DataProcessor::send_frame_2(int lambh, int lambl, int lamth, int lamtl, int bvolth, int bvoltl, int iat){
    xSemaphoreTake(_mqtt_mutex, portMAX_DELAY);
    if(!_mqttClient->connected()){
        return;
    }
    StaticJsonDocument<200> doc;
    doc["lamb"] = (lambh * 256) + lambl;
    doc["lamt"] = (lamth * 256) + lamtl;
    doc["bvol"] = (bvolth * 256) + bvoltl;
    doc["iat"] = iat;
    char buffer[256];
    serializeJson(doc, buffer);
    _mqtt_controller->publish_can_frame_2(buffer);
    xSemaphoreGive(_mqtt_mutex);
}