#include "libraries/enums/EnumSwitchMode.h"
#include "libraries/SwitchProcessor/SwitchProcessor.h"
#include "libraries/Switch/Switch.h"

Switch *_switch;
Switch *_switchModeSelect;

void setup()
{
  // set the built in LED pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  _switch = new Switch(2, INPUT_PULLUP, EnumSwitchMode::Momentary);
  _switchModeSelect = new Switch(7, INPUT_PULLUP, EnumSwitchMode::Latching);
}

void loop()
{
  bool bSwitchState = _switchModeSelect->GetState();

  if(bSwitchState == true)
    _switch->SetSwitchMode(EnumSwitchMode::Latching);
  else
    _switch->SetSwitchMode(EnumSwitchMode::Momentary);

  bool bState = _switch->GetState();

  if (!bState)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}
