#ifndef CANCONTROLLER_HPP
#define CANCONTROLLER_HPP

#define RX_PIN 5
#define TX_PIN 4
#define POLLING_RATE_MS 100

#include "driver/twai.h"
#include "common/common_libraries.hpp"
#include "common/g24_telemetry_data.hpp"

class CANController {
public:
    CANController();
    ~CANController();
    void listen();

    static void listenTask(void *arg) {
        CANController *controller = static_cast<CANController *>(arg);
        controller->listen();
        vTaskDelete(NULL); // Optionally delete the task if listen ever returns
    }

    const EngineData getEngineData(){
        return _engdata;
    }
    
private:
    EngineData _engdata;
    twai_message_t _rx_message;
};

#endif