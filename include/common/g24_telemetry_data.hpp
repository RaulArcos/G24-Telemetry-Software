#ifndef G24_TELEMETRY_DATA_HPP
#define G24_TELEMETRY_DATA_HPP

/**
 * @file g24_telemetry_data.hpp
 * @brief This file contains the definition of the G24TelemetryData struct.
*/

class G24TelemetryData{
    public:
        virtual void setframe(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int g = 0) = 0;
};

class EngineData: public G24TelemetryData{
    public:
        void setframe(int rpmHigh, int rpmLow, int tpsHigh, int tpsLow, int ecthigh, int ectlow, int a = 0){
            
            Serial.println("rpmHigh: " + String(rpmHigh) + " rpmLow: " + String(rpmLow) + " tpsHigh: " + String(tpsHigh) + " tpsLow: " + String(tpsLow) + " ecthigh: " + String(ecthigh) + " ectlow: " + String(ectlow));
            
            _rpm = rpmHigh * 256 + rpmLow;
            _tps = (tpsHigh * 256 + tpsLow);
            _tps = _tps / 10.0;
            _etc = (ecthigh * 256 + ectlow) - 40;
            _etc = _etc / 10.0;
        }
        const int getRPM(){
            return _rpm;
        }
        const double getTPS(){
            return _tps;
        }
        const double getETC(){
            return _etc;
        }
    private:
        int _rpm = 0;
        double _tps = 0.0;
        double _etc = 0;
};

#endif