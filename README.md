# G24 Telemetry Software
This is the telemetry code for the 2024 University of Cádiz Formula Student Car that participated both in FSAustria and FSSpain.
It consist of a simple implementation using  a ESP32 with a LTE SIM Module integrated (T-SIM7600E/G-H), which takes data from diferent sensors, including using CAN Bus for taking in engine data from the Link G4+ ECU.

![pako_eNqlV2tvqzYY_isWHyZORquQ5tKiqtJ2Kp2jaZ2yk-7LFAkZcMCrsZlt2mZV99vPiw0UCKmWLh-Sx4_fi-33YufFiUVCnMCJGVbqluJU4nzLEXwSKkmsqeDo12-WMTLo80-_oRdLVJ8fYex-6oz_HRKPgiZIaSz1Ic2o0oSPiBOehDtYC3H1E6ZhTpTCKQk1qlFXYyARS4I1-VkId](https://github.com/user-attachments/assets/459de471-667c-440c-a6e2-6e0f136251b8)

For sending the data outside, it uses MQTT to send messages to a NodeRED service that came handy to implement an easy and scalable web interface that able this project to watch live telemetry.

https://github.com/user-attachments/assets/b691ba97-b2c0-4a9c-93ff-64290d17f69a
