// /**
//  * @file led_strip.cpp
//  * @author Raúl Arcos Herrera
//  * @brief This file contains the implementation of the LED Strip class for Link G4+ ECU.
//  */ 

// #include "../include/led_strip.hpp"

// void LedStrip::display_warning(int warning){
//     if(warning == STOP_CAR_WARNING){
//         for(int i = 0; i < NUM_PIXELS; i++){
//             _ws2812b.setPixelColor(i, 255, 0, 0);
//         }
//         _ws2812b.show();
//     }
// }

// void LedStrip::set_rpm(int rpm){
//     _rpm = rpm;
// }

// void LedStrip::display_rpm(int rpm) {
//     if (rpm > RPM_MAX) {
//         for (int i = 0; i < NUM_PIXELS; i++) {
//             _ws2812b.setPixelColor(i, _ws2812b.Color(255, 0, 0));
//         }
//         _ws2812b.show();
//         delay(50);
//         for (int i = 0; i < NUM_PIXELS; i++) {
//             _ws2812b.setPixelColor(i, 0);
//         }
//         _ws2812b.show();
//         delay(50);
//     } else {
//         int numLeds = map(rpm, RPM_MIN, RPM_MAX, 0, NUM_PIXELS);

//         for (int i = 0; i < NUM_PIXELS; i++) {
//             if (i < numLeds) {
//                 if (i < NUM_PIXELS / 3) {
//                     _ws2812b.setPixelColor(i, _ws2812b.Color(0, 255, 0));
//                 } else if (i < 2 * NUM_PIXELS / 3) {
//                     _ws2812b.setPixelColor(i, _ws2812b.Color(255, 255, 0));
//                 } else {
//                     _ws2812b.setPixelColor(i, _ws2812b.Color(255, 0, 0));
//                 }
//             } else {
//                 _ws2812b.setPixelColor(i, 0);
//             }
//         }
//         _ws2812b.show();
//     }
// }

// void LedStrip::display_startup(){
//     uint32_t colors[3] = { _ws2812b.Color(255, 0, 0), _ws2812b.Color(0, 255, 0), _ws2812b.Color(0, 0, 255) };

//     for (int pass = 0; pass < 3; pass++) {
//         for (int i = 0; i <= NUM_PIXELS - 4; i++) {
//             _ws2812b.clear();
//             _ws2812b.show();
//             for (int j = 0; j < 4; j++) {
//                 _ws2812b.setPixelColor(i + j, colors[pass]);
//             }
//             _ws2812b.show();
//             delay(10);
//         }

//         for (int i = NUM_PIXELS - 4; i >= 0; i--) {
//             _ws2812b.clear();
//             _ws2812b.show();
//             for (int j = 0; j < 4; j++) {
//                 _ws2812b.setPixelColor(i + j, colors[pass]);
//             }
//             _ws2812b.show();
//             delay(10); 
//         }
//     }
//     _ws2812b.clear();
//     _ws2812b.show();
// }

// void LedStrip::update(){
//     display_rpm(_rpm);
// }

