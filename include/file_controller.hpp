#ifndef FILE_CONTROLLER_HPP
#define FILE_CONTROLLER_HPP

#include "SPIFFS.h"
class FileController {
public:
    FileController();
    bool init();
    bool write(const char* filename, const char* message);
    bool read(const char* filename, char* message);
    bool remove(const char* filename);
    bool exists(const char* filename);
    bool list();
    bool format();
private:
    bool _isInitialized;
};


#endif

