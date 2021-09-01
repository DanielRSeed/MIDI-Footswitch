#include "EnumSwitchMode.h"
#include "SwitchProcessor.h"
#include "Switch.h"

// our mode select switch. This determines whether we're in latching or momentary mode
Switch *_switchModeSelect = NULL;

// our control switch. This is a switch that we'll use to output MIDI signals with
Switch *_switchControlSwitch = NULL;

void setup()
{
  // set the built in LED pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  // create our switches
  _switchControlSwitch = new Switch(2, INPUT_PULLUP, EnumSwitchMode::Momentary);
  _switchModeSelect = new Switch(7, INPUT_PULLUP, EnumSwitchMode::Latching);
}

void loop()
{
  // find out what switch mode we're in
  EnumSwitchMode enumSwitchMode = _switchModeSelect->GetState();
   
   // set the switch mode for the control switch
  if(enumSwitchMode == EnumSwitchMode::Latching)
  {
    _switchControlSwitch->SetSwitchMode(EnumSwitchMode::Latching);
  }
  else
  {
    _switchControlSwitch->SetSwitchMode(EnumSwitchMode::Momentary);
  }

  // get the switch state now we know what type of switch we're dealing with
  bool bState = _switchControlSwitch->GetState();

  // handle the state
  if (!bState)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
