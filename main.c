#include <msp430g2231.h>

// CLK P1.0
// SER A P1.1

// index+1 of array digitx denotes whether led i will be on or off for the digitx
const char digit0[] = {1, 1, 1, 1, 1, 1, 0, 0};
const char digit1[] = {0, 1, 1, 0, 0, 0, 0, 0};
const char digit2[] = {1, 1, 0, 1, 1, 0, 1, 0};
const char digit3[] = {1, 1, 1, 1, 0, 0, 1, 0};
const char digit4[] = {0, 1, 1, 0, 0, 1, 1, 0};
const char digit5[] = {1, 0, 1, 1, 0, 1, 1, 0};
const char digit6[] = {1, 0, 1, 1, 1, 1, 1, 0};
const char digit7[] = {1, 1, 1, 0, 0, 0, 0, 0};
const char digit8[] = {1, 1, 1, 1, 1, 1, 1, 0};
const char digit9[] = {1, 1, 1, 1, 0, 1, 1, 0};

const char* digits[10];

char secondsUnitsDigitIndex = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watch dog timer
	
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P2OUT = 0;
    P2DIR = 0;

    P1OUT = 0;  // setting all gpio to zero initially
    P1DIR |= (BIT0 + BIT1); //  P1.0 - P1.5 are outputs, P1.6 and P1.7 are not being used

    digits[0] = digit0;
    digits[1] = digit1;
    digits[2] = digit2;
    digits[3] = digit3;
    digits[4] = digit4;
    digits[5] = digit5;
    digits[6] = digit6;
    digits[7] = digit7;
    digits[8] = digit8;
    digits[9] = digit9;

    signed char led;
    while(1) {
        for (led = 7; led >= 0; led--) {
            P1OUT = digits[secondsUnitsDigitIndex][led]*2;
            _delay_cycles(0.025);   // time delay between ser change and srclk high = 25ns
            P1OUT |= BIT0;  // clk high
            _delay_cycles(0.025);   // pulse duration for srclk high = 25ns
            P1OUT &= ~(BIT0);   // clk low
        }

        _delay_cycles(1000000);

        if (secondsUnitsDigitIndex==9) {
            secondsUnitsDigitIndex = 0;
        } else {
            secondsUnitsDigitIndex++;
        }
    }
}
