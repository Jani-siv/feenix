#include <stdint.h>

extern uint8_t _sbss;
extern uint8_t _ebss;

volatile uint8_t *data = &_sbss;
volatile uint8_t *data_end = &_ebss;


int main() {
    while(data < data_end)
    {
        data = 0x0;
        data++;
    }
    while(1);
    return 0;
}