#include <stdint.h>
#define UART0_DATA ((volatile unsigned long *)(0x4000C000))
#define UART0_FLAG ((volatile unsigned long *)(0x4000C018))
#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

extern uint8_t _sbss;
extern uint8_t _ebss;
volatile uint8_t *data = &_sbss;
volatile uint8_t *data_end = &_ebss;

// Declare functions
void myputs(char *string1);
void myputc(char mychar);
int main(void);

// Define the vector table

// Start of main program
int main(void)
{
    char helloworld[]="Hello world\n";
    char* hello = &helloworld[0];
    *NVIC_CCR = *NVIC_CCR | 0x200; /* Set STKALIGN in NVIC */
    myputs(hello);
    while(1);
    return(0);
}
// Functions
void myputs(char *string1)
{
    char mychar;
    int j;
    j=0;
    do {
        mychar = string1[j];
        if (mychar!=0) {
            myputc(mychar);
            j++;
        }
    } while (mychar != 0);
    return;
}
void myputc(char mychar)
{
// Wait until busy flag is clear
    while ((*UART0_FLAG & 0x20) != 0);
// Output character to UART
    *UART0_DATA = mychar;
    return;
}
