/**
 * @file can_controller.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the CAN Controller class for Link G4+ ECU.
 */

#include "../include/can_controller.hpp"

CANController::CANController(){
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    esp_err_t install_status = twai_driver_install(&g_config, &t_config, &f_config);
    if (install_status != ESP_OK) {
        Serial.println("Failed to install TWAI driver");
        return;
    }

    esp_err_t start_status = twai_start();
    if (start_status != ESP_OK) {
        Serial.println("Failed to start TWAI driver");
        return;
    }
}

CANController::~CANController(){
    twai_stop();
    twai_driver_uninstall();
}

void CANController::listen(){
    while(true){
        if(twai_receive(&_rx_message, pdMS_TO_TICKS(POLLING_RATE_MS)) == ESP_OK){
            Serial.printf("ID: %x\nByte:", _rx_message.identifier);
            if (!(_rx_message.rtr)) {
                for (int i = 0; i < _rx_message.data_length_code; i++) {
                Serial.printf(" %d = %02x,", i, _rx_message.data[i]);
                }
            }
            Serial.println("");

            switch(_rx_message.identifier){
                case 1:
                    _engdata.setframe(_rx_message.data[0], _rx_message.data[1], _rx_message.data[2], _rx_message.data[3], _rx_message.data[4], _rx_message.data[5]);
                    Serial.println("Engine Data Received");
                    break;
                default:
                    break;
            }
        }
        delay(10);
    }
}