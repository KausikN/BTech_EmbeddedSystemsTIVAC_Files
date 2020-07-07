/*
 * Takes inputs from switches and decides what note to output to the buzzer.
 * Port E, bits 3-0 have 4 piano keys.
 * Port F, bits 3-0 have 4 piano keys.
*/

/**
 * Global variable which is accessable from other functions
 * store the index of the corresponding input
 */
extern unsigned short freq_index;

/**
 * Initializes piano key inputs.
 */
void InitPiano(void);

/**
 * Reads the input from PE3-PE0 and PF3-PF0.
 *
 * @notes    Returns to freq_index with values from 0 to 8 depending on key pressed
 *            
 *            0 if key 0 = note C = PE0 is pressed
 *            1 if key 1 = note D = PE1 is pressed
 *            2 if key 2 = note E = PE2 is pressed
 *            3 if key 3 = note F = PE3 is pressed
              4 if key 4 = note G = PF0 is pressed
 *            5 if key 5 = note A = PF1 is pressed
 *            6 if key 6 = note B = PF2 is pressed
 *            7 if key 7 = note CH = PF3 is pressed
 */
void PianoIn(void);
