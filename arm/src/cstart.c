#define STACK_TOP 0x20000800
#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))
// Declare functions
void myputs(char *string1);
void myputc(char mychar);
int main(void);
void nmi_handler(void);
void hardfault_handler(void);
// Define the vector table
__attribute__ ((section("vectors")))
void (* const VectorArray[])(void) = {
    (void (*)(void)) STACK_TOP,
(void (*)(void)) main,
nmi_handler,
hardfault_handler
};
// Start of main program
int main(void)
{
    const char *helloworld[]={"Hello world\n"};
    *NVIC_CCR = *NVIC_CCR | 0x200; /* Set STKALIGN in NVIC */
    myputs(*helloworld);
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
#define UART0_DATA ((volatile unsigned long *)(0x4000C000))
#define UART0_FLAG ((volatile unsigned long *)(0x4000C018))
// Wait until busy flag is clear
    while ((*UART0_FLAG & 0x20) != 0);
// Output character to UART
    *UART0_DATA = mychar;
    return;
}
//Dummy handlers
void nmi_handler(void)
{
    return;
}
void hardfault_handler(void)
{
    return;
}