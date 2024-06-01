#ifndef MQTTCONTROLLER_HPP
#define MQTTCONTROLLER_HPP

#include "common/common_libraries.hpp"
#include "common/aws_certificates.hpp"
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

class MQTTController {
public:
    MQTTController();
    void connect();
    static void callback(char* topic, byte* payload, unsigned int length);
    void publish_telemetry(const char* topic, const char* message);

private:
    const char* _mqtt_server = "broker.hivemq.com";
    const int _mqtt_port = 1883;
    WiFiClient _espClient;
    PubSubClient _client = PubSubClient(_espClient);
    AWSCertificates _awsCertificates;
};

#endif