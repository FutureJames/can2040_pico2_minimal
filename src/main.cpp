//  Import in C mode to avoid C++ name mangling
extern "C" {
  #include "can2040.h"
}

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

// Determine if the target is an rp2350
#ifdef PICO_RP2350
  #include "RP2350.h"
#else
  #include "RP2040.h"
#endif

static uint32_t pio_num = 0;
static uint32_t irq_num = 1;
static uint32_t bitrate = 500000;
static uint32_t gpio_rx = 4;
static uint32_t gpio_tx = 5;

static struct can2040 cbus;

//Callback to handle messages
static void can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
    char buffer[128];
    if (notify == CAN2040_NOTIFY_RX){   
      snprintf(buffer, sizeof(buffer), "CAN: rx msg: (id: %0x, size: %0x, data: %0x, %0x)\n", msg->id & 0x7ff, msg->dlc, msg->data32[0], msg->data32[1]);
      printf("%s", buffer);
    } else if (notify == CAN2040_NOTIFY_TX) {
      snprintf(buffer, sizeof(buffer), "CAN: tx msg: (id: %0x, size: %0x, data: %0x, %0x)\n", msg->id & 0x7ff, msg->dlc, msg->data32[0], msg->data32[1]);
      printf("%s", buffer); 
    } else if (notify & CAN2040_NOTIFY_ERROR) {
      //For some reason printing a serial message here causes a crash
      return;
    }
}

static void PIOx_IRQHandler(void){
    can2040_pio_irq_handler(&cbus);
}

void canbus_setup(void){
    // get the actual system clock frequency dynamically 
    //  to account for overclocking.
    // pico1 = 125000000
    // pico2 = 150000000
    uint32_t sys_clock = clock_get_hz(clk_sys);

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIOx_IRQHandler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, irq_num);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
}

int main(){
  //Needed for printf
  stdio_init_all();

  printf("Initializing CAN Bus...\n"); 
  canbus_setup();

  // Set up a test message to send
  can2040_msg msg = {
    .id = (uint32_t)(0xDEADBEEF | CAN2040_ID_EFF),
    .dlc = 8,
    .data32 = {
            0xEFBEADDE,
            0x78563412
    }
  };

  printf("Attempting Test Message: DEADBEEF 12345678\n");
  can2040_transmit(&cbus, &msg);

  // While the system sleeps, the IRQ handler will be called
  printf("Listening on CAN for 500sec...\n");
  sleep_ms(500000);
  printf("Exiting...\n");
  can2040_stop(&cbus);
  return 0;
}