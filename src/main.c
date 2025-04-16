
#include "pico/stdlib.h"
#include <stdbool.h>

//Minimal includes for CAN2040 
#include <stdio.h>
#include "can2040.h"

// Determine if the target is an rp2350
#ifdef PICO_RP2350
  #include "RP2350.h"
#else
  #include "RP2040.h"
#endif

#define CAN_GPIO_RX 10
#define CAN_GPIO_TX 11

static struct can2040 cbus;

static void
can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
    // Add message processing code here...
    printf("CAN message received: ID=0x%03X, DLC=%d, Data=", msg->id, msg->dlc);
}

static void
PIOx_IRQHandler(void)
{
    can2040_pio_irq_handler(&cbus);
}

void
canbus_setup(void)
{
    uint32_t pio_num = 0;
    uint32_t sys_clock = 125000000, bitrate = 500000;
    uint32_t gpio_rx = 4, gpio_tx = 5;

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIOx_IRQHandler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
}

int main()
{
    stdio_init_all();
    canbus_setup();
}