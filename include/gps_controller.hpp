#ifndef GPS_CONTROLLER_HPP
#define GPS_CONTROLLER_HPP

#include "common/common_libraries.hpp"
#include "data_processor.hpp"
#include <TinyGPS++.h>
#include <HardwareSerial.h>

class GPSController {
public:
    GPSController(int rx_pin, int tx_pin);
    void listen();
    void set_data_processor(DataProcessor *data_processor);

    static void listenTask(void *arg) {
        GPSController *controller = static_cast<GPSController *>(arg);
        controller->listen();
        vTaskDelete(NULL); // Optionally delete the task if listen ever returns
    }

private:
    DataProcessor *_data_processor;
    int _rx_pin;
    int _tx_pin;
    HardwareSerial _neogps;
    TinyGPSPlus _gps;
    bool _new_data = false;
};

#endif