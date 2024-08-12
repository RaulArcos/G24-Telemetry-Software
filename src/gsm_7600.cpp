/**
 * @file gsm_7600.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the GSM7600 class.
 */

#include "../include/gsm_7600.hpp"


GSM7600::GSM7600() : _modem(Serial1), _client(_modem), _connected(false) {}

void GSM7600::begin() {
    Serial1.begin(UART_BAUD, SERIAL_8N1, MODEM_RX, MODEM_TX);
    Serial.println("Powering on the modem...");

    pinMode(MODEM_PWRKEY, OUTPUT);
    pinMode(MODEM_FLIGHT, OUTPUT);
    digitalWrite(MODEM_FLIGHT, HIGH);

    modemPowerOn();
    delay(1000);

    Serial.println("Initializing modem...");
    while(!_modem.init()){
        Serial.println("Failed to initialize modem");
        delay(10000);
        if(!_modem.init()){
            modemReset();
        }
    }
    
    print_modem_info();
    connect();
}

void GSM7600::end() {
    modemPowerOff();
}

void GSM7600::connect() {
    Serial.print("Setting network mode to LTE...");
    SerialAT.println("AT+CNMP=51");  // Set to LTE only
    delay(1000);
    String response = "";
    unsigned long startMillis = millis();
    while (millis() - startMillis < 5000) { // Wait up to 5 seconds for a response
        if (SerialAT.available()) {
            response += SerialAT.readStringUntil('\n');
        }
    }
    Serial.print("AT+CNMP=38 response: ");
    Serial.println(response);

    Serial.print("Connecting to network...");
    if (!_modem.waitForNetwork()) {
        Serial.println(" fail");
        return;
    }
    Serial.println(" success");
    if (!_modem.gprsConnect(_apn, "", "")) {
        Serial.println(" fail");
        return;
    }
    Serial.println("GPRS connected");
}

void GSM7600::disconnect() {
    _modem.gprsDisconnect();
    _connected = false;
}

bool GSM7600::is_connected() {
    return _modem.isNetworkConnected() && _modem.isGprsConnected();
}

int GSM7600::get_signal_strength() {
    return _modem.getSignalQuality();
}

void GSM7600::print_modem_info() {
    // Print modem info
    String modemInfo = _modem.getModemInfo();
    Serial.print("Modem: ");
    Serial.println(modemInfo);

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

String GSM7600::get_network_type() {
    // Send AT command to query network registration status
    SerialAT.println("AT+CNMP?");
    delay(100);

    String response = "";
    unsigned long startMillis = millis();
    while (millis() - startMillis < 5000) { // Wait up to 5 seconds for a response
        if (SerialAT.available()) {
            response += SerialAT.readStringUntil('\n');
        }
    }

    Serial.print("AT+CNMP? response: ");
    Serial.println(response);

    int idx = response.indexOf("+CNMP:");
    if (idx != -1) {
        // Extract the relevant part of the response
        response = response.substring(idx);
        Serial.print("Extracted response: ");
        Serial.println(response);

        int networkMode = -1;
        // Example response: +CNMP: 2
        int numFields = sscanf(response.c_str(), "+CNMP: %d", &networkMode);

        if (numFields == 1) {
            switch (networkMode) {
                case 2: return "Automatic";
                case 13: return "GSM Only";
                case 14: return "WCDMA Only";
                case 38: return "LTE Only";
                case 59: return "TDS-CDMA Only";
                case 9: return "CDMA Only";
                case 10: return "EVDO Only";
                case 19: return "GSM+WCDMA";
                case 22: return "CDMA+EVDO";
                case 48: return "Any but LTE";
                case 60: return "GSM+TDSCDMA";
                case 63: return "GSM+WCDMA+TDSCDMA";
                case 67: return "CDMA+EVDO+GSM+WCDMA+TDSCDMA";
                case 39: return "GSM+WCDMA+LTE";
                case 51: return "GSM+LTE";
                case 54: return "WCDMA+LTE";
                default: return "Unknown";
            }
        }
    }
    return "Unknown";
}

bool GSM7600::check_connection() {
    Serial.println("Checking GSM connection...");
    if (!is_network_connected()) {
        Serial.println("Network disconnected, attempting to reconnect...");
        if (!_modem.waitForNetwork()) {
            Serial.println("Failed to reconnect to the network");
            return false;
        }
        Serial.println("Network reconnected");
    }

    if (!is_gprs_connected()) {
        Serial.println("GPRS disconnected, attempting to reconnect...");
        if (!_modem.gprsConnect(_apn, "", "")) {
            Serial.println("Failed to reconnect to GPRS");
            return false;
        }
        Serial.println("GPRS reconnected");
    }
    return true;
}

void GSM7600::modemPowerOn(){
  digitalWrite(MODEM_PWRKEY, HIGH);
  delay(300);
  digitalWrite(MODEM_PWRKEY, LOW);
}

void GSM7600::modemPowerOff(){
  pinMode(MODEM_PWRKEY, OUTPUT);
  digitalWrite(MODEM_PWRKEY, LOW);
  delay(1500);
  digitalWrite(MODEM_PWRKEY, HIGH);
}

void GSM7600::modemReset(){
  modemPowerOn();
  delay(1000);
  modemPowerOff();
}

bool GSM7600::is_network_connected() {
    return _modem.isNetworkConnected();
}

bool GSM7600::is_gprs_connected() {
    return _modem.isGprsConnected();
}