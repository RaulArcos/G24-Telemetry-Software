// #ifndef LED_STRIP_HPP
// #define LED_STRIP_HPP

// #include <Adafruit_NeoPixel.h>
// #include "common/color.hpp"

// #define STOP_CAR_WARNING 1

// #define RPM_MIN 6000
// #define RPM_MAX 11000

// class LedStrip{
// public:
//     LedStrip(int pin, int num_pixel): _ws2812b(num_pixel, pin, NEO_GRB + NEO_KHZ800), _warning(0), _brightness(255)  {}

//     static void updateTask(void *arg) {
//         LedStrip *ledStrip = static_cast<LedStrip*>(arg);
//         ledStrip->update();
//         vTaskDelete(NULL);
//     }

//     void update();

//     void set_rpm(int rpm);

//     void begin(){
//         _ws2812b.begin();
//     }   

//     void set_brightness(uint8_t brightness) {
//         _ws2812b.setBrightness(brightness);
//         _ws2812b.show();
//     }

//     void display_warning(int warning);
//     void display_rpm(int rpm);
//     void display_startup();

// private:
//     Adafruit_NeoPixel _ws2812b;
//     std::vector<Color> _colors;
//     int _rpm;
//     int _warning;
//     int _brightness;
// };

// #endif