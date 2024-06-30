/**
 * @file gsm_controller.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the LTE Controller for G24 Telemetry.
 */

#include "../include/gsm_controller.hpp"
#include <string>

void GSMController::begin() {
    delay(10);
    modemPowerOn();

    pinMode(MODEM_FLIGHT, OUTPUT);
    digitalWrite(MODEM_FLIGHT, HIGH);

    if (!_modem.init()) {
        Serial.println("Failed to initialize modem");
        return;
    }

    String ret;
    ret = _modem.setNetworkMode(2);
    Serial.println("setNetworkMode:" + ret);

    String name = _modem.getModemName();
    Serial.println("Modem Name:" + name);

    String modemInfo = _modem.getModemInfo();
    Serial.println("Modem Info:" + modemInfo);

    if (GSM_PIN && _modem.getSimStatus() != 3) {
        _modem.simUnlock(GSM_PIN);
    }
    
    Serial.print("Waiting for network...");
    if (!_modem.waitForNetwork()) {
        Serial.println(" fail");
        delay(10000);
        return;
    }
    Serial.println(" success");

    if (_modem.isNetworkConnected()) {
        Serial.println("Network connected");
    }

    Serial.print(F("Connecting to "));
    Serial.print(_apn);
    if (!_modem.gprsConnect(_apn, _gprsUser, _gprsPass)) {
        Serial.println(" fail");
        delay(10000);
        return;
    }
    Serial.println(" success");

    if (_modem.isGprsConnected()) {
        Serial.println("GPRS connected");
    }
}

void GSMController::check_connection() {
    if (!_modem.isNetworkConnected()) {
        Serial.println("Network disconnected");
        if (!_modem.waitForNetwork(180000L, true)) {
            Serial.println(" fail");
            delay(10000);
            return;
        }
        if (_modem.isNetworkConnected()) {
            Serial.println("Network re-connected");
        }
        // and make sure GPRS/EPS is still connected
        if (!_modem.isGprsConnected()) {
            Serial.println("GPRS disconnected!");
            Serial.print(F("Connecting to "));
            Serial.print(_apn);
            if (!_modem.gprsConnect(_apn, _gprsUser, _gprsPass)) {
                Serial.println(" fail");
                delay(10000);
                return;
            }
            if (_modem.isGprsConnected()) {
                Serial.println("GPRS reconnected");
            }
        }
    }
}

void GSMController::print_network_info() {
    // Print signal quality
    int csq = _modem.getSignalQuality();
    Serial.print("Signal quality: ");
    Serial.println(csq);

    // Print network type
    String netType = get_network_type();
    Serial.print("Network type: ");
    Serial.println(netType);

    // Additional information about the network can be printed here if needed
}

String GSMController::get_network_type() {
    // Send AT command to query network registration status
    SerialAT.println("AT+COPS?");
    delay(100);
    
    String response = "";
    while (SerialAT.available()) {
        response += SerialAT.readStringUntil('\n');
    }

    Serial.print("AT+COPS? response: ");
    Serial.println(response);

    int idx = response.indexOf("+COPS:");
    if (idx != -1) {
        // Extract the relevant part of the response
        response = response.substring(idx);
        Serial.print("Extracted response: ");
        Serial.println(response);

        int commaIdx = response.lastIndexOf(',');
        if (commaIdx != -1 && commaIdx + 1 < response.length()) {
            int type = response.charAt(commaIdx + 1) - '0';
            switch (type) {
                case 0: return "GSM";
                case 1: return "GSM Compact";
                case 2: return "UTRAN";
                case 3: return "GSM w/EGPRS";
                case 4: return "UTRAN w/HSDPA";
                case 5: return "UTRAN w/HSUPA";
                case 6: return "UTRAN w/HSDPA and HSUPA";
                case 7: return "E-UTRAN";
                default: return "Unknown";
            }
        }
    }
    return "Unknown";
}

void GSMController::modemPowerOn(){
  pinMode(MODEM_PWRKEY, OUTPUT);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(1000);
  digitalWrite(MODEM_PWRKEY, HIGH);
}

void GSMController::modemPowerOff(){
  pinMode(MODEM_PWRKEY, OUTPUT);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(1500);
  digitalWrite(MODEM_PWRKEY, HIGH);
}

void GSMController::modemReset(){
  modemPowerOn();
  delay(1000);
  modemPowerOff();
}


