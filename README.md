This is a minimal build for the rpi Pico1/2 that includes the CANBus library: https://github.com/KevinOConnor/can2040

Tested with a RPi Pico_1 and Pico_2w

Using a Waveshare SN65HVD230 CAN Board tranciever (with terminating resistor)

Pin connections:

SN65HVD230 pin 3.3v    --->  Pico pin 36 3v3(out)
SN65HVD230 pin GND     --->  Pico pin 3  GND
SN65HVD230 pin CAN_RX  --->  Pico pin 6  GP4
SN65HVD230 pin CAN_TX  --->  Pico pin 7  GP5

Sample Serial Output:

Initializing CAN Bus...
Attempting Test Message: DEADBEEF 12345678
Listening on CAN for 500sec...
CAN: tx msg: (id: 2, size: 8, data: efbeadde, 78563412)
CAN: rx msg: (id: 3, size: 8, data: cccccccc, cccccccc)
CAN: rx msg: (id: 3, size: 8, data: aaaaaaaa, aaaaaaaa)
CAN: rx msg: (id: 3, size: 8, data: bbbbbbbb, bbbbbbbb)