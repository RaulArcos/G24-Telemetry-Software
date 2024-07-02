#ifndef GSMCONTROLLER_HPP
#define GSMCONTROLLER_HPP

#include "common/lilygo_sim7600_params.hpp"

#define TINY_GSM_YIELD_MS 2
#define TINY_GSM_MODEM_SIM7600
#define TINY_GSM_RX_BUFFER 1024
#define SerialAT Serial1
#define TINY_GSM_USE_GPRS true

#include <TinyGsmClient.h>

class GSM7600 {
public:
    GSM7600();
    void begin();
    void end();
    void connect();
    void disconnect();
    bool is_connected();
    bool is_network_connected();
    bool is_gprs_connected();
    bool check_connection();
    int get_signal_strength();
    TinyGsmClient* get_client() { return &_client;}

private:
    const char* _apn = "airtelwap.es";
    const char* _gprsUser = "";
    const char* _gprsPass = "";
    TinyGsm _modem;
    TinyGsmClient _client;
    uint32_t lastReconnectAttempt = 0;
    String get_network_type();
    bool _connected;
    void modemPowerOn();
    void modemPowerOff();
    void modemReset();
    void print_modem_info();
};

#endif
