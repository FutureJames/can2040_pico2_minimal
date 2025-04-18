# Purpose:
This is a minimal build for the rpi Pico1/2 that includes the CANBus library [can2040](https://github.com/KevinOConnor/can2040): 

Tested with a both a [Raspberry Pi](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html) Pico_1 *(2040)* and Pico_2w *(2350)*

Using a [Waveshare SN65HVD230 CAN Board](https://www.waveshare.com/wiki/SN65HVD230_CAN_Board) transceiver (with terminating resistor)

The CAN transceiver lines H and L must be connected to a know good CANBUS for testing.  

## Pin connections:
```
SN65HVD230 pin 3.3v    --->  Pico pin 36 3v3(out)
SN65HVD230 pin GND     --->  Pico pin 3  GND
SN65HVD230 pin CAN_RX  --->  Pico pin 6  GP4
SN65HVD230 pin CAN_TX  --->  Pico pin 7  GP5
```

## Sample Serial Output:
```
Initializing CAN Bus...
Attempting Test Message: DEADBEEF 12345678
Listening on CAN for 500sec...
CAN: tx msg: (id: 2, size: 8, data: efbeadde, 78563412)
CAN: rx msg: (id: 3, size: 8, data: cccccccc, cccccccc)
CAN: rx msg: (id: 3, size: 8, data: aaaaaaaa, aaaaaaaa)
CAN: rx msg: (id: 3, size: 8, data: bbbbbbbb, bbbbbbbb)
```
