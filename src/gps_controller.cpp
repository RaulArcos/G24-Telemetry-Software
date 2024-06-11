/**
 * @file gps_controller.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the GPS Controller class for NEO-6M GPS Module.
 */

#include "../include/gps_controller.hpp"

GPSController::GPSController(int rx_pin, int tx_pin): _rx_pin(rx_pin), _tx_pin(tx_pin), _neogps(1) {
    _neogps.begin(9600, SERIAL_8N1, rx_pin, tx_pin);
}

void GPSController::listen() {
    while(true){
        bool newData = false;
        while (_neogps.available()){
            if (_gps.encode(_neogps.read())){
                newData = true;         
            }
        }

        if(newData == true){
            newData = false;
            _data_processor->send_gps_data(_gps.location.lat(), _gps.location.lng(), _gps.speed.kmph());
        }
        _data_processor->send_satellites_data(_gps.satellites.value());
        delay(100);
    }  
    
}

void GPSController::set_data_processor(DataProcessor *data_processor) {
    _data_processor = data_processor;
}
