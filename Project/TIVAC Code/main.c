/*
 * Creates a sinusoid sound wave using 8-bit DAC and simulate C, D, E, F, G, A, B and C(Higher Freq)
 * notes of the piano.
 * Port B, bits 7-0 have the 8-bit DAC.
 * Port E, bits 3-0 have 4 piano keys.
 * Port F, bits 3-0 have 4 piano keys.
 */

/**
 * Required hardware I/O connections
 *
 * PD7 must be connected to DAC output
 * 128*R resistor DAC bit 0 on PB0 (least significant bit)
 * 64*R resistor DAC bit 1 on PB1
 * 32*R resistor DAC bit 2 on PB2
 * 16*R resistor DAC bit 3 on PB3
 * 8*R resistor DAC bit 4 on PB4
 * 4*R resistor DAC bit 5 on PB5
 * 2*R resistor DAC bit 6 on PB6
 * 1*R resistor DAC bit 7 on PB7 (most significant bit)
 * 4 switches connected to PE3-PE0
 * 4 switches connected to PF3-PF0
 */

#include "tm4c123gh6pm.h"
#include "sound.h"
#include "piano.h"
#include "TExaS.h"

// Function prototypes:
void EnableInterrupts(void); // Enable interrupts

int main(void) {
    // Setup
    // for the real board grader to work
    // activate grader and set system clock to 80 MHz
    TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210, ScopeOn);
    InitSound();        // initialize SysTick and DAC
    InitPiano();        // initialize Switches
    EnableInterrupts(); // enable interrupts

    // Loop
    while (1) {
        PianoIn(); // read input from switches

        // if the index is out of range (no switch is pressed)
        if (freq_index == 8) {
            StopSound(); // turn off the sound
        }
        // otherwise
        else {
            // adjust the frequency similarly to C, D, E, F, G, A, B and C(Higher Freq)
            PlaySound(FREQ_SYSTICK_TO_WAVE[freq_index]);
        }
    }
}
