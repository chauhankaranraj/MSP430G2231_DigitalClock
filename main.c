#include <msp430g2231.h>

// SRCLK P1.0
// SER1 P1.1
// SER2 P1.2
// SER3 P1.3
// SER4 P1.4

// Led 1-7 of seven segment display correspond to outputs A-G of bit shift register

int main(void){

    // TODO: update watch dog timer to make clock display go back to 0000 when the day is over
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P2OUT = 0;
    P2DIR = 0;

    P1OUT = 0;  // setting all gpio to zero initially
    P1DIR = 1 + 2 + 4 + 8 + 16 + 32; //  P1.0 - P1.5 are outputs, P1.6 and P1.7 are not being used

    while(1) {
        P1OUT = 1+2;
    }
}
