
#include <stdio.h>
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define PIN22        22u
#define PIN06        6u
#define CLOCK_K64 (21000000U)
#define DELAY (1000000U)

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };



int main(void) {

	CLOCK_EnableClock(kCLOCK_PortB);//SIM->SCGC5 = 0x400;
	CLOCK_EnableClock(kCLOCK_PortC);

	 PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio); //PORTB->PCR[22] = 0x00000100;
	 PORT_SetPinMux(PORTC, PIN06, kPORT_MuxAsGpio);

	 GPIO_PinInit(GPIOB, PIN22, &led_config);
	 GPIO_PinInit(GPIOC, PIN06, &sw_config);


    while(1) {

	if (! GPIO_PinRead(GPIOC, PIN06))
		{
			GPIO_PortClear(GPIOB, 1u << PIN22);
			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
  			GPIO_PortSet(GPIOB, 1u << PIN22);
  			SDK_DelayAtLeastUs(DELAY, CLOCK_K64);
		}




    }
    return 0 ;
}
