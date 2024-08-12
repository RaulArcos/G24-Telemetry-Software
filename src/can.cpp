/**
 * @file can.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the CAN Controller class for Link G4+ ECU.
 */

#include "../include/can.hpp"

void CAN::start(){
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)TX_PIN, (gpio_num_t)RX_PIN, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_125KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    esp_err_t install_status = twai_driver_install(&g_config, &t_config, &f_config);
    if (install_status != ESP_OK) {
        Serial.println("Failed to install TWAI driver");
        return;
    }else{
        Serial.println("TWAI driver installed");
    }

    esp_err_t start_status = twai_start();
    if (start_status != ESP_OK) {
        Serial.println("Failed to start TWAI driver");
        return;
    }else{
        Serial.println("TWAI driver started");
    }
}

CAN::~CAN(){
    twai_stop();
    twai_driver_uninstall();
}

void CAN::send_frame(twai_message_t message){
    twai_transmit(&message, pdMS_TO_TICKS(TRANSMIT_RATE_MS));
}

twai_message_t CAN::createBoolMessage(bool b0, bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7){
    twai_message_t message;
    memset(&message, 0, sizeof(message)); 
    message.identifier = 0x001;
    message.data[0] = (b7 << 7) | (b6 << 6) | (b5 << 5) | (b4 << 4) |
                      (b3 << 3) | (b2 << 2) | (b1 << 1) | b0;
    message.data_length_code = 8;
    message.flags = TWAI_MSG_FLAG_NONE; 
    return message;
}
void CAN::listen(){
    esp_err_t result = twai_receive(&_rx_message, pdMS_TO_TICKS(POLLING_RATE_MS));
    if (result == ESP_OK) {
        // Check if the frame is not all zeros
        bool is_all_zero = true;
        for (int i = 0; i < _rx_message.data_length_code; i++) {
            if (_rx_message.data[i] != 0) {
                is_all_zero = false;
                break;
            }
        }

        if (!is_all_zero) {
            // Serial.print("Received: ");
            // for (int i = 0; i < _rx_message.data_length_code; i++) {
            //     Serial.print(_rx_message.data[i]);
            //     Serial.print(" ");
            // }
            // Serial.println();

            // switch (_rx_message.data[0]) {
            //     case 0:
            //         _data_processor->send_frame_0(_rx_message.data[1], _rx_message.data[2], _rx_message.data[3], _rx_message.data[4], _rx_message.data[5], _rx_message.data[6], _rx_message.data[7]);
            //         break;
            //     case 1:
            //         _data_processor->send_frame_1(_rx_message.data[1], _rx_message.data[2], _rx_message.data[3], _rx_message.data[4], _rx_message.data[5], _rx_message.data[6], _rx_message.data[7]);
            //         break;
            //     case 2:
            //         _data_processor->send_frame_2(_rx_message.data[1], _rx_message.data[2], _rx_message.data[3], _rx_message.data[4], _rx_message.data[5], _rx_message.data[6], _rx_message.data[7]);
            //         break;
            //     default:
            //         Serial.println("Unknown frame type");
            //         break;
            // }
        }
    } else {
        Serial.println("Error receiving CAN frame");
    }
}
