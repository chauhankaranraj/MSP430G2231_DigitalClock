#include <msp430g2231.h>

//#define SRCLK P1.0
//#define SER1 P1.1
//#define SER2 P1.2
//#define SER3 P1.3
//#define SER4 P1.4
//#define RCLK P1.5

// Led 1-7 of seven segment display correspond to outputs A-G of bit shift register

//void updateSecondsUnitsDisplay() {}
//
//void updateSecondsTensDisplay(){}
//
//void updateMintuesUnitsDisplay(){}
//
//void updateMintuesTensDisplay(){}

int main(void) {
    // TODO: update watch dog timer to make clock display go back to 0000 when the day is over
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1OUT = 0;
    P1DIR = 1 + 2 + 4 + 8 + 16 + 32; //  P1.0 - P1.5 are outputs, P1.6 and P1.7 are not being used

    const char digit0[] = {BIT1, BIT1, BIT1, BIT1, BIT1, BIT1, BIT0};
    const char digit1[] = {BIT0, BIT1, BIT1, BIT0, BIT0, BIT0, BIT0};
    const char digit2[] = {BIT1, BIT1, BIT0, BIT1, BIT1, BIT0, BIT1};
    const char digit3[] = {BIT1, BIT1, BIT1, BIT1, BIT0, BIT0, BIT1};
    const char digit4[] = {BIT0, BIT1, BIT1, BIT0, BIT0, BIT1, BIT1};
    const char digit5[] = {BIT1, BIT0, BIT1, BIT1, BIT0, BIT1, BIT1};
    const char digit6[] = {BIT1, BIT0, BIT1, BIT1, BIT1, BIT1, BIT1};
    const char digit7[] = {BIT1, BIT1, BIT1, BIT0, BIT0, BIT0, BIT0};
    const char digit8[] = {BIT1, BIT1, BIT1, BIT1, BIT1, BIT1, BIT1};
    const char digit9[] = {BIT1, BIT1, BIT1, BIT1, BIT0, BIT1, BIT1};

    const char* digits[10];
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

    char secondsUnitsDigitIndex = 0;
    char secondsTensDigitIndex = 0;
    char minutesUnitsDigitIndex = 0;
    char minutesTensDigitIndex = 0;

    while(1) {
        // wait for timer for completion of one minute

        // update seconds units display
        signed char led;
        for (led = 6; led >= 0; led--) {
            P1OUT |= digits[secondsUnitsDigitIndex][led];   // set ser1 to the current bit for the current digit
            _delay_cycles(1);   // time delay between ser1 change and srclk high
            P1OUT |= BIT0;  // srclk high
            _delay_cycles(1);   // pulse duration for srclk high
            P1OUT &= ~(BIT0);   // srclk low
        }
        _delay_cycles(1);   // time delay between srclk pulse and rclk high
        P1OUT |= BIT5;
        _delay_cycles(1);
        P1OUT &= ~(BIT5);

        //TODO: put this line of code at the end
        secondsUnitsDigitIndex++;


        // TODO: when srclkis high the first regs=ister will read data as well, even though only the second register should be reading




        // update seconds tens display
        if (secondsUnitsDigitIndex == 10) {
            secondsUnitsDigitIndex = 0;
            P1OUT |= digits[secondsTensDigitIndex][led];   // set ser1 to the current bit for the current digit
            _delay_cycles(1);   // time delay between ser1 change and srclk high
            P1OUT |= BIT0;  // srclk high
            _delay_cycles(1);   // pulse duration for srclk high
            P1OUT &= ~(BIT0);   // srclk low
        }

    }
}
