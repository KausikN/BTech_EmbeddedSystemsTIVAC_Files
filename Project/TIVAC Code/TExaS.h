// TExaS.h

enum InputPorts{
  SW_PIN_PA5432 = 0,
  SW_PIN_PB3210 = 1,
  SW_PIN_PE3210 = 4
};

enum OutputPorts{
  DAC_PIN_PA5432 = 0, // optionally, you can use PA7-2, but the top two bits are not graded
  DAC_PIN_PB3210 = 1, // optionally, you can use PB5-0, but the top two bits are not graded
  DAC_PIN_PE3210 = 4  // optionally, you can use PE5-0, but the top two bits are not graded
};

enum ScopeModes{
  ScopeOff = 0,   // no scope needed
  ScopeOn = 1     // turn on UART0 and stream analog data from PD3 to TExaSdisplay
};
// TExaS_Init
void TExaS_Init(enum InputPorts iport, enum OutputPorts oport, enum ScopeModes scope);

// TExaS_Stop
void TExaS_Stop(void);
