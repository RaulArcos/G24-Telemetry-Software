#ifndef DATAPROCESSOR_HPP
#define DATAPROCESSOR_HPP

#include "common/common_libraries.hpp"

class DataProcessor {
public:
    DataProcessor() = default;
    char* process(std::vector<float> data);
};

#endif