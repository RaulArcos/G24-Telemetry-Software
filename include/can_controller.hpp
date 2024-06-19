#ifndef CANCONTROLLER_HPP
#define CANCONTROLLER_HPP

#define RX_PIN 16
#define TX_PIN 17
#define POLLING_RATE_MS 10
#define TRANSMIT_RATE_MS 10

#include "driver/twai.h"
#include "common/common_libraries.hpp"
#include "data_processor.hpp"
#include "common/g24_telemetry_data.hpp"

class CANController {
public:
    CANController() = default;
    ~CANController();
    void start();
    void listen();
    void send_frame(twai_message_t message);
    twai_message_t createBoolMessage(bool b0, bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7);

    void set_data_proccessor(DataProcessor *data_processor){
        _data_processor = data_processor;
    }

    static void listenTask(void *arg) {
        CANController *controller = static_cast<CANController *>(arg);
        controller->listen();
        vTaskDelete(NULL); // Optionally delete the task if listen ever returns
    }

private:
    twai_message_t _rx_message;
    DataProcessor *_data_processor;
};

#endif