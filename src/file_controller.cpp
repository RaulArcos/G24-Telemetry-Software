/**
 * @file file_controller.cpp
 * @author Raúl Arcos Herrera
 * @brief This file contains the implementation of the File Controller for AWS - G24 Telemetry.
 */

#include "../include/file_controller.hpp"

FileController::FileController(){
    _isInitialized = false;
}

bool FileController::init(){
    if(!_isInitialized){
        if(SPIFFS.begin()){
            _isInitialized = true;
            return true;
        }
    }
    return false;
}

bool FileController::write(const char* filename, const char* message){
    if(_isInitialized){
        File file = SPIFFS.open(filename, FILE_WRITE);
        if(!file){
            return false;
        }
        if(file.print(message)){
            file.close();
            return true;
        }
        file.close();
    }
    return false;
}

bool FileController::read(const char* filename, char* message){
    if(_isInitialized){
        File file = SPIFFS.open(filename, FILE_READ);
        if(!file){
            return false;
        }
        if(file.available()){
            file.readBytes(message, file.size());
            file.close();
            return true;
        }
        file.close();
    }
    return false;
}

bool FileController::remove(const char* filename){
    if(_isInitialized){
        if(SPIFFS.remove(filename)){
            return true;
        }
    }
    return false;
}

bool FileController::exists(const char* filename){
    if(_isInitialized){
        if(SPIFFS.exists(filename)){
            return true;
        }
    }
    return false;
}

bool FileController::list(){
    if(_isInitialized){
        File root = SPIFFS.open("/");
        File file = root.openNextFile();
        while(file){
            Serial.print(file.name());
            Serial.print(" - ");
            Serial.println(file.size());
            file = root.openNextFile();
        }
        return true;
    }
    return false;
}

bool FileController::format(){
    if(_isInitialized){
        if(SPIFFS.format()){
            _isInitialized = false;
            return true;
        }
    }
    return false;
}