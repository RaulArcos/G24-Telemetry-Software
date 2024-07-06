/**
 * @file ublox_gps.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the GPS Controller class for NEO-6M GPS Module.
 */

#include "../include/ublox_gps.hpp"

UboxGPS::UboxGPS(): _neogps(1) {
    _neogps.begin(38400, SERIAL_8N1, _rx_pin, _tx_pin);
}

bool UboxGPS::gps_data_is_new(float lat, float lng){
    return lat != _last_lat || lng != _last_lng;
}

bool UboxGPS::satellites_data_is_new(int satellites){
    return satellites != _last_satellites;
}

void UboxGPS::listen(){
    while(true){    
        Serial.println("Listening GPS");
        while (_neogps.available()){
            _gps.encode(_neogps.read());
        }
        if(gps_data_is_new(_gps.location.lat(), _gps.location.lng())){
            _data_processor->send_gps_data(_gps.location.lat(), _gps.location.lng(), _gps.speed.kmph());
            _last_lat = _gps.location.lat();
            _last_lng = _gps.location.lng();
        }
        if(satellites_data_is_new(_gps.satellites.value())){
            _last_satellites = _gps.satellites.value();
            _data_processor->send_satellites_data(_gps.satellites.value());
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }   
}

void UboxGPS::set_data_processor(DataProcessor *data_processor) {
    _data_processor = data_processor;
}
