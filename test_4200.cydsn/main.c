#include "project.h"

int main(void)
{
    CyGlobalIntEnable;

    UART_Start();
    UART_PutString("Test\r\n");
    
    Nokia5110_start();
    Nokia5110_setPixel(10, 10);
    Nokia5110_setPixel(20, 20);
    Nokia5110_setPixel(30, 30);
    Nokia5110_setPixel(15, 15);
    Nokia5110_updateDisplay();
    CyDelay(1000);
    Nokia5110_clearPixel(15, 15);
    Nokia5110_updateDisplay();
    
    while(1) {
    }

}

/* [] END OF FILE */
