#ifndef GPS_CONTROLLER_HPP
#define GPS_CONTROLLER_HPP

#include "common/common_libraries.hpp"
#include "data_processor.hpp"
#include <TinyGPS++.h>
#include <HardwareSerial.h>

class GPSController {
public:
    GPSController();
    void listen();
    void set_data_processor(DataProcessor *data_processor);
    bool gps_data_is_new(float lat, float lng);
    bool satellites_data_is_new(int satellites);

    static void listenTask(void *arg) {
        GPSController *controller = static_cast<GPSController *>(arg);
        controller->listen();
        vTaskDelete(NULL); // Optionally delete the task if listen ever returns
    }

private:
    DataProcessor *_data_processor;
    int _rx_pin = 0; //16
    int _tx_pin = 1; //17
    HardwareSerial _neogps;
    TinyGPSPlus _gps;
    float _last_lat = 0.00;
    float _last_lng = 0.00;
    int _last_satellites = -1;
};

#endif