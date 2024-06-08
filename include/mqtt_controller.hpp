#ifndef MQTTCONTROLLER_HPP
#define MQTTCONTROLLER_HPP

#include "common/common_libraries.hpp"
#include <PubSubClient.h>
#include <WiFiClient.h>

class MQTTController {
public:
    MQTTController();
    void connect();
    static void callback(char* topic, byte* payload, unsigned int length);
    void set_callback(std::function<void(char*, byte*, unsigned int)> func);
    void publish_telemetry(const char* topic, const char* message);
    void publish_test(const char* message);
    PubSubClient* get_client();

    const char* test_topic = "G24/telemetry/test";

private:
    const char* _mqtt_server = "broker.hivemq.com";
    const int _mqtt_port = 1883;
    WiFiClient _espClient;
    PubSubClient _client = PubSubClient(_espClient);
};

#endif