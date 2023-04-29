#include "config.h"
#include "input.h"

uint16_t inputData = 0;

void inputUpdate(void)
{
    uint16_t status = 0;

    GPIO_ResetBits(SR_GPIO, SR_LOAD_PIN);
    GPIO_SetBits(SR_GPIO, SR_LOAD_PIN);

    for (uint8_t i = 0; i < 16; i++)
    {
        if (GPIO_ReadInputDataBit(SR_GPIO, SR_DATA_PIN))
            status |= (0x8000 >> i);

        GPIO_SetBits(SR_GPIO, SR_CLK_PIN);
        GPIO_ResetBits(SR_GPIO, SR_CLK_PIN);
    }

    inputData = config.invert ? status >> 8 | status << 8 : ~(status >> 8 | status << 8);
}
