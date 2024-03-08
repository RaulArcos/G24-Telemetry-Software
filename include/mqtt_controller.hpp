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

private:
    const char* _mqtt_server = "a3gqsinr6fjc3h-ats.iot.us-west-2.amazonaws.com";
    const int _mqtt_port = 8883;
    WiFiClientSecure _espClient;
    PubSubClient _client = PubSubClient(_espClient);
    AWSCertificates _awsCertificates;
};

#endif