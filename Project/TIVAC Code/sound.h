// convert from the frequency of the SysTick
// to the frequency of the sound wave
// has 8 elements representing the most suitable value
// f_sound = f_SysTick / 16
extern const unsigned long Frequency_Period[8];

/**
 * Initializes Systick periodic interrupts and DAC.
 */
void InitSound(void);

/**
 * Changes SysTick periodic interrupts to start sound output.
 *
 * @param  period  interrupt period
 *                 1 unit of period = 12.5 ns
 *                 maximum is 2^24 - 1
 *                 minimum is determined by the length of ISR
 */
void PlaySound(unsigned long period);

/**
 * Stops outputing to DAC.
 */
void StopSound(void);
