#include "config.h"
#include "input.h"
#include "modbus.h"

static uint8_t rxData[MODBUS_MAX_LENGTH], rxLength = 0, rxFlag = 0;

int main(void)
{
    configInit();
    boardInit();

    while (1)
    {
        inputUpdate();

        if (rxFlag)
        {
            modbusHandler(rxData, rxLength);
            rxLength = 0;
            rxFlag = 0;
        }

        if (configFlag)
        {
            configWrite();
            boardInitUART();
            configFlag = 0;
        }
    }
}

void UART_TIMER_HANDLER(void)
{
    if (TIM_GetITStatus(UART_TIMER, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(UART_TIMER, TIM_IT_Update);
        TIM_ITConfig(UART_TIMER, TIM_IT_Update, DISABLE);
        rxFlag = 1;
    }
}

void UART_HANDLER(void)
{
    if (USART_GetITStatus(UART_PORT, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(UART_PORT, USART_IT_RXNE);
        rxData[rxLength++] = (uint8_t) USART_ReceiveData(UART_PORT);

        TIM_SetCounter(UART_TIMER, 0);
        TIM_ClearFlag(UART_TIMER, TIM_FLAG_Update);
        TIM_ITConfig(UART_TIMER, TIM_IT_Update, ENABLE);
    }
}

void TICK_HANDLER(void)
{
    static uint32_t tick = 0;
    static uint8_t led = 1;

    if (!(tick % 500))
    {
        GPIO_WriteBit(LED_GPIO, LED_PIN, led);
        led ^= 1;
    }

    if (!(tick % 1000))
        uptime++;

    tick++;
}
