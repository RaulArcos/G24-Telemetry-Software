#include <stdint.h>
#include <string>

class Color {
public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Color(uint8_t r, uint8_t g, uint8_t b) 
        : red(r), green(g), blue(b) {}

    Color(const std::string &hexCode) {
        if (hexCode[0] == '#') {
            red = static_cast<uint8_t>(std::stoi(hexCode.substr(1, 2), nullptr, 16));
            green = static_cast<uint8_t>(std::stoi(hexCode.substr(3, 2), nullptr, 16));
            blue = static_cast<uint8_t>(std::stoi(hexCode.substr(5, 2), nullptr, 16));
        } else {
            red = green = blue = 0;
        }
    }

    uint32_t toInt() const {
        return (red << 16) | (green << 8) | blue;
    }

    std::string toHex() const {
        char hex[8];
        snprintf(hex, sizeof(hex), "#%02X%02X%02X", red, green, blue);
        return std::string(hex);
    }
};
