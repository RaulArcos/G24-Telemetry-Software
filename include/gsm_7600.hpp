#ifndef GSMCONTROLLER_HPP
#define GSMCONTROLLER_HPP

#define TINY_GSM_MODEM_SIM7600
#define TINY_GSM_RX_BUFFER 1024
#include <TinyGsmClient.h>

#define SerialAT Serial1
#define TINY_GSM_DEBUG Serial

#define TINY_GSM_USE_GPRS true

// set GSM PIN, if any
#define GSM_PIN ""

#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  60 

#define UART_BAUD   115200
#define MODEM_DTR     25
#define MODEM_TX      27
#define MODEM_RX      26
#define MODEM_PWRKEY  4
#define MODEM_DTR     32
#define MODEM_RI      33
#define MODEM_FLIGHT  25
#define MODEM_STATUS  34

class GSM7600 {
public:
    GSM7600(): _modem(SerialAT), _client(_modem) {};
    void begin();
    void modemPowerOn();
    void modemPowerOff();
    void modemReset();
    void check_connection();
    TinyGsmClient* get_client() { return &_client; }
    void print_network_info();

private:
    const char* _apn = "airtelwap.es";
    const char* _gprsUser = "";
    const char* _gprsPass = "";
    TinyGsm _modem;
    TinyGsmClient _client;
    uint32_t lastReconnectAttempt = 0;
    String get_network_type();
};

#endif
