#include <Wire.h>

int32_t ch1_start, ch1_stop, ch1;
// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin PC13 as an output.
    Serial.begin(57600);
    pinMode(PC13, OUTPUT);

    Timer2.attachCompare1Interrupt(handler_ch1);
    TIMER2_BASE->CR1 = TIMER_CR1_CEN;
    TIMER2_BASE->CR2 = 0;
    TIMER2_BASE->SMCR = 0;
    TIMER2_BASE->DIER = TIMER_DIER_CC1IE | TIMER_DIER_CC2IE | TIMER_DIER_CC3IE | TIMER_DIER_CC4IE;
    TIMER2_BASE->EGR = 0;

  TIMER2_BASE->CCMR1 = 0b100000001; //Register is set like this due to a bug in the define table (30-09-2017)
  TIMER2_BASE->CCMR2 = 0b100000001; //Register is set like this due to a bug in the define table (30-09-2017)
  TIMER2_BASE->CCER = TIMER_CCER_CC1E | TIMER_CCER_CC2E | TIMER_CCER_CC3E | TIMER_CCER_CC4E;
  TIMER2_BASE->PSC = 71;
  TIMER2_BASE->ARR = 0xFFFF;
  TIMER2_BASE->DCR = 0;
//    TIMER2_BASE->CCMR1 = TIMER_CCMR1_CC1S_INPUT_TI1;
//    TIMER2_BASE->PSC = 71;
//    TIMER2_BASE->ARR = 0xFFFF; //Setting Auto reload registers
//    TIMER2_BASE->DCR = 0;
  
}

// the loop function runs over and over again forever
void loop() 
{
    Serial.println(ch1);
    delay(50);
}



void handler_ch1(void)
{
    if( 0b1 & GPIOA_BASE->IDR >> 0)
    {
        ch1_start = TIMER2_BASE->CCR1;
        TIMER2_BASE->CCER |= TIMER_CCER_CC1P;
    }
    else
    {
        ch1 = TIMER2_BASE->CCR1 - ch1_start;
        if( ch1 < 0)
            ch1 += 0xFFFF;
        TIMER2_BASE->CCER &= ~TIMER_CCER_CC1P;
    }

}
