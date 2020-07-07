/**
 * Initializes DAC and writes data into a 8-bit DAC.
 * Note that 8-bit DAC connected to PB7-PB0.
 */

/**
 * Initializes 8-bit DAC.
 */
void InitDac(void);

/**
 * Writes output to DAC.
 *
 * @param  data  8-bit data, 0 to 255
 */
void OutDac(unsigned long data);
