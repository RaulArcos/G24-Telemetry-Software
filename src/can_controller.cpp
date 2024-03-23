/**
 * @file can_controller.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the CAN Controller class for Link G4+ ECU.
 */

#include "../include/can_controller.hpp"

CANController::CANController(){
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)RX_PIN, (gpio_num_t)TX_PIN, TWAI_MODE_LISTEN_ONLY);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
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
            switch(_rx_message.identifier){
                case 1:
                    _data.RPM = (_rx_message.data[3] * 256 + _rx_message.data[4]) / 4;
                    Serial.println(_data.RPM);
                    break;
                case 2:
                    _data.TPS = _rx_message.data[3] * 100 / 255;
                    _data.MAP = _rx_message.data[4] * 100 / 255;
                    _data.IAT = _rx_message.data[5] - 40;
                    _data.BAT = _rx_message.data[6] / 2;
                    _data.ECT = _rx_message.data[7] - 40;
                    break;
                default:
                    break;
            }
        }
    }
}