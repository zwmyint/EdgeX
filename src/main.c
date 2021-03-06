#include "sysctl.h"
#include "ai_task.h"
#include "lora_task.h"
#include "config.h"
#include "fpioa.h"
#include "gpio_common.h"
#include "console.h"
#include "dmac.h"
#include "gpiohs.h"
#include "stdio.h"
#include "sysctl.h"
#include "spi.h"

#define PLL0_OUTPUT_FREQ 800000000UL
#define PLL1_OUTPUT_FREQ 400000000UL
#define PLL2_OUTPUT_FREQ 45158400UL

int main(void)
{
    /* Set CPU and dvp clk */
    sysctl_pll_set_freq(SYSCTL_PLL0, PLL0_OUTPUT_FREQ);
    sysctl_pll_set_freq(SYSCTL_PLL1, PLL1_OUTPUT_FREQ);
    sysctl_pll_set_freq(SYSCTL_PLL2, PLL2_OUTPUT_FREQ);

    dmac_init();
    plic_init();
    sysctl_enable_irq();
    rtc_init();

    // Needed to enable debugging
    sysctl_set_power_mode(SYSCTL_POWER_BANK0, SYSCTL_POWER_V18);
    sysctl_set_spi0_dvp_data(1);

    console_register();

    /* Start the AI processing on the second core */
    register_core1(ai_task, 0);

    sleep(3);

    /* Execute radio sw */
    //lora_task();

    while(1){
      sleep(1);
    }

    return 0;
}

