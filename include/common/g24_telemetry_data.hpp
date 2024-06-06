#ifndef G24_TELEMETRY_DATA_HPP
#define G24_TELEMETRY_DATA_HPP

/**
 * @file g24_telemetry_data.hpp
 * @brief This file contains the definition of the G24TelemetryData struct.
*/

class EngineData{
    public:
        void setframe1(int rpmHigh, int rpmLow, int tpsHigh, int tpsLow, int maphigh, int maplow, int d4){
            _rpm = rpmHigh * 256 + rpmLow;
            _tps = (tpsHigh * 256 + tpsLow);
            _map = (maphigh * 256 + maplow);
            _d4 = d4;
        }
        void setframe2(int d1, int d2, int d3, int lambdatargethigh, int lambdatargetlow, int lambdahigh, int lambdalow){
            _d1 = d1;
            _d2 = d2;
            _d3 = d3;
            _lambdatarget = (lambdatargethigh * 256 + lambdatargetlow);
            _lambda = (lambdahigh * 256 + lambdalow);
            _lambda = _lambda / 1000;
        }
        const int getRPM(){
            return _rpm;
        }
        const double getTPS(){
            return _tps;
        }
        const double getMAP(){
            return _map;
        }
        const double getLambdaTarget(){
            return _lambdatarget;
        }
        const double getLambda(){
            return _lambda;
        }
        const bool getD1(){
            return _d1;
        }
        const bool getD2(){
            return _d2;
        }
        const bool getD3(){
            return _d3;
        }
        const bool getD4(){
            return _d4;
        }

    private:
        int _rpm = 0;
        double _tps = 0.0;
        double _map = 0.0;
        double _lambdatarget = 0.0;
        double _lambda = 0.0;
        bool _d1 = false;
        bool _d2 = false;
        bool _d3 = false;
        bool _d4 = false;
};

class BattWheelSpeedData{
    public:
        void setframe1(int battvoltHigh, int battvoltLow, int lfwsHigh, int lfwsLow, int rfwsHigh, int rfwsLow){
            _batt_volt = (battvoltHigh * 256 + battvoltLow);
            _batt_volt = _batt_volt / 100;
            _lf_ws = (lfwsHigh * 256 + lfwsLow);
            _rf_ws = (rfwsHigh * 256 + rfwsLow);
        }
        void setframe2(int lrwsHigh, int lrwsLow, int rrwsHigh, int rrwsLow){
            _lr_ws = (lrwsHigh * 256 + lrwsLow);
            _rr_ws = (rrwsHigh * 256 + rrwsLow);
        }
        const double getBattVolt(){
            return _batt_volt;
        }
        const double getLFWS(){
            return _lf_ws;
        }
        const double getLRWS(){
            return _lr_ws;
        }
        const double getRFWS(){
            return _rf_ws;
        }
        const double getRRWS(){
            return _rr_ws;
        }

    private:
        double _batt_volt = 0.0;
        double _lf_ws = 0.0;
        double _lr_ws = 0.0;
        double _rf_ws = 0.0;
        double _rr_ws = 0.0;
};

class TempGearData{
    public: 
        void setframe1(int iatHigh, int iatLow, int ectHigh, int ectLow, int gear){
            _iat = (iatHigh * 256 + iatLow);
            _ect = (ectHigh * 256 + ectLow);
            _gear = gear;
        }
        const double getIAT(){
            return _iat;
        }
        const double getECT(){
            return _ect;
        }
        const int getGear(){
            return _gear;
        }
    private:
        double _iat = 0.0;
        double _ect = 0.0;
        int _gear = 0;
};

#endif