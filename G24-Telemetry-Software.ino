#include "include/can_controller.hpp"
#include "include/lte_controller.hpp"
#include "include/wifi_controller.hpp"
#include "include/data_processor.hpp"
#include "include/mqtt_controller.hpp"

WifiController wifiController("FormulaGades", "g24evo24");

void setup() {
    Serial.begin(115200);
    Serial.println("G24::WifiController - Attempting Wifi Conection...");
    if(wifiController.connect()){
        Serial.println("G24::WifiController - Connected to WiFi!");
    }else{
        Serial.println("G24::WifiController - Failed to connect to WiFi! Timeout!");
    }

}

void loop() {

}